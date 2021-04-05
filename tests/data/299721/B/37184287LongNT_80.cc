#include<bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const ull MOD = 1e9 + 7;

ull ADDMOD(ull a, ull b)
{
    return (a%MOD + b%MOD)%MOD;
}

ull MULMOD(ull a, ull b)
{
    ull tmp = a;
    for(int i = 1; i < b; i++)
    {
        tmp = ADDMOD(tmp, a);
    }
    return tmp;
}

int main()
{
    ull n;
    cin >> n;
    ull tmp;
    ull tmp2;
    cin >> tmp;
    for(int i = 0; i < n - 1; i++)
    {
        cin >> tmp2;
        tmp = MULMOD(tmp, tmp2);
    }
    cout << tmp;
}