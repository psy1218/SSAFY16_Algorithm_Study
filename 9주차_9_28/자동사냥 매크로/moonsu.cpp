#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;


// 위치 정보 구조체
struct POS {
	int y, x;
};

// 적 정보 구조체
struct ENERMY_INFO {
	POS pos;
	int move_value;
};

// 적 정보 정렬 구조체
struct ENERMY_COMP {
	bool operator() (ENERMY_INFO& a, ENERMY_INFO& b) {
		if (a.move_value == b.move_value) {
			if(a.pos.y == b.pos.y) {
				return a.pos.x < b.pos.x;
			}

			return a.pos.y < b.pos.y;
		}

		return  a.move_value < b.move_value;
	}
};

// 적 정보
int enermy_idx;
ENERMY_INFO enermy[400];

// 맵 정보
int map[20][20];

// 큐 정보
int front, rear;
ENERMY_INFO que[400];

// flood fill 방문 배열
bool visited[20][20];

int n, answer;

// 방향 배열
int dy[] = {-1, 0, 1, 0};
int dx[] = {0, 1, 0, -1};

/* 빠른 입출력 설정 */
void fast_io() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}


/* 맵 정보 입력 */
void input_map(POS& pos) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				pos = { i, j };
				map[i][j] = 0;
			}
		}
	}
}


/* 이동 가능한지 확인 */
bool can_move(POS pos) {
	if (pos.y < 0 || pos.y >= n || pos.x < 0 || pos.x >= n) {
		return false;
	}

	if (visited[pos.y][pos.x]) {
		return false;
	}

	return true;
}


/* 적 위치 탐색 */
bool search_enermy(int level, POS& pos) {
	// 초기화
	enermy_idx = 0;
	front = rear = 0;
	memset(visited, false, sizeof(visited));
	
	// 초기 위치 큐에 삽입
	que[rear++] = { pos, 0 };
	visited[pos.y][pos.x] = true;

	while (front < rear) {
		ENERMY_INFO& cur = que[front++];

		for (int i = 0; i < 4; i++) {
			int ny = cur.pos.y + dy[i];
			int nx = cur.pos.x + dx[i];

			// 이동 불가하거나, 현재 레벨보다 높은 경우
			if (!can_move({ny, nx}) || map[ny][nx] > level) {
				continue;
			}

			// 이동 가능하고, 현재 레벨보다 낮은 경우
			if (map[ny][nx] < level && map[ny][nx]) {
				enermy[enermy_idx++] = { {ny, nx}, cur.move_value + 1 };
			}

			visited[ny][nx] = true;
			que[rear++] = { {ny, nx}, cur.move_value + 1 };
		}
	}

	// 잡을 수 있는 적이 없는 경우
	if (!enermy_idx) {
		return false;
	}

	// 정렬 후, 가장 가까운 적 위치로 이동
	sort(enermy, enermy + enermy_idx, ENERMY_COMP());

	pos = enermy[0].pos; // 내 위치 초기화
	answer += enermy[0].move_value; // 이동 비용 저장
	map[enermy[0].pos.y][enermy[0].pos.x] = 0; // 적 제거

	return true;
}


int main() {
	fast_io();

	POS pos;

	cin >> n;
	input_map(pos);

	answer = 0;
	int level = 2;
	int exp = 0;
	while (true) {
		if (!search_enermy(level, pos)) {
			break;
		}

		exp++;
		if (exp == level) {
			level++;
			exp = 0;
		}
	}

	cout << answer;
}