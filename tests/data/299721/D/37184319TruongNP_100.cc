//
//  main.cpp
//  Midterm_TASK ASSIGNMENT
//
//  Created by Nguyễn Trường on 10/23/20.
//
 
#include <iostream>
 
using namespace std;
 
int n,m,k,c[40][40],cmin = 999999999, ctask[40], tcost = 0, ans = 999999999;
 
bool check(int i, int v){
    if (ctask[v]+1>k) {
        return false;
    }
//    if (ctask[v] + (n-i)/m > k) {
//        return false;
//    }
    return true;
}
 
void tryy(int i){
    for (int v=1; v<=m; v++) {
        if (check(i,v)) {
            ctask[v]++;
            tcost += c[v][i];
            if (i==n) {
                ans = ans < tcost ? ans : tcost;
            } else {
                if (tcost+cmin*(n-i) < ans){
                    tryy(i+1);
                }
            }
            ctask[v]--;
            tcost -= c[v][i];
        }
    }
}
 
int main(int argc, const char * argv[]) {
    cin >> n >> m >> k;
    for (int i=1; i<=m; i++) {
        for (int j=1; j<=n; j++) {
            cin >> c[i][j];
            cmin = cmin > c[i][j] ? c[i][j] : cmin;
        }
    }
    tryy(1);
    cout << ans;
    return 0;
}