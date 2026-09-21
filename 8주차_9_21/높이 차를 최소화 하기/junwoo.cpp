#include <iostream>
#include <queue>

using namespace std;

int n, m;
int board[100][100];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool bfs(int low, int high){
    // 시작점 자체가 범위 밖이면 불가능
    if (board[0][0] < low || board[0][0] > high){
        return false;
    }

    // 도착점 자체가 범위 밖이면 불가능
    if (board[n-1][m-1] < low || board[n-1][m-1] > high){
        return false;
    }

    bool visited[100][100] = {};

    queue<pair<int, int>> q;

    q.push({0, 0});
    visited[0][0] = true;

    while (!q.empty()){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        if (r == n-1 && c == m-1){
            return true;
        }

        for (int d = 0; d < 4; d++){
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr < 0 || nr >= n || nc < 0 || nc >= m){
                continue;
            }

            if (visited[nr][nc]){
                continue;
            }

            // 허용한 높이 범위 벗어나면 이동 불가
            if (board[nr][nc] < low || board[nr][nc] > high){
                continue;
            }

            visited[nr][nc] = true;
            q.push({nr, nc});
        }
    }

    return false;
    
}

bool possible(int diff){
    for (int low = 1; low + diff <= 500; low++){
        int high = low + diff;

        if (bfs(low, high)){
            return true;
        }
    }

    return false;
}

int main() {
    cin >> n >> m;

    int min_val = 1000;
    int max_val = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
            if (min_val > board[i][j]){
                min_val = board[i][j];
            }
            if (max_val < board[i][j]){
                max_val = board[i][j];
            }
        }
    }

    int answer = board[n-1][m-1] - board[0][0];

    // Please write your code here.
    int left = 0;
    int right = max_val - min_val;

    while (left <= right){
        int mid = (left + right) / 2;

        if (possible(mid)){
            answer = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }

    }

    cout << answer << "\n";

    return 0;
}
