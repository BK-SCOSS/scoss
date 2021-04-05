#include <iostream>

using namespace std;

int main () {
    int n, m, s, count = 0;
    int arr[100000];

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < n; i++) {
        s = 0;
        for (int j = i; j < n; j++) {
            s += arr[j];
            if (s <= m) {
                count++;
            } else {
                break;
            }
        }
    }

    cout << count;

    return 0;
}