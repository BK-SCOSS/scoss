#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
int n, m;
int a[100000];
long long sum;
void input(){
    cin >> n >> m;
    for(int i = 0;i<n;i++){
        cin >> a[i];
    }
}
int main(){
    sum = 0;
    input();
    int count = 0;
    for(int i = 0; i<n;i++){
        for(int j=i;j<n;j++){
            sum = sum + a[j];
            if(sum<=m){
                count++;
            }
        }
        sum = 0;
    }
    cout << count;
    return 0;
}