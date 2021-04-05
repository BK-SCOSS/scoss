#include <bits/stdc++.h>
#define MAX_N 1000000
using namespace std;
unsigned long long N,a[MAX_N],S;
void input(){
    cin>>N;
    for(int i=0;i<=N-1;i++){
        cin>>a[i];
    }
}
unsigned long long add_MOD(unsigned long long a,unsigned long long b){
    unsigned long long c;
    c=(10^9+7)-a;
    if(b<c){
        return a+b;
    }
    else return b-c;
}
unsigned mutil_MOD(unsigned long long a,unsigned long long b){
    unsigned long long c=a;
    for(int i=1;i<=b-1;i++){
        c=add_MOD(c,a);
    }
    return c;
}
void pro_MOD(){
unsigned long long c=a[0];
    for(int i=1;i<=N-1;i++){
        c=mutil_MOD(c,a[i]);
    }
    cout<<c<<endl;
}
int main(){
    input();
    pro_MOD();
    return 0;
}
