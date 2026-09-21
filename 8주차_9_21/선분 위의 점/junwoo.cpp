#include <iostream>
#include <algorithm>

using namespace std;

int n, m;

int points[100000];

int st[100000], ed[100000];

int lower_bound_idx(int target) {
    int left = 0;
    int right = n;

    while (left < right) {
        int mid = (left + right) / 2;

        if (points[mid] >= target) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }

    return left;
}

int upper_bound_idx(int target) {
    int left = 0;
    int right = n;

    while (left < right) {
        int mid = (left + right) / 2;

        if (points[mid] > target) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }

    return left;
}

int main() {

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> points[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> st[i] >> ed[i];
    }

    // 이분 탐색을 위해 점들을 정렬
    sort(points, points + n);

    for (int i = 0; i < m; i++) {

        // st[i] 이상인 첫 번째 위치
        int left_idx = lower_bound_idx(st[i]);

        // ed[i]보다 큰 첫 번째 위치
        int right_idx = upper_bound_idx(ed[i]);

        cout << right_idx - left_idx << '\n';
    }

    return 0;
}
