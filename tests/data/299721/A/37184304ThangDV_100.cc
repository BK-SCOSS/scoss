#include<iostream>

using namespace std;

int main()
{
    int n,m;
    cin>>n>>m;
    int k=0;
    int s[n];
    for(int i=0;i<n;i++)
    {
        cin>>s[i];
    }
    int temp=0,a=0;

    for(int i=0;i<n;i++)
    {
        temp=0;
        k++;
        for(int j=i;j<n;j++)
        {
        temp=temp+s[j];
        if(temp<=m) a++;

    }}
    cout << a;
}
