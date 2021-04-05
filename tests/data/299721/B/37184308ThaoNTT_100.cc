#include <bits/stdc++.h>
using namespace std;

unsigned long long p = 1000000007;

int main() {
    int n,a[1000001];
    cin >>n;
    for (int i=1;i<=n;i++)cin >>a[i];
    int tmp=a[1];
    for (int i=2;i<=n;i++){
        tmp=((unsigned long long)(tmp)*a[i])%p;
        
    }
    cout << tmp;
    return 0;
}
