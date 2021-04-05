//
//  main.cpp
//  ProMod
//
//  Created by Lan Chu on 10/23/20.
//

#include <bits/stdc++.h>
#include <vector>


using namespace std;

/*
vector<unsigned long long> arr;
unsigned long long P;
int n;

void swap(unsigned long long *a, unsigned long long *b)
{
    unsigned long long temp = *a;
    *a = *b;
    *b = temp;
}
 
unsigned long long remainOfSum(unsigned long long a, unsigned long long b, unsigned long long P)
{
    a%=P;
    b%=P;
    unsigned long long temp = P - a;
    if(temp < b)// if a+b > P
        return b - temp;
    else
        return (a+b)%P;
}
 
unsigned long long remainOfProd(unsigned long long a, unsigned long long b, unsigned long long P)
{
    if(a==0||b==0)  return 0;
    if(a==1) return b%P;
    if(b==1) return a%P;
 
    if(a < b)  swap(&a, &b);
    unsigned long long remainOfHalf = remainOfProd(a, b/2, P);
    unsigned long long result = remainOfSum(remainOfHalf, remainOfHalf, P);
 
    if(b%2 == 0)
        return result;
    else
        return remainOfSum(result, a, P);
    return 0;
}

unsigned long long remainOfExp(unsigned long long a, unsigned long long b, unsigned long long P)
{
    if(a <= 1 || b == 1) return a%P;
    if(b == 0) return 1%P;
 
    unsigned long long remainOfHalf = remainOfExp(a, b/2, P);
    unsigned long long result = remainOfProd(remainOfHalf, remainOfHalf, P);
 
    if(b%2 == 0)
        return result;
    else
        return remainOfProd(result, a, P);
    return 0;
}

unsigned long long remainOfSequence()
{
    sort(arr.begin(), arr.end());
    
    unsigned long long result = 1;
    int b = 1;
    unsigned long long
    for(int i=0; i<n-1; ++i)
    {
        if(arr[i] == arr[i + 1])
            b++;
        else
        {
            unsigned long long tempRemain = remainOfExp(arr[i], b, P);
            result = remainOfProd(result, tempRemain, P);
        }
    }
    
    return result;
    
}

int main(int argc, const char * argv[]) {
    P = (int)pow(10, 9) + 7;
    cin >> n;
    for(int i=0; i<n; ++i)
    {
        unsigned long long x; cin >> x;
        arr.push_back(x);
    }
    
    cout << remainOfSequence();
    
    return 0;
}
 */


int main(int argc, const char * argv[])
{
    unsigned long long result = 1;
    unsigned long long n;
    unsigned long long P = (unsigned long long)(pow(10, 9)) + 7;
    
    cin >> n;
    
    for(int i=0; i<n; ++i)
    {
        unsigned long long inputNum;
        cin >> inputNum;
        result = (inputNum * result) % P;
    }
    
    cout << result;
    return 0;
}
