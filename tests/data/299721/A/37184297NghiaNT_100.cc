#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
	int n,m;
	int count;
	count=0;
	cin>>n>>m;
	int a[n],s[n];
	s[0]=0;
	
	for(int i = 1; i <= n; ++i)
	{
		cin>>a[i];
		if(i==0) s[i]=a[i];
		else s[i] = s[i-1]+a[i];
	}


	for (int i = 0; i < n; ++i)
	{
		for (int j = i+1; j <= n; ++j)
		{
			if (s[j]-s[i]<=m) 
				count++;		
		}
	}

	cout<<count;
	return 0;
}