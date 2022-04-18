#include <stdio.h>
#include <stdlib.h>
#define maximum(a, b) ((a > b) ? a : b )

typedef struct Item {
  int weight;
  int value;
  char label[2];
}Item;

void fillKnapsack(Item *items, int **M, int rows, int cols){
  for (int i = 0; i < cols; i++) M[0][i] = 0;
  for (int j = 0; j < rows; j++) M[j][0] = 0;

  /* 
    Our matrix starts at [1][1], 
    [0][*] and [*][0] are dedicated to initial     
    conditions 
  */
  //Our items array starts at [0][0]
  for (int k = 1; k < rows; k++) {
    for (int w = 1; w < cols; w++){
      if (items[k-1].weight > w)
        M[k][w] = M[k-1][w];
      else {
        int wi = items[k-1].weight;
        M[k][w] = maximum(items[k-1].value + M[k-1][w-wi], M[k-1][w]);  
      }
    }
  }
}

void findSolution(int **M, int rows, int cols){
  
}

void finalMatrix(int **M, int rows, int cols){
  for (int i = 0; i < rows; i++){
    printf("|");
    for (int w = 0; w < cols; w++)
      printf("%d%c", M[i][w], " |"[w+1==cols]);
    printf("\n");
  }
}

int main(void) {
  int items_qtt = 0, knapsack_max_weight = 0;

  scanf("%d %d", &items_qtt, &knapsack_max_weight);
  int **M = (int **) malloc(sizeof(int*)*(items_qtt+1));
  Item *items = (Item*) malloc(sizeof(Item)*items_qtt);

  for (int i = 0; i < items_qtt; i++){
    scanf("%s %d %d", items[i].label, &items[i].value, &items[i].weight);
  }
  
  if (M == NULL || items == NULL){
    printf("Error during memory allocation!\n");
    exit(0);
  }
  for (int row = 0; row <= items_qtt; row++){
    M[row] = (int *) malloc(sizeof(int)*knapsack_max_weight);
    if (M[row] == NULL) {
      printf("Error during memory allocation!\n");
      exit(0);
    }
  }

  int rows = (items_qtt+1), cols = (knapsack_max_weight+1);
  fillKnapsack(items, M, rows, cols);

  finalMatrix(M, rows, cols);

  for (int q = 0; q < items_qtt; q++)
    printf("|%s|%.2d|%d|\n", items[q].label, items[q].value, items[q].weight);
  
  return 0;
}