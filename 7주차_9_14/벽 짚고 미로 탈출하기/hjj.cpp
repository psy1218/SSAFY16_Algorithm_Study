#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Pos {
    int x;
    int y;
};

struct State {
    Pos pos;
    int t;
};

int main() {
    int n;
    cin >> n;

    int x, y;
    cin >> x >> y;
    x--;
    y--;

    vector<vector<bool>> maze(n, vector<bool>(n, true));
    char curr = '\0';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> curr;
            if (curr == '#') maze[i][j] = false;
        }
    }

    // 각각 오른쪽, 위쪽, 왼쪽, 아래 방향
    // 오른쪽 방향 이동시: 다음 좌표의 아래 칸이 벽인지 확인
    // 위쪽 방향 이동시: 다음 좌표의 오른쪽 칸이 벽인지 확인
    // 왼쪽 방향 이동시: 다음 좌표의 위 칸이 벽인지 확인
    // 아래쪽 방향 이동시: 다음 좌표의 왼쪽 칸이 벽인지 확인
    int dx[4] = { 1, 0, -1, 0 };
    int dy[4] = { 0, -1, 0, 1 };

    int direction_idx = 0;

    queue<State> route;
    route.push({ { x, y }, 0 });

    State curr_state;
    int nx, ny;
    int c_right_x, c_right_y;
    while (!route.empty()) {
        curr_state = route.front();
        route.pop();

        c_right_x = curr_state.pos.x + dx[(direction_idx + 3) % 4];
        c_right_y = curr_state.pos.y + dy[(direction_idx + 3) % 4];
        if (maze[c_right_y][c_right_x]) direction_idx = (direction_idx + 3) % 4;

        for (int i = 0; i < 4; i++) {
            nx = curr_state.pos.x + dx[(direction_idx + i) % 4];
            ny = curr_state.pos.y + dy[(direction_idx + i) % 4];

            if (nx < 0 || nx >= n || ny < 0 || ny >= n) return curr_state.t + 1;
            if (!maze[ny][nx]) continue;
            else {
                direction_idx = direction_idx + i;
                route.push({ {nx, ny}, curr_state.t + 1 });
                break;
            }
        }
    }

    return -1;
}
