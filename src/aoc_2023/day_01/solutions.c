#include "solutions.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

int extract_number(char *line) {
    int first_digit = -1;
    int last_digit = -1;
    for (size_t i = 0; i < strlen(line); i++) {
        if (isdigit(line[i])) {
            int digit = line[i] - '0';
            if (first_digit == -1) {
                first_digit = digit;
            } else {
                last_digit = digit;
            }
        }
    }
    if (last_digit == -1) {
        last_digit = first_digit;
    }
    return (first_digit * 10) + last_digit;
}

int solve_part_one(char const *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: cannot open %s file\n", filename);
        exit(EXIT_FAILURE);
    }
    int answer = 0;
    char line[MAX_LEN];
    while (fgets(line, MAX_LEN, fp)) {
        answer += extract_number(line);
    }
    fclose(fp);
    return answer;
}
