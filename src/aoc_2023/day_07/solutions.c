#include "solutions.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 16

int compare_card_counts(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

void get_hand_type(Hand *hand) {
    int card_counts[TOTAL_CARD_TYPES] = {};

    for (size_t i = 0; i < HAND_CARDS; i++) {
        card_counts[hand->cards[i]]++;
    }

    int jokers_count = card_counts[JOKER];
    card_counts[JOKER] = 0;

    qsort(card_counts, TOTAL_CARD_TYPES, sizeof(int), compare_card_counts);

    if (card_counts[0] == 5 - jokers_count) {
        hand->type = FIVE_OF_A_KIND;
        return;
    } else if (card_counts[0] == 4 - jokers_count) {
        hand->type = FOUR_OF_A_KIND;
        return;
    } else if (card_counts[0] + card_counts[1] + jokers_count == 5) {
        hand->type = FULL_HOUSE;
        return;
    } else if (card_counts[0] == 3 - jokers_count) {
        hand->type = THREE_OF_A_KIND;
        return;
    } else if (card_counts[0] + card_counts[1] + jokers_count == 4) {
        hand->type = TWO_PAIR;
        return;
    } else if (card_counts[0] == 2 - jokers_count) {
        hand->type = ONE_PAIR;
        return;
    } else {
        hand->type = HIGH_CARD;
        return;
    }
}

Hand parse_hand(char *line, bool jokers) {
    Hand hand;
    for (int i = 0; i < HAND_CARDS; i++) {
        enum Card card;
        if (isdigit(line[i])) {
            card = line[i] - '1';
            hand.cards[i] = card;
        } else if (line[i] == 'A') {
            card = ACE;
            hand.cards[i] = card;
        } else if (line[i] == 'T') {
            card = TEN;
            hand.cards[i] = card;
        } else if (line[i] == 'J') {
            if (jokers) {
                card = JOKER;
            } else {
                card = JACK;
            }
            hand.cards[i] = card;
        } else if (line[i] == 'Q') {
            card = QUEEN;
            hand.cards[i] = card;
        } else if (line[i] == 'K') {
            card = KING;
            hand.cards[i] = card;
        } else {
            fprintf(
                stderr, "ERROR: found unexpected '%c' in hand input\n", line[i]
            );
            exit(EXIT_FAILURE);
        }
    }

    hand.bid = atoi(line + 5);

    return hand;
}

void parse_hands(char const *filename, Hand *hands, size_t *hands_count) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: cannot open %s file\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LEN];
    while (fgets(line, MAX_LEN, fp)) {
        hands[*hands_count] = parse_hand(line, false);
        (*hands_count)++;
    }

    fclose(fp);
}

int compare_hands(const void *a, const void *b) {
    Hand *hand_a = (Hand *)a;
    Hand *hand_b = (Hand *)b;

    if (hand_a->type > hand_b->type) {
        return 1;
    }
    if (hand_a->type < hand_b->type) {
        return -1;
    }

    for (size_t i = 0; i < HAND_CARDS; i++) {
        if (hand_a->cards[i] == hand_b->cards[i]) {
            continue;
        }
        if (hand_a->cards[i] > hand_b->cards[i]) {
            return 1;
        } else {
            return -1;
        }
    }

    return 0;
}

int solve_part_one(char const *filename) {
    Hand hands[MAX_HANDS];
    size_t hand_count = 0;
    parse_hands(filename, hands, &hand_count);

    for (size_t i = 0; i < hand_count; i++) {
        get_hand_type(&hands[i]);
    }

    qsort(hands, hand_count, sizeof(Hand), compare_hands);

    int answer = 0;

    for (size_t i = 0; i < hand_count; i++) {
        int rank = i + 1;
        answer += hands[i].bid * rank;
    }

    return answer;
}

void parse_hands_with_jokers(
    char const *filename, Hand *hands, size_t *hands_count
) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: cannot open %s file\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LEN];
    while (fgets(line, MAX_LEN, fp)) {
        hands[*hands_count] = parse_hand(line, true);
        (*hands_count)++;
    }

    fclose(fp);
}

int solve_part_two(char const *filename) {
    Hand hands[MAX_HANDS];
    size_t hand_count = 0;
    parse_hands_with_jokers(filename, hands, &hand_count);

    for (size_t i = 0; i < hand_count; i++) {
        get_hand_type(&hands[i]);
    }

    qsort(hands, hand_count, sizeof(Hand), compare_hands);

    int answer = 0;

    for (size_t i = 0; i < hand_count; i++) {
        int rank = i + 1;
        answer += hands[i].bid * rank;
    }

    return answer;
}
