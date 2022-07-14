#include <string.h>

#include "common.h"
#include "binary_level.h"
#include "decimal_level.h"

unsigned get_scale(s21_decimal value) {
    unsigned scale = (value.bits_u32_t[3] >> SCALE_SHIFT) & 0xff;
    return scale;
}

int set_scale(s21_decimal *value, int scale) {
    unsigned error = scale < 0 || scale > 28;
    if (!error) value->bits_u32_t[3] = (get_sign(*value) << SIGN_SHIFT) | (scale << SCALE_SHIFT);
    return error;
}

bool get_sign(s21_decimal value) {
    return value.bits_u32_t[3] >> SIGN_SHIFT;
}

void set_sign(s21_decimal *value, bool negative) {
    value->bits_u32_t[3] = (negative << SIGN_SHIFT) | (get_scale(*value) << SCALE_SHIFT);
}

/**
 * Addition of two decimals
 * Ignores scale and sign
 * Returns nonzero value if overflow occurs
**/
int base_addition(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
    uint32_t carrial = 0;
    for (size_t i = 0; i < 3; i++) {
        uint64_t r = (uint64_t) value1.bits_u32_t[i] +
                     (uint64_t) value2.bits_u32_t[i] +
                     carrial;
        carrial = r >> 32;
        result->bits_u32_t[i] = r;
    }
    return carrial;
}

/**
 * Subtracts value2 from value1
 * Ignores scale and sign
 * Does not work correctly if base of value1 less than base of value2
**/
void base_subtraction(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
    uint32_t borrow = 0;
    for (size_t i = 0; i < 3; i++) {
        uint64_t r = (uint64_t) value1.bits_u32_t[i] -
                     (uint64_t) value2.bits_u32_t[i] -
                     borrow;
        borrow = value1.bits_u32_t[i] < value2.bits_u32_t[i];
        result->bits_u32_t[i] = r & MASK_32;
    }
}

/*********************************
 * Helper for base_multiplication
 * Adds carrials to overflow value
**********************************/
void add_carrials(s21_decimal *overflow, uint32_t mul_carrial, uint32_t add_carrial, int index) {
    s21_decimal dec_mul_carrial, dec_add_carrial;
    uint32_t mantiss_mul_carrial[3] = {0};
    uint32_t mantiss_add_carrial[3] = {0};
    mantiss_mul_carrial[index] = mul_carrial;
    mantiss_add_carrial[index] = add_carrial;
    init_value(&dec_mul_carrial, mantiss_mul_carrial, 0, 0);
    init_value(&dec_add_carrial, mantiss_add_carrial, 0, 0);
    base_addition(*overflow, dec_mul_carrial, overflow);
    base_addition(*overflow, dec_add_carrial, overflow);
}

/**********************************************************************************
 * Multiplication of two decimals.
 * Uses simple column multiplication algorithm.
 * Ignores scale and sign.
 * Returns nonzero value if overflow occurs.
 **********************************************************************************
 * s21_decimal *result:
 *     result of multiplication
 * s21_decimal *overflow:
 *     overflow of *result;
 *     *result and *overflow mantisses could be imagined as a single 192-bit integer,
 *     where *overflow contains higher bit fields and *result - lower bit fields
**********************************************************************************/
int base_multiply(s21_decimal value1, s21_decimal value2,
                  s21_decimal *result, s21_decimal *overflow) {
    int is_overflow = 0;
    init_default(overflow);
    init_default(result);
    for (size_t i = 0; i < 3; i++) {
        uint32_t mul_carrial = 0;
        uint32_t add_carrial = 0;
        size_t overflow_index = 0;
        for (size_t j = 0; j < 3; j++) {
            uint64_t r = (uint64_t) value1.bits[i] *
                         (uint64_t) value2.bits[j] +
                                         mul_carrial +
                                         add_carrial;
            mul_carrial = r >> 32;
            if (j + i < 3) {
                r = (r & MASK_32) + result->bits[j + i];
                add_carrial = r >> 32;
                result->bits_u32_t[i + j] = r & MASK_32;
            } else {
                r = (r & MASK_32) + overflow->bits[overflow_index];
                is_overflow |= r != 0;
                add_carrial = r >> 32;
                overflow->bits[overflow_index] = r & MASK_32;
                overflow_index++;
            }
        }
        add_carrials(overflow, mul_carrial, add_carrial, i);
    }
    return is_overflow;
}

bool is_zero(s21_decimal value) {
    return bits_eq(value, DEC_ZERO);
}

bool is_one(s21_decimal value) {
    return bits_eq(value, DEC_ONE);
}

/**
 * Divides value1 by value2
 * Ignores sign and scale
 * Writes result of division in *result
 * Writes remainder of division in *remainder
**/
int base_divide(s21_decimal value1, s21_decimal value2,
                    s21_decimal *result, s21_decimal *remainder) {
    if (is_zero(value2)) return DEC_DIV_BY_ZERO;
    init_default(result);
    init_default(remainder);
    if (is_zero(value1)) return DEC_OK;
    if (is_one(value2)) {
        copy_full(result, &value1);
        return DEC_OK;
    }
    copy_mantiss(remainder, &value1);
    for (int32_t i = last_bit(*remainder) - last_bit(value2); i >= 0; i--) {
        s21_decimal tmp1, tmp2;
        left_shift(&value2, &tmp1, i);
        if ((bits_lt(tmp1, *remainder) || bits_eq(tmp1, *remainder)) && !is_zero(tmp1)) {
            base_subtraction(*remainder, tmp1, remainder);
            left_shift(&DEC_ONE, &tmp2, i);
            base_addition(*result, tmp2, result);
        }
    }

    return DEC_OK;
}

/**
 * Removes trailing zeroes from fractional part of decimal
**/
void remove_trailing_zeros(s21_decimal value, s21_decimal *result) {
    unsigned scale = get_scale(value);
    while (true) {
        s21_decimal res_tmp, rem_tmp;
        base_divide(value, DEC_TEN, &res_tmp, &rem_tmp);
        if (!is_zero(rem_tmp) || !scale) break;
        copy_mantiss(&value, &res_tmp);
        set_scale(&value, --scale);
    }
    copy_full(result, &value);
}

/*****************************************************************************
 * Removes one digit from beginning and implements bank rounding
 * Scale and sign remain unchanged
 * if removed digit < 5 - result remains unchanged
 * if removed digit > 5 - result increments by one
 * if removed digit == 5 and rightmost digit is odd
 *     result increments by one
 * if removed digit == 5 and rightmost digit is even (including zero)
 *     result remains unchanged
 * About bank rounding - https://rounding.to/understanding-the-bankers-rounding
******************************************************************************/
void base_bank_rounding(s21_decimal value, s21_decimal *result) {
    s21_decimal last_digit;
    base_divide(value, DEC_TEN, result, &last_digit);
    if (bits_gt(last_digit, DEC_FIVE) || (bits_eq(last_digit, DEC_FIVE) && get_bit(*result, 0) != 0)) {
        base_addition(*result, DEC_ONE, result);
    }
}

