#include <bits/stdc++.h>
using namespace std;
const int N = 100;
const int INF = 100000010;
long long c[N][N];
long long cmin;
int x[N];
int n, m;
bool appear[N];
long long f;
int ans;

void input()
{
    cin >> n >> m;

    cmin = INF;
    for (int k = 1; k <= n; k++)
    {
        for (int j = 1; j <= n; j++)
        {
            int w;
            cin >> w;
            c[k][j] = w;
            if (w != 0)
                cmin = w < cmin ? w : cmin;
        }
    }
}
void solution()
{
    if (f + c[x[n]][x[1]] <= m)
    {
        ans++;
    }
}
void TRY(int k)
{
    for (int v = 1; v <= n; v++)
    {
        if (!appear[v])
        {
            x[k] = v;
            appear[v] = true;
            f = f + c[x[k - 1]][x[k]];
            if (k == n)
                solution();
            else
            {
                if (f + cmin * (n - k) < m)
                    TRY(k + 1);
            }
            appear[v] = false;
            f = f - c[x[k - 1]][x[k]];
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
    TRY(2);
    cout << ans << endl;
}
int main()
{
    input();
    solve();
}