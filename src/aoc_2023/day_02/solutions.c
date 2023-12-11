#include "solutions.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

int max(int a, int b) {
    return (a > b) ? a : b;
}

CubeGame parse_game(char *line) {
    int game_id;
    sscanf(line, "Game %d:", &game_id);

    char *game_reveals = strchr(line, ':') + 1;
    Bag game_bag = {.red_cubes = 0, .green_cubes = 0, .blue_cubes = 0};

    char *reveal_save_ptr = NULL;
    char *reveal_token = strtok_r(game_reveals, ";", &reveal_save_ptr);
    while (reveal_token) {
        char *cubes_save_ptr = NULL;
        char *cubes_token = strtok_r(reveal_token, ",", &cubes_save_ptr);
        while (cubes_token) {
            char colour[8];
            int count;
            sscanf(cubes_token, "%d %s", &count, colour);
            if (strcmp(colour, "red") == 0) {
                game_bag.red_cubes = max(count, game_bag.red_cubes);
            } else if (strcmp(colour, "green") == 0) {
                game_bag.green_cubes = max(count, game_bag.green_cubes);
            } else if (strcmp(colour, "blue") == 0) {
                game_bag.blue_cubes = max(count, game_bag.blue_cubes);
            }

            cubes_token = strtok_r(NULL, ",", &cubes_save_ptr);
        }
        reveal_token = strtok_r(NULL, ";", &reveal_save_ptr);
    }

    CubeGame game = {.id = game_id, .bag = game_bag};
    return game;
}

bool is_possible_game(CubeGame game) {
    if (game.bag.red_cubes > MAX_RED) {
        return false;
    }
    if (game.bag.green_cubes > MAX_GREEN) {
        return false;
    }
    if (game.bag.blue_cubes > MAX_BLUE) {
        return false;
    }
    return true;
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
        CubeGame game = parse_game(line);
        if (is_possible_game(game)) {
            answer += game.id;
        }
    }

    return answer;
}
