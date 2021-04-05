#include <bits/stdc++.h>
using namespace std;
const int N=100;
const long long INF=1e18;
long long c[20][20];
long long x[100],appear[100];
long long n,m,f,minf,dem;
long long cmin;

bool check(int v,int k){
	return appear[v]==0;
}

void in(){
	if (f+c[x[n]][x[1]]<minf) minf=f+c[x[n]][x[1]];
	if (f+c[x[n]][x[1]]<=m) {
		dem++;
		// for (int i = 1; i <= n; ++i)
		// {
		// 	cout<<x[i]<<" ";
		// }
		// cout<<f+c[x[n]][x[1]]<<endl;
	}
}

void xuly(int k){
	for (int v = 2; v <= n; ++v)
	{
		if(check(v,k)){
			x[k]=v;
			appear[v]=1; //update
			f=f+c[x[k-1]][x[k]];
			if (k==n) in();
			else {
				if (f+cmin*(n-k+1)<=m)
					xuly(k+1);
			}
			appear[v]=0; //recover
			f=f-c[x[k-1]][x[k]];
		}
	}
}

int main(){
// 	freopen("inp.txt","r", stdin);
	cin >>n>>m;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			c[i][j]=INF;
		}
	}
	memset(appear,0,100);
	minf=INF; f=0;
	cmin=INF; dem=0;
	x[1]=1;
	appear[1]=1;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			cin>>c[i][j];
			if (c[i][j]!=0) cmin = c[i][j]>cmin ? cmin:c[i][j];
		}
	}
	xuly(2);
	cout<<dem;
}