// Problema: https://codeforces.com/problemset/problem/711/C
// Linguagem:  GNU C11

#include <stdio.h>
#include <stdlib.h>
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _b : _a; })

const long long INF = 1e15;
long long mem[102][102][102];
long long litres[102][102];
int *trees;
int n, m, k;

void initialize(){
	for(int i=0;i<=n;i++){
	       for(int j=0;j<=k;j++){
	           for(int l=0;l<=m;l++){
	               mem[i][j][l]=INF;
	           }
	       }
	}
}

void paint_trees(){

	if (trees[1] == 0){
		for (int i = 1; i <= m; i++){
			mem[1][1][i] = litres[1][i];
		}
	} else {
		mem[1][1][trees[1]] = 0;
	}

	for (int i = 2; i <= n; i++){
		for (int j = 1; j <= k; j++){
			if (!trees[i]){
				for (int p = 1; p <= m; p++){
					mem[i][j][p] = min(mem[i][j][p], mem[i-1][j][p]+litres[i][p]);

					for (int p1 = 1; p1 <= m; p1++){

						if (p1 == p) 
							continue;

						mem[i][j][p] = min(mem[i][j][p], mem[i-1][j-1][p1] + litres[i][p]);
					}
				}
			} else {
				mem[i][j][trees[i]] = min(mem[i][j][trees[i]], mem[i-1][j][trees[i]]);

				for (int p1 = 1; p1 <= m; p1++){
					if (p1 == trees[i]) 
						continue;

					mem[i][j][trees[i]] = min(mem[i][j][trees[i]], mem[i-1][j-1][p1]);
				}
			}
		}
	}
}

long long find_solution(){
	long long solution = INF;

	for (int j = 1; j <= m; j++)
		solution = min(solution, mem[n][k][j]);

	if (solution != INF)
		return solution;
	else
		return -1;
}

int main(){
	scanf("%d %d %d", &n, &m, &k);

	trees = (int *) malloc(sizeof(int)*n);

	initialize();
	
	for (int i=1; i<=n; i++)
		scanf("%d", &trees[i]);

	for(int i=1; i<=n; i++){
       		for(int j=1; j<=m; j++){
           		scanf("%lld", &litres[i][j]);
       		}
   	}

	paint_trees();

	printf("%lld\n", find_solution());

	free(trees);
	return 0;
}
