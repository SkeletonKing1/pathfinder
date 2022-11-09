#include "pathfinder.h"

void mx_error_execution(int error_num, char *details) {
    const char *error_descriptions[] = {
        "error: line 1 is not valid\n",
        "error: line ",
        " is not valid\n",
        "error: invalid number of islands\n",
        "error: duplicate bridges\n",
        "error: sum of bridges lengths is too big\n",
        "usage: ./pathfinder [filename]\n"
    };
    switch(error_num) {
        case 0: 
            
            write(2,error_descriptions[0],mx_strlen(error_descriptions[0]));
            exit(1);
            break;
        case 1:
            write(2,error_descriptions[1],mx_strlen(error_descriptions[1]));
            write(2,details,mx_strlen(details));
            write(2,error_descriptions[2],mx_strlen(error_descriptions[2]));
            mx_strdel(&details);
            exit(1);
            break;
        case 2:
            write(2,error_descriptions[3],mx_strlen(error_descriptions[3]));
            exit(1);
            break;
        case 3:
            write(2,error_descriptions[4],mx_strlen(error_descriptions[4]));
            exit(1);
            break;
        case 4:
            write(2,error_descriptions[5],mx_strlen(error_descriptions[5]));
            exit(1);
            break;
        case 5:
            write(2,error_descriptions[6],mx_strlen(error_descriptions[6]));
            exit(1);
            break;
        default:
            break;
    }
}
