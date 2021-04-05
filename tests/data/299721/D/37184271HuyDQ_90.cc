#include <bits/stdc++.h>
using namespace std;
const int N = 30;
int n, m, q;
int c[N][N];
int cmin=1e7;
bool appear[N];
int f;
int cnt[N];
int min_f;
void input()
{
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> c[i][j];
            cmin = c[i][j] < cmin ? c[i][j] : cmin;
        }
    }
    // for (int i = 1; i <= n; i++)
    // {
    //     appear[i] = false;
    // }
    // for (int i = 1; i <= m; i++)
    // {
    //     cnt[i] = 0;
    // }
    f = 0;
    min_f = 100000;
}
void solution()
{
    if (f < min_f)
    {
        min_f = f;
    }
}
bool check(int v,int k){
    if(appear[k]){
        return false;
    }
    if(cnt[v]>=q){
        return false;
    }
    return true;
}
void TRY(int k)
{
    for (int v = 1; v <= m; v++)
    {
        if (check(v,k))
        {
            f += c[v][k];
            appear[k] = true;
            cnt[v] += 1;
            if (k == n)
            {
                solution();
            }
            else
            {
                if(f + cmin*(n-k) < min_f)
                    TRY(k + 1);
            }
            appear[k] = false;
            cnt[v] -= 1;
            f -= c[v][k];
        }
    }
}
int main()
{
    input();
    TRY(1);
    cout << min_f;
}
