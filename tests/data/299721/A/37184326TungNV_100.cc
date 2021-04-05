#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAX = 10000;
int a[MAX];
int main(){
	int n, m, count=0;
    int sum = 0;
    
   cin >> n >> m;
   for (int i=0;i<n;i++){
    cin>>a[i];
    }
    
    for (int i=0;i<n;i++){
        sum = 0;
        for (int j=i;j<n;j++){
        sum = sum + a[j];
         if (sum<=m){
        count++;    
        }
        }      
    }
        cout<<count;
}