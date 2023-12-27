#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "solutions.h"

void test_solve_part_one() {
    assert(solve_part_one("example_01.txt") == 6);
}

void test_get_starting_nodes() {
    NetworkNode nodes[4] = {};
    nodes[0].name = strdup("11A");
    nodes[1].name = strdup("11B");
    nodes[2].name = strdup("11Z");
    nodes[3].name = strdup("22A");
    size_t nodes_count = 4;

    NetworkNode *curr_nodes[4] = {};
    size_t curr_nodes_count = 0;
    get_starting_nodes(curr_nodes, &curr_nodes_count, nodes, nodes_count);

    assert(curr_nodes_count == 2);
    assert(strcmp(curr_nodes[0]->name, "11A") == 0);
    assert(strcmp(curr_nodes[1]->name, "22A") == 0);
}

void test_solve_part_two() {
    assert(solve_part_two("example_02.txt") == 6);
}

int main(void) {
    printf("Running tests...\n");
    test_solve_part_one();
    test_get_starting_nodes();
    test_solve_part_two();
    printf("PASSED\n");
}
