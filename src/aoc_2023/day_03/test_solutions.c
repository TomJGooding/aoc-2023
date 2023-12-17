#include <assert.h>
#include <stdio.h>

#include "solutions.h"

void test_is_part_number() {
    char row_above[] = {0};
    char current_row[] = "467..114..";
    char row_below[] = "...*......";

    Number valid_part_number = {.value = 467, .col_start = 0, .col_end = 2};
    assert(is_part_number(valid_part_number, row_above, current_row, row_below)
    );

    Number invalid_part_number = {.value = 114, .col_start = 5, .col_end = 7};
    assert(
        !is_part_number(invalid_part_number, row_above, current_row, row_below)
    );
}

void test_solve_part_one() {
    assert(solve_part_one("example.txt") == 4361);
}

void test_get_adjacent_parts() {
    char row_above[] = "467..114..";
    char current_row[] = "...*......";
    char row_below[] = "..35..633.";
    size_t maybe_gear_col = 3;

    AdjacentParts adjacent_parts =
        get_adjacent_parts(maybe_gear_col, row_above, current_row, row_below);

    assert(adjacent_parts.count == 2);
    int gear_ratio = adjacent_parts.numbers[0] * adjacent_parts.numbers[1];
    assert(gear_ratio == 16345);
}

void test_solve_part_two() {
    assert(solve_part_two("example.txt") == 467835);
}

int main(void) {
    printf("Running tests...\n");
    test_is_part_number();
    test_solve_part_one();
    test_get_adjacent_parts();
    test_solve_part_two();
    printf("PASSED\n");
}
