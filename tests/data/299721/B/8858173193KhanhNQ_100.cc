#include <iostream>
#include <math.h>
using namespace std;
int main() {
	unsigned long long n, kq;
	cin>>n;
	unsigned long long a[n];
	for (int i=0;i<n;i++) cin>>a[i];
	kq=a[0]%1000000007;
	for (int i=1;i<n;i++) {
		a[i]%=1000000007;
		kq*=a[i];
		kq%=1000000007;
	}
	cout<<kq;
	return 0;
}
	
