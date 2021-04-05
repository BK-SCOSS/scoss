#include <iostream>
#include <algorithm>
using namespace std;

int n, m , ans;
int a[100010];

int main() {
    cin >> n >> m;
          a[0] = 0;
          for(int i = 1 ; i<=n ;++i)
          {
              cin >> a[i];
              a[i] += a[i-1];
          }
          for(int i = 1 ; i<=n ; i++)
          {
              int p = lower_bound(a , a+i+1, a[i] - m) - a;
              ans +=i - p;
          }
          cout<<ans;
          return 0;
}
