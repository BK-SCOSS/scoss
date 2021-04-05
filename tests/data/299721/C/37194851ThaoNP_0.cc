#include <bits/stdc++.h>
using namespace std;

int N;
int M;
int c[15][15];
int tour[15]; 
int cnt=0;
int tourLen;
bool appear[15];


void input() {
    cin >> N >> M;
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) cin >> c[i][j];
    }
}

void solution() {
    cnt++;
    cout << "Solution " << cnt << ": ";
    for (int i=1;i<=N;i++) cout << tour[i] << " "; cout << endl;
}

void TRY(int k) {
    for (int v=1;v<N;v++) {
        if (!appear[v]) {
            tour[k] = v;
            appear[v] = true;
            if (k==N) solution();
            else TRY(k+1);
            appear[v] = false;
        }
    }
}

int main() {
    input();
    TRY(1);
    return 0;
}