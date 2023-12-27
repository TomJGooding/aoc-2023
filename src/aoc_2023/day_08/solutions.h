#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stddef.h>

typedef struct NetworkNode {
    char *name;
    char *left;
    char *right;
} NetworkNode;

size_t solve_part_one(char const *filename);

void get_starting_nodes(
    NetworkNode **curr_nodes,
    size_t *curr_nodes_count,
    NetworkNode *nodes,
    size_t nodes_count
);

size_t solve_part_two(char const *filename);

#endif  // SOLUTIONS_H
