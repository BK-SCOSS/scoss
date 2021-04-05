#include<bits/stdc++.h>

using namespace std;

int N; // N task
int M; // M employee
int K; // max tasks per employee
int C[40][40]; // cost of employee i for task j
bool assigned[40]; // task j assigned
int take[40][40]; // i takes task j; take[i][0] = task count
int minVal;
int tmpTest;
int minCost;

void INPUT()
{
    minCost = 100000;
    cin >> N >> M >> K;
    for(int i = 1; i <= M; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            cin >> C[i][j];
            if(C[i][j] != 0 && C[i][j] < minCost)
                minCost = C[i][j];
        }
    }
}

void INIT()
{
    minVal = 100000;
    tmpTest = 0;

    for(int i = 0; i < 40; i++)
    {
        assigned[i] = false;
        for(int j = 0; j < 40; j++)
        {
            take[i][j] = 0;
        }
    }
}
/*
void SOLUTION()
{
    int tmpVal = 0;

    for(int i = 1; i <= M; i++)
    {
        for(int j = 1; j <= take[i][0]; j++)
        {
            tmpVal += C[i][take[i][j]];
        }
    }

    if(tmpVal < minVal && tmpVal != 0)
    {
        minVal = tmpVal;
    }
        
}
*/

void SOLUTION()
{
    if(tmpTest < minVal)
    {
        minVal = tmpTest;
    }
}
bool allAssigned()
{
    for(int i = 1; i <= N; i++)
    {
        if(!assigned[i])
            return false;
    }
    return true;
}

bool assignable(int i)
{
    if(take[i][0] >= K)
        return false;

    return true;
}

void TRY(int k) // task k
{
    for(int i = 1; i <= M; i++) // employee i
    {
        if(assignable(i))
        {
            take[i][0]++;
            //take[i][take[i][0]] = k;
            tmpTest += C[i][k];

            if(k == N)
            {
                    SOLUTION();
            }
            else
            {
                if(tmpTest + (N - k + 1) * minCost <= minVal)
                    TRY(k+1);
            }

            //take[i][take[i][0]] = 0;
            take[i][0]--;
            tmpTest -= C[i][k];
        }
    }
}

void SOLVE()
{
    TRY(1);
    cout << minVal;
}

int main()
{
    INIT();
    INPUT();
    SOLVE();
}