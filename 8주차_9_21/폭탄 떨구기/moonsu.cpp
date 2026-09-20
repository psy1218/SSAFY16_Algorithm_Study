#include <iostream>
#include <algorithm>

using namespace std;

int n, k;
double boom[50000];

/* 모든 폭탄 제거 가능 여부 반환 */
bool possible(int r) {
    int idx = 0;
    for (int bomb = 0; bomb < k && idx < n; bomb++) {
        // 폭탄 설치 기준 폭발 범위 계산
        int boom_range = boom[idx] + 2 * r;

        // 폭발 범위 내에 있는 폭탄 제거
        while (idx < n && boom[idx] <= boom_range) {
            idx++;
        }
    }

    return idx == n;
}


int main() {
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> boom[i];
    }

    // 폭탄 위치 정렬
    sort(boom, boom + n);

    int left = 0;
    int right = boom[n - 1] - boom[0];

    int answer = right;
    while (left <= right) {
        int mid = (left + right) / 2;

        // 폭탄 제거 가능 여부 확인
        if (possible(mid)) {
            // 가능할 경우 더 작은 R 탐색
            answer = mid;
            right = mid - 1;
        }
        else {
            // 불가능할 경우 더 큰 R 탐색
            left = mid + 1;
        }
    }

    cout << answer;

    return 0;
}