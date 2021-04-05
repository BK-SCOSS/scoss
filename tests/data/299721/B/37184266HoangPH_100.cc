#include <iostream>
using namespace std;

int main ()
{
    long long n;
    long long ans = 1;
    cin >> n;
    for (long long i = 1; i <=n ;i++)
    {
        long long x;
        cin >> x;
        ans = (ans * (x%1000000007))%1000000007;
    }
    cout << ans;
}
