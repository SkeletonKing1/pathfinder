#include "pathfinder.h"

void mx_reinit(t_island *islands, int size) {
     for (int i = 0; i < size; i++) {
        islands[i].mark = 2147483647;
        islands[i].is_visited = false;
    }
}

void try_to_find_another_shortest_root(t_island *islands, int **roots_matrix, int matrix_size, int begin_index, int end, int *visited_islands, int size);

void try_to_find_another_shortest_root_with_deleted_bond(t_island *islands, int **roots_matrix,int matrix_size, int begin_index, int end) {
   // printf("%s\n",islands[begin_index].name);
//    printf("%s\n",islands[end].name);

  int visited_islands[matrix_size];
  visited_islands[0] = end + 1;
  int k = 1; 
  int weight = islands[end].mark; 
  int temp_end = end;
  int iteration_count = 0;
      
  while (temp_end != begin_index && iteration_count < matrix_size + 1) 
  {
    for (int i = 0; i<matrix_size; i++) {
   //   printf("%s - %s\n",islands[temp_end].name,islands[i].name);
      if (roots_matrix[i][temp_end] != 0)  
      {
     //   printf("%s - %s\n",islands[temp_end].name,islands[i].name);
    //    printf("%d this mark\n", weight);
     //   printf("%d root\n",roots_matrix[i][temp_end]);
     //   printf("%d other mark\n",islands[i].mark);
        int temp = weight - roots_matrix[i][temp_end]; 
        if (temp == islands[i].mark) 
        {                
          weight = temp; 
          temp_end = i;      
          visited_islands[k] = i + 1; 
          k++;
          break;
        }
      }
    }
    iteration_count++;
  }
  if (iteration_count > matrix_size)
      return;
  
  
  printf("=======================================\n");
  printf("Path: %s -> %s\n",islands[begin_index].name, islands[end].name);
  printf("Route: ");
  for (int i = k - 1; i >= 0; i--) {
      if (i - 1 >= 0) {
          printf("%s -> ", islands[visited_islands[i] - 1].name);
          continue;
      }
    printf("%s\n", islands[visited_islands[i] - 1].name);
  }
  printf("Distance: ");
  for (int i = k - 2,j = 0; i >= 0; i--) {
      if (i - 1 >= 0) {
          printf("%d + ",islands[visited_islands[i] - 1].mark - islands[visited_islands[i + 1] - 1].mark);
          j++;
          continue;
      }
      if (j == 0)
          printf("%d\n",islands[visited_islands[i] - 1].mark - islands[visited_islands[i + 1] - 1].mark);
      else 
          printf("%d = %d\n",islands[visited_islands[i] - 1].mark - islands[visited_islands[i + 1] - 1].mark,islands[visited_islands[i] - 1].mark);
  }
  printf("=======================================\n");
        
      if (k > 2)
          try_to_find_another_shortest_root(islands, roots_matrix, matrix_size, begin_index, end, visited_islands,k);
}
void try_to_find_another_shortest_root(t_island *islands, int **roots_matrix, int matrix_size, int begin_index, int end, int *visited_islands, int size) {
   // int last_visited_islands[matrix_size];
    
    for (int i = 0; i < size - 2; i++) {
    int temp_marks[matrix_size];
  //  printf("NEW ITERATION\n");
    for (int j = 0; j < matrix_size; j++) {
       temp_marks[j] = islands[j].mark;
    //  printf("%d  ",temp_marks[j]);
   }
 //  printf("\n");
  // int test = 0;
   for (int k = i; k < size;) {
       
   temp_marks[visited_islands[size - 2 - i] - 1] = 2147483647;
   
  // for (int bla = 0; bla < matrix_size; bla++) {
  //     printf("%d - %s  ",temp_marks[bla],islands[bla].name);
  // }
  // printf("\n");
   int temp_visited_islands[matrix_size]; 
   temp_visited_islands[0] = end + 1; 
   int temp_k = 1; 
   int weight = islands[end].mark; 
   int temp_end = end;
   int iteration_count = 0;
  while (temp_end != begin_index && iteration_count < matrix_size + 1) 
  {
      
    for (int count = 0; count<matrix_size; count++) {
      if (roots_matrix[count][temp_end] != 0)   
      {
         
        int temp = weight - roots_matrix[count][temp_end];
        
        if (temp == temp_marks[count]) 
        {                
          weight = temp; 
          temp_end = count;      
          temp_visited_islands[temp_k] = count + 1; 
          temp_k++;
          break;
        }
      }
    }
      iteration_count++;
  }

  bool is_same = true;
  for (int i = 0; i < temp_k; i++) {
      if (visited_islands[i] != temp_visited_islands[i])
          is_same = false;
  }
  if (temp_end != begin_index) {
      break;
  }
  else if (is_same)
      continue;
  
//for (int i = temp_k - 1; i >= 0; i--)
 //   printf("%d ", temp_visited_islands[i] - 1);
 // printf("\n");
  
  for (int island = 0; island < matrix_size; island++) {
  if (islands[temp_visited_islands[temp_k - 2 - i + (size - temp_k)] - 1].name == islands[island].name)
      temp_marks[island] = 2147483647;
  }  
   //  for (int bla = 0; bla < matrix_size; bla++) {
    //  printf("%d - %s  ",temp_marks[bla],islands[bla].name);
   //}
  // printf("\n");
   
  printf("=======================================\n");
  printf("Path: %s -> %s\n",islands[begin_index].name, islands[end].name);
  printf("Route: ");
  for (int i = temp_k - 1; i >= 0; i--) {
      if (i - 1 >= 0) {
          printf("%s -> ", islands[temp_visited_islands[i] - 1].name);
          continue;
      }
    printf("%s\n", islands[temp_visited_islands[i] - 1].name);
  }
  printf("Distance: ");
  for (int i = temp_k - 2,j = 0; i >= 0; i--) {
      if (i - 1 >= 0) {
          printf("%d + ",islands[temp_visited_islands[i] - 1].mark - islands[temp_visited_islands[i + 1] - 1].mark);
          j++;
          continue;
      }
      if (j == 0)
          printf("%d\n",islands[temp_visited_islands[i] - 1].mark - islands[temp_visited_islands[i + 1] - 1].mark);
      else 
          printf("%d = %d\n",islands[temp_visited_islands[i] - 1].mark - islands[temp_visited_islands[i + 1] - 1].mark,islands[temp_visited_islands[i] - 1].mark);
  }
  printf("=======================================\n");
//  if (test > 3)
 //     exit(1);
 // test++;
   } 
    }
}
void mx_algo(t_island *islands, int **roots_matrix, int matrix_size) {
    for (int verticle = 0; verticle < matrix_size; verticle++) {
    int min, minindex, temp;
    int begin_index = verticle;
    islands[begin_index].is_visited = 0;
    islands[begin_index].mark = 0;
  
    do {
    minindex = 2147483647;
    min = 2147483647;
    for (int i = 0; i<matrix_size; i++) {
        
      if (islands[i].is_visited == 0 && islands[i].mark < min)
      { 
        min = islands[i].mark;
        minindex = i;
      }
    }
    if (minindex != 2147483647)
    {
      for (int i = 0; i<matrix_size; i++)
      {
        if (roots_matrix[minindex][i] > 0)
        {
          temp = min + roots_matrix[minindex][i];
          if (temp < islands[i].mark)
          {
            islands[i].mark = temp;
          }
        }
      }
      islands[minindex].is_visited = 1;
    }
    } while (minindex < 2147483647);
  
  for (int end = begin_index + 1; end < matrix_size; end++) { 
  int visited_islands[matrix_size];
  visited_islands[0] = end + 1;
  int k = 1; 
  int weight = islands[end].mark; 
  int temp_end = end;
  int iteration_count = 0;
  while (temp_end != begin_index && iteration_count < matrix_size + 1) 
  {
    for (int i = 0; i<matrix_size; i++) {
      // printf("this %s - other %s  root = %d   ",islands[temp_end].name,islands[i].name,roots_matrix[temp_end][i]);
      // printf("\n");
    //       for (int i = 0; i < matrix_size; i++) {
     //   for (int j = 0; j < matrix_size; j++) {
    //        printf("%d  ",roots_matrix[i][j]); 
    //    }
    //    printf("\n");
    
      if (roots_matrix[i][temp_end] != 0)  
      {
     //    printf("have root this %s - other %s   ",islands[temp_end].name,islands[i].name);
     //     printf("\n");
        int temp = weight - roots_matrix[i][temp_end]; 
        if (temp == islands[i].mark) //&& mx_no_other_shortest_roots(islands, roots_matrix, matrix_size, begin_index,temp_end,i,weight)) 
        {                
          weight = temp; 
          temp_end = i;      
          visited_islands[k] = i + 1; 
          k++;
          break;
        }
      }
    }
    iteration_count++;
  }
  if (temp_end != begin_index)
      break;
  
  printf("=======================================\n");
  printf("Path: %s -> %s\n",islands[begin_index].name, islands[end].name);
  printf("Route: ");
  for (int i = k - 1; i >= 0; i--) {
      if (i - 1 >= 0) {
          printf("%s -> ", islands[visited_islands[i] - 1].name);
          continue;
      }
    printf("%s\n", islands[visited_islands[i] - 1].name);
  }
  printf("Distance: ");
  for (int i = k - 2,j = 0; i >= 0; i--) {
      if (i - 1 >= 0) {
          printf("%d + ",islands[visited_islands[i] - 1].mark - islands[visited_islands[i + 1] - 1].mark);
          j++;
          continue;
      }
      if (j == 0)
          printf("%d\n",islands[visited_islands[i] - 1].mark - islands[visited_islands[i + 1] - 1].mark);
      else 
          printf("%d = %d\n",islands[visited_islands[i] - 1].mark - islands[visited_islands[i + 1] - 1].mark,islands[visited_islands[i] - 1].mark);
  }
  printf("=======================================\n");
        
      if (k > 2)
          try_to_find_another_shortest_root(islands, roots_matrix, matrix_size, begin_index, end, visited_islands,k);
      else if (k == 2) {
          int temp = roots_matrix[begin_index][end];
          roots_matrix[begin_index][end] = 0;
          roots_matrix[end][begin_index] = 0;
          try_to_find_another_shortest_root_with_deleted_bond(islands,roots_matrix,matrix_size,begin_index,end);
          roots_matrix[begin_index][end] = temp;
          roots_matrix[end][begin_index] = temp;
      }
    }
     mx_reinit(islands,matrix_size);
}
}

void mx_run(char **lines) {
    int matrix_size = mx_atoi(lines[0]);
    t_island *islands = mx_get_islands_arr((const char **)lines);
    for (int i = 0; i < matrix_size; i++) 
        printf("%s ",islands[i].name);
    printf("\n");
    int **roots_matrix = mx_convert_roots_to_matrix(lines,islands);
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            printf("%d  ",roots_matrix[i][j]); 
        }
        printf("\n");
    }
    mx_algo(islands, roots_matrix, matrix_size);
     //free used memory
    for (int i = 0; i < matrix_size; i++)
        free(roots_matrix[i]);
    free(roots_matrix);
    
    mx_del_strarr(&lines);
    
    for (int i = 0;i < matrix_size; i++) {
        mx_strdel(&islands[i].name);
    }
    free(islands);
    
}

