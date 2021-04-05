#include <bits/stdc++.h>

using namespace std;
#define MAX 1e6

int n, cost[16][16], m;
int x[16];

long long cmin = 1e7;
long long f;
int visit[16];

int countRes = 0;

void input(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            long long a;
            cin >> a;
            cost[i][j] = a;

        }
    }

}

int TRY(int k){
    for(int i = 1; i <= n; i++){
        if(!visit[i]){
            x[k] = i;
            visit[i] = 1;
            f += cost[x[k-1]][x[k]];
            if(k==n){
                if(f + cost[x[n]][x[1]] < m) {
                    countRes++;
                }
            }
            else{
                TRY(k+1);
            }
            visit[i]= 0;
            f -= cost[x[k-1]][x[k]];
        }
    }
}

void solve(){
    for(int i = 1; i <= n; i++){
        visit[i] = 0;
    }
    f = 0;
    x[1] = 1;
    visit[1] = 1;
    TRY(2);
    cout << countRes;
}

int main(){
    input();
   
    solve();
    return 0;
}
