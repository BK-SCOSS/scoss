/*Given a sequence of positive integers a1,…,aN (0<ai≤109+7). You are required to compute the product S=a1×⋯×aN. In order to avoid overflow (if any), You should report the value S modulo 109+7. */

#include <bits/stdc++.h>
using namespace std;
const int C = 1000000007;
const int N = 1000000;
unsigned long long res = 1;

int main()
{
  int n;
  cin >> n;
  unsigned long long a[N];
  for(int i=0; i<n; i++)
  {
    cin >> a[i];
  }
  for(int i=0; i<n; i++)
  {
    res = (res*(a[i]%C))%C;
  }
  cout << res;
  return 0;
}

