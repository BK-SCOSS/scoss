// Example program
#include <iostream>
#include <string>
using namespace std;
int n, m, count=0;
int sum = 0;
int a[1000000];
int main()
{
   cin >> n >> m;
   for (int i=0;i<n;i++){
    cin>>a[i];
     //   cout << a[i];

    }
    
    for (int i=0;i<n;i++){
        sum = 0;
        for (int j=i;j<n;j++){
        sum+=a[j];
         if (sum<=m){
        count++;    
        }
        }
        
       
    }
    
    cout<<count;
}
