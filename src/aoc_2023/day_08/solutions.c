#include "solutions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 512
#define MAX_NODES 1024

void parse_nodes(FILE *fp, NetworkNode *nodes, size_t *nodes_count) {
    char name[4];
    char left[4];
    char right[4];
    while (fscanf(fp, "%3s = (%3s, %3s)", name, left, right) == 3) {
        nodes[*nodes_count].name = strdup(name);
        nodes[*nodes_count].left = strdup(left);
        nodes[*nodes_count].right = strdup(right);
        (*nodes_count)++;
    }
}

NetworkNode *find_node(char *name, NetworkNode *nodes, size_t nodes_count) {
    for (size_t i = 0; i < nodes_count; i++) {
        if (strcmp(nodes[i].name, name) == 0) {
            return &nodes[i];
        }
    }
    return NULL;
}

size_t solve_part_one(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: could not open %s file\n", filename);
        exit(EXIT_FAILURE);
    }

    char directions[MAX_LEN];
    fscanf(fp, "%s", directions);
    size_t directions_count = strlen(directions);

    NetworkNode nodes[MAX_NODES] = {};
    size_t nodes_count = 0;
    parse_nodes(fp, nodes, &nodes_count);

    fclose(fp);

    size_t answer = 0;

    NetworkNode *curr_node = find_node("AAA", nodes, nodes_count);
    size_t directions_idx = 0;
    while (strcmp(curr_node->name, "ZZZ") != 0) {
        if (directions_idx == directions_count) {
            directions_idx = 0;
        }
        char direction = directions[directions_idx];
        switch (direction) {
            case 'L':
                curr_node = find_node(curr_node->left, nodes, nodes_count);
                break;
            case 'R':
                curr_node = find_node(curr_node->right, nodes, nodes_count);
                break;
        }
        directions_idx++;
        answer++;
    }

    return answer;
}

void get_starting_nodes(
    NetworkNode **curr_nodes,
    size_t *curr_nodes_count,
    NetworkNode *nodes,
    size_t nodes_count
) {
    for (size_t i = 0; i < nodes_count; i++) {
        if (nodes[i].name[2] == 'A') {
            curr_nodes[*curr_nodes_count] = &nodes[i];
            (*curr_nodes_count)++;
        }
    }
}

size_t gcd(size_t x, size_t y) {
    // Computes the Greatest Common Divisor with the Euclidean algorithm
    if (y == 0) {
        return x;
    }
    return gcd(y, x % y);
}

size_t lcm(size_t x, size_t y) {
    // Computes the Lowest Common Multiple using the Greatest Common Divisor
    return (x * y) / gcd(x, y);
}

size_t solve_part_two(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: could not open %s file\n", filename);
        exit(EXIT_FAILURE);
    }

    char directions[MAX_LEN];
    fscanf(fp, "%s", directions);
    size_t directions_count = strlen(directions);

    NetworkNode nodes[MAX_NODES] = {};
    size_t nodes_count = 0;
    parse_nodes(fp, nodes, &nodes_count);

    fclose(fp);

    NetworkNode *curr_nodes[MAX_NODES] = {};
    size_t curr_nodes_count = 0;
    get_starting_nodes(curr_nodes, &curr_nodes_count, nodes, nodes_count);

    size_t step_counts[curr_nodes_count];
    for (size_t i = 0; i < curr_nodes_count; i++) {
        size_t directions_idx = 0;
        int steps_count = 0;
        while (curr_nodes[i]->name[2] != 'Z') {
            if (directions_idx == directions_count) {
                directions_idx = 0;
            }
            char direction = directions[directions_idx];
            switch (direction) {
                case 'L':
                    curr_nodes[i] =
                        find_node(curr_nodes[i]->left, nodes, nodes_count);
                    break;
                case 'R':
                    curr_nodes[i] =
                        find_node(curr_nodes[i]->right, nodes, nodes_count);
                    break;
            }
            directions_idx++;
            steps_count++;
        }

        step_counts[i] = steps_count;
    }

    size_t answer = 1;
    for (size_t i = 0; i < curr_nodes_count; i++) {
        answer = lcm(answer, step_counts[i]);
    }

    return answer;
}
