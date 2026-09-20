#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int n, m;
int board[100][100];

// BFS 탐색용 구조체
struct QUE_INFO {
    int y, x;
};

// BFS 탐색용 큐
int front, rear;
QUE_INFO que[1000000];

bool visited[100][100];

// 4방향 탐색
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

/* 방문 배열 초기화 */
void init() {
    front = rear = 0;

    for (int i = 0; i < n; i++) {
        fill(visited[i], visited[i] + m, false);
    }
}


/* 방문 가능 여부 반환 */
bool can_visit(int y, int x, int low, int high) {
    // 범위 확인
    if (y < 0 || y >= n || x < 0 || x >= m) {
        return false;
    }

    // 방문 여부 확인
    if (visited[y][x]) {
        return false;
    }

    // 높이 범위에 속함 여부 확인
    if (board[y][x] < low || board[y][x] > high) {
        return false;
    }

    return true;
}


/* BFS 탐색 */
bool bfs(int low, int high) {
    init();

    visited[0][0] = true;
    que[rear++] = { 0, 0 };

    while (front < rear) {
        QUE_INFO& cur = que[front++];

        // 목적지 도착
        if (cur.y == n - 1 && cur.x == m - 1) {
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];

            // 좌표 범위 확인
            if (!can_visit(ny, nx, low, high)) {
                continue;
            }

            visited[ny][nx] = true;
            que[rear++] = { ny, nx };
        }
    }

    return false;
}


/* 높이 차 d로 도착 가능한지 확인 */
bool possible(int d, int min_num, int max_num) {
    int start_num = board[0][0];
    for (int low = min_num; low + d <= max_num; low++) {
        int high = low + d;

        // 시작점이 범위 안에 있는지 확인하고 BFS 탐색
        if (start_num >= low && start_num <= high && bfs(low, high)) {
            return true;
        }
    }

    return false;
}


int main() {
    cin >> n >> m;

    int min_num = INT_MAX;
    int max_num = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];

            min_num = min(min_num, board[i][j]);
            max_num = max(max_num, board[i][j]);
        }
    }

    int left = 0;
    int right = max_num - min_num;
    int answer = right;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (possible(mid, min_num, max_num)) {
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