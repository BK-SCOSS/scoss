#include <bits/stdc++.h>
    using namespace std;
    const int N=1000;
    bool appear[N];
    long long f;
    int n,m,cmin;;
    int c[N][N];
    int x[N];
    int countt = 0;
    bool check(int v){
    if (appear[v]) return false;
    return true;
}


    void solution(){
        if (f+c[x[n]][x[1]] <= m) countt++;
    }
    void input(){
        cin >> n >> m;
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++){
                cin >> c[i][j];
                if (c[i][j]<cmin && i!=j) cmin=c[i][j];
            }
    }
    void TRY(int k){
        for (int v=1;v<=n;v++){
            if (check(v)){
                x[k]=v;
                appear[v]=true;
                f=f+c[x[k-1]][x[k]];
                if (k==n){
                    solution();
                }
                else{
                    if (f+cmin*(n-k+1) <= m)
                    TRY(k+1);
                }
                appear[v]=false;
                f=f-c[x[k-1]][x[k]];
            }
        }
    }
    void solve(){
        x[1]=1;
        cmin=9999999;
        appear[1]=true;
        input();
        TRY(2);
        cout << countt << endl;
    }
    int main(){
        solve();
    }
