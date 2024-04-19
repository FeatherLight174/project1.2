#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char ** argv){
  if(argc<3){
    printf("Usage:\n");
    printf("./main <input file> <output file>\n");
    exit(0);
  }

  char * input_file_name = argv[1];
  char * output_file_name = argv[2];

  FILE * input_file = fopen(input_file_name,"r");
  FILE * output_file = fopen(output_file_name,"w");
  
  if(input_file == NULL){
    printf("Error: unable to open input file %s\n",input_file_name);
    exit(0);
  }

  if(output_file == NULL){
    printf("Error: unable to open output file %s\n",output_file_name);
    fclose(input_file);
    exit(0);
  }

  /* YOUR CODE HERE */
  int initial_length = 0;
  int initial_width = 0;
  fscanf(input_file, "%d", &initial_length);
  fscanf(input_file, "%d", &initial_width);
  int **initial_matrix;
  initial_matrix = (int**)malloc(sizeof(int *)*initial_width);
  for(int i = 0; i < initial_width; i++){
    initial_matrix[i] = (int*)malloc(sizeof(int)*initial_length);
  }
  for(int i = 0; i < initial_width; i++){
    for(int j = 0; j < initial_length; j++){
      fscanf(input_file, "%d", &initial_matrix[i][j]);
    }
  }
  int kernel_length = 0;
  int kernel_width = 0;
  fscanf(input_file, "%d", &kernel_length);
  fscanf(input_file, "%d", &kernel_width);
  int **kernel_matrix;
  kernel_matrix = (int**)malloc(sizeof(int *)*kernel_width);
  for(int i = 0; i < kernel_width; i++){
    kernel_matrix[i] = (int*)malloc(sizeof(int)*kernel_length);
  }
  for(int i = 0; i < kernel_width; i++){
    for(int j = 0; j < kernel_length; j++){
      fscanf(input_file, "%d", &kernel_matrix[i][j]);
    }
  }
  int result_length = initial_length - kernel_length + 1;
  int result_width = initial_width - kernel_width + 1;
  int **result_matrix;
  result_matrix = (int**)malloc(sizeof(int *)*result_width);
  for(int i = 0; i < result_width; i++){
    result_matrix[i] = (int*)malloc(sizeof(int)*result_length);
  }
  for(int i = 0; i < result_width; i++){
    for(int j = 0; j < result_length; j++){
      result_matrix[i][j] = 0;
    }
  }
  for(int i = 0; i < result_width; i++){
    for(int j = 0; j < result_length; j++){
      for(int x = i; x < i+kernel_width; x++){
        for(int y = j; y < j+kernel_length; y++){
          result_matrix[i][j]+=initial_matrix[x][y]*kernel_matrix[x-i][y-j];
        }
      } 
    }
  }
  
  for(int i = 0; i < result_width; i++){
    for(int j = 0; j < result_length; j++){
      fprintf(output_file, "%d", result_matrix[i][j]);
      if(j == result_length - 1){
        fputs("\n", output_file);
      }
      else{
        fputs(" ", output_file);
      }
    }
  }

  for(int i = 0; i < initial_width; i++){
    free(initial_matrix[i]);
  }
  free(initial_matrix);
  for(int i = 0; i < kernel_width; i++){
    free(kernel_matrix[i]);
  }
  free(kernel_matrix);
  for(int i = 0; i < result_width; i++){
    free(result_matrix[i]);
  }
  free(result_matrix);


  fclose(input_file);
  fclose(output_file);

  return 0;
}
