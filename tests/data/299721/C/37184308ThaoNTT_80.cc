//
//  main.cpp
//  TSPCOUNT
//
//  Created by Nguyen Thi Thu Thao on 10/23/20.
//

#include <bits/stdc++.h>
using namespace std;
int N,M;int c[30][30];
int load=0;int x[30];bool appear[30];int co=0;int cmin=9999999;

void solution(){
//    cout << load+c[x[N]][1]<<endl;
    if (load + c[x[N]][1]<=M) co++;
}

void TRY(int k){
    for (int v=2;v<=N;v++){
    //    cout << v<<endl;
        if (!appear[v]){
            
            x[k]=v;
            appear[v]=true;
            load=c[x[k-1]][x[k]]+load;
    //        cout << "k:"<<k<<"v:"<<v<<"load:"<<load<<endl;
            if (k==N) solution();
            else {
                if (load + (N-k+1)*cmin < M) TRY(k+1);
            }
            appear[v]=false;
            load=load-c[x[k-1]][x[k]];
        }
    }
}

int main() {
    cin >> N >> M;
    for (int i=1;i<=N;i++)
    for (int j=1;j<=N;j++)
    {
        cin >> c[i][j];
        cmin = cmin > c[i][j] ? c[i][j]:cmin;
    }
    x[1]=1;
    for (int i=2;i<=N;i++) appear[i] = false;
    if (cmin*N>M ){cout << co ; return 0;}
    TRY(2);
    cout << co;
    return 0;
}
