
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int N, M, K;

// 패널 사이 이동 시간
int distPanel[15][15];

// 각 패널에서 엘리베이터까지 거리
int distElevator[15];

// 각 패널을 켜기 전에 필요한 패널 목록
int need[15];


int dp[1 << 15][15];

vector<vector<int>> bfs(
    int sr, int sc, vector<string>& grid
) {
    vector<vector<int>> dist(
        N, vector<int>(M, -1)
    );

    queue<pair<int, int>> q;

    q.push({sr, sc});
    dist[sr][sc] = 0;

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr < 0 || nr >= N ||
                nc < 0 || nc >= M) continue;

            if (grid[nr][nc] == '#') continue;

            if (dist[nr][nc] != -1) continue;

            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});
        }
    }

    return dist;
}

// 두 패널 사이의 이동 시간
int getDist(
    int a, int b, vector<vector<int>>& panels
) {
    // 같은 층이라면 직접 이동
    if (panels[a][0] == panels[b][0]) {
        return distPanel[a][b];
    }

    // 다른 층이라면 반드시 엘리베이터 이용
    int floorDiff = abs(
        panels[a][0] - panels[b][0]
    );

    return distElevator[a]
         + floorDiff
         + distElevator[b];
}

int solution(int h, vector<string> grid,
             vector<vector<int>> panels,
             vector<vector<int>> seqs) {

    N = grid.size();
    M = grid[0].size();
    K = panels.size();

    // 엘리베이터 위치 찾기
    int er = 0;
    int ec = 0;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (grid[r][c] == '@') {
                er = r;
                ec = c;
            }
        }
    }

    // 모든 패널을 기준으로 BFS
    for (int i = 0; i < K; i++) {

        // 문제 좌표는 1부터 시작
        int sr = panels[i][1] - 1;
        int sc = panels[i][2] - 1;

        vector<vector<int>> dist =
            bfs(sr, sc, grid);

        // 현재 패널 -> 엘리베이터
        distElevator[i] = dist[er][ec];

        // 현재 패널 -> 다른 패널
        for (int j = 0; j < K; j++) {
            int nr = panels[j][1] - 1;
            int nc = panels[j][2] - 1;

            distPanel[i][j] = dist[nr][nc];
        }
    }

    // 선행 조건 비트마스킹
    for (int i = 0; i < K; i++) {
        need[i] = 0;
    }

    for (int i = 0; i < seqs.size(); i++) {
        int a = seqs[i][0] - 1;
        int b = seqs[i][1] - 1;

        // b를 켜려면 a가 먼저 켜져 있어야 함
        need[b] |= (1 << a);
    }

    // DP 초기화
    int fullMask = (1 << K) - 1;

    for (int mask = 0; mask <= fullMask; mask++) {
        for (int i = 0; i < K; i++) {
            dp[mask][i] = INF;
        }
    }

    // 기술자는 1번 패널 위치에서 출발
    // 아직 1번 패널이 켜진 것은 아님
    dp[0][0] = 0;

    //  비트마스크 DP
    for (int mask = 0; mask <= fullMask; mask++) {

        for (int cur = 0; cur < K; cur++) {

            if (dp[mask][cur] == INF) continue;

            // 다음에 활성화할 패널 선택
            for (int next = 0; next < K; next++) {

                // 이미 활성화한 패널
                if (mask & (1 << next)) continue;

                // 선행 패널이 모두 활성화됐는지 확인
                if ((mask & need[next]) != need[next])
                    continue;

                // 현재 패널 -> 다음 패널
                int moveCost = getDist(
                    cur, next, panels
                );

                // 이동할 수 없는 경우
                if (moveCost < 0) continue;

                // 다음 패널 활성화
                int nextMask = mask | (1 << next);

                dp[nextMask][next] = min(
                    dp[nextMask][next],
                    dp[mask][cur] + moveCost
                );
            }
        }
    }

    // 모든 패널을 활성화한 최소 시간
    int answer = INF;

    for (int i = 0; i < K; i++) {
        answer = min(answer, dp[fullMask][i]);
    }

    return answer;
}
