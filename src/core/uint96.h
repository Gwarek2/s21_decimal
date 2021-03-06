#ifndef _CORE_UINT_96_H
#define _CORE_UINT_96_H

#include <limits.h>
#include "structs.h"

#define MASK_32 0xFFFFFFFFl
#define SCALE_SHIFT 16
#define SIGN_SHIFT 31

enum comparison_result {
    LT = -1,
    EQ = 0,
    GT = 1,
};

static const s21_decimal DEC_ZERO = {{0, 0, 0, 0}};
static const s21_decimal DEC_ONE = {{1, 0, 0, 0}};
static const s21_decimal DEC_FIVE = {{5, 0, 0, 0}};
static const s21_decimal DEC_TEN = {{10, 0, 0, 0}};
static const s21_decimal DEC_MAX = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
static const s21_decimal DEC_INT_MAX = {{INT_MAX, 0, 0, 0}};
static const s21_decimal DEC_INT_MIN = {{INT_MIN, 0, 0, 1}};
static const unsigned int max32bit = 4294967295;
static const unsigned int maxScale = 1835008;

static const s21_decimal ten_power[29] = {
    {{ 0x1, 0, 0}},
    {{ 0xA, 0, 0}},
    {{ 0x64, 0, 0}},
    {{ 0x3E8, 0, 0}},
    {{ 0x2710, 0, 0}},
    {{ 0x186A0, 0, 0}},
    {{ 0xF4240, 0, 0}},
    {{ 0x989680, 0, 0}},
    {{ 0x5F5E100, 0, 0}},
    {{ 0x3B9ACA00, 0, 0}},
    {{ 0x540BE400, 0x2, 0}},
    {{ 0x4876E800, 0x17, 0}},
    {{ 0xD4A51000, 0xe8, 0}},
    {{ 0x4E72A000, 0x918, 0}},
    {{ 0x107A4000, 0x5AF3, 0}},
    {{ 0xA4C68000, 0x38D7E, 0}},
    {{ 0x6FC10000, 0x2386F2, 0}},
    {{ 0x5D8A0000, 0x1634578, 0}},
    {{ 0xA7640000, 0xDE0B6B3, 0}},
    {{ 0x89E80000, 0x8AC72304, 0}},
    {{ 0x63100000, 0x6BC75E2D, 0x5}},
    {{ 0xDEA00000, 0x35C9ADC5, 0x36}},
    {{ 0xB2400000, 0x19E0C9BA, 0x21E}},
    {{ 0xF6800000, 0x02C7E14A, 0x152D}},
    {{ 0xA1000000, 0x1BCECCED, 0xD3C2}},
    {{ 0x4A000000, 0x16140148, 0x84595}},
    {{ 0xE4000000, 0xDCC80CD2, 0x52B7D2}},
    {{ 0xE8000000, 0x9FD0803C, 0x33B2E3C}},
    {{ 0x10000000, 0x3E250261, 0x204FCE5E}},
};

int init_value(s21_decimal *value, const unsigned mantiss[3], bool negative, unsigned scale);
void init_default(s21_decimal *value);
void copy_full(s21_decimal *dest, const s21_decimal *src);
void copy_mantiss(s21_decimal *dest, const s21_decimal *src);
unsigned init_sign_and_scale(int sign, int scale);
int get_atr(s21_decimal src, int *exp);
unsigned get_scale(s21_decimal value);
int set_scale(s21_decimal *value, int scale);
bool get_sign(s21_decimal value);
void set_sign(s21_decimal *value, bool negative);

int get_bit(s21_decimal value, int n);
void set_bit(s21_decimal *value, int n, int bit);
int left_shift(const s21_decimal *value, s21_decimal *result, size_t shift);
int right_shift(s21_decimal *src);
uint32_t last_bit(s21_decimal value);

int cmp(const s21_decimal value1, const s21_decimal value2);
int eq(const s21_decimal value1, const s21_decimal value2);
int lt(const s21_decimal value1, const s21_decimal value2);
int gt(const s21_decimal value1, const s21_decimal value2);
bool is_zero(const s21_decimal value);

int base_addition(s21_decimal value1, s21_decimal value2, s21_decimal *result);
void base_subtraction(s21_decimal value1, s21_decimal value2, s21_decimal *result);
int base_multiply(s21_decimal value1, s21_decimal value2, s21_decimal *result, s21_decimal *overflow);
void base_divide(s21_decimal value1, s21_decimal value2, s21_decimal *result, s21_decimal *remainder);

void remove_trailing_zeros(s21_decimal value, s21_decimal *result);
int equalize_scales(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *overflow);

#endif  // _CORE_UINT_96_H
