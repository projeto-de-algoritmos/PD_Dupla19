#include <limits.h> //supports INT_MIN
#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ((a > b) ? a : b)

int *pre, MSC = INT_MIN, *solution;
int longestSubsequenceIndex = -1;

void computeSubsequenceLength(int *L, int *A, int n) {
  for (int j = 1; j < n; j++) {
    L[j] = 1;
    pre[j] = 0;
    for (int i = 1; i < j; i++) {
      if (A[i] < A[j] && (L[i] + 1) > L[j]) {
        L[j] = L[i] + 1;
        pre[j] = i;
      }
    }
    if (L[j] > MSC) {
      MSC = L[j];
      longestSubsequenceIndex = j;
    }
  }
}

void findSubsequence(int j, int *A) {
  if (j == 0)
    return;
  else {
    printf("%d ", A[j]);
    findSubsequence(pre[j], A);
  }
  printf("\n");
  return;
}

int main(void) {
  int qtt = 0, aux = 0, k = 1;

  scanf("%d", &qtt);
  int *A = (int *) malloc(sizeof(int)*(qtt+1));
  int *L = (int *)malloc(sizeof(int) * (qtt+1));
  pre = (int *)malloc(sizeof(int) * (qtt+1));

  A[0] = 0;
  L[0] = 0;
  pre[0] = 0;
  while (qtt--) {
    scanf("%d", &aux);
    A[k++] = aux;
  }

  computeSubsequenceLength(L, A, k);
  solution = (int *)malloc(sizeof(int) * MSC);

  printf("Tamanho da maior subsequência crescente: %d\n", MSC);
  printf("Maior subsequência crescente:\n");
  findSubsequence(longestSubsequenceIndex, A);

  free(A);
  free(L);
  free(pre);
  free(solution);

  return 0;
}