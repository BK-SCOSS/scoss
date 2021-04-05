#include <bits/stdc++.h>

using namespace std;

const int N=1000;
int n,m,cmin,f,cnt;
int c[N][N];
int x[N];
bool appear[N];

void input(){
    cin >> n >> m;
    cmin=9999999;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            cin >> c[i][j];
            if (cmin>c[i][j] && i!=j) cmin=c[i][j];
        }
}

void solution(){
    if (f+c[x[n]][x[1]]<=m) cnt++;
}

void TRY(int k){
    for(int v =1; v <= n; v++){
        if(!appear[v]){
            x[k] = v;
            appear[v] = true;
            f = f + c[x[k-1]][x[k]];
            if(k == n) solution();
            else{
                if(f + cmin*(n-k+1) <= m)
                    TRY(k+1);
            }
            appear[v] = false;
            f = f - c[x[k-1]][x[k]];
        }

    }
}

void solve(){
    cnt=0;
    for(int v = 1; v <= n; v++) appear[v] = false;
    f = 0;
    x[1] = 1;
    appear[1] = true;
    TRY(2);
    cout <<  cnt << endl;
}

int main(){
    input();
    solve();
}
