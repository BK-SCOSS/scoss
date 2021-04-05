#include <iostream>
#include <vector>
using namespace std;

int n,m;

int ans = 0;

int main()
{
    cin >> n >> m;
    int a[n];
    for (int i = 0; i <n ;i++)
    {
        cin >> a[i];
    }
    vector <int> b[n];

    for (int i = 0; i < n ; i++)
    {
        if (a[i] <= m )
        {
            b[i].push_back(a[i]);
        }
    }
    int j = 1;
     for (int i = 1; i<n ; i++)
    {
        for (int v = j-1 ; v >= 0 ; v--)
        {
            int M = b[i][b[i].size()-1] + a[v];
            if (M <= m)
            {
                b[i].push_back(M);
            }else
            {
                break;
            }
        }
        j++;
    }
    for (int i = 0 ; i< n ;i++ )
    {
        ans += b[i].size();
    }
    cout<<ans;



}
