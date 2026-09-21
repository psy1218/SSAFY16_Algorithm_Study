#include <iostream>
#include <algorithm>

using namespace std;

int n, k;
int x[50000];

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    sort(x, x + n);

    int start = 0;
    int end = 1000000000;
    int r;
    int answer = end;

    while (start <= end) {
        r = start + (end - start) / 2;

        int d = 0;
        int bombs = 0;
        while (d < n && bombs <= k) {
            d = upper_bound(x + d, x + n, x[d] + 2 * r) - x;
            bombs++;
        }

        if (bombs > k) {
            start = r + 1;
        }
        else {
            answer = r;
            end = r - 1;
        }
    }

    cout << answer << "\n";

    return 0;
}
