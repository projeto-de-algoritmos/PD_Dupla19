// Problema: https://codeforces.com/contest/1324/problem/E
// Linguagem: GNU C++20 (64) 

#define v vector <int>
#define vv vector <v>
#include <bits/stdc++.h>
using namespace std;


int main(){

    int n, l, h,r;

    cin >> n >> h >> l >> r;

    v horas(n+1);

    for(int i=1; i<=n;i++){
        cin >> horas[i];
    }

    vv matriz(n+2, v(h+1));

    for(int k=0; k<h;k++){
        matriz[n+1][k] = 0;
    }

    for (int i=n; i>=1;i--){
        for(int k=0; k<h;k++){
            // ai 
            int horario1 = (k + horas[i])%h;
            int cont1;
            if (l<= horario1 && horario1 <= r){
                cont1= 1;
            } else{
                cont1= 0;
            }
            matriz[i][k] = matriz[i+1][horario1] + cont1;

            //ai-1
            int horario2 = (k + (horas[i] - 1))%h;
            int cont2;
            if (l<= horario2 && horario2 <= r){
                cont2= 1;
            } else{
                cont2= 0;
            }

            matriz[i][k] = max(matriz[i][k], matriz[i+1][horario2] + cont2);
        }
    }

    cout << matriz[1][0];
    return 0;


}



