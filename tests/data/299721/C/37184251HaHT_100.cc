#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 15+1;
const int INF = 1e9+7;
int n, m;
int c[MAXN][MAXN];

int cmin; 

int ans;
bool visited[MAXN];
void exhsearh(int lastnode, int cnt, int cost) {
	//cout << lastnode << " " << cnt << " " << cost << endl;
	for(int i = 1; i < n; i++) 
		if(visited[i] == false && cost + c[lastnode][i] + cmin*(n-cnt) <= m) {
			visited[i] = true;
			if(cnt == n-1) {
				if(cost + c[lastnode][i] + c[i][0] <= m)
					ans++;
			}
			else
				exhsearh(i, cnt+1, cost + c[lastnode][i]);
			visited[i] = false;
		}
}
 
int main() {
	//freopen("1.inp", "r", stdin);
	
	scanf("%d %d", &n, &m);
	cmin = INF;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			scanf("%d", &c[i][j]);
			if(i != j)
				cmin = min(cmin, c[i][j]);
		}
 
	ans = 0;
	memset(visited, false, sizeof visited);
	visited[0] = true;
	exhsearh(0, 1, 0);
	printf("%d\n", ans);
	return 0;
}