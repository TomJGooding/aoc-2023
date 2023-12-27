#ifndef SOLUTIONS_H
#define SOLUTIONS_H

typedef struct NetworkNode {
    char *name;
    char *left;
    char *right;
} NetworkNode;

int solve_part_one(char const *filename);

#endif  // SOLUTIONS_H
