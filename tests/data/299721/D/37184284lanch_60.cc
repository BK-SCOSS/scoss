//
//  main.cpp
//  takeAssignment
//
//  Created by Lan Chu on 10/23/20.
//

#include <iostream>

using namespace std;

const int N = 20;
const int M = 30;
int n, m, k;

int cost[M+1][N+1];
int minTotalCost;
int curTotalCost;
int minCost;
int numTaskOfStaff[M+1];
int minCostOfTask[N+1];

bool promisingAssignment(int curTask)
{
    int expectedCost = 0;
    for(int i=curTask + 1; i<=n; ++i)
        expectedCost += minCostOfTask[i];
    return curTotalCost + expectedCost <= minTotalCost && curTotalCost + minCost * (n - curTask) <= minTotalCost;
}

void tryAssign(int curTask)
{
    if(curTask > n)
    {
        minTotalCost = curTotalCost < minTotalCost ? curTotalCost : minTotalCost;
        return ;
    }
    
    for(int staff = 1; staff <= m; ++staff)
    {
        if(numTaskOfStaff[staff] < k)
        {
            curTotalCost += cost[staff][curTask];
            numTaskOfStaff[staff]++;
            
            if(promisingAssignment(curTask))
                tryAssign(curTask + 1);
            
            curTotalCost -= cost[staff][curTask];
            numTaskOfStaff[staff]--;
        }
    }
}

void solve()
{
    // input
    cin >> n >> m >> k;
    minCost = INT_MAX;
    for(int i=1; i<=m; i++)
    {
        numTaskOfStaff[i] = 0;
        for(int j=1; j<=n; ++j)
        {
            minCostOfTask[j] = INT_MAX;
            cin >> cost[i][j];
            minCost = cost[i][j] < minCost ? cost[i][j] : minCost;
        }
    }
    
    for(int i = 1; i<= n; ++i)
    {
        for(int j= 1; j <=m; ++j)
            minCostOfTask[j] = cost[j][i] < minCostOfTask[j] ? cost[j][i] : minCostOfTask[j];
    }
    
    // solve
    minTotalCost = INT_MAX;
    curTotalCost = 0;
    tryAssign(1);
    cout << minTotalCost;
    
}


int main(int argc, const char * argv[]) {
    solve();
    return 0;
}
