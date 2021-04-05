#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30+1;
const int MAXM = 20+1;
const int INF = 1e9+7;
int c[MAXM][MAXN];
int n, m, k;

int ans;
int cmin;
int visited[MAXM];
void exhsearch(int task, int cost) {
	for(int i = 0; i < m; i++) {
		if(visited[i] < k && cost + c[i][task] + cmin*(n-task-1) < ans) {
			visited[i]++;
			if(task == n-1) 
				ans = cost + c[i][task];
			else
				exhsearch(task+1, cost + c[i][task]);
			visited[i]--;
		}
	}
}
int main() {
	//freopen("1.inp", "r", stdin);

	scanf("%d %d %d", &n, &m, &k);
	cmin = INF;
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++) {
			scanf("%d", &c[i][j]);
			cmin = min(cmin, c[i][j]);
		}

	ans = INF;
	memset(visited, 0, sizeof visited);

	exhsearch(0, 0);
	
	printf("%d\n", ans);

	return 0;
}