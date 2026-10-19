#include <iostream>
#include <unordered_map>

#define MAX_QUE_SIZE 10000

using namespace std;

// 좌표 구조체
struct Pos {
	int y, x;

	// 좌표 비교
	bool is_same(Pos pos) {
		return this->y == pos.y && this->x == pos.x;
	}
};

// 맵 크기
int n, m;

// 시작 위치 및 목적지 좌표
Pos start, dist;

// 맵 정보 및 방문 여부
char map[50][50];
unordered_map<int, bool> visited[50][50];


/* BFS 탐색을 위한 큐 구조체
pos : 현재 위치
mask : 현재 획득한 키 정보
time : 현재까지 이동한 시간
*/
struct QUE_INFO {
	Pos pos;
	int mask, time;
};

// BFS 탐색을 위한 큐
int front, rear;
QUE_INFO que[MAX_QUE_SIZE];

// 상하좌우 이동을 위한 좌표
int dy[] = { -1, 0, 1, 0 };
int dx[] = { 0, 1, 0, -1 };


/* 입출력 최적화 */
void fast_io() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
}


/* 맵 정보 입력 */
void input() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];

			// 시작위치 및 목적지 저장
			if (map[i][j] == '0') {
				start = { i, j };
			}
			else if (map[i][j] == '1') {
				dist = { i, j };
			}
		}
	}
}


/* 이동 가능한지 확인 */
bool can_move(int y, int x, int mask) {
	// 맵 범위 확인
	if (y < 0 || y >= n || x < 0 || x >= m) {
		return false;
	}

	// 방문 여부 확인
	if (visited[y][x][mask]) {
		return false;
	}

	// 벽인지 확인
	if (map[y][x] == '#') {
		return false;
	}

	// 키 획득 여부 확인
	if (map[y][x] >= 'A' && map[y][x] <= 'F') {
		if (!(mask & (1 << (map[y][x] - 'A')))) {
			return false;
		}
	}

	return true;
}


/* 키 획득 시 마스크 갱신 */
int update_key(int y, int x, int mask, char key) {
	if (map[y][x] >= 'a' && map[y][x] <= 'f') {
		mask |= (1 << (key - 'a'));
	}

	return mask;
}


/* 기본 값 초기화 */
void reset() {
	front = rear = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j].clear();
		}
	}
}


/* BFS 탐색 */
int bfs() {
	reset();
	visited[start.y][start.x][0] = true;
	que[(rear++ % MAX_QUE_SIZE)] = { start, 0, 0 };

	while (front < rear) {
		QUE_INFO& cur = que[(front++ % MAX_QUE_SIZE)];

		// 목적지 도착 시 탐색 중지
		if (cur.pos.is_same(dist)) {
			return cur.time;
		}

		// 4방향 탐색
		for (int i = 0; i < 4; i++) {
			int ny = cur.pos.y + dy[i];
			int nx = cur.pos.x + dx[i];

			// 이동 가능한지 확인
			if (!can_move(ny, nx, cur.mask)) {
				continue;
			}
			visited[ny][nx][cur.mask] = true;

			// 키 획득 시 마스크 갱신
			int new_mask = update_key(ny, nx, cur.mask, map[ny][nx]);
			que[(rear++ % MAX_QUE_SIZE)] = { { ny, nx }, new_mask, cur.time + 1 };
		}
	}

	return -1;
}


int main() {
	fast_io();

	int tc;
	cin >> tc;

	for (int t = 1; t <= tc; t++) {
		cin >> n >> m;

		input();
		cout << "#" << t << " " << bfs() << "\n";
	}
}