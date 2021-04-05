#include<iostream>
using namespace std;

int main(){
	int n,m,ans=0;
	cin>>n>>m;
	int e[1000000];
	for(int i=0;i<n;i++){
		cin>>e[i];
	}
	int sum;
	for(int i=0;i<n;i++){
		sum=0;
		for(int j=i;j<n;j++){
			if(e[i]>m) break;
			sum+=e[j];
			if(sum<=m){
				ans++;
			}else{
				break;
			}
		}
	}
	cout<<ans;
	return 0;
}