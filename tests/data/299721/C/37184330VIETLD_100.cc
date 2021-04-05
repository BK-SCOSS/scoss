#include<iostream>
#include<bits/stdc++.h>
using namespace std;
const int N = 1000000; 
int n;
long long M;
int x[30];
int c[30][30];
long long f;
bool appear[N];
long long cmin;
vector<int> va;
void input(){
    cmin = N;
    cin >> n >> M;
    appear[0] = false;
    for(int i = 1;i<=n;i++){
        appear[i] = false;
        for(int j = 1;j<=n;j++){
            cin >> c[i][j];
            if(cmin > c[i][j] && c[i][j] !=0){
                cmin = c[i][j];
            }
        }
    }
}
void solution(){
    if(f+c[x[n]][x[1]] <= M){
        va.push_back(x[3]);
    }
}
void TRY(int k){
    int v;
    for(int v = 2;v<=n;v++){
        if(!appear[v]){
            x[k] = v;
            appear[v] = true;
            f = f + c[x[k-1]][x[k]];
            if(k==n){
                solution();
            }
            else{
                if(f + (n-k)*cmin < M){
                    TRY(k+1);
                }
            }
            appear[v] = false;
            f = f - c[x[k-1]][x[k]];
        }
    }
    
}
void solve(){
    x[1] = 1;
    TRY(2);
    cout << va.size();
}
 
int main(){
    input();
    solve();
    return 0;
}