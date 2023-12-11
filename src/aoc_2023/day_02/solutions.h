#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdbool.h>

typedef struct Bag {
    int red_cubes;
    int green_cubes;
    int blue_cubes;
} Bag;

typedef struct CubeGame {
    int id;
    Bag bag;
} CubeGame;

CubeGame parse_game(char *line);

bool is_possible_game(CubeGame game);

int solve_part_one(char const *filename);

#endif  // SOLUTIONS_H
