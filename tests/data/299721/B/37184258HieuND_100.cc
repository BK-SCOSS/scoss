

#include <iostream>
 
using namespace std;
 
int main()
{
    long long n,ans,S=1;
    cin >> n;
    for(int i=0; i<n; i++){
        long long b;
        cin >> b;
        S= S*b;
        S= S%1000000007;
    }
    ans = S%1000000007;
    cout<<ans;
    return 0;
}
