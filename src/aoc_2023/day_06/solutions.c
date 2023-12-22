#include "solutions.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void parse_races(char const *filename, Race *races, size_t *races_count) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: could not open %s file\n", filename);
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "Time:");
    int time;
    while (fscanf(fp, "%d", &time)) {
        Race race = {.time = time};
        races[*races_count] = race;
        (*races_count)++;
    }
    fscanf(fp, "Distance:");
    size_t race_idx = 0;
    int distance;
    while (fscanf(fp, "%d", &distance) != EOF) {
        races[race_idx].record_dist = distance;
        race_idx++;
    }

    fclose(fp);
}

long long int count_ways_to_win(Race race) {
    long long int count = 0;
    for (long long int charge_time = 1; charge_time < race.time;
         charge_time++) {
        long long int remaining_time = race.time - charge_time;
        long long int distance = charge_time * remaining_time;
        if (distance > race.record_dist) {
            count++;
        }
    }
    return count;
}

int solve_part_one(char const *filename) {
    Race races[MAX_RACES] = {};
    size_t races_count = 0;
    parse_races(filename, races, &races_count);

    int answer = count_ways_to_win(races[0]);
    for (size_t i = 1; i < races_count; i++) {
        answer *= count_ways_to_win(races[i]);
    }

    return answer;
}

Race parse_single_race(char const *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: could not open %s file\n", filename);
        exit(EXIT_FAILURE);
    }

    long long int time = 0;
    long long int distance = 0;
    int num;

    fscanf(fp, "Time:");
    while (fscanf(fp, "%d", &num)) {
        int num_digits = (int)log10(num) + 1;
        time *= pow(10, num_digits);
        time += num;
    }
    fscanf(fp, "Distance:");
    while (fscanf(fp, "%d", &num) != EOF) {
        int num_digits = (int)log10(num) + 1;
        distance *= pow(10, num_digits);
        distance += num;
    }

    fclose(fp);

    Race race = {.time = time, .record_dist = distance};
    return race;
}

long long int solve_part_two(char const *filename) {
    Race race = parse_single_race(filename);
    return count_ways_to_win(race);
}
