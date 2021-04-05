#include<bits/stdc++.h>
using namespace std;

const int N = 50;
int n, m,K;
int c[N][N];
int load[N];
int f;
int x[N];
int f_min;
int c_min;

void input(){
    cin >> n >>m >>K;
    for ( int i = 1; i <= m; i++ ){
        for ( int j = 1; j <= n; j++ ){
            cin >> c[i][j];
            c_min = min(c_min, c[i][j]);
        }
    }
}
void solution(){
    f_min = min(f_min, f);
}
int check( int v, int k){
    return ( load[v] < K);
}
void TRY( int k){
    for ( int v = 1; v <= m; v++){
        if ( check ( v, k)){
            //x[k] = v;
            load[v] += 1;
            f += c[v][k];
            if ( k == n)
                solution();
            else
            {
                if (( f + c_min*(n-k) ) < f_min)
                    TRY(k+1);
            }
            load[v] -= 1;
            f -= c[v][k];
        }
    }
}

int main(){
    memset(c, 0, sizeof(c));
    memset(load, 0, sizeof(load));
    //memset(x, 0, sizeof(x));
    f = 0;
    f_min = 1000000;
    c_min = 1000000;
    input();
    TRY(1);
    cout << f_min << endl;
}
