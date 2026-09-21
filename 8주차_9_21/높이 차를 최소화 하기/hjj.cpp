#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, m;
int board[100][100];

struct State {
    int row;
    int col;
    int gap_of_height;
};

int main() {
    cin >> n >> m;
    if (n > 100 || m > 100) return 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    int dr[2] = { 0, 1 };
    int dc[2] = { 1, 0 };

    queue<State> route;
    route.push({ 0, 0, 500 });

    State curr;
    int curr_gap_of_height;
    int nr = 0;
    int nc = 0;

    int max_h = board[0][0];
    int min_h = board[0][0];

    int answer = 500;
    priority_queue<int> answers;

    while (!route.empty()) {
        curr = route.front();
        route.pop();

        if (curr.row == n - 1 && curr.col == m - 1) {
            answers.push(-curr.gap_of_height);
            continue;
        }

        for (int dir_idx = 0; dir_idx < 2; dir_idx++) {
            nr = curr.row + dr[dir_idx];
            nc = curr.col + dc[dir_idx];

            if (nr >= n || nc >= m) {
                continue;
            }
            else {
                max_h = max(max_h, board[nr][nc]);
                min_h = min(min_h, board[nr][nc]);
                curr_gap_of_height = max_h - min_h;
                route.push({ nr, nc, curr_gap_of_height });
            }
        }
    }

    if (!answers.empty()) {
        cout << -answers.top() << "\n";
    }
    else cout << answer << "\n";
}
