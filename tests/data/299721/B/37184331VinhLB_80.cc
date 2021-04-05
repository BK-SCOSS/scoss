#include <bits/stdc++.h>
using namespace std;

const int P = 1000000007;
const int MAX = 1000001;

int a[MAX], N;

unsigned long long addMod(unsigned long long a, unsigned long long b) {
    a = a % P;
    b = b % P;
    int temp = P - a;
    if (temp < b) {
        return b - temp;
    }
    return a + b;
}

unsigned long long mulMod(unsigned long long a, unsigned long long b) {
    if (a == 0 || b == 0) return 0;
    if (a == 1) return b % P;
    if (b == 1) return a % P;
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    unsigned long long c = 0;

    if (b % 2 == 0) {
        c = mulMod(a, b / 2);
        c = addMod(c, c);
    } else {
        c = mulMod(a, (b - 1) / 2);
        c = addMod(c, c);
        c = addMod(a, c);
    }
    
    return c;
}

unsigned long long prodMod(int k) {
    if (k == 1) return a[k] % P;
    return mulMod(prodMod(k - 1), a[k]);
}

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    cout << prodMod(N);
}