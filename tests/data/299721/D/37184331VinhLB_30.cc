#include <bits/stdc++.h>
using namespace std;

const int MAX_COL = 31, MAX_ROW = 21;
int N, M, K;
int c[MAX_ROW][MAX_COL];
int slot[MAX_ROW];
bool assigned[MAX_COL];
int curCost = 0, minCost = 0;

bool check(int k, int v) {
    if (assigned[k]) return false;
    return true;
}

bool done() {
    for (int i = 1; i <= N; i++) {
        if (!assigned[i]) return false;
    }
    return true;
}

void doTask(int k) {
    for (int v = 1; v <= M; v++) {
        if (check(k, v)) {
            if (slot[v] > 0) {
                slot[v] -= 1;
                assigned[k] = true;
                curCost += c[v][k];
                if (done()) {
                    if (minCost == 0 || curCost < minCost) {
                        minCost = curCost;
                    }
                } else {
                    doTask(k + 1);
                }
            } else {
                continue;
            }
            if (assigned[k]) {
                slot[v] += 1;
                assigned[k] = false;
                curCost -= c[v][k];
            }

        }
    }
}

int main() {
    cin >> N >> M >> K;
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> c[i][j];
            assigned[j] = false;
        }
        slot[i] = K;
    }
    doTask(1);
    cout << minCost;
}