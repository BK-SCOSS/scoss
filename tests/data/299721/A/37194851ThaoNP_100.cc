#include <bits/stdc++.h>
using namespace std;

int N;
int M;
int s[1000001];
int cnt = 0;
int sum_now;

void input() {
    cin >> N >> M;
    for (int i=0;i<N;i++) cin >> s[i];
}

void solution() {
    for (int i=0;i<N;i++) {
        sum_now = 0;
        for (int j=i;j<N;j++) {
            if ((sum_now + s[j]) <= M) {
                sum_now += s[j];
                cnt++;
            }
            else break;
        }
    }
    cout << cnt << endl;
}

int main() {
    input();
    solution();
    return 0;
}