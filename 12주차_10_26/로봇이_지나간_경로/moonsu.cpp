// y중 가장 큰거 > x중 가장 큰거

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/* 정답 구조체 */
struct Data {
    int y, x, dir;
	int path_len = INT_MAX;
    string path = "";
};

// 정답
Data answer;


// 출발지 정보 구조체
struct Pair {
	int y, x;
};

struct cmp {
    bool operator()(const Pair& a, const Pair& b) {
        if (a.y == b.y) {
            return a.x > b.x;
        }

        return a.y > b.y;
    }
};

// 출발지 배열
int loc_size;
Pair loc[25 * 25];
int s_y, s_x, s_dir;


// 기본 정보
int H, W;
vector<vector<char>> grid;
vector<vector<bool>> visited;

// 최대 점유 위치 개수
int full_move;

// 방향
char dir[4] = { '>', 'v', '<', '^' };

// 4방향 탐색
int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };


/* 이동 가능 여부 반환 */
bool can_move(int y, int x, int dir) {
    for (int i = 1; i < 3; i++) {
		y += dy[dir];
		x += dx[dir];

        // 범위 확인
        if (y < 0 || y >= H || x < 0 || x >= W) {
            return false;
        }

        // 방문 여부
        if (visited[y][x]) {
            return false;
        }

        // 이동 가능 여부
        if (grid[y][x] != '#') {
            return false;
        }
    }

    return true;
}

void dfs(int y, int x, int dir, string path, int path_len) {
    // 모든 경로에 방문 했을 경우
    if (path_len == full_move) {
		if (answer.path.empty() || answer.path.size() > path.size()) {
			answer = {s_y, s_x, s_dir, path_len, path};
		}

		return;
    }

    int ny, nx, nd;

    // 우회전
    nd = (dir + 1) % 4;
    if (can_move(y, x, nd)) {
        for (int i = 1; i <= 2; i++) {
            ny = y + dy[nd] * i;
            nx = x + dx[nd] * i;

            visited[ny][nx] = true;
        }

        dfs(ny, nx, nd, path + "RA", path_len + 2);

        for (int i = 1; i <= 2; i++) {
            ny = y + dy[nd] * i;
            nx = x + dx[nd] * i;

            visited[ny][nx] = false;
        }
    }


	// 좌회전
    nd = (dir + 3) % 4;
    if (can_move(y, x, nd)) {
        for (int i = 1; i <= 2; i++) {
            ny = y + dy[nd] * i;
            nx = x + dx[nd] * i;

            visited[ny][nx] = true;
        }

        dfs(ny, nx, nd, path + "LA", path_len + 2);

        for (int i = 1; i <= 2; i++) {
            ny = y + dy[nd] * i;
            nx = x + dx[nd] * i;

            visited[ny][nx] = false;
        }
    }

    // 직진
	ny = y + dy[dir] * 2;
	nx = x + dx[dir] * 2;
    if (can_move(y, x, dir)) {
        for (int i = 1; i <= 2; i++) {
            ny = y + dy[dir] * i;
            nx = x + dx[dir] * i;

            visited[ny][nx] = true;
        }

        dfs(ny, nx, dir, path + "A", path_len + 2);

        for (int i = 1; i <= 2; i++) {
            ny = y + dy[dir] * i;
            nx = x + dx[dir] * i;

            visited[ny][nx] = false;
        }
    }
}


/* 주변에 '#'이 있는지 확인 */
bool check_around(int y, int x) {

    int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || ny >= H || nx < 0 || nx >= W) {
			continue;
		}

		if (grid[ny][nx] == '#') {
            cnt++;
		}
	}

	return cnt == 1;
}


int main() {
    cin >> H >> W;

    full_move = 0;
    grid.resize(H, vector<char>(W));
    visited.resize(H, vector<bool>(W, false));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];

			if (grid[i][j] == '#') {
				full_move++;
			}
        }
    }


	// 출발지 후보 찾기
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (grid[i][j] == '#' && check_around(i, j)) {
                loc[loc_size++] = {i, j};
            }
        }
    }
    
    sort(loc, loc + loc_size, cmp());


    // 출발지 후보에서 경로 탐색
    for (int i = 0; i < loc_size; i++) {
        for (int j = 0; j < 4; j++) {
            s_y = loc[i].y;
            s_x = loc[i].x;
            s_dir = j;

            visited[s_y][s_x] = true;
            dfs(s_y, s_x, s_dir, "", 1);
            visited[s_y][s_x] = false;
        }
    }

	cout << answer.y + 1 << " " << answer.x + 1 << "\n";
	cout << dir[answer.dir] << "\n";
	cout << answer.path << "\n";

    return 0;
}
