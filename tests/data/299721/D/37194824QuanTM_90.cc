#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int n,m,k; // tasks | staffs | max tasks
int C[40][40];
bool visited[40];
long long sumCost; 
long long minimalCost = LONG_LONG_MAX;
int minCostArr[40];
int taskNum[40]; // number of task to staff ith
void input(){
    cin >> n >> m >> k;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin >> C[i][j];
        }
    }
    minCostArr[n+1] = INT_MAX;
    for(int i=n;i>=1;i--){
        minCostArr[i] = min(minCostArr[i+1],C[1][i]);
        for(int j=1;j<=m;j++){
            minCostArr[i] = min(C[j][i],minCostArr[i]);
        }
    }
    for(int i=n-1;i>=1;i--) minCostArr[i] += minCostArr[i+1];
}
bool check(int i, int v){
    if(visited[i]==true) return false;
    if(taskNum[v] < k) return true;
    else return false;
}
// i is ith staff
void Try(int i){
    for(int v=1;v<=m;v++){
        if(check(i,v)){
            visited[i] = true;
            sumCost += C[v][i];
            taskNum[v]++;
            if(i==n){
                if(sumCost<minimalCost) minimalCost = sumCost;
            }
            else if(sumCost+minCostArr[i+1] < minimalCost) Try(i+1);
            visited[i] = false;
            taskNum[v]--;
            sumCost -= C[v][i];
        }
    }
}

int main(){
    input();
    Try(1);
    // for(int i=1;i<=n;i++) cout << minCostArr[i] << " ";
    // cout << endl;
    cout << minimalCost << endl;
}