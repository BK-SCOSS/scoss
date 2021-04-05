#include <iostream>
 
using namespace std;
 
typedef unsigned long long ull;
const int N = 32, M = 22;
int n, m, K;
int c[M][N];
 
int load[M];
int cost;
bool assigned[N];
int mcostassign = 1000000;
int mcost;
 
void input()
{
    cin >> n >> m >> K;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> c[i][j];
            mcostassign = mcostassign < c[i][j] ? mcostassign : c[i][j];
        }
    }
    mcost = 1000000;
}
 
void solve()
{
    if (cost < mcost)
        mcost = cost;
}
 
void TRY(int k)
{
    for (int v = 1; v <= m; v++) //assign course k to teacher v
    {
        if (load[v] < K)
        {
            load[v]++;
            cost += c[v][k];
            if (k == n)
                solve();
            else if (cost + mcostassign * (n-k) < mcost)
                TRY(k + 1);
            cost -= c[v][k];
            load[v]--;
        }
    }
}
 
int main()
{
    input();
    TRY(1);
    cout << mcost << endl;
}