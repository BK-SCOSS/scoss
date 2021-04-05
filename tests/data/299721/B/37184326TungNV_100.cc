#include<bits/stdc++.h>
#include<iostream>
#define MAX 1000000
#define P 1000000007
typedef unsigned long long ll;
using namespace std;

unsigned int n;
ll mul = 1;
ll a[MAX];


int main(){
	
   cin >> n;
   for (int i=0;i<n;++i) cin>>a[i];
    for (int i=0;i<n;i++)
        mul = ((mul)*a[i])%P;
    
    cout<<mul;
}