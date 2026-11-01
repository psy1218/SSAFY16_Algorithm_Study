#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int H, W;
int total = 0;

vector<vector<char>> grid;

struct pos {
    int x = 0;
    int y = 0;
    int direction = -1;

    int start_x = 0;
    int start_y = 0;
    int start_direction = -1;

    int cnt = 0;

    string commands;
};

vector<pos> result;

int dxdy[4][2] = {
    {-1, 0},  // 북
    {0, -1},  // 서
    {1, 0},   // 남
    {0, 1}    // 동
};

const char direction_char[4] = {
    '^', '<', 'v', '>'
};

bool is_valid(int y, int x) {
    return y >= 0 && y < H && x >= 0 && x < W;
}

// 현재 위치에서 해당 방향으로 2칸 전진 가능한지 확인
bool is_valid_2forward(
    int y,
    int x,
    int direction,
    const vector<vector<bool>>& visit
) {
    int dy = dxdy[direction][0];
    int dx = dxdy[direction][1];

    int ny1 = y + dy;
    int nx1 = x + dx;

    int ny2 = y + 2 * dy;
    int nx2 = x + 2 * dx;

    if (!is_valid(ny1, nx1) || !is_valid(ny2, nx2)) {
        return false;
    }

    if (grid[ny1][nx1] != '#' || grid[ny2][nx2] != '#') {
        return false;
    }

    if (visit[ny1][nx1] || visit[ny2][nx2]) {
        return false;
    }

    return true;
}

// BFS로 경로의 끝점 찾기
pos bfs(int start_y, int start_x) {

    vector<vector<bool>> visit(
        H, vector<bool>(W, false)
    );

    queue<pos> q;

    pos start_pos;
    start_pos.y = start_y;
    start_pos.x = start_x;

    q.push(start_pos);
    visit[start_y][start_x] = true;

    pos last_pos = start_pos;

    while (!q.empty()) {
        pos cur_pos = q.front();
        q.pop();
        last_pos = cur_pos;
        for (int i = 0; i < 4; i++) {
            int dy = dxdy[i][0];
            int dx = dxdy[i][1];

            int ny = cur_pos.y + dy;
            int nx = cur_pos.x + dx;

            if (is_valid(ny, nx)) {
                if (!visit[ny][nx] && grid[ny][nx] == '#') {
                    visit[ny][nx] = true;
                    pos nxt_pos;
                    nxt_pos.y = ny;
                    nxt_pos.x = nx;
                    q.push(nxt_pos);
                }
            }
        }
    }
    return last_pos;
}

// 시작점에서 모든 # 칸을 방문하는 명령어 생성
void bfs2(int start_y, int start_x) {

    vector<vector<bool>> visit(
        H, vector<bool>(W, false)
    );

    queue<pos> q;

    pos start_pos;

    start_pos.y = start_y;
    start_pos.x = start_x;

    start_pos.start_y = start_y;
    start_pos.start_x = start_x;

    start_pos.cnt = 1;

    // 처음 바라볼 방향 결정
    for (int i = 0; i < 4; i++) {

        int ny = start_y + dxdy[i][0];
        int nx = start_x + dxdy[i][1];

        if (is_valid(ny, nx) && grid[ny][nx] == '#') {

            start_pos.direction = i;
            start_pos.start_direction = i;

            break;
        }
    }

    if (start_pos.direction == -1) {
        return;
    }
    q.push(start_pos);
    visit[start_y][start_x] = true;
    while (!q.empty()) {
        pos cur_pos = q.front();
        q.pop();

        // 모든 # 칸을 방문했다면 결과 저장
        if (cur_pos.cnt == total) {
            result.push_back(cur_pos);
            return;
        }

        for (int i = 0; i < 4; i++) {
            if (!is_valid_2forward(cur_pos.y, cur_pos.x, i, visit)) {
                continue;
            }

            pos nxt_pos = cur_pos;

            // 현재 방향과 이동할 방향 비교
            int diff = (i - cur_pos.direction + 4) % 4;

            if (diff == 1) {
                nxt_pos.commands += 'L';
            }
            else if (diff == 2) {
                nxt_pos.commands += "RR";
            }
            else if (diff == 3) {
                nxt_pos.commands += 'R';
            }

            // 두 칸 전진
            nxt_pos.commands += 'A';

            int dy = dxdy[i][0];
            int dx = dxdy[i][1];

            // 첫 번째 칸 방문 처리
            visit[cur_pos.y + dy][cur_pos.x + dx] = true;

            // 두 번째 칸 방문 처리
            visit[cur_pos.y + 2 * dy][cur_pos.x + 2 * dx] = true;

            nxt_pos.y = cur_pos.y + 2 * dy;
            nxt_pos.x = cur_pos.x + 2 * dx;
            nxt_pos.direction = i;
            nxt_pos.cnt += 2;
            q.push(nxt_pos);
            break;
        }
    }
}

int main() {
    cin >> H >> W;
    grid.resize(H, vector<char>(W));

    int first_y = -1;
    int first_x = -1;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '#') {
                total++;
                // 처음 발견한 # 좌표 저장
                if (first_y == -1) {
                    first_y = i;
                    first_x = j;
                }
            }
        }
    }

    // 첫 번째 끝점 찾기
    pos endpoint1 = bfs(first_y, first_x);

    // 반대쪽 끝점 찾기
    pos endpoint2 = bfs(endpoint1.y, endpoint1.x);

    // 양쪽 끝점에서 각각 경로 탐색
    bfs2(endpoint1.y, endpoint1.x);
    bfs2(endpoint2.y, endpoint2.x);

    // 명령어 개수가 가장 적은 결과 선택
    sort(
        result.begin(),
        result.end(),
        [](const pos& a, const pos& b) {

            if (a.commands.size() != b.commands.size()) {
                return a.commands.size() < b.commands.size();
            }

            // 명령어 개수가 같으면 행이 큰 좌표 우선
            if (a.start_y != b.start_y) {
                return a.start_y > b.start_y;
            }

            // 행이 같으면 열이 큰 좌표 우선
            return a.start_x > b.start_x;
        }
    );

    if (result.empty()) {
        return 0;
    }

    pos answer = result[0];

    cout << answer.start_y + 1 << " "
        << answer.start_x + 1 << "\n";

    cout << direction_char[answer.start_direction] << "\n";

    cout << answer.commands << "\n";

    return 0;
}
