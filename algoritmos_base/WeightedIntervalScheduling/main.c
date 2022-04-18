#include <stdio.h>
#include <stdlib.h>
#define less(a, b) (a < b)
#define exch(a, b) {job temp = a; a = b; b = temp;}

typedef struct job {
  char label[2];
  int initialTime;
  int finishTime;
  int weight;
} job;

int *M;
job *jobs;

int maximum(int a, int b){
  return (a > b) ? a : b;
}

int equ(int jobIndex){
  for (int i = jobIndex-1; i >= 0; i--)
    if (jobs[i].finishTime <= jobs[jobIndex].initialTime)
      return i;
  return 0;
}

void merge(job *v, int l, int r1, int r2) {
  job *v2 = (job *)malloc(sizeof(job) * (r2 - l + 1));
  int k = 0, i = l, j = r1 + 1;

  while (i <= r1 && j <= r2) {
    if (less(v[i].finishTime, v[j].finishTime))
      v2[k++] = v[i++];
    else
      v2[k++] = v[j++];
  }

  while (i <= r1)
    v2[k++] = v[i++];

  while (j <= r2)
    v2[k++] = v[j++];

  k = 0;

  for (i = l; i <= r2; i++)
    v[i] = v2[k++];

  free(v2);
}

void mergeSort(job *v, int l, int r) {
  if (l >= r)
    return;
  int middle = (r + l) / 2;

  mergeSort(v, l, middle);
  mergeSort(v, middle + 1, r);
  merge(v, l, middle, r);
}

int computeOpt(int jobIndex){
  if (M[jobIndex] == -1)
    M[jobIndex] = maximum(jobs[jobIndex].weight + computeOpt(equ(jobIndex)), computeOpt(jobIndex-1));
  return M[jobIndex];
}

void printScheduling(int jobIndex){
  if (jobIndex == 0)
    printf("\n");
  else if ((M[jobIndex] + M[equ(jobIndex)]) > M[jobIndex-1]){
    printf("%s ", jobs[jobIndex].label);
    printScheduling(equ(jobIndex));
  }
  else
    printScheduling(jobIndex-1);
}

int main(void) {
  int tasks = -1;

  while (tasks) {
    printf("Digite o número de tarefas ou 0 para sair:\n>");
    scanf("%d", &tasks);

    if (!tasks)
      exit(0);

    M = (int *) malloc(sizeof(int)*(tasks+1));
    jobs = (job *)malloc(sizeof(job)*(tasks+1));

    M[0] = 0;
    for (int i = 1; i <= tasks; i++) {
      M[i] = -1;
      printf("(Tarefa %d) Digite o nome, os tempos de início e fim e o peso:\n>",
             i + 1);
      scanf("%s %d %d %d", jobs[i].label, &jobs[i].initialTime,
            &jobs[i].finishTime, &jobs[i].weight);
    }
    
    mergeSort(jobs, 1, tasks);
    int totalWeight = computeOpt(tasks);
    printf("Total weight = %d\n", totalWeight);
    printf("Jobs incluídos:\n");
    printScheduling(tasks);
  }

  free(jobs);
  free(M);
  return 0;
}