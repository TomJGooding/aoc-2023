#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "solutions.h"

void test_parse_game() {
    char line[] = "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
    CubeGame game = parse_game(line);
    assert(game.id == 5);
    assert(game.bag.red_cubes == 6);
    assert(game.bag.green_cubes == 3);
    assert(game.bag.blue_cubes == 2);
}

void test_is_possible_game() {
    Bag max_bag = {.red_cubes = 12, .green_cubes = 13, .blue_cubes = 14};
    CubeGame game = {.id = 1, .bag = max_bag};
    assert(is_possible_game(game));

    game.bag.blue_cubes += 1;
    assert(!is_possible_game(game));
}

void test_solve_part_one() {
    assert(solve_part_one("example.txt") == 8);
}

int main(void) {
    printf("Running tests...\n");
    test_parse_game();
    test_is_possible_game();
    test_solve_part_one();
    printf("PASSED\n");
}
