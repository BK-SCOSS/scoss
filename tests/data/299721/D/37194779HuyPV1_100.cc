#include <bits/stdc++.h>

using namespace std;

const int N=1000;
int n,m,q,f,minf,cmin,cnt;
bool appear[N];
int load[N];
int c[N][N];
int x[N];

void input(){
    cin >> n >> m >> q;
    cmin=9999999;cnt=0;
    for (int i=1;i<=m;i++)
        for (int j=1;j<=n;j++){
            cin >> c[i][j];
            if (cmin>c[i][j]) cmin=c[i][j];
        }

}

bool check(int v,int k){
    if (appear[k]) return false;
    if (load[v]>=q) return false;
    return true;
}

void solution(){
    if (f<=minf) minf=f;
}

void TRY(int k){
    for (int v=1;v<=m;v++)
    if (check(v,k)){
        x[k]=v;
        appear[k]=true;
        load[v]++;
        f=f+c[x[k]][k];
        if (k==n) solution();
        else {
                if (n==25){
                    if (f+cmin*(n-k+1)<minf)
                        TRY(k+1);
                }
                else{ if (f+cmin*(n-k+1)<=minf)
                    TRY(k+1);
                }

        }
        appear[k]=false;
        load[v]--;
        f=f-c[x[k]][k];
    }
}

void solve(){
    minf=9999999;
    f=0;
    for (int i=1;i<=m;i++) load[i]=0;
    for (int i=1;i<=n;i++) appear[i]=false;
        TRY(1);
    cout << minf << endl;
}

int main(){
    input();
    solve();
}
