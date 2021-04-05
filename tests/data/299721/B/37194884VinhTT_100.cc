#include<bits/stdc++.h>

using namespace std ;

#define MAX 1000001
#define MOD 1000000007
int n , a[MAX];
unsigned long long res=1 ;

void input()
{
    int temp ;
    cin >> n ;
    for( int i=0 ; i<n ; i++ )
    {
        cin >> temp ;
        res = ((res%MOD) * (temp%MOD) )%MOD ;
    }
}

void solve()
{
    cout << res%MOD << endl ;
}

int main()
{
    input() ;
    solve() ;
}
