#include <bits/stdc++.h>
using namespace std;

const int MAX = 100000;
int N, M;
int a[MAX];
int noSeq = 0;

void subSeq(int k, int v) {
    if (k > N) return;
    if (v > N) {
        subSeq(k + 1, k + 1);
    } else {
        int curSum = 0;
        for (int i = k; i <= v; i++) {
            curSum += a[i];
        }
        if (curSum <= M) {
            noSeq += 1;
            subSeq(k, v + 1);
        } else {
            subSeq(k + 1, k + 1);
        }
    }
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    subSeq(1, 1);
    cout << noSeq;
}