#include "pathfinder.h"

int main(int argc, char* argv[]) {
    if (argc != 2) 
        mx_error_execution(wrong_usage,NULL);
    
    mx_error_processing(mx_file_to_str(argv[1]));
    char *lines_str = mx_file_to_str(argv[1]);
    char **lines = mx_strsplit(lines_str,'\n');
    mx_strdel(&lines_str);
    mx_run(lines);
}
