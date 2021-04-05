#include<bits/stdc++.h>

using namespace std;

int N;
unsigned long long M;
int S[20][20];
int x[20];
bool visited[20];
unsigned long long tmpCost;
int cnt;
int minCost;

void INIT()
{
    tmpCost = 0;
    cnt = 0;
    for(int i = 1; i <= N; i++)
    {
        visited[i] = false;
        x[i] = 0;
    }
}

void INPUT()
{
    minCost = 10000;
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> S[i][j];
            if(S[i][j] != 0 && S[i][j] < minCost)
                minCost = S[i][j];
        }
    }
}

void SOLUTION()
{
    if(tmpCost + S[x[N]][1] <= M)
        cnt++;
}

void TRY(int k)
{
    for(int i = 2; i <= N; i++)
    {
        
        if(!visited[i])
        {
            
            x[k] = i;
            visited[i] = true;
            tmpCost += S[x[k-1]][x[k]];

            if(k == N)
            {
                SOLUTION();
            }
            else
            {
                if(tmpCost+(N-k)*minCost < M)
                    TRY(k+1);
            }

            visited[i] = false;
            tmpCost -= S[x[k-1]][x[k]];
        }
    }
}

void SOLVE()
{
    x[1] = 1;
    visited[1] = true;
    TRY(2);
    cout << cnt;
}

int main()
{
    INPUT();
    INIT();
    SOLVE();
}
