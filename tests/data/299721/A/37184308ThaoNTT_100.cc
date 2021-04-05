//
//  main.cpp
//  SUBSEQ
//
//  Created by Nguyen Thi Thu Thao on 10/23/20.
//

#include <bits/stdc++.h>
using namespace std;
int N,M;int a[10001];int co=0;
void input(){
    cin >> N>>M;
    for (int i=1;i<=N;i++){
        cin >> a[i];
    }
}
void solve(){
    for (int i=1;i<=N;i++){
        int tong=0;
  //      cout << a[i]<<endl;
        for (int j=i;j<=N;j++){
            tong=tong+a[j];
         //   cout <<"Tong:"<< tong<<endl;
      //      cout << "a[j]"<<a[j]<<"vi tri thu"<<j<<endl;
            
            if (tong <= M) co++;
      //      cout << "count:"<<co<<endl;
        }
    }
}

int main() {
    input();
    solve();
    cout <<co;
    return 0;
}
