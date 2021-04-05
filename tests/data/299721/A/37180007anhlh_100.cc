#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;

int a[N];
int sum[N];

int main() {
	int n, m;
	cin >> n >> m;
	
	sum[0] = 0;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		sum[i] = a[i] + sum[i-1];
	}
	
	int start = 0;
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		while(sum[i] - sum[start] > m)
			start++;
		ans = ans + i-start;
	}

	cout << ans << endl;
	return 0;
}