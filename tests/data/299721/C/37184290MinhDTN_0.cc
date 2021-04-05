#include <iostream>
using namespace std;

int main(){
    int n,m;
    int a[20][20];
    cin >> n ;
    cin >> m;
    int countS=0;
    for(int i=1; i<=n; i++){
        for(int j=1;i<=n;j++){
            cin >> a[i][j];
        }
    }
    int x=1;

    for(int y=1; y<=n;y++){
        int distance=0;
        int j=y;
        do{
        if(j>n){
            j=1;
            }
          else{
            distance=distance+a[x][j];
          }
          x++;
          j++;
        }while(j!=1);
        if(distance<=m) {countS++;}
    }
   cout << countS;

}