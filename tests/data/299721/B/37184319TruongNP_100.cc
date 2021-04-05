//
//  main.cpp
//  Midterm_PRODMOD
//
//  Created by Nguyễn Trường on 10/23/20.
//

#include <iostream>

using namespace std;

int n, m = 1000000007;

unsigned long long addMod(unsigned long long a, unsigned long long b, unsigned long long p){
    a=a%p;
    b=b%p;
    unsigned long long tmp = p - a;
    if (tmp>b) {
        return a+b;
    }
    return b-tmp;
}
 
unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long p){
    if (a==0 || b==0) {
        return 0;
    }
    if (a==1) {
        return b%p;
    }
    if (b==1) {
        return a%p;
    }
    if (a>b) {
        unsigned long long tmp = a; a=b; b=tmp;
    }
    unsigned long long c = mulmod(a/2, b, p);
    c = addMod(c, c, p);
    if (a%2==0) {
        return c;
    } else {
        return addMod(c, b, p);
    }
}

int main(int argc, const char * argv[]) {
    cin >> n;
    long long ans = 1;
    for (int i=1; i<=n; i++) {
        long long a;
        cin >> a;
        ans = (ans * (a%m)) % m;
    }
    cout << ans;
    return 0;
}
