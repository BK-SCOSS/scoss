#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+1;
int a[MAXN];

int main() {
	//freopen("1.inp", "r", stdin);

	int n, m;
	cin >> n >> m;
	int sum0 = 0, i0 = -1; 
	int sum = 0;
	long long ans = 0;
	for(int i = 0; i < n; i++) {
		cin >> a[i];
		sum += a[i];
		while(sum - sum0 > m) {
			i0++;
			sum0 += a[i0];
		}
		ans += (1ll*i-i0);
	}
	cout << ans << endl;
	return 0;
}