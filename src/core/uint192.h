/****************************************************
 * Uint192 type is implemented for handling overflows
 * in arithmetic operations with s21_decimal type
*****************************************************/

#ifndef _CORE_UINT192_H
#define _CORE_UINT192_H

#include "structs.h"

static const uint192 UINT192_ZERO = {{0}};
static const uint192 UINT192_ONE = {{1}};
static const uint192 UINT192_FIVE = {{5}};
static const uint192 UINT192_TEN = {{10}};
static const uint192 UINT192_DEC_MAX = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};

void copy_uint192(uint192 *buffer, const uint192 value);
void convert_to_uint192(s21_decimal higher, s21_decimal lower, uint192 *result);
int convert_to_decimal(uint192 value, s21_decimal *buffer);
void left_shift_uint192(const uint192 value, size_t n, uint192 *result);
void sub_uint192(uint192 value1, uint192 value2, uint192 *result);
int add_uint192(uint192 value1, uint192 value2, uint192 *result);
bool mul_uint192(uint192 value1, uint192 value2, uint192 *result);
void divide_uint192(uint192 value1, uint192 value2, uint192 *result, uint192 *remainder);
bool eq_uint192(uint192 value1, uint192 value2);
bool lt_uint192(uint192 value1, uint192 value2);
bool gt_uint192(uint192 value1, uint192 value2);
void print_hex_uint192(uint192 value);
void bank_rounding_uint192(uint192 value, uint192 *result);
int round_result(uint192 value, s21_decimal *result, int *scale);

#endif  // _CORE_UINT192_H
