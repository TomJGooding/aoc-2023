#include "solutions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

WinningNumbers parse_winning_numbers(char *winning_data) {
    WinningNumbers winning_numbers = {.count = 0, .numbers = {0}};
    char *winning_save_ptr = NULL;
    char *winning_number = strtok_r(winning_data, " ", &winning_save_ptr);
    while (winning_number) {
        winning_numbers.numbers[winning_numbers.count] = atoi(winning_number);
        winning_numbers.count++;
        winning_number = strtok_r(NULL, " ", &winning_save_ptr);
    }

    return winning_numbers;
}

Scratchcard parse_scratchcard(char *scratchcard_data) {
    Scratchcard scratchcard = {.count = 0, .numbers = {0}};
    char *scrathcard_save_ptr = NULL;
    char *scratchard_number =
        strtok_r(scratchcard_data, " ", &scrathcard_save_ptr);
    while (scratchard_number) {
        scratchcard.numbers[scratchcard.count] = atoi(scratchard_number);
        scratchcard.count++;
        scratchard_number = strtok_r(NULL, " ", &scrathcard_save_ptr);
    }

    return scratchcard;
}

Game parse_game(char *line) {
    char *data = strchr(line, ':') + 1;
    char *save_ptr = NULL;
    char *winning_data = strtok_r(data, "|", &save_ptr);
    char *scratchcard_data = strtok_r(NULL, "|", &save_ptr);

    WinningNumbers winning_numbers = parse_winning_numbers(winning_data);
    Scratchcard scratchcard = parse_scratchcard(scratchcard_data);

    Game game = {
        .winning_numbers = winning_numbers,
        .scratchcard = scratchcard,
        .score = 0};
    return game;
}

int solve_part_one(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: cannot open %s file\n", filename);
        exit(EXIT_FAILURE);
    }

    int answer = 0;

    char line[256];
    while (fgets(line, MAX_LEN, fp)) {
        Game game = parse_game(line);
        int match_count = 0;
        for (size_t i = 0; i < game.scratchcard.count; i++) {
            for (size_t j = 0; j < game.winning_numbers.count; j++) {
                if (game.scratchcard.numbers[i] ==
                    game.winning_numbers.numbers[j]) {
                    match_count++;

                    if (match_count == 1) {
                        game.score += 1;
                    } else {
                        game.score *= 2;
                    }
                }
            }
        }
        answer += game.score;
    }

    fclose(fp);

    return answer;
}
