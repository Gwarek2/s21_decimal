#include "test_main.h"

START_TEST(test_32_bits_1) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {3, 0, 0};
    unsigned v2[3] = {1, 0, 0};
    unsigned v3[3] = {0, 0, 0};
    unsigned v4[3] = {4, 0, 0};
    init_value(&n1, v1, 0, 0);
    init_value(&n2, v2, 0, 0);
    init_value(&result, v3, 0, 0);
    init_value(&expected, v4, 0, 0);
    int overflow = bit_addition(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_int_eq(overflow, 0);
} END_TEST

START_TEST(test_32_bits_2) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {0xffff23a3, 0, 0};
    unsigned v2[3] = {0x3ef23f, 0, 0};
    unsigned v3[3] = {0, 0, 0};
    unsigned v4[3] = {0x003e15e2, 1, 0};
    init_value(&n1, v1, 0, 0);
    init_value(&n2, v2, 0, 0);
    init_value(&result, v3, 0, 0);
    init_value(&expected, v4, 0, 0);
    int overflow = bit_addition(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_int_eq(overflow, 0);
} END_TEST

START_TEST(test_64_bits_1) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {UINT_MAX, 0, 0};
    unsigned v2[3] = {1, 0, 0};
    unsigned v3[3] = {0, 0, 0};
    unsigned v4[3] = {0, 1, 0};
    init_value(&n1, v1, 0, 0);
    init_value(&n2, v2, 0, 0);
    init_value(&result, v3, 0, 0);
    init_value(&expected, v4, 0, 0);
    int overflow = bit_addition(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_int_eq(overflow, 0);
} END_TEST

START_TEST(test_64_bits_2) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {0x003e15e2, 0x1, 0};
    unsigned v2[3] = {0x12345678, 0xffffffff, 0};
    unsigned v3[3] = {0, 0, 0};
    unsigned v4[3] = {0x12726C5A, 0, 0x1};
    init_value(&n1, v1, 0, 0);
    init_value(&n2, v2, 0, 0);
    init_value(&result, v3, 0, 0);
    init_value(&expected, v4, 0, 0);
    int overflow = bit_addition(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_int_eq(overflow, 0);
} END_TEST

START_TEST(test_64_bits_3) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {UINT_MAX, 0, 0};
    unsigned v2[3] = {UINT_MAX, 0, 0};
    unsigned v3[3] = {0, 0, 0};
    unsigned v4[3] = {UINT_MAX - 1, 1, 0};
    init_value(&n1, v1, 0, 0);
    init_value(&n2, v2, 0, 0);
    init_value(&result, v3, 0, 0);
    init_value(&expected, v4, 0, 0);
    int overflow = bit_addition(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_int_eq(overflow, 0);
} END_TEST

START_TEST(test_96_bits_1) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {UINT_MAX, UINT_MAX, 0};
    unsigned v2[3] = {UINT_MAX, UINT_MAX, 0};
    unsigned v3[3] = {0, 0, 0};
    unsigned v4[3] = {UINT_MAX - 1, UINT_MAX, 1};
    init_value(&n1, v1, 0, 0);
    init_value(&n2, v2, 0, 0);
    init_value(&result, v3, 0, 0);
    init_value(&expected, v4, 0, 0);
    int overflow = bit_addition(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_int_eq(overflow, 0);
} END_TEST

START_TEST(test_96_bits_overflow) {
    s21_decimal n1, n2, result, expected;
    unsigned v1[3] = {UINT_MAX, UINT_MAX, UINT_MAX};
    unsigned v2[3] = {UINT_MAX, UINT_MAX, UINT_MAX};
    unsigned v3[3] = {0, 0, 0};
    unsigned v4[3] = {UINT_MAX - 1, UINT_MAX, UINT_MAX};
    init_value(&n1, v1, 0, 0);
    init_value(&n2, v2, 0, 0);
    init_value(&result, v3, 0, 0);
    init_value(&expected, v4, 0, 0);
    int overflow = bit_addition(n1, n2, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
    ck_assert_int_eq(overflow, 1);
} END_TEST

Suite *bit_addition_suite(void) {
    Suite *s = suite_create("suite_bit_addition");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_32_bits_1);
    tcase_add_test(tc, test_32_bits_2);
    tcase_add_test(tc, test_64_bits_1);
    tcase_add_test(tc, test_64_bits_2);
    tcase_add_test(tc, test_64_bits_3);
    tcase_add_test(tc, test_96_bits_1);
    tcase_add_test(tc, test_96_bits_overflow);

    suite_add_tcase(s, tc);
    return s;
}
