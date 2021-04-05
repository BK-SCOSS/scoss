#include<bits/stdc++.h>
using namespace std;

const unsigned long long N = 10e7;
unsigned long long a;
unsigned long long n;
unsigned long long result;

const long long p = 1e9+7;
unsigned long long plus_mod (unsigned long long a, unsigned long long b ){
    unsigned long long c;
    	a = a % p;
    	b = b % p;
    	//return (a+b)%p;
    	c = p - a;
    	if ( c <= b)
    		return b - c;
    	else
    		return a + b; 	
    	
    }
     
unsigned long long time_mod(unsigned long long a, unsigned long long b){
    	if ( a == 1)
    		return b % p;
    	if ( b == 1)
    		return a % p;
    	unsigned long long c = b / 2;
    	unsigned long long tmp = time_mod(a, c);
    	if ( b % 2 == 0)
    		return plus_mod(tmp, tmp);
    	else
    		return plus_mod(plus_mod(tmp, tmp), a); 
    }
void input(){
    cin >> n;
    unsigned long long tmp;
    result = 1;
    for ( int i = 0 ; i < n; i++){
       cin >> tmp;
       a = tmp;
       result = time_mod( result, a); 
    }
}

int main(){
    input();
    cout << result << endl;
}