#include <stdio.h>
#include <time.h>

#include "solutions.h"

int main(void) {
    printf("--- Day 5: If You Give A Seed A Fertilizer ---\n");

    clock_t start;
    clock_t end;

    start = clock();
    printf("Answer for part 1: %u ", solve_part_one("input.txt"));
    end = clock();
    printf("(took %.4f seconds)\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    printf("Answer for part 2: %d ", solve_part_two("input.txt"));
    end = clock();
    printf("(took %.4f seconds)\n", (double)(end - start) / CLOCKS_PER_SEC);
}
