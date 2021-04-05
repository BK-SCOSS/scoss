#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    long long a[1000];
    cin>>n;
    for(int i=0;i<n;i++)
    cin>>a[i];
    long long s=1;
    long long d,m,k;
    for(int i=0;i<n;i++)
    {s=s*a[i]; d=s%(10^9+7); k=k+d;}
     m=k%(10^9+7);
    cout<<d;
}
