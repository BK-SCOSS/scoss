#include <bits/stdc++.h>

using namespace std;

const int MOD=1000000007;
const int N=1000001;
int a[N];
int n;
long long kq;

void in_solve(){
    cin >> n;
    kq=1;
    for (int i=1;i<=n;i++){
        cin >> a[i];
        kq= ((kq%MOD) *(a[i]%MOD ))%MOD ;
    }
    cout << kq%MOD << endl;
}

int main(){
    in_solve();

}
