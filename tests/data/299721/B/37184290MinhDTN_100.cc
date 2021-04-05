#include <iostream>

using namespace std;

int main () {
    long long n, s, x;

    cin >> n;

    s = 1;
    for (int i = 0; i < n; i++) {
        cin >> x;
        s = (s*x)%(1000000007);
    }
    cout << s;

    return 0;
}