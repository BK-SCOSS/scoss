#include <iostream>
#include <algorithm>  
using namespace std;

int n;
long long ans = 1;
const long long mod = 1e9+7;

int main() {
    cin >> n;
	for(int i = 1 ; i<=n ;++i)
	{
	    long long x;
	    cin >> x;
	    ans *= x;
	    ans %= mod;
	}
	cout<<ans;
	return 0;
}
