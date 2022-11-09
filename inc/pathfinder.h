#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"

enum error {
    first_line_is_invalid,
    n_line_is_invalid,
    invalid_islands_amount,
    duplicate_bridges,
    summary_distance_is_to_big,
    wrong_usage
};

typedef struct s_island {
    char *name;
    bool is_visited;
    int mark;
} t_island;

int **mx_convert_roots_to_matrix(char **lines, t_island *islands);

t_island *mx_get_islands_arr(const char  **lines);

void mx_run(char **lines);

void mx_error_processing(char *str);

void mx_error_execution(int error_num, char *details);

#endif
