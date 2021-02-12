#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_cyclic(int** adjacency_arrays, int number_of_vertices);
void add_edge(int** adjacency_arrays, int number_of_vertices, int source_vertice, int destination_vertice);

int main(){
  int number_of_vertices;
  printf("Please enter number of vertices\n");
  scanf("%d", &number_of_vertices);
  int** adjacency_arrays = (int**)malloc(sizeof(int*) * number_of_vertices);
  for(int i = 0; i < number_of_vertices; i++){
    adjacency_arrays[i] = (int*)malloc(sizeof(int) * number_of_vertices);
    for(int j = 0; j < number_of_vertices; j++){
      adjacency_arrays[i][j] = -1;
    }
  }

  bool cond = true;
  while(cond){
    printf("Please enter an edge or type a negative value to finish adding edges\n");
    int vertice1;
    printf("Please enter source vertice:");
    scanf("%d", &vertice1);
    if(vertice1 < 0){
      cond = false;
      printf("Finished edge adding...\n");
    }
    else if(vertice1 >= number_of_vertices){
      printf("There is no such vertice. Please try again\n");
    }
    else{
      int vertice2;
      printf("Please enter destination vertice:");
      scanf("%d", &vertice2);
      if(vertice2 < 0 || vertice2 >= number_of_vertices){
        printf("There is no such vertice. Please try again\n");
      }
      else{
        add_edge(adjacency_arrays, number_of_vertices, vertice1, vertice2);
        printf("Edge added from %d to %d\n", vertice1, vertice2);
      }
    }
  }

  printf("Adjacency Arrays:\n");
  for(int i = 0; i < number_of_vertices; i++){
    printf("Edges from %d: ", i);
    for(int j = 0; j < number_of_vertices; j++){
      if(adjacency_arrays[i][j] == -1){
        break;
      }
      else{
        printf("%d ", adjacency_arrays[i][j]);
      }
    }
    printf("\n");
  }

  if(is_cyclic(adjacency_arrays, number_of_vertices)){
    printf("Graph contains cycle.\n");
  }
  else{
    printf("Graph does not contain any cycle.\n");
  }

  for(int i = 0; i < number_of_vertices; i++){
    free(adjacency_arrays[i]);
  }
  free(adjacency_arrays);
  return 0;
}

void add_edge(int** adjacency_arrays, int number_of_vertices, int source_vertice, int destination_vertice){
  for(int i = 0; i < number_of_vertices; i++){
    if(adjacency_arrays[source_vertice][i] == -1){
      adjacency_arrays[source_vertice][i] = destination_vertice;
      break;
    }
  }
}

bool is_cyclic_helper(int** adjacency_arrays, int number_of_vertices, int v, bool* visited, bool* rec_stack){
  if(visited[v] == false){
    visited[v] = true;
    rec_stack[v] = true;

    int* current = adjacency_arrays[v];
    for(int i = 0; i < number_of_vertices; i++){
      if(current[i] == -1){
        break;
      }
      if(!visited[current[i]] && is_cyclic_helper(adjacency_arrays, number_of_vertices, current[i], visited, rec_stack)){
        return true;
      }
      else if(rec_stack[current[i]]){
        return true;
      }
    }
  }
  rec_stack[v] = false;
  return false;
}

bool is_cyclic(int** adjacency_arrays, int number_of_vertices){
  bool* visited = (bool*)malloc(number_of_vertices * sizeof(bool));
  bool* rec_stack = (bool*)malloc(number_of_vertices * sizeof(bool));

  for(int i = 0; i < number_of_vertices; i++){
    visited[i] = false;
    rec_stack[i] = false;
  }

  for(int j = 0; j < number_of_vertices; j++){
    if(is_cyclic_helper(adjacency_arrays, number_of_vertices, j, visited, rec_stack)){
      return true;
    }
  }
  free(visited);
  free(rec_stack);
  return false;
}
