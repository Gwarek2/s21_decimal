#include "test_main.h"

START_TEST(test_zero) {
    s21_decimal input = {{0, 0, 0, init_sign_and_scale(0, 15)}};
    s21_decimal expected = {{0}};
    s21_decimal result;
    s21_round(input, &result);
    ASSERT_DECIMAL_EQ
}
END_TEST

START_TEST(test_32_bit_1) {
    s21_decimal input = {{362732873, 0, 0, init_sign_and_scale(1, 0)}};
    s21_decimal expected = {{362732873, 0, 0, init_sign_and_scale(1, 0)}};
    s21_decimal result;
    s21_round(input, &result);
    ASSERT_DECIMAL_EQ
}
END_TEST

// -4.5 => -5
START_TEST(test_32_bit_2) {
    s21_decimal input = {{45, 0, 0, init_sign_and_scale(0, 1)}};
    s21_decimal expected = {{5, 0, 0, 0}};
    s21_decimal result;
    s21_round(input, &result);
    ASSERT_DECIMAL_EQ
}
END_TEST

// -438732872.43743877 =>-438732872
START_TEST(test_64_bit_1) {
    s21_decimal input = {{0xb54ac285, 0x9bde85, 0, init_sign_and_scale(1, 8)}};
    s21_decimal expected = {{0x1a268848, 0, 0, init_sign_and_scale(1, 0)}};
    s21_decimal result;
    s21_round(input, &result);
    ASSERT_DECIMAL_EQ
}
END_TEST

// 8684958394.00000000 => 8684958394
START_TEST(test_64_bit_2) {
    s21_decimal input = {{0x4C577A00, 0xC0D845D, 0, init_sign_and_scale(0, 8)}};
    s21_decimal expected = {{0x5A9F2BA, 0x2, 0, init_sign_and_scale(0, 0)}};
    s21_decimal result;
    s21_round(input, &result);
    ASSERT_DECIMAL_EQ
}
END_TEST

// -7.9228162514264337593543950335 => -8
START_TEST(test_96_bits_1) {
    s21_decimal input = {
        {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, init_sign_and_scale(1, 28)}};
    s21_decimal expected = {{8, 0, 0, init_sign_and_scale(1, 0)}};
    s21_decimal result;
    s21_round(input, &result);
    ASSERT_DECIMAL_EQ
}
END_TEST

Suite *s21_round_suite() {
    Suite *s = suite_create("suite_s21_round");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_zero);
    tcase_add_test(tc, test_32_bit_1);
    tcase_add_test(tc, test_32_bit_2);
    tcase_add_test(tc, test_64_bit_1);
    tcase_add_test(tc, test_64_bit_2);
    tcase_add_test(tc, test_96_bits_1);

    suite_add_tcase(s, tc);
    return s;
}
