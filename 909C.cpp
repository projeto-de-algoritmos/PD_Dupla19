// Problema: https://codeforces.com/contest/909/problem/C
// Linguagem: GNU C++20 (64) 

#define v vector <int>
#define vv vector <v>
#define vc vector <char>
const int modulo = 1e9 + 7;
#include <bits/stdc++.h>
using namespace std;

int main(){
    int N;

    cin >> N;

    vc comandos(N+1);

    for (int i = 1; i<= N; i++){
        cin >> comandos[i];
    }

    vv matriz(N+1, v(N+2));

    for (int i = 0; i<= N +1; i++){
        matriz[N][i] = 1; 
    }

    for (int i = N-1; i>=1;i--){
        int total = 0;
        for(int k =0; k<=N;k++){
            total+= matriz[i+1][k];
            total %=modulo;
            if(comandos[i] == 'f'){
                matriz[i][k] = matriz[i+1][k+1];
            }else{
                matriz[i][k] = total;
            }
        }

    }

    cout << matriz[1][0];
    return 0;

}
