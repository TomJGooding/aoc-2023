#include <assert.h>
#include <stdio.h>

#include "solutions.h"

void test_solve_part_one() {
    int expected = 142;
    int actual = solve_part_one("example_01.txt");
    assert(actual == expected);
}

void test_extract_number_with_digit_words() {
    int expected = 83;
    int actual = extract_number_with_digit_words("eightwothree");
    assert(actual == expected);
}

void test_solve_part_two() {
    int expected = 281;
    int actual = solve_part_two("example_02.txt");
    assert(actual == expected);
}

int main(void) {
    printf("Running tests...\n");
    test_solve_part_one();
    test_extract_number_with_digit_words();
    test_solve_part_two();
    printf("PASSED\n");
}
