#include<iostream>

using namespace std;
const int N = 100;
int x[N];
int n;
bool appear[N];
int f, Q;
int c[30][30];
int fmin = 100000000;
int count_t;

void input(){
    cin >> n >> Q;
    for (int i = 1; i <= n ; i++)
        for (int j = 1; j <= n ; j++){
            cin >> c[i][j];
            if ( fmin > c[i][j] && i != j) fmin = c[i][j];
	}
}

bool check (int v, int k){
    if (appear[v] == true) return false;
    else return true;
}


void TRY(int k){
    for (int v = 2 ;v <= n; v++){
        if (check(v, k)){
              x[k] = v;
              appear[v] = true;

              f += c[x[k-1]][x[k]];
             // cout << x[k-1] << " " << x[k] << " " << c[x[k-1]][x[k]] << endl;
            if (Q > f + (n-k)*fmin){
                if (k == n ) {
                  //   cout << endl<< f + c[x[k]][x[1]] << endl;
                    if (Q >= f + c[x[k]][x[1]]) count_t++;
                 }
                 else {
                 TRY(k+1);
                }
                 }
                
        f -= c[x[k-1]][x[k]];
        appear[v] = false;
        }
    }
}

int main (){
    x[1] = 1; f = 0 ; 
    count_t = 0;
    input();
    for (int v = 1; v <= n; v++)
        appear[v] = false;
    TRY(2);
    cout << endl << count_t << endl;
    return 0;
}