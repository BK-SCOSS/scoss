#include <iostream>
#include <math.h>
using namespace std;

unsigned long long int a[1000001], exp_t;

int main() {
    int n;

    exp_t = 1;
	cin>>n;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        exp_t *= a[i];
    }
    cout << exp_t;

	return 0;
}