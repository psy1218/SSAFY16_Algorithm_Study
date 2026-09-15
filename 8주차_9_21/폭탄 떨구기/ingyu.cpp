#include <iostream>
#include <algorithm>

using namespace std;

int n, k;
int x[50000];

bool is_possible(int R) {
    int bomb_cnt = 0;
    int i = 0;
    while (i < n) {
        // 가장 왼쪽의 아직 제거되지 않은 점 x[i]
        bomb_cnt++;
        // 폭탄을 x[i] + R에 떨어뜨림
        // 따라서 x[i] ~ x[i] + 2R까지 제거 가능
        long long range_end = (long long)x[i] + 2LL * R;

        // 해당 폭탄으로 제거되는 점들 건너뛰기
        while (i < n && x[i] <= range_end) {
            i++;
        }
        if (bomb_cnt > k) {
            return false;
        }
    }

    return true;
}

int main() {
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    sort(x, x + n);
    int start = 0;
    int end = x[n - 1] - x[0];
    int answer = end;

    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (is_possible(mid)) {
            answer = mid;
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }

    cout << answer;

    return 0;
}
