#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "solutions.h"

void test_get_hand_type() {
    Hand five_of_kind = {.cards = {ACE, ACE, ACE, ACE, ACE}};
    get_hand_type(&five_of_kind);
    assert(five_of_kind.type == FIVE_OF_A_KIND);

    Hand four_of_kind = {.cards = {ACE, ACE, EIGHT, ACE, ACE}};
    get_hand_type(&four_of_kind);
    assert(four_of_kind.type == FOUR_OF_A_KIND);

    Hand full_house = {.cards = {TWO, THREE, THREE, THREE, TWO}};
    get_hand_type(&full_house);
    assert(full_house.type == FULL_HOUSE);

    Hand three_of_kind = {.cards = {TEN, TEN, TEN, NINE, EIGHT}};
    get_hand_type(&three_of_kind);
    assert(three_of_kind.type == THREE_OF_A_KIND);

    Hand two_pair = {.cards = {TWO, THREE, FOUR, THREE, TWO}};
    get_hand_type(&two_pair);
    assert(two_pair.type == TWO_PAIR);

    Hand one_pair = {.cards = {ACE, TWO, THREE, ACE, FOUR}};
    get_hand_type(&one_pair);
    assert(one_pair.type == ONE_PAIR);

    Hand high_card = {.cards = {TWO, THREE, FOUR, FIVE, SIX}};
    get_hand_type(&high_card);
    assert(high_card.type == HIGH_CARD);
}

void test_parse_hand() {
    char line[] = "32T3K 765";
    Hand actual = parse_hand(line);

    enum Card expected_cards[5] = {THREE, TWO, TEN, THREE, KING};
    assert(memcmp(actual.cards, expected_cards, sizeof(actual.cards)) == 0);

    assert(actual.bid == 765);
}

void test_parse_hands() {
    Hand hands[MAX_HANDS];
    size_t hands_count = 0;
    parse_hands("example.txt", hands, &hands_count);
    assert(hands_count == 5);
}

void test_compare_hands_when_different_types() {
    Hand five_of_kind = {
        .cards = {ACE, ACE, ACE, ACE, ACE}, .type = FIVE_OF_A_KIND};
    Hand three_of_kind = {
        .cards = {TEN, TEN, TEN, NINE, EIGHT}, .type = THREE_OF_A_KIND};
    Hand high_card = {
        .cards = {TWO, THREE, FOUR, FIVE, SIX}, .type = HIGH_CARD};

    Hand hands[3] = {three_of_kind, five_of_kind, high_card};

    qsort(hands, 3, sizeof(Hand), compare_hands);

    assert(hands[0].type == HIGH_CARD);
    assert(hands[1].type == THREE_OF_A_KIND);
    assert(hands[2].type == FIVE_OF_A_KIND);
}

void test_compare_hands_when_same_type() {
    Hand winning_hand = {
        .cards = {SEVEN, SEVEN, EIGHT, EIGHT, EIGHT}, .type = FULL_HOUSE};
    Hand losing_hand = {
        .cards = {SEVEN, SEVEN, SEVEN, EIGHT, EIGHT}, .type = FULL_HOUSE};

    Hand hands[2] = {winning_hand, losing_hand};

    qsort(hands, 2, sizeof(Hand), compare_hands);

    assert(memcmp(&hands[0], &losing_hand, sizeof(Hand)) == 0);
    assert(memcmp(&hands[1], &winning_hand, sizeof(Hand)) == 0);
}

void test_solve_part_one() {
    assert(solve_part_one("example.txt") == 6440);
}

int main(void) {
    printf("Running tests...\n");
    test_get_hand_type();
    test_parse_hand();
    test_parse_hands();
    test_compare_hands_when_different_types();
    test_compare_hands_when_same_type();
    test_solve_part_one();
    printf("PASSED\n");
}
