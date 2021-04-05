#include <iostream>
using namespace std;
typedef unsigned long long ull;
ull n, k;
ull m = 1e9 + 7;
// ull add_mod(ull a, ull b)
// {
//     a = a % m;
//     b = b % m;
//     ull c = m - a;
//     if (b > c)
//         return b - c;
//     else
//         return b + a;
// }
ull addmod(ull a,ull b){
	a=a%m;
	b=b%m;
	ull tmp=m-a;
	if(tmp>b) return a+b;
	else return b-tmp;
}
ull mulmod(ull a,ull b){
	if(a==1) return b%m;
	if(b==1) return a%m;
	if(a>b){
		int tmp=a,a=b,b=tmp;
	}
	ull c= mulmod(a/2,b);
	c=addmod(c,c);
	if(a%2==0) return c;
	else return addmod(c,b);
}
// ull mul_mod(ull a, ull b)
// {
//     if (a == 1)
//         return b % m;
//     if (b == 1)
//         return a % m;
//     if (a < b)
//     {
//         ull m = a;
//         a = b;
//         b = m;
//     }
//     ull res = 0;
//     while (b > 0)
//     {
//         if (b & 1)
//         {
//             res = add_mod(res, a);
//         }
//         b = b >> 1;
//         a = add_mod(a, a);
//     }
//     return res;
// }
int main()
{
    cin >> n;
    ull arr[n];
    ull m;
    ull s=1;
    for (ull i = 0; i < n; i++)
    {
        cin >> m;
        s=mulmod(s,m);
    }
    if (n == 1)
        return arr[0];
    cout << s;
}