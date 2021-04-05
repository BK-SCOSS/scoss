
#include <bits/stdc++.h>
using namespace std;
const int k= 1000000007;
const int N= 1000001;
int a[N];
long long ans;
int main(){
    int n;
    cin>>n;
    for (int i =1; i<=n; i++)
        cin>>a[i];
    ans = 1;
    for (int i=1; i<=n; i++){
        ans= (ans*a[i])%k;
    }
    cout<<ans;
    return 0;
}
