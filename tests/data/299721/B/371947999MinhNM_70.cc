#include <bits/stdc++.h>
using namespace std;

unsigned long long a[100001], n, s, k;

unsigned long long factorial(int n)
{
    const unsigned int M = 1000000007;
    unsigned long long f = 1;
    for (int i = 1; i <= n; i++)
    f = (f*i) % M; 
    return f;
}

void input()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
}

void solve()
{
    s = 1;
    for (int i = 0; i < n; i++)
    {
        a[i] = a[i] % 1000000007;
        s = s % 1000000007;
        s = s * a[i]; 
    }
    cout << s << endl;
}

int main()
{
    input();
    solve();
}