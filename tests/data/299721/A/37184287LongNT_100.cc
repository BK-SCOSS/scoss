#include<bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
ull N;
ull M;
int S[10002];
ull tmpSum;
ull cnt;

void INPUT()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
        cin >> S[i];
}


void TRY()
{
    for(int i = 1; i <= N; i++)
    {
        for(int j = i; j <= N; j++)
        {
            if(tmpSum + S[j] <= M)
            {
                cnt++;
                tmpSum += S[j];
                if(j == N)
                    tmpSum = 0;
            }
            else
            {
                tmpSum = 0;
                break;
            }
        }
    }
}

int main()
{
    tmpSum = 0;
    cnt = 0;
    INPUT();
    TRY();
    cout << cnt;
}