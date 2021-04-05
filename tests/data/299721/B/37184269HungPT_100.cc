#include <bits/stdc++.h>
#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;

int main(){
    int x, n;
    cin >> n;
    int res = 1;
    for (int i = 0; i < n; ++i){
        cin >> x;
        res = (1ll * res * x) % MOD;
    }
    cout << res;
    return 0;
}