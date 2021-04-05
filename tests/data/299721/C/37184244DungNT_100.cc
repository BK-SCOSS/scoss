#include<iostream>
using namespace std;
const long INF = 100000000000;
const int N = 100;
#define ll long long
ll c[N][N];
ll c_min;
int x[N];
int n,m, M;
ll f;
ll min_f; // minimal distance.
ll cnt = 0;

bool appear[N];
 
void solution() {
    // if(f+c[x[n]][x[1]] < min_f) {
    //     min_f = f + c[x[n]][x[1]];
    // // }
    // cout << "solution: " << endl;
    // for(int i = 1; i<= n ; i++) {
    //     cout << x[i] << " ";
    // }
    // cout << endl;
    if ( f + c[x[n]][x[1]] <= m) {
        cnt += 1;
    }
}
 
void input() {
    cin >> n >> m;
    c_min = INF;
 
    for(int i =1; i<= n; i++) {
        for(int j = 1; j <=n; j++)
        // c[i][j] = INF;
        {
            int tmp;
            cin >> tmp;
            if (tmp < c_min && tmp!= 0) {
                c_min = tmp;
            }
            c[i][j] = tmp;
        }
 
    }
 
    // for (int k = 1; k<= m ; k++) {
    //     int i, j;
    //     ll w;
    //     cin >> i >> j >> w;
    //     c[i][j] = w;
    //     c_min = w < c_min ? w: c_min;
    // }
}
 
void TRY(int k) {
    for(int v = 1; v<= n ; v++) 
    if(!appear[v]) {
        x[k] = v;
        appear[v] = true;
        f = f + c[x[k-1]][x[k]];
        if(k == n) solution();
        else {
            if(f+ c_min*(n-k) < m)
            TRY(k+1);
        }
        // x[k] = 0;
        appear[v] = false;
        f = f - c[x[k-1]][x[k]];
    }
}
 
void solve() {
    for(int v = 1; v <= n; v++) appear[v] = false;
    f = 0;
    x[1] = 1;
    appear[1] = true;
    // min_f = INF;
    TRY(2);
    cout << cnt << endl;
}
 
int main() {
    input();
    // cout << " cmin: " << c_min << endl;
    solve();
}

