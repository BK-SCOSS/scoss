#include <bits/stdc++.h>

using namespace std;

const int N=100001;
int n,m,cnt,t;
int a[N];


void input(){
    cin >> n >> m;
    for (int i=1;i<=n;i++)
        cin >> a[i];
}

void solve(){
    cnt=0;
    for (int i=0;i<n;i++){
        t=0;
        for (int j=i+1;j<=n;j++){
            t=t+a[j];
            if (t<=m) cnt++;
            }
        }
    cout << cnt << endl;
}

int main(){
    input();
    solve();
}
