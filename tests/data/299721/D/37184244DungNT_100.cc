
#include <iostream>
 
using namespace std;
 
typedef unsigned long long ull;
const int N = 32, M = 22;
int n, m, K;
int c[M][N];
 
int load[M];
int cost;
// bool assigned[N];
int min_c = 1000000;
int min_tt;
 
void input()
{
    cin >> n >> m >> K;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> c[i][j];
            min_c = min_c < c[i][j] ? min_c : c[i][j];
        }
    }
    min_tt = 1000000;
}
 
void solve()
{
    if (cost < min_tt)
        min_tt = cost;
}
 
void TRY(int k)
{
    for (int v = 1; v <= m; v++) //assign course k to teacher v
    {
        if (load[v] < K)
        {
            load[v]++;
            // assigned[k] = true;
            cost += c[v][k];
            if (k == n)
                solve();
            else if (cost + min_c * (n-k) < min_tt)
                TRY(k + 1);
            cost -= c[v][k];
            // assigned[k] = false;
            load[v]--;
        }
    }
}
 
int main()
{
    input();
    TRY(1);
    cout << min_tt << endl;
}
