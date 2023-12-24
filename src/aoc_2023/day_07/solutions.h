#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdbool.h>
#include <stddef.h>

#define HAND_CARDS 5

#define MAX_HANDS 1024

enum Card {
    JOKER,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE,
    TOTAL_CARD_TYPES
};

enum HandType {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND,
};

typedef struct Hand {
    enum Card cards[HAND_CARDS];
    int bid;
    enum HandType type;
} Hand;

void get_hand_type(Hand *hand);

Hand parse_hand(char *line, bool jokers);

void parse_hands(char const *filename, Hand *hands, size_t *hands_count);

int compare_hands(const void *a, const void *b);

int solve_part_one(char const *filename);

void parse_hands_with_jokers(
    char const *filename, Hand *hands, size_t *hands_count
);

int solve_part_two(char const *filename);

#endif  // SOLUTIONS_H
