#include <bits/stdc++.h>
using namespace std;
 
int n,m,k,minf,f,max_task,amin;
int a[40][40];
int x[40];
int x_best[40];
int done[40];
 
bool check(int v, int k){
	if (done[v]>=max_task) return false;
	return true;
}
 
void in(){
	if (f<minf){
		minf=f;
		for (int i = 1; i <= n; ++i)
		{
			x_best[i]=x[i];
		}
	}
}
 
void xuly(int k){
	for (int v = 1; v <= m; ++v){
		if (check(v,k)){
			x[k]=v;
			done[v]++;
			f+=a[v][k];
			if (k==n) in();
			else {
				if (f+amin*(n-k)<minf) xuly(k+1);
			}
			done[v]--;
			f-=a[v][k];
		}
	}
}
 
int main(int argc, char const *argv[])
{
//  	freopen("inp.txt","r",stdin);
	cin>>n>>m>>max_task;
	memset(a,0,sizeof(a));
	memset(x,0,sizeof(x));
	memset(done,0,sizeof(done));
	minf=1e9;
	amin=1e9;
	f=0;
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			cin>>a[i][j];
			amin = a[i][j]>amin ? amin:a[i][j];
		}
	}
	xuly(1);
	// for (int i = 1; i <= n; ++i)
	// 	{
	// 		cout<<x_best[i]<<" ";
	// 	}
	// cout<<endl;
	cout<<minf;
	return 0;
}