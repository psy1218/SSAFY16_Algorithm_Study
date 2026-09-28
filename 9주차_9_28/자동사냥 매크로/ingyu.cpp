#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Monster {
    int dist;
    int r;
    int c;
};

int N;
int board[20][20];

int level = 2;
int expCnt = 0;

int curR, curC;
int totalTime = 0;

int dr[4] = {-1, 0, 0, 1};
int dc[4] = {0, -1, 1, 0};

bool findMonster(int &targetR, int &targetC, int &targetDist) {
    int dist[20][20];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = -1;
        }
    }

    queue<pair<int, int>> q;
    vector<Monster> candidates;

    q.push({curR, curC});
    dist[curR][curC] = 0;

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr < 0 || nr >= N || nc < 0 || nc >= N)
                continue;

            if (dist[nr][nc] != -1)
                continue;

            // 현재 레벨보다 높은 몬스터가 있는 칸은 지나갈 수 없음
            if (board[nr][nc] > level)
                continue;

            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});

            // 현재 레벨보다 낮은 몬스터만 사냥 가능
            if (board[nr][nc] >= 1 && board[nr][nc] < level) {
                candidates.push_back({
                    dist[nr][nc],
                    nr,
                    nc
                });
            }
        }
    }

    if (candidates.empty())
        return false;

    sort(candidates.begin(), candidates.end(),
         [](const Monster &a, const Monster &b) {
             // 1. 거리
             if (a.dist != b.dist)
                 return a.dist < b.dist;

             // 2. 가장 위
             if (a.r != b.r)
                 return a.r < b.r;

             // 3. 가장 왼쪽
             return a.c < b.c;
         });

    targetDist = candidates[0].dist;
    targetR = candidates[0].r;
    targetC = candidates[0].c;

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];

            if (board[i][j] == 9) {
                curR = i;
                curC = j;

                // 캐릭터가 있던 칸은 빈칸으로 처리
                board[i][j] = 0;
            }
        }
    }

    while (true) {
        int targetR;
        int targetC;
        int targetDist;

        // 더 이상 사냥할 수 있는 몬스터가 없으면 종료
        if (!findMonster(targetR, targetC, targetDist))
            break;

        // 이동 시간 추가
        totalTime += targetDist;

        // 해당 몬스터 사냥
        board[targetR][targetC] = 0;

        // 캐릭터 위치 이동
        curR = targetR;
        curC = targetC;

        // 경험치 1 증가
        expCnt++;

        // 경험치와 레벨이 같아지면 레벨업
        if (expCnt == level) {
            level++;
            expCnt = 0;
        }
    }

    cout << totalTime << '\n';

    return 0;
}
