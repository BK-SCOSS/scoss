#include<bits/stdc++.h>
using namespace std;

const int N = 20;
int n;
int m;
int c[N][N];
int c_max;
bool appear[N];
int dem;
int f;
int x[N];

void input(){
    cin >> n >> m;
    int tmp;
    for ( int i = 1; i <= n; i++){
        for ( int j = 1; j <= n; j++){
            cin >> tmp;
            c[i][j] = tmp;
            if ( i != j)
                c_max = min(c_max, c[i][j]);
        }
    }
}

void solution(){
    //cout << "dem = " << dem << endl;

    if ( f + c[x[n]][1] <= m)
        dem += 1;
}

void TRY( int k){
    for ( int v = 1; v <= n; v++){
        if ( !appear[v] ){
            x[k] = v;
            appear[v] = true;
            f += c[x[k-1]][x[k]];
            //cout << " k = " << k << "v = " << v <<" f = " << f << endl;
            if ( k == n)
                solution();
            else
            { 
                if (( f + c_max*( n-k )) <= m)
                    TRY(k+1);
            }
            appear[v] = false;
            f -= c[x[k-1]][x[k]];
        }
    }
}

int main(){
    memset(c, 0, sizeof(c));
    memset( appear, false, sizeof(appear));
    memset(x, 0, sizeof(x));
    dem = 0;
    c_max = 10000000;
    input();
    x[1] = 1;
    appear[1] = true;
    TRY(2);
    cout << dem << endl;
}