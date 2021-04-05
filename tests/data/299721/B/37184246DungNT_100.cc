#include <iostream>


using namespace std;



int main()
{
  unsigned long long n,a[1000000],p=1000000007,c=1;
   cin>>n;
   for (long long i = 0;i<n;i++){
    cin>>a[i];
    c *= a[i]%p;
    c = c%p;
   }
   cout<<c%p;
    return 0;

}