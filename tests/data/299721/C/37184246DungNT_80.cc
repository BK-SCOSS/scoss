#include <iostream>
using namespace std;
int n,m,a[21],b[21][21],t[21], ans = 99999999, countt=0;
bool dd[21];
void tryy(int i){
      for (int j=2;j<=n;j++){
            if (t[i]<m){
        if (dd[j]==false && t[i]<m){
            a[i] = j;
            dd[j] = true;

            if(i==n){
                  if  (t[i-1] + b[a[i-1]][a[i]]+b[a[i]][1] <=m) countt++;
            } else {
            t[i] = t[i-1] + b[a[i-1]][a[i]];
            if (t[i]<m){
                tryy(i+1);
            }
            t[i] = t[i-1];
        }
        dd[j] = false;

      }
    }
}
}

int main(){

    cin >> n >> m;
    for (int i = 1;i<=n;i++){
            for (int j = 1;j<=n;j++){
             b[i][j] = 99999999;
            }
    }
       for (int i=1; i<=n; i++) {
        dd[i] = false;
    }
    for (int i=1; i<=n; i++){
       for (int j=1; j<=n;j++){
       cin >> b[i][j];
       }
    }
    a[1] = 1;
    t[1] = 0;
    dd[1] = true;
    tryy(2);
   cout << countt;
    return 0;
}
