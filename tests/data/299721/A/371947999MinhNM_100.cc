#include <bits/stdc++.h>
using namespace std;

int a[10001], m, n, s;
int res = 0;

int countsub (int a[], int n, int k)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {
            if (sum + a[j] <= k)
            {
                sum = a[j] + sum;
                count++;
            }
            else break;
        }
    }
    return count;
}

void input()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];
}

void solve()
{
    int size = sizeof (a);
    res = countsub (a, n, m);
    cout << res << endl;
}

int main()
{
    input();
    solve();
}