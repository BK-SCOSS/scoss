#include <bits/stdc++.h>
using namespace std;

int TSP(int grph[][16], int p, int n, int m) {
   vector<int> ver;
   int count = 0;
   for (int i = 0; i < n; i++)
      if (i != p)
         ver.push_back(i);
         
   do {
      int cur_pth = 0;
      int k = p;
      for (int i = 0; i < ver.size(); i++) {
         cur_pth += grph[k][ver[i]];
         k = ver[i];
      }
      cur_pth += grph[k][p];
      if (cur_pth <= m) count++;
   }
   while (next_permutation(ver.begin(), ver.end()));
   return count;
}
int main() {
	int n , m;
	cin >>n >>m;
	int grph[16][16];
   for (int i =0; i < n; i++) {
   	for(int j =0; j <n; j++) {
   		int a;
   		cin >> a;
   		grph[i][j] = a;
	   }
   }
   cout<< TSP(grph, 0, n, m) << endl;
   return 0;
}