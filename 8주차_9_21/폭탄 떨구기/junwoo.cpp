#include <iostream>
#include <algorithm>

using namespace std;

int N, K;
int x[100000];

bool possible(int R) {

    int cnt = 0;
    int idx = 0;

    while (idx < N) {

        // 새로운 폭탄 사용
        cnt++;

        // 가장 왼쪽의 아직 제거되지 않은 점
        int start = x[idx];

        // 이 폭탄이 제거할 수 있는 가장 오른쪽 위치
        int end = start + 2 * R;

        // end 이하의 점들을 모두 제거
        while (idx < N && x[idx] <= end) {
            idx++;
        }

        // 이미 K개보다 많이 사용했다면 불가능
        if (cnt > K) {
            return false;
        }
    }

    return true;
}

int main() {

    cin >> N >> K;

    for (int i = 0; i < N; i++) {
        cin >> x[i];
    }

    sort(x, x + N);

    int left = 0;
    int right = x[N - 1] - x[0];

    int answer = right;

    while (left <= right) {

        int mid = (left + right) / 2;

        if (possible(mid)) {
            answer = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    cout << answer << '\n';

    return 0;
}
