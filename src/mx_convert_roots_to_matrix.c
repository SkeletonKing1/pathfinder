#include "pathfinder.h"


int **mx_convert_roots_to_matrix(char **lines, t_island *islands) {
    int islands_amount = mx_atoi(lines[0]);//hardcode
    int distance;
    int **roots_matrix = (int**)malloc(islands_amount * sizeof(int*));
    char **splitted_line;
    for (int i = 0; i < islands_amount; i++)
        roots_matrix[i] = (int*)malloc(islands_amount * sizeof(int));
    
    for (int i = 0; i < islands_amount; i++) {
        for (int j = 0; j < islands_amount; j++)
            roots_matrix[i][j] = 0;
    }
    for (int i = 0; i < islands_amount; i++) {
        for (int j = 1; lines[j]; j++) {
            if (mx_get_substr_index(lines[j],islands[i].name) != -1) {
                for (int k = i + 1; k < islands_amount; k++) {
                    if (mx_get_substr_index(lines[j],islands[k].name) != -1) {
                        splitted_line = mx_strsplit(lines[j],',');
                        distance = mx_atoi(splitted_line[1]);
                        roots_matrix[i][k] = distance;
                        roots_matrix[k][i] = distance;
                        mx_del_strarr(&splitted_line);
                    }
                }
            }
        }
    }
    return roots_matrix;
}
   
    
    
    
    
    
    
    
    
    
    
    
