#include<iostream>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int s[n];
    int temp=1;
    int sodu;
    int a=1;
    for(int i=0;i<n;i++)
    {
        cin>>s[i];
        temp*=s[i];
        sodu=s[i]%(1000000000+7);
        if(sodu!=0)
        a*=sodu;
        else a=0;
        if(a>1000000000+7) a=a%(100000000+7);
    }
    cout << a;

}

