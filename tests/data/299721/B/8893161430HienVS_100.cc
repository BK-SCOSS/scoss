#include<iostream>
using namespace std;

#define N 1000000007;

int main(){
	long long n;
	cin>>n;
	unsigned long long e[1000000];
	unsigned long long sum=1;
	for(int i=0;i<n;i++){
		cin>>e[i];
		sum*=e[i];
		sum%=N;
	}
	cout<<sum;
	return 0;
}