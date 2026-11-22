#include <string>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int row, col;
vector<string> board2;
int dxdy[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

bool is_valid(int x, int y) {
    return x >= 0 && x < col && y >= 0 && y < row;
}

// (x, y)에서 4방향으로 미끄러져 멈추는 위치들을 반환
vector<pair<int, int>> beam(int x, int y) {
    vector<pair<int, int>> result;
    for (int d = 0; d < 4; d++) {
        int dx2 = dxdy[d][0];
        int dy2 = dxdy[d][1];
        int nx = x;
        int ny = y;
        while (is_valid(nx, ny)) {
            nx += dx2;
            ny += dy2;
            if (!is_valid(nx, ny)) {            // 벽에 닿으면 한 칸 전
                result.push_back({nx - dx2, ny - dy2});
                break;
            }
            if (board2[nx][ny] == 'D') {        // 장애물이면 한 칸 전
                result.push_back({nx - dx2, ny - dy2});
                break;
            }
        }
    }
    return result;
}

int solution(vector<string> board) {
    board2 = board;
    row = board[0].size();
    col = board.size();
    pair<int, int> start = {0, 0}, goal = {0, 0};
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (board[i][j] == 'R') start = {i, j};
            if (board[i][j] == 'G') goal = {i, j};
        }
    }

    // 다익스트라 (최소 힙)
    int INF = 10e8;
    vector<vector<int>> distance(col, vector<int>(row, INF));
    priority_queue<tuple<int, int, int>,
                   vector<tuple<int, int, int>>,
                   greater<tuple<int, int, int>>> pq;
    distance[start.first][start.second] = 0;
    pq.push({0, start.first, start.second});

    while (!pq.empty()) {
        auto [dist, x, y] = pq.top();
        pq.pop();
        if (dist != distance[x][y]) continue;   // 더미 데이터
        for (auto [nxt_x, nxt_y] : beam(x, y)) {
            if (dist + 1 < distance[nxt_x][nxt_y]) {
                distance[nxt_x][nxt_y] = dist + 1;
                pq.push({dist + 1, nxt_x, nxt_y});
            }
        }
    }

    int answer = distance[goal.first][goal.second];
    if (answer == INF) answer = -1;
    return answer;
}
