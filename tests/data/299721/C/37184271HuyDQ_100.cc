#include <bits/stdc++.h>
using namespace std;
const int N = 100;
const int INF = 1000000000;
long long c[N][N];
long long cmin=INF;
int x[N];
int n;
int m;
int cnt=0;
bool appear[N];
long long f;
void input(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> c[i][j];
            if (i != j && cmin > c[i][j])
                cmin = c[i][j];
    }
    }
}
void solution(){
    if(f + c[x[n]][x[1]] <= m){
        cnt++;
    }
}
void TRY(int k){
    for(int v =1; v <= n; v++){
        if(!appear[v]){
            x[k] = v;
            appear[v] = true;
            f = f + c[x[k-1]][x[k]];
            if(k == n) solution();
            else{
                 if((n  - k) * cmin + f < m)
                    TRY(k+1);
            }
            appear[v] = false;
            f = f - c[x[k-1]][x[k]];
        }

    }
}
void solve(){
    for(int v = 1; v <= n; v++) appear[v] = false;
    f = 0;
    x[1] = 1;
    appear[1] = true;
    TRY(2);
    cout <<  cnt << endl;
}
int main(){
    input();
    // cout << cmin;
    solve();
}