#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
int board[101][101];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool bfs(int low, int high) {
    // 시작점과 도착점부터 범위 안에 있어야 함
    if (board[0][0] < low || board[0][0] > high)
        return false;

    if (board[n - 1][m - 1] < low || board[n - 1][m - 1] > high)
        return false;

    bool visited[101][101] = {};
    queue<pair<int, int>> q;

    q.push({0, 0});
    visited[0][0] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == n - 1 && y == m - 1)
            return true;

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                continue;

            if (visited[nx][ny])
                continue;

            // 허용된 높이 범위를 벗어나면 이동 불가
            if (board[nx][ny] < low || board[nx][ny] > high)
                continue;

            visited[nx][ny] = true;
            q.push({nx, ny});
        }
    }

    return false;
}

bool is_possible(int diff) {
    // 사용할 최소 높이 low를 하나씩 시도
    for (int low = 1; low + diff <= 500; low++) {
        int high = low + diff;

        if (bfs(low, high))
            return true;
    }

    return false;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    int left = 0;
    int right = 499;
    int answer = 499;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (is_possible(mid)) {
            answer = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    cout << answer;

    return 0;
}
