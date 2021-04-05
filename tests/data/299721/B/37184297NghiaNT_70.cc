#include <iostream>
#include <bits/stdc++.h> 

#define MOD 1000000007

using namespace std;



unsigned long long mod(string num, unsigned long long a) 
{ 
    unsigned long long res = 0; 
  
    for (int i = 0; i < num.length(); i++) 
         res = (res*10 + (int)num[i] - '0') % a; 
  
    return res; 
}

int main()
{
    int n;
    cin >> n;
    unsigned long prod = 1;
    
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        prod = prod * num;
        prod = mod(to_string(prod), MOD);
    }
    
    cout << prod;
    return 0;
}