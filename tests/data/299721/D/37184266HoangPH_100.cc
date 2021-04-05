#include <iostream>
#include <vector>
using namespace std;
 
int nTask,nStaff,k;
int a[21][31];
vector <int> staff[21];
int Totalcost[21] = {};
int cmin[31];
void input()
{
    cin >> nTask >> nStaff >> k;
    for (int i = 1; i <= nStaff ; i++)
    {
        for (int j = 1; j <= nTask; j++)
        {
            cin >> a[i][j];
 
        }
    }
    for (int i = nTask ;i >= 1; i-- )
    {
        int mi = 99999;
        for (int j = 1; j <= nStaff; j++)
        {
            mi = min(mi,a[j][i]);
        }
        if (i == nTask)
        {
            cmin[i] = mi;
        }else
        {
            cmin[i] = cmin[i+1] + mi;
        }
    }
}
int ans = 999999;
int max1 ;
void Try(int i)
{
    for (int v = 1; v <= nStaff; v++)
    {
        if (staff[v].size() < k)
        {
            staff[v].push_back(i);
            Totalcost[v] += a[v][i];
            max1 = 0;
            for (int j = 1; j <= nStaff; j++)
            {
                max1 += Totalcost[j];
            }
            if (i == nTask)
            {
 
                ans = ans > max1 ? max1 : ans;
            }else
            {
                if (max1 + cmin[i+1] < ans)
                {
                    Try(i+1);
                }
            }
            staff[v].pop_back();
            Totalcost[v] -= a[v][i];
 
        }
    }
}
 
int main()
{
    input();
    Try(1);
    cout<<ans;
}