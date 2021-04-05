
#include <bits/stdc++.h>
using namespace std;
#define N 1000000
 
int main()
{
    int n, m;
    cin >> n >> m;
    int arr[100000];
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int cnt = 0;
    for(int i = 0; i < n; i++)
    {
        int temp = arr[i];
        if(temp <= m)
            cnt += 1;
        else
        {
            continue;
        }
        int j = i + 1;
        while(j < n && temp <= m)
        {
            temp += arr[j];
            if(temp <= m)
                cnt += 1;
            j++;
        }
    }
    cout << cnt << endl;
}