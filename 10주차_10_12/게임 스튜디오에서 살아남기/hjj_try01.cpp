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
    int answer = recursive(day + 1, 0, t) + recursive(day + 1, b + 1, t) + recursive(day + 1, 0, t + 1);

    return memoization[day][b][t] = answer;
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