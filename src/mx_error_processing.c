#include "pathfinder.h"
//errors on file existence or emptity is handled in mx_filelen funtion.

bool is_valid_line(const char *str) {
    if(mx_count_substr(str,"-") != 1 || mx_count_substr(str,",") != 1) {
        return false;
    }
    
    char **splitted_line = mx_strsplit(str,',');
    if (splitted_line == NULL) {
        return false;
    }
    int distance = mx_atoi(splitted_line[1]);
   
    if (distance <= 0) {
        return false;
    }
    
    char *s = mx_strnew(mx_strlen(splitted_line[0]));
    mx_strcpy(s,splitted_line[0]);
    mx_del_strarr(&splitted_line);
    char **splitted_islands = mx_strsplit(s,'-');
    mx_strdel(&s);
    if (mx_strcmp(splitted_islands[0],splitted_islands[1]) == 0) {
        mx_del_strarr(&splitted_islands);
        return false;
    }
    
    for (int i = 0; i < 2; i++) {
        int current_str_len = mx_strlen(splitted_islands[i]);
        for (int j = 0; j < current_str_len; j++) {
            if (!mx_isalpha(splitted_islands[i][j])) {
                mx_del_strarr(&splitted_islands);
                return false;
            }
            
        }
    }
    mx_del_strarr(&splitted_islands);
    return true;
}

void check_on_first_line_validity(char **lines) {
    int islands_amount = mx_atoi(lines[0]);
    if(islands_amount <= 0) {
        mx_del_strarr(&lines);
        mx_error_execution(first_line_is_invalid,NULL);
    }
}

void check_on_n_line_validity(char **lines) {
    for (int i = 1; lines[i]; i++) {
        if(!is_valid_line(lines[i])) {
            char *num = mx_itoa(i + 1);
            mx_del_strarr(&lines);
            mx_error_execution(n_line_is_invalid,num);
        }
    }
}
void check_on_islands_amount(char **lines) {
    int islands_amount = mx_atoi(lines[0]);
  //  printf("%d\n",islands_amount);
    int size_count = 1;
    while(lines[size_count])
        size_count++;
    size_count--;
    char **islands = malloc((size_count * 2 + 1) * sizeof(char*));
    int size = 0;
    
    for (int i = 1; lines[i]; i++) {
       
        char **splitted_line = mx_strsplit(lines[i],',');
        char **splitted_islands = mx_strsplit(splitted_line[0],'-');
        islands[size] = mx_strnew(mx_strlen(splitted_islands[0]));
        mx_strcpy(islands[size],splitted_islands[0]);
      //  printf("%s\n",islands[size]);
        size++;
        islands[size] = mx_strnew(mx_strlen(splitted_islands[1]));
        mx_strcpy(islands[size],splitted_islands[1]);
     //    printf("%s\n",islands[size]);
        size++;
        mx_del_strarr(&splitted_islands);
        mx_del_strarr(&splitted_line);
        
    }
     islands[size] = NULL;
    
    if (size < islands_amount) {
          mx_del_strarr(&islands);
          mx_del_strarr(&lines);
          mx_error_execution(invalid_islands_amount,NULL);
    }
    
    for (int i = 0; islands[i]; i++) {
        for (int j = i + 1; islands[j]; j++) {
            if (mx_strcmp(islands[i],islands[j]) == 0) {
                size--;
                break;
            }
        }
    }

    if (size != islands_amount) {
        mx_del_strarr(&islands);
        mx_del_strarr(&lines);
        mx_error_execution(invalid_islands_amount,NULL);
    }
    mx_del_strarr(&islands);
}

void check_on_duplicating_bridges(char **lines) {
  //  int bridges_amount = mx_atoi(lines[0])*2;
    int size_count = 1;
    while(lines[size_count])
        size_count++;
    size_count--;
    
    char **bridges = malloc((size_count + 1) * sizeof(char*));
    int size = 0;
    
    for (int i = 1; lines[i]; i++) {
        char **splitted_line = mx_strsplit(lines[i],',');
        bridges[size] = mx_strnew(mx_strlen(splitted_line[0])); 
        mx_strcpy(bridges[size],splitted_line[0]);
        size++;
        mx_del_strarr(&splitted_line);
    }
    bridges[size] = NULL;
    for(int i = 0; bridges[i];i++) {
        for (int j = i + 1; bridges[j]; j++) {
            if(mx_strcmp(bridges[i],bridges[j]) == 0) {
                mx_del_strarr(&bridges);
                mx_del_strarr(&lines);
                mx_error_execution(duplicate_bridges,NULL);
            }
        }
    }
     
     mx_del_strarr(&bridges);
}
void check_on_max_distance(char **lines) {
    long sum = 0;
    for (int i = 1; lines[i]; i++) {
        int indx = mx_get_char_index(lines[i], ',');
        sum += (long)mx_atoi(lines[i] + indx + 1);
    }
    if (sum > 2147483647) {
        mx_del_strarr(&lines);
        mx_error_execution(summary_distance_is_to_big,NULL);
    }
}

void mx_error_processing(char *str) {
    char **lines = mx_strsplit(str,'\n');
    mx_strdel(&str);
    check_on_first_line_validity(lines);
    check_on_n_line_validity(lines);
    check_on_islands_amount(lines);
    
    check_on_duplicating_bridges(lines);

    check_on_max_distance(lines);
    
    mx_del_strarr(&lines);
    
}

