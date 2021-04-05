#include <iostream>

using namespace std;

typedef unsigned long long ull;
const int MAX = 100000;

int M, N;
int a[MAX + 1];
int ans;

void input()
{
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        cin >> a[i];
    }
}

void TRY(int start)
{
    int tmp = a[start];
    if (tmp <= M)
        ans++;
    for (int i = start + 1; i <= N; i++)
    {
        if (tmp + a[i] <= M)
        {
            tmp += a[i];
            ans++;
        }
        else
            break;
    }
}

void solve()
{
    for (int i = 1; i <= N; i++)
        TRY(i);

    cout << ans << endl;
}

int main()
{
    input();
    solve();
}