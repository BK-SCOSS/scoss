#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int n,m;
int C[30][30];
int X[30]; 
bool visited[30];
int T[30];
long long Count;
int minCost = INT_MAX;
void input(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> C[i][j];
            if(i!=j && minCost > C[i][j]) minCost = C[i][j];
        }
    }
}
void init(){
    visited[1] = true;
    X[1] = 1;
    T[1] = 0;
}

void Try(int k){
    for(int v=2;v<=n;v++){
        if(visited[v]==false){
            X[k] = v;
            T[k] = T[k-1]+C[X[k-1]][v];
            if(T[k]+(n-k+1)*minCost<=m){
                if(k<n){
                    visited[v] = true;
                    Try(k+1);
                    visited[v] = false;
                }
                else{
                    if(T[n]+C[X[n]][1] <= m) Count++;
                }
            }
        }
    }
}

int main(){
    input();
    init();
    Try(2);
    cout << Count << endl;
}