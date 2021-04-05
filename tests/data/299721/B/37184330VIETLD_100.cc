#include<iostream>
#include<bits/stdc++.h>
using namespace std;
const long long N = 1000000007;
int main(){
    long long n;
    cin >> n;
    long long product = 1;
    long long a[1000000];
    for(long long i = 0;i<n;i++){
        cin >> a[i];
        product = (product*(a[i]))%N;
    }
    cout << product%N;
}