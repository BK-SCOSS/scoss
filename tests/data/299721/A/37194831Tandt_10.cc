#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n,m,i,d,j;
    int a[30];
    d=0;
    int s=0;
    cin>>n>>m;
    for(i=0;i<n;i++)
    cin>>a[i];

    for(i=0;i<n;i++)
    {   if(a[i]<=m) d=d+1;}
    for(i=0;i<n;i++)
    {s=a[i];
    for(j=1;j<n;j++)
    {if((s=s+a[j])<=m) d=d+1;
    else break;
     }}

    cout<<d;
}