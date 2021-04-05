//
//  main.cpp
//  subArray
//
//  Created by Lan Chu on 10/23/20.
//

#include <iostream>
#include <vector>

using namespace std;

int numSolution;

int main(int argc, const char * argv[]) {
    int n, m;
    cin >> n >> m;
    
    vector <int> arr;
    for(int i=0; i<n; ++i)
    {
        int x; cin >> x;
        arr.push_back(x);
    }
    
    numSolution = 0;
    int curSum = 0;
    for(int i=0; i<arr.size(); ++i)
    {
        curSum = arr[i];
        if(curSum <= m)
            numSolution++;
        for(int j=i+1; j<arr.size(); ++j)
        {
            curSum += arr[j];
            if(curSum <=m)
                numSolution++;
            else
                break;
        }
    }
    
    cout << numSolution;
    return 0;
}
