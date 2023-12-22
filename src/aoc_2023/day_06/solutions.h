#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stddef.h>

#define MAX_RACES 4

typedef struct Race {
    int time;
    int record_dist;
} Race;

void parse_races(char const *filename, Race *races, size_t *races_count);

int count_ways_to_win(Race race);

int solve_part_one(char const *filename);

#endif  // SOLUTIONS_H
