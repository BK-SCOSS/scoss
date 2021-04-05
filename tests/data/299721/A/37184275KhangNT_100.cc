#include <bits/stdc++.h>
#define MAX_N 100000
#define MAX_M 100000
using namespace std;
unsigned long long N,M,a[MAX_N],c=0,sum,T;
void input(){
    cin>>N>>M;
    for(int i=0;i<=N-1;i++){
        cin>>a[i];
    }
}
void solve(){
    for(int i=0;i<=N-1;i++){
    sum=0;
      for(int j=i;j<=N-1;j++){
             sum = sum + a[j];
             if(sum<=M)
             {c=c+1;
             }
             else break;
         }
    }
    cout<<c<<endl;
}
int main(){
    input();
    solve();
    return 0;
}