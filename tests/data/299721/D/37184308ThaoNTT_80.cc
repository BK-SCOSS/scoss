//
//  main.cpp
//  TASK_ASSIGNMENT
//
//  Created by Nguyen Thi Thu Thao on 10/23/20.
//

#include <bits/stdc++.h>
using namespace std;
int N,M,K;int c[50][50];int x[50];int cmin=999999;
int cost=0;int STAFF[50];
int cost_best=99999999;
bool check(int v,int k){ // STAFF v and task K
    if (STAFF[v]+1<=K) return true;
    return false;
}
void solution(){
    cost_best=cost_best>cost?cost:cost_best;
}

void TRY(int k){
    for (int v=1;v<=M;v++){
        if (check(v,k)){
            x[k]=v;
            STAFF[v]++;
            cost=cost+ c[v][k];
            if (k==N) solution();
            else
            {
                if (cost + (N-k+1)*cmin < cost_best) TRY(k+1);
            }
            STAFF[v]--;
            cost=cost - c[v][k];
        }
    }
}
int main() {
    cin >> N >> M >> K;
    for (int i =1;i<=M;i++)
    for (int j=1;j<=N;j++)
    {
        cin >> c[i][j];
        cmin = c[i][j]< cmin ? c[i][j]:cmin;
    }
    for (int i=1;i<=M;i++) STAFF[i]=0;
    TRY(1);
    cout << cost_best;
    return 0;
}
