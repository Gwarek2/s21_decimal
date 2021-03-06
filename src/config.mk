KERN := $(shell uname -s)

CC     := gcc
FLAGS  := -Wall -Werror -Wextra -std=c11 -g3 --coverage
ifdef ASAN
	FLAGS += -fsanitize=address
endif

TEST_FLAGS := -lcheck -lm -lpthread
ifeq ($(KERN),Linux)
	TEST_FLAGS += -lrt -lsubunit
endif
#TEST_FLAGS := $(shell pkg-config --libs check)
COV_FLAGS  := --coverage

INC_DIRS       := ./ core/ comparison/
TESTS_INC_DIRS := tests/
INC_FLAGS      := $(addprefix -I,$(INC_DIRS))
TEST_INC_FLAGS := $(addprefix -I,$(TESTS_INC_DIRS))

# Static check flags
CPPC       := cppcheck --enable=all --suppress=missingIncludeSystem
ALL_C      := $(shell find . -name "*.c")

# Dynamic memory check tool
ifeq ($(KERN),Darwin)
	MEM_TOOL := leaks -atExit --
else
	MEM_TOOL := valgrind --leak-check=full \
                         --show-leak-kinds=all \
                         -q
endif

ifdef LEAKS
	MEM_CHECK := $(MEM_TOOL)
endif

SRCS_H     := structs.h \
              s21_decimal.h \
              core/uint96.h \
              core/uint192.h
TESTS_H    := tests/test_main.h


SRCS_DIRS     := core/ \
                 arithmetics/ \
                 comparison/ \
                 conversion/ \
                 comparison/ \
                 rounding/
TESTS_DIR     := tests/
COV_DIR       := tests/coverage/
OBJ_DIRS      := $(addprefix obj/,$(SRCS_DIRS))
COV_OBJ_DIRS  := $(addprefix $(COV_DIR),$(OBJ_DIRS))


SRCS       := $(addprefix core/,uint96.c \
                                uint192.c) \
              $(addprefix arithmetics/,s21_negate.c \
                                       s21_mul.c \
                                       s21_add.c \
                                       s21_sub.c \
                                       s21_div.c \
                                       s21_mod.c) \
              $(addprefix conversion/,s21_from_int_to_decimal.c \
                                      s21_from_decimal_to_int.c \
                                      s21_from_decimal_to_float.c \
                                      s21_from_float_to_decimal.c) \
              $(addprefix comparison/,s21_comparison.c) \
              $(addprefix rounding/,s21_floor.c \
                                    s21_round.c \
                                    s21_truncate.c)
CORE_TESTS := $(addprefix $(TESTS_DIR)core/,eq_suite.c \
                                            lt_suite.c \
                                            base_addition_suite.c \
                                            base_subtraction_suite.c \
                                            base_multiply_suite.c \
                                            base_division_suite.c \
                                            remove_trailing_zeros_suite.c \
                                            equalize_scales_suite.c\
                                            uint192_division_suite.c \
                                            uint192_add_suite.c \
                                            uint192_mul_suite.c)
ARITHMETICS_TESTS := $(addprefix $(TESTS_DIR)arithmetics/,s21_negate_suite.c \
                                                          s21_mul_suite.c \
                                                          s21_div_suite.c \
                                                          s21_add_suite.c \
                                                          s21_sub_suite.c \
                                                          s21_mod_suite.c)
CONVERSION_TESTS  := $(addprefix $(TESTS_DIR)conversion/,s21_from_int_to_decimal_suite.c \
                                                         s21_from_decimal_to_int_suite.c \
                                                         s21_float_decimal_float_suite.c)
COMPARISON_TESTS   := $(addprefix $(TESTS_DIR)comparison/,s21_comparison_suite.c)
ROUNDING_TESTS    := $(addprefix $(TESTS_DIR)rounding/,s21_floor_suite.c \
                                                       s21_round_suite.c \
                                                       s21_truncate_suite.c)
TESTS      := $(TESTS_DIR)test_main.c \
              $(TESTS_DIR)output.c \
              $(CORE_TESTS) \
              $(ARITHMETICS_TESTS) \
              $(CONVERSION_TESTS) \
              $(COMPARISON_TESTS) \
              $(ROUNDING_TESTS)
OBJS       := $(patsubst %.c,obj/%.o,$(SRCS))
COV_OBJS   := $(patsubst %.c,$(COV_DIR)obj/%.o,$(SRCS))

BUILD_NAME := s21_decimal
BUILD_FILE := lib$(BUILD_NAME).a
TEST_EXEC  := test_main
TEST_EXEC  := $(TEST_EXEC)

COV_INFO   := $(COV_DIR)s21_decimal.info
COV_REPORT := $(COV_DIR)index.html

vpath %.c $(SRCS_DIRS)
