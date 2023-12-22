#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stddef.h>

#define MAX_RACES 4

typedef struct Race {
    long long int time;
    long long int record_dist;
} Race;

void parse_races(char const *filename, Race *races, size_t *races_count);

long long int count_ways_to_win(Race race);

int solve_part_one(char const *filename);

Race parse_single_race(char const *filename);

long long int solve_part_two(char const *filename);

#endif  // SOLUTIONS_H
