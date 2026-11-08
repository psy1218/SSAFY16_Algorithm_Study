#include <vector>
#include <algorithm>
using namespace std;

int solution(int temperature, int t1, int t2,
    int a, int b, vector<int> onboard) {

    const int INF = 1'000'000'000;
    const int OFFSET = 10;
    const int SIZE = 51;  // -10 ~ 40도

    int n = onboard.size();

    vector<vector<int>> memoization(n, vector<int>(SIZE, INF));

    // 음수 온도를 배열 인덱스로 변환
    int outside = temperature + OFFSET;
    int low = t1 + OFFSET;
    int high = t2 + OFFSET;

    // 0분: 실내 온도는 실외 온도와 같음
    memoization[0][outside] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int temp = 0; temp < SIZE; temp++) {

            if (memoization[i][temp] == INF) continue;

            // 1. 에어컨 OFF
            int next = temp;

            if (temp < outside) next++;
            else if (temp > outside) next--;

            memoization[i + 1][next] = min(
                memoization[i + 1][next],
                memoization[i][temp]
            );

            // 2. 에어컨 ON: 온도 유지
            memoization[i + 1][temp] = min(
                memoization[i + 1][temp],
                memoization[i][temp] + b
            );

            // 3. 에어컨 ON: 온도 1도 상승
            if (temp + 1 < SIZE) {
                memoization[i + 1][temp + 1] = min(
                    memoization[i + 1][temp + 1],
                    memoization[i][temp] + a
                );
            }

            // 4. 에어컨 ON: 온도 1도 하강
            if (temp - 1 >= 0) {
                memoization[i + 1][temp - 1] = min(
                    memoization[i + 1][temp - 1],
                    memoization[i][temp] + a
                );
            }
        }

        // 다음 시점에 승객이 탑승 중이라면
        // 쾌적 온도 범위 밖의 상태는 제거
        if (onboard[i + 1] == 1) {
            for (int temp = 0; temp < SIZE; temp++) {
                if (temp < low || temp > high) {
                    memoization[i + 1][temp] = INF;
                }
            }
        }
    }

    // 마지막 시점에서 가능한 최소 비용
    int answer = INF;

    for (int temp = 0; temp < SIZE; temp++) {
        answer = min(answer, memoization[n - 1][temp]);
    }

    return answer;
}