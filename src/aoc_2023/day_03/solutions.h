#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Number {
    int value;
    size_t row;
    size_t col_start;
    size_t col_end;
} Number;

bool is_part_number(
    Number maybe_part_number,
    char *row_above,
    char *current_row,
    char *row_below
);

int solve_part_one(char const *filename);

#endif  // SOLUTIONS_H
