#include <iostream>
#define MAX 100001

using namespace std;

int m, n;
int x[MAX];
int count = 0;
int sum = 0;


void input(){
  cin >> n >> m;
  for(int i = 1; i <= n; i++)
  {
    cin >> x[i];
  }
}

bool check(int c){
  if(c <= m) return true;
  else return false;
}

int solve(){
  for(int i = 1; i <= n; i++)
  {
    int tmp = i;
    sum = x[tmp];
    while(sum <= m && tmp <= n)
    {
      tmp++;
      if(sum <= m)
        count++;
      sum += x[tmp];
    }
  }
  return count;
}


int main() {
    int c;
    input();
    c = solve();
    cout << c << endl;
}
