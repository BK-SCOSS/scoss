#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main(){
    int A[100001];
    int n, m;
    cin >> n >> m;
    for(int i=0;i<n;i++) cin >> A[i];
    unsigned long long sum = 0;
    unsigned long long Count = 0;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if(sum+A[j]<=m){
                Count++;
                sum += A[j];
            }
            else break;
        }
        sum = 0;
    }
    cout << Count << endl;
}