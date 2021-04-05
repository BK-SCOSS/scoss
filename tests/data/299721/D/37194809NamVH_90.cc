#include <bits/stdc++.h>
#define N 31
using namespace std;
int n, m, klimit;
int Task[N][N];
int minCost = 100000000;
int cmin = 100000000;
// int Log[N];
bool appear[N];
int CountTasks[N];
int tempCost = 0;
bool check(int k, int t)
{
    return CountTasks[t] < klimit && !appear[k];
}
void solution()
{
    if(tempCost < minCost)
    {
        minCost = tempCost;
        // for(int i = 0; i < n; i++)
        // {
        //     cout << Log[i] << " ";
        // }
        // cout << endl;
    }
}
void solve(int k)
{
    for(int i = 0; i < m; i++)
    {
        if(check(k, i) && tempCost + Task[i][k] < minCost)
        {
            // Log[k] = i;
            appear[k] = true;
            CountTasks[i] += 1;
            tempCost += Task[i][k];
            if(k == n - 1)
            {
                solution();
            }
            else
            {
                if(tempCost + cmin*(n - k - 1) < minCost)
                    solve(k + 1);
            }
            CountTasks[i] -= 1;
            tempCost -= Task[i][k];
            appear[k] = false;
        }
    }
}
int main()
{
    cin >> n >> m >> klimit;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> Task[i][j];
            if(cmin > Task[i][j])
                cmin = Task[i][j];
        }
    }
    solve(0);
    cout << minCost << endl;
}