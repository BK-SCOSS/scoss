#include <bits/stdc++.h>
using namespace std;
const int MAX = 30;
int res =1000000000, sum=0;
bool done[MAX];
int a[MAX][MAX];
int cost[MAX];
int taskNum[MAX];

/*void TRY(int k, int n) 
{
    for (int v=1; v<=9; v++)
	{
        if (!appear[v]) 
		{
            x[k] = v;
            appear[v] = true;
            if (k==7) 
            {
            	if((1000*x[5] + 100*(x[1]-x[4]+x[6]) + 10*(x[2]+x[7]) + 2*x[3] - 62) == n)
            	cnt++;
			}
			
            else TRY(k+1, n);
            appear[v] = false;
        }
    }
}*/

void TRY(int N, int m, int M, int K)
{
  for(int i=0; i<N; i++)
  {
    if(!done[i])
    {
        if (taskNum[m] < K)
          {
            taskNum[m]++;
            sum += a[m][i]; 
            done[i] = true;
            //TRY(N, m+1, M, K);
            //done[i] = false;
          }
       else TRY(N, m+1, M, K);
       done[i] = false;
    }
  }
  if(sum < res) res = sum;
  //cout << res;
  sum =0;
}

int main()
{
  int N, M, K;//M: emplyees, N: tasks, K: max tasks
  cin >> N >> M >> K;
  for(int i=0; i<M; i++)
  {
    for(int j=0; j<N; j++)
    cin >> a[i][j];
  }
  for(int i=0; i<M; i++)
  {
    cost[i] = 0;
    taskNum[i] = 0;
  }
  for(int i=0; i<N; i++)
  done[i] = false;
  for(int m=0; m<M; m++)
  TRY(N, m, M, K);
  cout << res;
  return 0;
  
}