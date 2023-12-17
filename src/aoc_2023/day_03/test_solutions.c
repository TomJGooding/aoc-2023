#include <assert.h>
#include <stdio.h>

#include "solutions.h"

void test_is_part_number() {
    char row_above[] = {0};
    char current_row[] = "467..114..";
    char row_below[] = "...*......";

    Number valid_part_number = {
        .value = 467, .row = 0, .col_start = 0, .col_end = 2};
    assert(is_part_number(valid_part_number, row_above, current_row, row_below)
    );

    Number invalid_part_number = {
        .value = 114, .row = 0, .col_start = 5, .col_end = 7};
    assert(
        !is_part_number(invalid_part_number, row_above, current_row, row_below)
    );
}

void test_solve_part_one() {
    assert(solve_part_one("example.txt") == 4361);
}

int main(void) {
    printf("Running tests...\n");
    test_is_part_number();
    test_solve_part_one();
    printf("PASSED\n");
}
