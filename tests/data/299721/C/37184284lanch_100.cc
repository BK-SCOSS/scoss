//
//  main.cpp
//  TSPTour
//
//  Created by Lan Chu on 10/23/20.
//

#include <iostream>
#include <vector>

using namespace std;

const int N = 15;
int n;
int m;
int cost[N+1][N+1];

int path[N];
int curTotalCost;
int numSolution;
bool visited[N+1];
int minCost;

void input()
{
    cin >> n >> m;
    minCost = INT_MAX;
    for(int i=1; i<=n; ++i)
    {
        visited[i] = false;
        for(int j=1; j<=n; ++j)
        {
            cin >> cost[i][j];
            if(cost[i][j] != 0)
            minCost = cost[i][j] < minCost ? cost[i][j] : minCost;
        }
    }
}

bool isPromisingPath(int curPos)
{
    int numCityLeft = n - curPos;
    return curTotalCost + numCityLeft * minCost <= m;
}

void tryPath(int curPos)
{
    if(curPos == n)
    {
        int prevCity = path[curPos - 1];
        curTotalCost += cost[prevCity][1];
        
        if(curTotalCost <= m)
            numSolution++;
        
        curTotalCost -= cost[prevCity][1];
        return;
    }
    
    int prevCity = path[curPos-1];
    for(int curCity = 1; curCity <= n; ++curCity)
    {
        if(!visited[curCity])
        {
            path[curPos] = curCity;
            curTotalCost += cost[prevCity][curCity];
            visited[curCity] = true;
            if(isPromisingPath(curPos))
                tryPath(curPos + 1);
            path[curPos] = 0;
            curTotalCost -= cost[prevCity][curCity];
            visited[curCity] = false;
        }
    }
}

void solve()
{
    path[0] = 1;
    visited[1] = true;
    curTotalCost = 0;
    numSolution = 0;
    
    tryPath(1);
    cout << numSolution;
}

int main(int argc, const char * argv[]) {
    input();
    solve();
    return 0;
}
