#include <stdio.h>
#include <time.h>

#include "solutions.h"

int main(void) {
    printf("--- Day 6: Wait For It ---\n");

    clock_t start;
    clock_t end;

    start = clock();
    printf("Answer for part 1: %d ", solve_part_one("input.txt"));
    end = clock();
    printf("(took %.4f seconds)\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    printf("Answer for part 2: %lld ", solve_part_two("input.txt"));
    end = clock();
    printf("(took %.4f seconds)\n", (double)(end - start) / CLOCKS_PER_SEC);
}
