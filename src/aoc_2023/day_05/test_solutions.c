#include <assert.h>
#include <stdio.h>

#include "solutions.h"

void test_solve_part_one() {
    assert(solve_part_one("example.txt") == 35);
}

void test_solve_part_two() {
    assert(solve_part_two("example.txt") == 46);
}

int main(void) {
    printf("Running tests...\n");
    test_solve_part_one();
    test_solve_part_two();
    printf("PASSED\n");
}
