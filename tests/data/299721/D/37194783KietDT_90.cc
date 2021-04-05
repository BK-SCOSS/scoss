#include<iostream>

using namespace std;
const int N = 100;
int x[N];
int n, m, Q;
bool appear[N][N];
int load[N];
int f;
int c[31][31];
int cmin = 1000000000;
int fmin = 100000000;

void input(){
    cin >> n >> m >> Q;
    for (int i = 1; i <= m ; i++)
        for (int j = 1; j <= n ; j++){
            cin >> c[i][j];//i la gvien// j la bai hoc 
            if ( fmin > c[i][j] ) fmin = c[i][j];
	}
}

bool check (int v, int k){
   
    if (appear[v][k] == false && load[v] < Q)
        return true;
    else return false;
}

void solution(int k){
   // cout << f << endl;
    if (f < cmin ) cmin =f;
}

//m la giao vien
// n la bai hoc 

void TRY(int k){
    for (int v = 1 ;v <= m; v++){
        if (check(v, k)){
              x[k] = v;
              appear[v][k] = true;

              if (v <= m) load[v] ++;
              else load[v] --;
              //cout << "kk" <<load[v] <<"kk";

              f += c[x[k]][k];
             // cout << x[k] << " " << k << " " << c[x[k]][k] << endl;
             if (cmin > f + (n-k)*fmin){
                 if (k == n) solution(k);
                 else {
                 TRY(k+1);
              }
        }
        if (v <= m) load[v] = load[v] -1;
        else load[v] = load[v] + 1;
        f -= c[x[k]][k];
        appear[v][k] = false;
        }
    }
}

int main (){
    x[0] = 0; f = 0; 
    input();
    for (int v = 1; v <= m; v++){
        for (int k = 1; k <= n; k++)
                appear[v][k] = false;
                load [v] = 0;
    }
    TRY(1);
    cout << cmin << endl;
    return 0;
}