#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

const int INF = 1'000'000'000;

// 특정 유형에 mentorCount명을 배정했을 때의 대기 시간
int calculateWait(const vector<pair<int, int>>& requests, int mentorCount) {
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < mentorCount; i++) {
        pq.push(0);
    }

    int totalWait = 0;

    for (auto [start, duration] : requests) {
        int earliest = pq.top();
        pq.pop();

        int actualStart = max(start, earliest);

        totalWait += actualStart - start;

        pq.push(actualStart + duration);
    }

    return totalWait;
}

int solution(int k, int n, vector<vector<int>> reqs) {

    // 1. 상담 유형별 요청 분리
    vector<vector<pair<int, int>>> requests(k + 1);

    for (const auto& req : reqs) {
        int start = req[0];
        int duration = req[1];
        int type = req[2];

        requests[type].push_back({ start, duration });
    }

    // 2. 유형별 상담원 수에 따른 대기 시간 계산
    vector<vector<int>> wait(k + 1, vector<int>(n + 1, 0));

    for (int t = 1; t <= k; t++) {
        for (int m = 1; m <= n - k + 1; m++) {
            wait[t][m] = calculateWait(requests[t], m);
        }
    }

    // 3. DP 초기화
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, INF));
    dp[0][0] = 0;

    // 4. 상담 유형별 인원 배정
    for (int t = 1; t <= k; t++) {
        for (int used = t; used <= n; used++) {
            for (int m = 1; m <= used - (t - 1); m++) {

                if (dp[t - 1][used - m] == INF)
                    continue;

                dp[t][used] = min(
                    dp[t][used],
                    dp[t - 1][used - m] + wait[t][m]
                );
            }
        }
    }

    return dp[k][n];
}