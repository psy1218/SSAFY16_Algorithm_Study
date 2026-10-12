#include <iostream>
#include <algorithm>

using namespace std;

int n;
int coin[1001];
int memoization[1001][4];

int climb(int index, int one_step_remains) {
    // 불가능한 경로
    if (index < 0 || one_step_remains < 0)
        return -1000000000;

    // 출발점
    if (index == 0)
        return 0;

    // 이미 계산한 상태
    if (memoization[index][one_step_remains] != -1)
        return memoization[index][one_step_remains];

    // 2칸 이동
    int answer = climb(index - 2, one_step_remains);

    // 1칸 이동
    if (one_step_remains >= 1) {
        answer = max(
            answer,
            climb(index - 1, one_step_remains - 1)
        );
    }

    // 현재 계단의 동전 추가
    answer += coin[index];

    return memoization[index][one_step_remains] = answer;
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> coin[i];
    }

    for (int i = 0; i < 1001; i++) {
        for (int j = 0; j < 4; j++) {
            memoization[i][j] = -1;
        }
    }

    cout << climb(n, 3);

    return 0;
}