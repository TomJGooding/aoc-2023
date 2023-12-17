#include <assert.h>
#include <stdio.h>

#include "solutions.h"

void test_parse_winning_numbers() {
    char winning_data[] = " 41 48 83 86 17 ";
    WinningNumbers actual = parse_winning_numbers(winning_data);
    assert(actual.count == 5);
    assert(actual.numbers[0] == 41);
    assert(actual.numbers[4] == 17);
}

void test_parse_scratchcard() {
    char scratchcard_data[] = " 83 86  6 31 17  9 48 53";
    Scratchcard actual = parse_scratchcard(scratchcard_data);
    assert(actual.count == 8);
    assert(actual.numbers[0] == 83);
    assert(actual.numbers[7] == 53);
}

void test_parse_game() {
    char line[] = "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53";
    Game actual = parse_game(line);
    assert(actual.winning_numbers.count == 5);
    assert(actual.scratchcard.count == 8);
}

void test_solve_part_one() {
    assert(solve_part_one("example.txt") == 13);
}

int main(void) {
    printf("Running tests...\n");
    test_parse_winning_numbers();
    test_parse_scratchcard();
    test_parse_game();
    test_solve_part_one();
    printf("PASSED\n");
}
