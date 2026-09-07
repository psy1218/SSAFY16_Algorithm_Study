#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, k;
int grid[100][100];
int r, c;

struct Pos {
    int r;
    int c;
};

int main() {
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    cin >> r >> c;
    r--;
    c--;

    int dr[4] = { -1, 0, 0, 1 };
    int dc[4] = { 0, -1, 1, 0 };

    queue<Pos> route;
    vector<vector<bool>> visited(n + 1, vector<bool>(n + 1, 0));
    Pos init_pos = { r, c };
    route.push(init_pos);
    Pos curr_pos;
    Pos max_able_pos = init_pos;
    int nr;
    int nc;

    for (int i = 0; i < k; i++) {
        while (!route.empty()) {
            curr_pos = route.front();
            route.pop();
            visited[curr_pos.r][curr_pos.c] = 1;

            for (int dir_idx = 0; dir_idx < 4; dir_idx++) {
                nr = curr_pos.r + dr[dir_idx];
                nc = curr_pos.c + dc[dir_idx];

                if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                if (grid[init_pos.r][init_pos.c] <= grid[nr][nc]) continue;
                if (visited[nr][nc]) continue;
                else {
                    if (max_able_pos.r == init_pos.r && max_able_pos.c == init_pos.c) {
                        max_able_pos.r = nr;
                        max_able_pos.c = nc;
                    }
                    else {
                        if (grid[max_able_pos.r][max_able_pos.c] < grid[nr][nc]) {
                            max_able_pos.r = nr;
                            max_able_pos.c = nc;
                        }
                        else if (grid[max_able_pos.r][max_able_pos.c] == grid[nr][nc]) {
                            if (max_able_pos.r > nr || (max_able_pos.r == nr && max_able_pos.c > nc)) {
                                max_able_pos.r = nr;
                                max_able_pos.c = nc;
                            }
                        }
                    }
                    route.push({ nr, nc });
                    visited[nr][nc] = 1;
                }
            }
        }

        if (max_able_pos.r == init_pos.r && max_able_pos.c == init_pos.c) break;
        else {
            init_pos = max_able_pos;
            route.push(init_pos);
            visited.assign(n + 1, vector<bool>(n + 1, 0));
        }
    }

    cout << (max_able_pos.r + 1) << " " << (max_able_pos.c + 1);
}
