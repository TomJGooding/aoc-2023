#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stddef.h>

typedef struct Scratchcard {
    size_t count;
    int numbers[32];
} Scratchcard;

typedef struct WinningNumbers {
    size_t count;
    int numbers[32];
} WinningNumbers;

typedef struct Game {
    Scratchcard scratchcard;
    WinningNumbers winning_numbers;
    int score;
} Game;

WinningNumbers parse_winning_numbers(char *winning_data);

Scratchcard parse_scratchcard(char *scratchcard_data);

Game parse_game(char *line);

int solve_part_one(char const *filename);

#endif  // SOLUTIONS_H
