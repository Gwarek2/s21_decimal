KERN := $(shell uname -s)

CC     := gcc
FLAGS  := -Wall -Werror -Wextra -g3
ifdef ASAN
	FLAGS += -fsanitize=address
endif

TEST_FLAGS := -lcheck -lm -lpthread
ifeq ($(KERN),Linux)
	TEST_FLAGS += -lrt -lsubunit
endif
TEST_FLAGS := $(shell pkg-config --libs check)
COV_FLAGS  := --coverage

INC_DIRS       := ./ core/
TESTS_INC_DIRS := tests/
INC_FLAGS      := $(addprefix -I,$(INC_DIRS))
TEST_INC_FLAGS := $(addprefix -I,$(TESTS_INC_DIRS))

# Static check flags
LINT_DIR   := ../materials/linters/*
LINT       := python3 cpplint.py --extensions=c
LINT_FILES := cpplint.py CPPLINT.cfg
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

SRCS_H     := decimal_type.h \
              s21_decimal.h \
              core/common.h \
              core/output.h \
              core/binary_level.h \
              core/decimal_level.h
TESTS_H    := tests/test_main.h


SRCS_DIRS     := core/ \
                 arithmetic/ \
                 comparison/ \
                 conversion/
TESTS_DIR     := tests/
COV_DIR       := coverage_info/
OBJ_DIRS      := $(addprefix obj/,$(SRCS_DIRS))
COV_OBJ_DIRS  := $(addprefix $(COV_DIR),$(OBJ_DIRS))


SRCS       := $(addprefix core/,common.c \
                                output.c \
                                binary_level.c \
                                decimal_level.c) 
CORE_TESTS := $(addprefix $(TESTS_DIR)core/,bits_eq_suite.c \
                                            bits_lt_suite.c \
                                            base_addition_suite.c \
                                            base_subtraction_suite.c \
                                            base_multiply_suite.c \
                                            base_division_suite.c \
                                            remove_trailing_zeros_suite.c)
TESTS      := $(TESTS_DIR)test_main.c \
              $(CORE_TESTS)

OBJS       := $(patsubst %.c,obj/%.o,$(SRCS))
COV_OBJS   := $(patsubst %.c,$(COV_DIR)obj/%.o,$(SRCS))


LIB_STATIC := s21_decimal.a
TEST_EXEC  := test_main
TEST_EXEC  := $(TEST_EXEC)
COV_EXEC   := $(COV_DIR)gcov_exec

COV_INFO   := $(COV_DIR)s21_decimal.info
COV_REPORT := $(COV_DIR)index.html

vpath %.c $(SRC_DIRS)