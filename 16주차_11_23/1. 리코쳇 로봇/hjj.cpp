#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Pos {
    int x;
    int y;
};

int solution(vector<string> board) {
    const int n = static_cast<int>(board.size());     // 세로
    const int m = static_cast<int>(board[0].size());  // 가로

    const int dx[4] = { 1, -1, 0, 0 };
    const int dy[4] = { 0, 0, 1, -1 };

    // 1. 시작점과 목표점 찾기
    Pos start{ -1, -1 };
    Pos goal{ -1, -1 };

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            if (board[y][x] == 'R') {
                start = { x, y };
            }
            else if (board[y][x] == 'G') {
                goal = { x, y };
            }
        }
    }

    // 보드 밖이거나 장애물이면 true
    auto isBlocked = [&](int x, int y) -> bool {
        return x < 0 || x >= m ||
            y < 0 || y >= n ||
            board[y][x] == 'D';
        };

    // 2. 목표점 사전 검사
    // 목표점 바로 옆에 장애물이나 보드 경계가 하나도 없다면
    // 어떤 방향에서 접근해도 목표점에서 멈출 수 없다.
    bool hasStopper = false;

    for (int dir = 0; dir < 4; ++dir) {
        int nx = goal.x + dx[dir];
        int ny = goal.y + dy[dir];

        if (isBlocked(nx, ny)) {
            hasStopper = true;
            break;
        }
    }

    if (!hasStopper) return -1;

    // 3. BFS
    // dist[y][x]: 해당 칸에 멈추기까지 필요한 최소 이동 횟수
    // -1이면 아직 방문하지 않은 정지 위치
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<Pos> q;

    dist[start.y][start.x] = 0;
    q.push(start);

    while (!q.empty()) {
        Pos curr = q.front();
        q.pop();

        if (curr.x == goal.x && curr.y == goal.y) {
            return dist[curr.y][curr.x];
        }

        for (int dir = 0; dir < 4; ++dir) {
            int nx = curr.x;
            int ny = curr.y;

            // 다음 칸으로 이동할 수 있는 동안 계속 미끄러진다.
            while (!isBlocked(nx + dx[dir], ny + dy[dir])) {
                nx += dx[dir];
                ny += dy[dir];
            }

            // 최종 정지 위치가 이미 방문한 곳이면 건너뛴다.
            if (dist[ny][nx] != -1) continue;

            dist[ny][nx] = dist[curr.y][curr.x] + 1;
            q.push({ nx, ny });
        }
    }

    // 모든 정지 위치를 탐색했지만 목표점에 도달하지 못한 경우
    return -1;
}