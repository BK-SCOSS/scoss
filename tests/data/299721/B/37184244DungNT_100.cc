#include<iostream>
using namespace std;
#define MAX 1000009
typedef unsigned long long ull;
const ull P = 1e9 + 7;
ull arr[MAX];
ull n; 
ull addmod(ull a, ull b) {
    // a = a % P;
	// b = b % P;
	// ull c = P - a;
	// if (c>b) return (a + b);
	// else return (b - c);
    return (a + b) % P;
}

ull mulmod(ull a, ull b) // calculate a*b mod P
{
    if ( b == 1)
    return a % P;
    if (a == 1)
    return b % P;
    ull retval = 0;
    
    if (a < b) {
        ull tmp = a;
        a = b;
        b = tmp;
    }
        while(b> 0){
        if (b % 2 == 1)
        {
            retval = addmod(retval,a);
        }
        b /= 2;
        a = addmod(a,a);
        }
    
    return retval;
    
}

ull expmod(ull a, ull b) {
    ull retval = 1; // initialize result
    a = a % P;
    if ( a == 0) return 0;
    while (b > 0) {
        if ( b & 1)
            retval = mulmod(retval, a);
        b = b >> 1; // b/2
        a = mulmod(a,a);

    }
    return retval;

}

int main() {
    cin >> n;
    ull ret = 1;
    ull tmp;
    for(int i = 1; i<= n; i++ ) {
        cin >> tmp;
        arr[i] = tmp;
        ret = mulmod(ret, tmp);
    }
     cout << ret;
    
}