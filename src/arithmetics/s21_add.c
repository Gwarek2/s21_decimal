#include "uint96.h"
#include "uint192.h"

/*****************************************************************************
 * Adition with degree and sign
 * returns an error if the write is not possible to the format s21_decimal
 ******************************************************************************/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    init_default(result);
    int other_scale =
        get_scale(value_1) - get_scale(value_2);
    s21_decimal res = {{0}};
    s21_decimal overflow = {0};
    uint192 result_192 = {0};
    int sign_value_1 = get_sign(value_1);
    int sign_value_2 = get_sign(value_2);
    uint192 value_1_192 = {0};
    uint192 value_2_192 = {0};

    equalize_scales(&value_1, &value_2, &overflow);
    convert_to_uint192(
        other_scale < 0 ? overflow : DEC_ZERO, value_1, &value_1_192);
    convert_to_uint192(
        other_scale < 0 ? DEC_ZERO : overflow, value_2, &value_2_192);

    if (sign_value_1 && sign_value_2) {
        add_uint192(value_1_192, value_2_192, &result_192);
        set_sign(&res, 1);
    } else if (sign_value_1 && !sign_value_2) {
        if (gt_uint192(value_1_192, value_2_192)) {
            sub_uint192(value_1_192, value_2_192, &result_192);
            set_sign(&res, 1);
        } else {
            sub_uint192(value_2_192, value_1_192, &result_192);
            set_sign(&res, 0);
        }
    } else if (!sign_value_1 && sign_value_2) {
        if (gt_uint192(value_1_192, value_2_192) ||
            eq_uint192(value_1_192, value_2_192)) {
            sub_uint192(value_1_192, value_2_192, &result_192);
            set_sign(&res, 0);
        } else {
            sub_uint192(value_2_192, value_1_192, &result_192);
            set_sign(&res, 1);
        }
    } else if (!sign_value_1 && !sign_value_2) {
        add_uint192(value_1_192, value_2_192, &result_192);
        set_sign(&res, 0);
    }

    int scale = get_scale(value_1);
    int status = 0;

    int err = round_result(result_192, &res, &scale);
    if (err) {
        status = get_sign(res) ? DEC_SMALL : DEC_HUGE;
        *result = DEC_ZERO;
    } else {
        *result = res;
        set_scale(result, scale);
    }
    return status;
}
