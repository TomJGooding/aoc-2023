#include <assert.h>
#include <stdio.h>

#include "solutions.h"

void test_parse_races() {
    Race expected_races[3] = {
        {.time = 7, .record_dist = 9},
        {.time = 15, .record_dist = 40},
        {.time = 30, .record_dist = 200},
    };

    Race actual_races[MAX_RACES];
    size_t races_count = 0;
    parse_races("example.txt", actual_races, &races_count);

    assert(races_count == 3);
    for (size_t i = 0; i < races_count; i++) {
        assert(actual_races[i].time == expected_races[i].time);
        assert(actual_races[i].record_dist == expected_races[i].record_dist);
    }
}

void test_count_ways_to_win() {
    Race race = {.time = 7, .record_dist = 9};
    assert(count_ways_to_win(race) == 4);
}

void test_solve_part_one() {
    assert(solve_part_one("example.txt") == 288);
}

void test_parse_single_race() {
    Race actual = parse_single_race("example.txt");
    Race expected = {.time = 71530, .record_dist = 940200};
    assert(actual.time == expected.time);
    assert(actual.record_dist == expected.record_dist);
}

void test_solve_part_two() {
    assert(solve_part_two("example.txt") == 71503);
}

int main(void) {
    printf("Running tests...\n");
    test_parse_races();
    test_count_ways_to_win();
    test_solve_part_one();
    test_parse_single_race();
    test_solve_part_two();
    printf("PASSED\n");
}
