
#include <bits/stdc++.h>
#define MAX 999999999
 
using namespace std;

int n,m,k,c[40][40];
int cm = MAX;
int ct[40], tc = 0, ans = MAX;
 
bool ktra(int i, int v){
    if (ct[v]+1>k) return true;
   //if (ct[v] + (n-i)/m > k) return true;
    return false;
}
 
void sol(){
    ans = ans < tc ? ans : tc;
}

void dequy(int i){
    for (int v=1; v<=m; v++) {
        if (!ktra(i,v)) {
            ct[v]+=1;
            tc = tc + c[v][i];
            if (i==n) {
                sol();
            } else {
                if (tc+cm*(n-i) < ans) dequy(i+1);
            }
            ct[v]-=1;
            tc = tc - c[v][i];
        }
    }
}
 
int main() {
    cin >> n >> m >> k;
    for (int i=1; i<=m; i++) {
        for (int j=1; j<=n; j++) {
            cin >> c[i][j];
            if (cm > c[i][j]) {
                cm = c[i][j];
            }
        }
    }
    dequy(1);
    cout << ans;
    return 0;
}