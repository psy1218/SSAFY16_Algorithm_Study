#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int n, m;
int board[100][100];
int dxdy[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
struct pos {
    int x;
    int y;
};
bool is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}
bool bfs(int low_height, int high_height) {
    if (board[0][0] < low_height || board[0][0] > high_height) {
        return false;
    }
    if (board[n - 1][m - 1] < low_height || board[n - 1][m - 1] > high_height) {
        return false;
    }
    vector<vector<bool>> visit(n, vector<bool>(m));
    // memset(visit, false, sizeof(visit));
    for (int i = 0; i < n; i++) {
        fill(visit[i].begin(), visit[i].end(), false);
    }
    queue<pos> q;
    pos start;
    start.x = 0;
    start.y = 0;
    visit[0][0] = true;
    q.push(start);
    pos cur;
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        int cur_x = cur.x;
        int cur_y = cur.y;
        if (cur_x == n - 1 && cur_y == m - 1) {
            return true; // 가능한 최초의 경우
        }
        for (int i = 0; i < 4; i++) {
            int dx = dxdy[i][0];
            int dy = dxdy[i][1];
            int nx = cur_x + dx;
            int ny = cur_y + dy;
            int nxt_height = board[nx][ny];
            if (is_valid(nx, ny) && !visit[nx][ny] && board[nx][ny] <= high_height && board[nx][ny] >= low_height) {
                visit[nx][ny] = true;
                pos nxt;
                nxt.x = nx;
                nxt.y = ny;
                q.push(nxt);
            }
        }
    }
    return false;
}
bool is_possible(int diff) {
    // 가장 낮은 높이를 정하면 가장 높은 높이는 자동으로 정해진다(+diff)
    // 가장 낮은 높이 1 부터 500-diff 까지 탐색
    for (int low_height = 1; low_height <= 500 - diff; low_height++) {
        int high_height = low_height + diff;
        if (bfs(low_height, high_height)) {
            return true;
        }
    }
    return false; // 가능한 높이차 diff일때의 모든 높이에 대해서 탐색했는데도 가능한 경우가 없을경우 
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    // Please write your code here.
    // 높이차 diff 를 탐색하면서 가능한지 여부 확인
    int start = 0; // 엣지케이스. 가능한 높이차 = 0 인 경우도 있음. (모든 격자의 높이값이 같을때)
    int end = 500;
    int mid;
    int min_value = 500;
    while (start <= end) {
        mid = (start + end) / 2;
        // cout << "mid:" << mid << "\n";
        if (is_possible(mid)) {
            end = mid - 1;
            min_value = min(min_value, mid);
        }
        else {
            start = mid + 1;
        }
    }
    cout << min_value;
    return 0;
}
