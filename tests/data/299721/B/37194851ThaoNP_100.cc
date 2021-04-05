#include <bits/stdc++.h>
using namespace std;

int const MOD = 1000000007;
int N;
unsigned long long s[1000000];
unsigned long long product = 1;

void input() {
    cin >> N;
    for (int i=0;i<N;i++) cin >> s[i];
}

unsigned long long prodMod(unsigned long long a,unsigned long long b) {
    unsigned long long res = 0;
    a %= MOD;
    while (b) {
        if (b & 1) res = (res+a) % MOD;
        a = (2*a) % MOD;
        b >>=1;
    }
    return res;
}

int main() {
    input();
    product *= prodMod(s[0],s[1]);
    for (int j=2;j<N;j++) {
        product = prodMod(product,s[j]);
    }
    product %= MOD;
    cout << product;
    return 0;
}