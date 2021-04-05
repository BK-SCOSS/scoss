//
//  main.cpp
//  Midterm_TSPCOUNT
//
//  Created by Nguyễn Trường on 10/23/20.
//

#include <iostream>

using namespace std;

int n, m, c[20][20], tt[20], mark[20], ans = 0, kc = 0, cmin = 999999999;

void tryy(int i){
    for (int v=2; v<=n; v++) {
        if (!mark[v]) {
            tt[i] = v;
            mark[v] = 1;
            if (i==1) {
                kc += c[1][v];
            } else {
                kc += c[tt[i-1]][v];
            }
            if (i==n-1) {
                if (kc + c[v][1] <= m) {
                    ans++;
//                    for (int j=1; j<=n-1; j++){
//                        cout << tt[j] << " ";
//                    }
//                    cout << c[v][1] << " ";
//                    cout << ":" << kc+c[v][1];
//                    cout << endl;
                }
            } else {
                if (kc + cmin*(n-i) <= m) {
                    tryy(i+1);
                }
            }
            mark[v] = 0;
            if (i==1) {
                kc -= c[1][v];
            } else {
                kc -= c[tt[i-1]][v];
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> n >> m;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            cin >> c[i][j];
            if (i!=j) {
                cmin = cmin < c[i][j] ? cmin : c[i][j];
            }
        }
    }
    tryy(1);
    cout << ans;
    return 0;
}
