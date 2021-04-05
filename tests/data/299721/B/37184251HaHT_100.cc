#include <bits/stdc++.h>
using namespace std;

const int p = 1e9+7; 
const int MAXN = 1e6+1;

int a[MAXN];
int n;

int main() {
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >>a[i];
	int tmp=a[1];
	for(int i = 2; i <= n; i++) {
		//tmp=(unsigned long long)(tmp*a[i])%p;
		tmp=((unsigned long long)(tmp)*a[i])%p;
	}

	cout << tmp;
	return 0;
}