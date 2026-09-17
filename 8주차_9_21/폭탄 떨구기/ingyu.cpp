#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int n, k;
int x[50000];

bool is_possible(int R) {
    int i = 0;
    int bomb_cnt = 0;
    long long prev;
    long long cur_point;
    int cur;
    while (i < n) {
        cur_point = x[i]; // x[i] > prev 가 되는 최초의 (가장 왼쪽의) 인덱스 i
        prev = (long long)cur_point + 2LL * R; // 2LL = 정수2를 long long 자료형으로 선언하겠다는 뜻. 이 long long 자료형과 정수형을 곱한 결과의 자료형도 long long
        bomb_cnt++; // 폭탄이 터졌다고 가정. cur_point + R + 1 에.
        while (i < n && x[i] <= prev) { // x[i] > prev 가 되는 시점에 break
            // 현재 점의 좌표가 가장 오른쪽 좌표보다 왼쪽에 있으면 다음 좌표 탐색
            cur = x[i];
            i++;
        }

        if (bomb_cnt == k) {
            break; // k번 터졌다면 종료.
        }
    }
    if (i >= n) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    // 그리디로 풀면 됨. 매번 남아 있는 점 중에서 제일 왼쪽 점에 폭파범위가 닿도록 폭탄을 떨어뜨리면 됨.
    // 즉, 가장 왼쪽점이 x라면, 가장 오른쪽 점은 x+2R 이 됨.
    // 그리고 x 다음 점(오른쪽 점)을 순회하면서 이미 터졌는지 확인하고, 터졌다면 다음 점으로 순회.
    // 아직 터지지 않았으면 다시 그 점 x2부터 x2+2R 범위를 폭파시키면 됨.
    // 폭탄 터졌는지 여부는 prev에 직전의 폭발 범위 오른쪽 끝 좌표를 저장해서, 그보다 왼쪽인지 오른쪽인지 여부를 파악하면 됨.
    sort(x, x + n);
    long long start = 0;
    long long end = x[n-1] - x[0]; // 가장 큰 범위
    long long mid;
    long long ans = 10e8;
    while (start <= end) {
        mid = (start + end) / 2;
        // cout << mid << "\n";
        if (is_possible(mid)) {
            end = mid - 1;
            ans = min(ans, mid);
        }
        else {
            start = mid + 1;
        }
    }
    cout << ans;
    return 0;
}
