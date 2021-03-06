#ifndef _TEST_MAIN_H

#define _TEST_MAIN_H

#include <check.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "output.h"
#include "s21_decimal.h"
#include "time.h"
#include "uint96.h"
#include "uint192.h"

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

static const unsigned b_zero[3] = {0};

#define ASSERT_DECIMAL_EQ for (size_t i = 0; i < 4; i++) { \
                              ck_assert_msg(result.bits[i] == expected.bits[i], \
                                            "[%zu] %#x != %#x", i, result.bits[i], expected.bits[i]); \
                          }

#define ASSERT_UINT192_EQ for (size_t i = 0; i < 6; i++) { \
                              ck_assert_msg(result.bits[i] == expected.bits[i], \
                                            "[%zu] %#x != %#x", i, result.bits[i], expected.bits[i]); \
                          }

// Core
Suite *eq_suite();
Suite *lt_suite();
Suite *base_addition_suite();
Suite *base_subtraction_suite();
Suite *base_multiply_suite();
Suite *base_divide_suite();
Suite *remove_trailing_zeros_suite();
Suite *equalize_scales_suite();
Suite *uint192_add_suite();
Suite *uint192_division_suite();
Suite *uint192_mul_suite();

// Arithmetics
Suite *s21_mul_suite();
Suite *s21_div_suite();
Suite *s21_negate_suite();
Suite *s21_add_suite();
Suite *s21_sub_suite();
Suite *s21_mod_suite();

// Conversion
Suite *s21_from_int_to_decimal_suite();
Suite *s21_from_decimal_to_int_suite();
Suite *s21_float_decimal_float_suite();

// Compare
Suite *s21_compare_suite();

// Rounding
Suite *s21_floor_suite();
Suite *s21_round_suite();
Suite *s21_truncate_suite();

#endif  // _TEST_MAIN_H
