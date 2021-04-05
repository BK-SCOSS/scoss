#include <bits/stdc++.h>
using namespace std;

const int N = 100;
const int INF = 1000000000;
long long a[N][N];
long long cmin;
int x[N];
int n, m, res = 0;
bool appear[N];
long long f, min_f;

void input()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
}

void solution()
{
    if (f + a[x[n]][x[1]] < m)
        res++;
}

void TRY (int k)
{
    for (int v = 1; v < n; v++)
    {
        if (!appear[v])
        {
            x[k] = v;
            appear[v] = true;
            f = f + a[x[k-1]][x[k]];
            if (k == n) solution();
            else 
            {
                if (f + cmin * (n - k + 1) < m)
                    TRY (k+1);
            }
            appear[v] = false;
            f = f - a[x[k-1]][x[k]];
        }
    }
}

void solve()
{
    for (int v = 1; v <= n; v++)
        appear[v] = false;
    f = 0;
    x[1] = 1;
    appear[1] = true;
    min_f = INF;
    TRY (2);
    cout << res << endl;
}

int main()
{
    input();
    solve();
}