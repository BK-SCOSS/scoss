#include <bits/stdc++.h>
using namespace std;
const int N= 1000000;
int n, m, cnt=0;
int s = 0;
int a[N];
int main()
{
   cin >> n >> m;
   for (int i=0;i<n;i++){
    cin>>a[i];
    }
    for (int i=0;i<n;i++){
        s= 0;
        for (int j=i;j<n;j++){
        s+=a[j];
         if (s<=m){
        cnt++;
        }
        }


    }
    cout<<cnt;
}
