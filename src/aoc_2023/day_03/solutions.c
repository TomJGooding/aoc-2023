#include "solutions.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

bool is_symbol(char c) {
    return c != '.' && ispunct(c);
}

bool is_part_number(
    Number maybe_part_number,
    char *row_above,
    char *current_row,
    char *row_below
) {
    int col_left = max(0, maybe_part_number.col_start - 1);
    int col_right = min(strlen(current_row), maybe_part_number.col_end + 1);

    for (int i = col_left; i <= col_right; i++) {
        if (is_symbol(current_row[i])) {
            return true;
        }
        if (row_above[0] != '\0' && is_symbol(row_above[i])) {
            return true;
        }
        if (row_below[0] != '\0' && is_symbol(row_below[i])) {
            return true;
        }
    }

    return false;
}

int solve_part_one(char const *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: cannot open %s file\n", filename);
        exit(EXIT_FAILURE);
    }

    int answer = 0;

    char row_above[MAX_LEN] = {0};
    char current_row[MAX_LEN] = {0};
    char row_below[MAX_LEN] = {0};

    size_t row = 0;
    fgets(current_row, MAX_LEN, fp);

    while (fgets(row_below, MAX_LEN, fp)) {
        for (size_t col = 0; col < strlen(current_row); col++) {
            if (isdigit(current_row[col])) {
                Number maybe_part_number = {
                    .value = current_row[col] - '0',
                    .row = row,
                    .col_start = col,
                    .col_end = col};
                col++;
                while (isdigit(current_row[col])) {
                    maybe_part_number.value *= 10;
                    maybe_part_number.value += current_row[col] - '0';
                    maybe_part_number.col_end = col++;
                }
                if (is_part_number(
                        maybe_part_number, row_above, current_row, row_below
                    )) {
                    answer += maybe_part_number.value;
                }
            }
        }
        strncpy(row_above, current_row, MAX_LEN);
        strncpy(current_row, row_below, MAX_LEN);
        row++;
    }

    fclose(fp);

    // Finally check for last line of the input for any part numbers
    // TODO: Refactor to keep code DRY!
    strncpy(row_below, "", MAX_LEN);
    for (size_t col = 0; col < strlen(current_row); col++) {
        if (isdigit(current_row[col])) {
            Number maybe_part_number = {
                .value = current_row[col] - '0',
                .row = row,
                .col_start = col,
                .col_end = col};
            col++;
            while (isdigit(current_row[col])) {
                maybe_part_number.value *= 10;
                maybe_part_number.value += current_row[col] - '0';
                maybe_part_number.col_end = col++;
            }
            if (is_part_number(
                    maybe_part_number, row_above, current_row, row_below
                )) {
                answer += maybe_part_number.value;
            }
        }
    }

    return answer;
}
