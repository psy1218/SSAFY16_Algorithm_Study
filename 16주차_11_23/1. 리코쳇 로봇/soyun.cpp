
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int H, W;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool visited[101][101];
vector<string> grid;

struct Info {
    int r;
    int c;
    int cnt;
};

int bfs(int sr, int sc) {

    queue<Info> q;

    q.push({sr, sc, 0});
    visited[sr][sc] = true;

    while (!q.empty()) {

        Info cur = q.front();
        q.pop();

        if (grid[cur.r][cur.c] == 'G') {
            return cur.cnt;
        }

        for (int d = 0; d < 4; d++) {

            int nr = cur.r;
            int nc = cur.c;

            // 장애물이나 벽을 만날 때까지 이동
            while (true) {

                int next_r = nr + dr[d];
                int next_c = nc + dc[d];

                // 보드 범위를 벗어나면 멈춤
                if (next_r < 0 || next_r >= H ||
                    next_c < 0 || next_c >= W) break;

                // 장애물을 만나면 멈춤
                if (grid[next_r][next_c] == 'D') break;

                // 한 칸 이동
                nr = next_r;
                nc = next_c;
            }

            // 이동하지 못한 경우
            if (nr == cur.r && nc == cur.c) continue;

            // 이미 방문한 위치
            if (visited[nr][nc]) continue;

            // 방문 처리 후 큐에 추가
            visited[nr][nc] = true;
            q.push({nr, nc, cur.cnt + 1});
        }
    }

    // 목표에 도달할 수 없는 경우
    return -1;
}

int solution(vector<string> board) {

    grid = board;

    H = board.size();
    W = board[0].size();

    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {
            visited[r][c] = false;
        }
    }

    int sr = 0;
    int sc = 0;

    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {

            if (grid[r][c] == 'R') {
                sr = r;
                sc = c;
            }
        }
    }

    return bfs(sr, sc);
}


/* 백트래킹은 시간초과 - 테스트 케이스 커서 시간초과 . 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int H, W;
int answer = INT_MAX;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool visited[101][101];
vector<string> grid;

void dfs(int r, int c, int cnt) {

    // 현재 이동 횟수가 기존 정답 이상이면 종료
    if (cnt >= answer) return;

    // 목표 위치에 도착한 경우
    if (grid[r][c] == 'G') {
        answer = min(answer, cnt);
        return;
    }

    for (int d = 0; d < 4; d++) {

        int nr = r;
        int nc = c;

        // 장애물이나 벽을 만날 때까지 이동
        while (true) {

            int next_r = nr + dr[d];
            int next_c = nc + dc[d];

            // 보드 범위를 벗어나면 멈춤
            if (next_r < 0 || next_r >= H ||
                next_c < 0 || next_c >= W) break;

            // 장애물을 만나면 멈춤
            if (grid[next_r][next_c] == 'D') break;

            // 한 칸 이동
            nr = next_r;
            nc = next_c;
        }

        // 이동하지 못한 경우
        if (nr == r && nc == c) continue;

        // 현재 경로에서 이미 방문한 위치
        if (visited[nr][nc]) continue;

        visited[nr][nc] = true;
        dfs(nr, nc, cnt + 1);
        visited[nr][nc] = false;
    }
}

int solution(vector<string> board) {

    grid = board;

    H = board.size();
    W = board[0].size();

    answer = INT_MAX;

    fill(&visited[0][0], &visited[0][0] + 101 * 101, false);

    int sr = 0;
    int sc = 0;

    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {

            if (grid[r][c] == 'R') {
                sr = r;
                sc = c;
            }
        }
    }

    // 시작 위치 방문 처리
    visited[sr][sc] = true;

    dfs(sr, sc, 0);

    // 목표에 도달할 수 없는 경우
    if (answer == INT_MAX) return -1;

    return answer;
}

*/



// 목적지의 사방이 벽이 아니면 도달 불가능 = -1

