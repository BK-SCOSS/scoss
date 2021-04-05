#include <bits/stdc++.h>
using namespace std;
 
const long long P = 1e9+7;

unsigned long long summod(unsigned long long a, unsigned long long b){
    return ((a % P) + (b % P)) % P;
}
 
unsigned long long timemod(unsigned long long a, unsigned long long b){
	if (b==1) return a%P;
	unsigned long long tmp=timemod(a,b/2);
	if (b%2) return ((tmp+tmp)%P+a%P)%P;
	return (tmp+tmp)%P;
}

unsigned long long advanced_timemod(unsigned long long a, unsigned long long b){
    if (b==1) return a%P;
    unsigned long long tmp=timemod(a,b/2);
    if (b%2) return summod(summod(tmp,tmp),a)%P;
    return summod(tmp,tmp)%P;
}

int main(){
    // freopen("inp.txt","r", stdin);
	int n,k;
	unsigned long long res = 1ll*1;
	int res1=1;
	cin >> n;
	for (int i=0; i<n; i++){
		cin >> k;
        res = timemod(res,k);
	} 
	cout << res;
	return 0;
}