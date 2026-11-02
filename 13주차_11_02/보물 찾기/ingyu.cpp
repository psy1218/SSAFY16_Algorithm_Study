#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

extern int excavate(int);

static int dp[202][202];
static int choice[202][202];

int solution(int depth[], size_t depth_len, int money) {

int n = (int)depth_len;
// 1. 구간의 길이를 1부터 n까지 늘려가며 계산
for (int len = 1; len <= n; len++) {
    for (int start = 1; start + len - 1 <= n; start++) {
        int end = start + len - 1;
        dp[start][end] = INT_MAX;

        // 2. 현재 구간에서 먼저 굴착할 열 선택
        // 즉, [start, end] 구간 사이의 굴착할 열 = k
        for (int k = start; k <= end; k++) {
            int left = 0;
            int right = 0;
            // 왼쪽 구간의 최소 보장 비용
            if (k > start) { // k = start 인 경우엔 그 왼쪽 구간을 탐색할 필요가 없으므로
                left = dp[start][k - 1];
            }
            // 오른쪽 구간의 최소 보장 비용
            if (k < end) { // k = end 인 경우엔 그 오른쪽 구간을 탐색할 필요가 없으므로
                right = dp[k + 1][end];
            }
            // 현재 굴착 비용 + 최악의 경우 비용
            int cost = depth[k - 1]
                + (left > right ? left : right);

            // 가장 비용이 적게 드는 위치 저장
            // 즉, [start, end] 구간 사이의 열 k를 순회하면서, 어떤 k를 먼저 굴착하는게 '최악의 경우에도 보장되는 최소 비용'인지 탐색하는 과정
            // choide[start][end] = [start, end] 구간에서도 어떤 열을 먼저 굴착하냐에 따라서 보물을 찾는데 비용이 달라지는데
            // 최소 비용이 드는 열을 찾는 과정
            if (cost < dp[start][end]) {
                dp[start][end] = cost;
                choice[start][end] = k;
            }
        }
    }
}

// 3. DP에서 계산한 최적 탐색 순서대로 굴착 (이분탐색+dp)
int start = 1;
int end = n;

while (start <= end) {
    int col = choice[start][end];
    int result = excavate(col);
    if (result == 0) {
        return col;
    }
    else if (result == -1) {
        end = col - 1;
    }
    else {
        start = col + 1;
    }
}

return -1;
}
