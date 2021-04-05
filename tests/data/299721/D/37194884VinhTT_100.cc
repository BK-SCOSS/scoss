#include<bits/stdc++.h>

using namespace std ;

#define INF 1000000000

const int N = 100 ;
int c[N][N] , min_c , res , d ;
int n , m , kk , total_task[N] ;
int task[N];
bool appear[N] ;

void input() ;
bool check(int v,int k) ;
void solution() ;
void TRY( int k ) ;
void solve() ;

int main()
{
    input() ;
    solve() ;
}

bool check(int v,int k){
    if (appear[k]) return false;
    if (total_task[v]>=kk) return false;
    return true;
}

void input()
{
    cin >> n >> m >> kk ;
        min_c = INF ;
    for( int i=1 ; i<=m ; i++ )
        for( int j=1 ; j<=n ; j++ )
        {
            cin >> c[i][j] ;
            if( min_c > c[i][j])
                min_c = c[i][j] ;
        }
}



void solution()
{
    if( res >= d )
    {
        res = d ;
    }

}

void TRY( int k )
{
    for( int v=1; v<=m ; v++ )
    {
        if( check( v , k ) )
        {
            appear[k] = true ;
            task[k] = v ;
            total_task[v]++ ;
            d = d + c[task[k]][k] ;
            if( k==n ) solution() ;
            else
            {
                    if (n==25)
                    {
                        if (d+min_c*(n-k+1)<res)
                            TRY(k+1);
                    }
                    else
                    {
                        if (d+min_c*(n-k+1)<=res)
                            TRY(k+1);
                    }
            }
            appear[k] = false ;
            total_task[v]-- ;
            d = d- c[task[k]][k] ;
        }
    }
}

void solve()
{
    res = INF ;
    for( int i=1 ; i<=m ; i++ ) total_task[i] = 0;
    for (int i=1;i<=n;i++) appear[i]=false;
    d = 0 ;
    TRY(1) ;
    cout << res << endl ;
}
