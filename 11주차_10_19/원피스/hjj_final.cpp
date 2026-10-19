#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Status {
    int x = 0;
    int y = 0;
    unsigned int poneglyph = 0b0;
    int d = -1;
};

unsigned int update_poneglyph(unsigned int curr_comb, char new_poneglyph) {
    int idx = int(new_poneglyph) - int('a');

    return (curr_comb | (0b1 << idx));
}

bool is_pass(unsigned int comb, char secret_sea) {
    int idx = int(secret_sea) - int('A');

    if ((comb >> idx) & 0b1) return true;
    else return false;
}

int main() {
    int T;
    cin >> T;

    int dx[4] = { 1, -1, 0, 0 };
    int dy[4] = { 0, 0, 1, -1 };

    vector<vector<char>> worldmap;
    vector<vector<vector<bool>>> visited;

    for (int test_case = 1; test_case <= T; test_case++) {
        int N, M;
        cin >> N >> M;

        worldmap.assign(N, vector<char>(M));
        visited.assign(N, vector<vector<bool>>(M, vector<bool>(64, 0)));
        Status start;
        start.d = 0;
        Status end;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> worldmap[i][j];
                if (worldmap[i][j] == '0') {
                    start.x = j;
                    start.y = i;
                }
                else if (worldmap[i][j] == '1') {
                    end.x = j;
                    end.y = i;
                }
            }
        }

        queue<Status> route;
        route.push(start);
        visited[start.y][start.x][start.poneglyph] = true;

        Status curr_status;
        char curr_cell, next_cell;
        unsigned int curr_poneglyph;
        int x, y, nx, ny;

        while (!route.empty()) {
            curr_status = route.front();
            route.pop();

            x = curr_status.x;
            y = curr_status.y;
            curr_poneglyph = curr_status.poneglyph;

            // 도착한 경우
            if (x == end.x && y == end.y) {
                end.d = curr_status.d;
                break;
            }

            curr_cell = worldmap[y][x];

            // 새로운 포네그리프를 발견할 경우
            if (int(curr_cell) - int('a') >= 0 && int(curr_cell) - int('a') < 6) {
                curr_poneglyph = update_poneglyph(curr_poneglyph, curr_cell);
            }

            // 탐색
            for (int dir_idx = 0; dir_idx < 4; dir_idx++) {
                nx = x + dx[dir_idx];
                ny = y + dy[dir_idx];

                // 갈 수 없는 경우 필터
                // 1. 영역을 벗어난 경우
                if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;

                next_cell = worldmap[ny][nx];
                // 2. 이미 현재 포네그리프 상태에서 방문한 지역인 경우
                if (visited[ny][nx][curr_poneglyph]) continue;
                // 3. 갈 수 없는 경우 (소용돌이)
                if (next_cell == '#') continue;
                // 4. 포네그리프를 읽어야만 통과할 수 있는 바다인데, 해당하는 포네그리프를 소지하지 않은 경우
                else if (next_cell - int('A') >= 0 && int(next_cell) - int('A') < 6) {
                    if (!is_pass(curr_poneglyph, worldmap[ny][nx])) continue;
                }

                // 갈 수 있는 경우 루트 추가
                route.push({ nx, ny, curr_poneglyph, curr_status.d + 1 });
                visited[ny][nx][curr_poneglyph] = true;
            }
        }

        cout << "#" << test_case << " " << end.d << "\n";
        worldmap.clear();
        visited.clear();
    }
}