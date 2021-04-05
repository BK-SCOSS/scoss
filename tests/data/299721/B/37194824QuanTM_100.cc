#include <iostream>
#include <bits/stdc++.h>
#define M 1000000007;
using namespace std;
int main(){
    int n;
    cin >> n;
    long long *A;
    unsigned long long product = 1; 
    A = (long long*)malloc(sizeof(long long)*(n));
    for(int i=0;i<n;i++){
        cin >> A[i];
        product *= A[i]%M;
        product %=M;
    }
    cout << product;
}