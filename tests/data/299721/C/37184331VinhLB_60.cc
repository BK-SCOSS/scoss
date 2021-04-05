#include <bits/stdc++.h>
using namespace std;

const int MAX = 20;

int M, N, noTour = 0, curDistance = 0;
int a[MAX][MAX];
bool visited[MAX];
pair<bool, int> init = pair<bool, int>(false, 0);

bool check(int k, int v) {
    if (k == v) return false;
    if (visited[v]) return false;
    return true;
}

bool done() {
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) return false;
    }
    return true;
}

void goTour(int k) {
    for (int v = 1; v <= N; v++) {
        if (check(k, v)) {
            if (!init.first) {
                init.first = true;
                init.second = k;
            }
            curDistance += a[k][v];
            visited[k] = true;
            visited[v] = true;
            if (done()) {
                curDistance += a[v][init.second];
                if (curDistance <= M) {
                    noTour += 1;
                }
                curDistance -= a[v][init.second];
            } else {
                if (curDistance < M) {
                    goTour(v);
                }
            }
            curDistance -= a[k][v];
            visited[v] = false;
        }
    }
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> a[i][j];
        }
        visited[i] = false;
    }
    goTour(1);
    cout << noTour;
}