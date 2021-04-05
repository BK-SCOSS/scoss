/*Given a sequence s of N positive integers a1,…,aN and a positive integer M. A subsequence of s from index i to index j is defined to be ai,ai+1,…,aj (∀1≤i≤j≤N). The weight of a sequence is defined to be the sum of all elements of the sequence. Compute the number of subsequences of s whose weight is less than or equal to M.*/

#include <bits/stdc++.h>
using namespace std;
const int MAX = 100000;

int check(int i, int a[], int n, int m)
{
  int sum =0;
  int cnt =0;
  while(sum<=m)
  {
    if(i==n) break;
    sum += a[i];
    if(sum<=m) cnt++;
    i++;
  }
  return cnt;
}

int main()
{
  int n, m;
  int a[MAX];
  cin >> n >> m;
  for(int i=0; i<n; i++)
  {
    cin >> a[i];
  }
  int cnt =0;
  for(int i=0; i<n; i++)
    cnt += check(i, a,n, m);
  cout << cnt;
  return 0;
}