#include <iostream>
using namespace std;
int main() {
	int n,m;
	cin>>n>>m;
	int a[n];
	for (int i=0;i<n;i++) cin>>a[i];
	int kq;
	int kqend= a[0];
	if (kqend<=m) kq=1; else kq=0;
	for (int i=1;i<n;i++) {
	if ((kqend+a[i])<=m) {kqend+=a[i];kq++;} else {kqend=a[i];kq++;}
	if (a[i]<=m&&a[i]!=kqend) kq++;
}
cout<<kq;
return 0;
}
