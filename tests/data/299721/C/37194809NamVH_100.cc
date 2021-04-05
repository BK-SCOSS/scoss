#include <bits/stdc++.h>
#define N 20
int n, m;
using namespace std;
int arr[N][N];
bool appear[N];
int cmin = 1000000;
int ftemp = 0;
int cnt = 0;
int Log[N];
bool check(int k, int i)
{
    return !appear[i];
}
void solution()
{
    ftemp += arr[Log[n - 1]][0];
    if(ftemp <= m)
    {
        cnt += 1;
        // cout << ftemp << endl;
        // for(int i = 0; i < n; i++)
        // {
        //     cout << Log[i] << " ";
        // }
        // cout << endl;
    }
    ftemp -= arr[Log[n - 1]][0];   
}
void solve(int k)
{
    for(int i = 1; i < n; i++)
    {   
        if(check(k, i))
        {
            Log[k] = i;
            ftemp += arr[Log[k - 1]][i];
            appear[i] = true;
            if(k == n - 1)
                solution();
            else
            {
                if(ftemp + (n - k) <= m)
                    solve(k + 1);
            }
            ftemp -= arr[Log[k - 1]][i];
            appear[i] = false;
        }
    }   
}
int main()
{
    cin >> n >> m;
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
            if(i != j && cmin > arr[i][i])
                cmin = arr[i][j];
        }
    }
    for(int i = 0; i < n; i++)
    {
        appear[i] = false;
    }
    appear[0] = true;
    solve(1);
    // vector<int> per(n);
    // for(int i = 0; i < n; i++)
    //     per[i] = i; 
    // int cnt = 0;
    // while(next_permutation(per.begin() + 1, per.end()))
    // {
    //     int sum = 0;
    //     int k = 0;
    //     int i = 0;
    //     for(i = 0; i < n; i++)
    //     {
    //         sum += arr[k][per[i]];
    //         if(sum + (n - i + 1)*cmin >= m)
    //             break;
    //         k = per[i];
    //     }
    //     sum += arr[per[n - 1]][0];
    //     if(sum <= m)
    //         cnt++;
    // }
    cout << cnt << endl;
}