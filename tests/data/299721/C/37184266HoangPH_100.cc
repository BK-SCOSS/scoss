#include <iostream>
using namespace std;
int check[16] = {};
int n,m;
int a[16][16];
int x[16];
int cmin = 99999;
int ans = 0;
void input()
{
    cin>>n>>m;
    for(int i = 1; i <= n; i++)
    {
        for (int j = 1; j <=n ;j++)
        {
            cin>>a[i][j];
            if (i != j )
            {
                cmin = min(cmin,a[i][j]);
            }
        }
    }
}
int max1 = 0;
void Try(int i)
{
    for (int v =2; v <=n ;v++)
    {
        if (check[v] == 0)
        {
            x[i] = v;
            check[v] = 1;
            max1 += a[x[i-1]][x[i]];
            if (i == n)
            {
                if (max1 + a[x[i]][1] <= m)
                {
                 /*   for (int j = 1; j <= n ;j++)
                    {
                        cout<<x[j]<<" ";
                    }
                    cout<<endl;*/
                    
                    ans ++;
                }
            }else
            {
                if (max1 + (n-i)*cmin <= m)
                {
                    Try(i+1);
                }
            }
            check[v] = 0;
            max1 -= a[x[i-1]][x[i]];
        }
    }
}
int main()
{
    x[1] = 1;
    input();
    Try(2);
    cout<<ans;
}
