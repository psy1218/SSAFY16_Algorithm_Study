#include <iostream>
#include <algorithm>

using namespace std;

int N;
int memoization[1001][3][3];

int recursive(int day, int b, int t) {
    if (t >= 3 || b >= 3) return 0;
    if (day == N) return 1;

    // 이미 계산한 상태
    if (memoization[day][b][t] != -1)
        return memoization[day][b][t];

    // 계산
    // int 범위(약 2 * 10^9) 로는 3 ^ 1000 을 커버할 수 없음
    long long answer = 0;
    answer += recursive(day + 1, 0, t);
    answer += recursive(day + 1, b + 1, t);
    answer += recursive(day + 1, 0, t + 1);

    return memoization[day][b][t] = (answer % (1'000'000'000 + 7));
}

int main() {
    cin >> N;

    for (int i = 0; i < 1001; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                memoization[i][j][k] = -1;
            }
        }
    }

    cout << recursive(0, 0, 0);

    return 0;
}