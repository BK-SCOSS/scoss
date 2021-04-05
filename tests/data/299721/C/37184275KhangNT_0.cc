#include <bits/stdc++.h>
#define MAX_N 15
#define MAX_M 1000000
using namespace std;
int N,M,c[MAX_N][MAX_N],o=0,x[MAX_N],cou;
bool assigned[MAX_N];
void input(){
    cin>>N>>M;
    for(int i=0;i<=N-1;i++){
        assigned[i]=false;
    }
    for(int i=0;i<=N-1;i++){
        for(int j=0;j<=N-1;j++)
            cin>>c[i][j];
    }
}
bool check(int v,int k){
    if(assigned[k]) {return false;}
    return true;
}
void solution(){
    if(o<=M)
    {cou = cou+1;}
}
void TRY(int k){
    for(int v=0;v<=N-1;v++){
        if(check(v,k)){
        x[k]=v;
        assigned[k]=true;
        o=o+c[k][v];
        if(k==N) solution();
        else TRY(k+1);
        o=o-c[k][v];
        assigned[k]=false;
        }
    }
    cout<<cou<<endl;
}
int main(){
    input();
    TRY(0);return 0;
}
