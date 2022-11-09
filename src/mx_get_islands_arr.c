#include "pathfinder.h"

void init_island_fields(t_island *islands, int size) {
    for (int i = 0; i < size; i++) {
        islands[i].mark = 2147483647;
        islands[i].is_visited = false;
    }
}

char **get_splitted_islands(char *line) {
    char **splitted_islands, **splitted_line;
    splitted_line = mx_strsplit(line,',');
    char *splitted_line_str = mx_strnew(mx_strlen(splitted_line[0]));
    mx_strcpy(splitted_line_str, splitted_line[0]);
    mx_del_strarr(&splitted_line);
    splitted_islands = mx_strsplit(splitted_line_str,'-');
    mx_strdel(&splitted_line_str);
    
    return splitted_islands;
}

char **get_all_islands(const char **lines,int size) {
    char **all_islands = (char**)malloc((size - 1) * 2 * sizeof(char*));
    for (int i = 1,j = 0; i < size; i++) {
        char **splitted_islands = get_splitted_islands((char*)lines[i]);
        all_islands[j] = mx_strnew(mx_strlen(splitted_islands[0]));
        mx_strcpy(all_islands[j],splitted_islands[0]);
        j++;
        all_islands[j] = mx_strnew(mx_strlen(splitted_islands[1]));
        mx_strcpy(all_islands[j],splitted_islands[1]);
        j++;
        mx_del_strarr(&splitted_islands);
    }
    return all_islands;
}

t_island *mx_get_islands_arr(const char  **lines) {
    int islands_amount = mx_atoi((char*)lines[0]);
    int lines_count = 0;
    while(lines[lines_count])
        lines_count++;
    
    t_island *islands = (t_island*)malloc(islands_amount  * sizeof(t_island)); //hardcoded
    
    
    char **all_islands = get_all_islands(lines, lines_count);
    
    islands[0].name = mx_strnew(mx_strlen(all_islands[0]));
    mx_strcpy(islands[0].name, all_islands[0]);
      
    bool is_present;
    for (int i = 1,k = 1; i < (lines_count - 1)* 2; i++) {
        is_present = false;
        for (int j = 0; j < i; j++) {
            if (mx_strcmp(all_islands[i],all_islands[j])==0){
                is_present = true;
                break;
            }
        }
        if (!is_present) {
            islands[k].name = mx_strnew(mx_strlen(all_islands[i]));
            mx_strcpy(islands[k].name,all_islands[i]);
            k++;
        }
    }
    mx_del_strarr(&all_islands);
    init_island_fields(islands, islands_amount); //hardcoded
    return islands;
    
}

