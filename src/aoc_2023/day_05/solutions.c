#include "solutions.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

int get_map_type(char *line) {
    char *map_type_strs[TOTAL_MAP_TYPES] = {
        "seed-to-soil map:",
        "soil-to-fertilizer map:",
        "fertilizer-to-water map:",
        "water-to-light map:",
        "light-to-temperature map:",
        "temperature-to-humidity map:",
        "humidity-to-location map:"};

    int map_type = -1;

    for (int i = 0; i < TOTAL_MAP_TYPES; i++) {
        if (strcmp(map_type_strs[i], line) == 0) {
            map_type = i;
        }
    }

    return map_type;
}

unsigned int solve_part_one(char const *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: could not open %s file\n", filename);
        exit(EXIT_FAILURE);
    }

    unsigned int seeds[MAX_LEN] = {};
    size_t seed_count = 0;

    unsigned int seed;
    fscanf(fp, "seeds:");
    while (fscanf(fp, " %u", &seed)) {
        seeds[seed_count] = seed;
        seed_count++;
    }

    Map maps[TOTAL_MAP_TYPES];

    MapType map_type = SEED_TO_SOIL;
    char line[MAX_LEN];
    while (fgets(line, MAX_LEN, fp)) {
        if (isalpha(line[0])) {
            line[strcspn(line, "\n")] = '\0';
            int found_map_type = get_map_type(line);
            if (found_map_type == -1) {
                fprintf(stderr, "ERROR: failed to parse line '%s'\n", line);
                exit(EXIT_FAILURE);
            }
            map_type = found_map_type;
            Map map = {.type = map_type, .lines = {}, .lines_count = 0};
            maps[map_type] = map;
        }

        unsigned int dest_start;
        unsigned int src_start;
        unsigned int range_len;

        if (sscanf(line, "%u %u %u", &dest_start, &src_start, &range_len) ==
            3) {
            Range dest_range = {
                .start = dest_start, .stop = dest_start + range_len};
            Range src_range = {
                .start = src_start, .stop = src_start + range_len};

            MapLine map_line = {
                .dest_range = dest_range, .src_range = src_range};

            maps[map_type].lines[maps[map_type].lines_count] = map_line;
            maps[map_type].lines_count++;
        }
    }

    fclose(fp);

    unsigned int answer = 0;

    unsigned int src_num;
    unsigned int dest_num;
    for (size_t seed_idx = 0; seed_idx < seed_count; seed_idx++) {
        src_num = seeds[seed_idx];
        dest_num = seeds[seed_idx];
        for (size_t map_idx = 0; map_idx < TOTAL_MAP_TYPES; map_idx++) {
            for (size_t line_idx = 0; line_idx < maps[map_idx].lines_count;
                 line_idx++) {
                MapLine curr_line = maps[map_idx].lines[line_idx];
                if (src_num >= curr_line.src_range.start &&
                    src_num < curr_line.src_range.stop) {
                    unsigned int found_idx =
                        src_num - curr_line.src_range.start;
                    dest_num = curr_line.dest_range.start + found_idx;
                    break;
                }
            }
            src_num = dest_num;
        }

        if (seed_idx == 0 || dest_num < answer) {
            answer = dest_num;
        }
    }

    return answer;
}
