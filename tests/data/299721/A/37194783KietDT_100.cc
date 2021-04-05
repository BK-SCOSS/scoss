#include <iostream>
#include <math.h>
//#include <algorithm>

using namespace std;
long long a[1000001],b[10000001];
long long n, m, tmp;


int main() {
    long long count = 0;
    cin >> n; cin >> m;
    b[0]=0;

    for (int i=1;i<=n;i++) {
        cin>>a[i];
        b[i]=b[i-1]+a[i];
    }
    
    for (int i = 1; i <= n; i++){
        for (int j = 0; j < i; j++){
            tmp = b[i] - b[j];
            if (tmp <= m) count ++;
        }
    }
    cout << count << endl;

	return 0;
}