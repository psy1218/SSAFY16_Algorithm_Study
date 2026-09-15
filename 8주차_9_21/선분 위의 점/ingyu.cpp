#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int point[100000];

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> point[i];
    }

    sort(point, point + n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        int left = lower_bound(point, point + n, a) - point;
        int right = upper_bound(point, point + n, b) - point;

        cout << right - left << '\n';
    }

    return 0;
}
