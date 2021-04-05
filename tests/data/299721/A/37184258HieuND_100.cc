#include <bits/stdc++.h>
using namespace std;
int sumij (int arr[], int i, int j) {
	if (i == j) return arr[i];
	else return sumij (arr, i, j - 1) + arr[j];
}
int main() {
	int n, m;
	cin >> n >> m;
	int arr[n+1];
	int count = 0;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		arr[i] = a;
	}
	for (int i = 0; i< n; i ++) {
		for (int j = i; j < n; j++) {
			int sum = sumij (arr, i, j);
			if (sum <= m) {
				count ++;
			} else {
				break;
			}
		}
	}
	cout<< count;
}
