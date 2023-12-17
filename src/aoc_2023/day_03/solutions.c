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

AdjacentParts get_adjacent_parts(
    size_t maybe_gear_col, char *row_above, char *current_row, char *row_below
) {
    char *rows[3] = {row_above, current_row, row_below};
    AdjacentParts adjacent_parts = {.count = 0, .numbers = {0}};

    for (size_t i = 0; i < 3; i++) {
        for (size_t col = 0; col < strlen(rows[i]); col++) {
            if (isdigit(rows[i][col])) {
                Number part_number = {
                    .value = rows[i][col] - '0',
                    .col_start = col,
                    .col_end = col};
                col++;
                while (isdigit(rows[i][col])) {
                    part_number.value *= 10;
                    part_number.value += rows[i][col] - '0';
                    part_number.col_end = col++;
                }
                bool is_adjacent = false;
                for (size_t part_col = part_number.col_start;
                     part_col <= part_number.col_end;
                     part_col++) {
                    if (maybe_gear_col - 1 <= part_col &&
                        part_col <= maybe_gear_col + 1) {
                        is_adjacent = true;
                        break;
                    }
                }
                if (is_adjacent) {
                    adjacent_parts.numbers[adjacent_parts.count] =
                        part_number.value;
                    adjacent_parts.count++;
                }
            }
        }
    }
    return adjacent_parts;
}

int solve_part_two(const char *filename) {
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
            if (current_row[col] == '*') {
                AdjacentParts adjacent_parts =
                    get_adjacent_parts(col, row_above, current_row, row_below);
                if (adjacent_parts.count == 2) {
                    int gear_ratio =
                        adjacent_parts.numbers[0] * adjacent_parts.numbers[1];
                    answer += gear_ratio;
                }
            }
        }
        strncpy(row_above, current_row, MAX_LEN);
        strncpy(current_row, row_below, MAX_LEN);
        row++;
    }

    fclose(fp);

    // Finally check for last line of the input for any gears
    // TODO: Refactor to keep code DRY!
    strncpy(row_below, "", MAX_LEN);
    for (size_t col = 0; col < strlen(current_row); col++) {
        if (current_row[col] == '*') {
            AdjacentParts adjacent_parts =
                get_adjacent_parts(col, row_above, current_row, row_below);
            if (adjacent_parts.count == 2) {
                int gear_ratio =
                    adjacent_parts.numbers[0] * adjacent_parts.numbers[1];
                answer += gear_ratio;
            }
        }
    }

    return answer;
}
