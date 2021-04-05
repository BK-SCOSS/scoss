#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,s=0,cnt=0;
	cin >>n>>m;
	int arr[n];
	for(int i=0;i<n;i++){
		cin >>arr[i];
	}
	for(int i=0;i<n;i++){
        s=arr[i];
        if(s<=m) cnt++;
        for(int j=i+1;j<n;j++){
            s+=arr[j];
            if(s<=m) cnt++;
            else break;
        }
    }
    cout <<cnt;
}
