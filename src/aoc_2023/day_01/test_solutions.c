#include <assert.h>
#include <stdio.h>

#include "solutions.h"

void test_solve_part_one() {
    int expected = 142;
    int actual = solve_part_one("example.txt");
    assert(actual == expected);
}

int main(void) {
    printf("Running tests...\n");
    test_solve_part_one();
    printf("PASSED\n");
}
