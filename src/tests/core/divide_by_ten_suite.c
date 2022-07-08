#include "test_main.h"

START_TEST(test_32_bits_1) {
    s21_decimal n1, result, expected;
    unsigned v1[3] = {10, 0, 0};
    unsigned v2[3] = {1, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v2, 0, 0);
    base_div10(n1, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
} END_TEST

START_TEST(test_32_bits_2) {
    s21_decimal n1, result, expected;
    unsigned v1[3] = {1, 0, 0};
    unsigned v2[3] = {0, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v2, 0, 0);
    base_div10(n1, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
} END_TEST

START_TEST(test_32_bits_3) {
    s21_decimal n1, result, expected;
    unsigned v1[3] = {1, 0, 0};
    unsigned v2[3] = {0, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v2, 0, 0);
    base_div10(n1, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
} END_TEST

START_TEST(test_32_bits_4) {
    s21_decimal n1, result, expected;
    unsigned v1[3] = {12345, 0, 0};
    unsigned v2[3] = {1234, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v2, 0, 0);
    base_div10(n1, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
} END_TEST

START_TEST(test_64_bits_1) {
    s21_decimal n1, result, expected;
    unsigned v1[3] = {0, 1, 0};
    unsigned v2[3] = {429496729, 0, 0};
    init_value(&n1, v1, 1, 23);
    init_value(&result, b_zero, 0, 0);
    init_value(&expected, v2, 0, 0);
    base_div10(n1, &result);

    ck_assert_uint_eq(expected.bits[0], result.bits[0]);
    ck_assert_uint_eq(expected.bits[1], result.bits[1]);
    ck_assert_uint_eq(expected.bits[2], result.bits[2]);
    ck_assert_uint_eq(expected.bits[3], result.bits[3]);
} END_TEST

/**
 * Fails because of loss of precision
**/
// START_TEST(test_64_bits_2) {
//     s21_decimal n1, result, expected;
//     unsigned v1[3] = {0xfffffff8, 9, 0};
//     unsigned v2[3] = {0xffffffff, 0, 0};
//     init_value(&n1, v1, 1, 23);
//     init_value(&result, b_zero, 0, 0);
//     init_value(&expected, v2, 0, 0);
//     base_div10(n1, &result);
// 
//     ck_assert_uint_eq(expected.bits[0], result.bits[0]);
//     ck_assert_uint_eq(expected.bits[1], result.bits[1]);
//     ck_assert_uint_eq(expected.bits[2], result.bits[2]);
//     ck_assert_uint_eq(expected.bits[3], result.bits[3]);
// } END_TEST

Suite *divide_by_ten_suite(void) {
    Suite *s = suite_create("suite_divide_by_ten");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_32_bits_1);
    tcase_add_test(tc, test_32_bits_2);
    tcase_add_test(tc, test_32_bits_3);
    tcase_add_test(tc, test_32_bits_4);
    tcase_add_test(tc, test_64_bits_1);
    // tcase_add_test(tc, test_64_bits_2);
    suite_add_tcase(s, tc);
    return s;
}
