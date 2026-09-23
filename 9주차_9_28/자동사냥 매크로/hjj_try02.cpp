#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int monsters[10] = { 0, };

struct Pos {
	int x;
	int y;
};

struct playerState {
	Pos pos;
	int level = 2;
	int exp = 0;
	int d = 0;
	int remain_mobs = 0;
};

void lvlup(playerState& ps) {
	if (ps.exp >= ps.level) {
		ps.exp -= ps.level;
		ps.remain_mobs += monsters[ps.level];
		ps.level++;
	}
}

int main() {
	int n;
	cin >> n;

	vector<vector<int>> gameMap(n, vector<int>(n));

	playerState user_state;
	int playtime = 0;

	int cell;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> cell;
			if (cell == 9) {
				user_state.pos.x = j;
				user_state.pos.y = i;
				continue;
			}
			gameMap[i][j] = cell;
			monsters[cell]++;
		}
	}

	user_state.remain_mobs += monsters[1];

	int dx[4] = { 0, -1, 1, 0 };
	int dy[4] = { -1, 0, 0, 1 };

	vector<vector<bool>> visited;
	visited.assign(n, vector<bool>(n, false));

	queue<playerState> routes;
	routes.push(user_state);

	playerState curr_state;
	int x, y;
	int nx, ny;
	Pos npos;

	while (!routes.empty()) {
		curr_state = routes.front();
		routes.pop();

		x = curr_state.pos.x;
		y = curr_state.pos.y;

		if (gameMap[y][x] < curr_state.level && gameMap[y][x] != 0) {
			// 몬스터 처치
			// 1. 몬스터 칸 빈칸으로 전환
			// 2. 남아있는 몬스터 수 -1
			// 3. 유저의 경험치 증가 +1
			// 4. 이동거리 만큼 플레이 시간 증가
			// 5. 현재 경험치에 따른 레벨업 처리(lvlup())
			gameMap[y][x] = 0;
			curr_state.remain_mobs--;
			curr_state.exp++;
			playtime += curr_state.d;
			lvlup(curr_state);
			// 각종 초기화
			// 1. 이동거리 초기화
			// 2. 경로 큐 초기화
			// 3. 방문기록 초기화 (clear(), assign())
			curr_state.d = 0;
			while (!routes.empty()) routes.pop();
			visited.clear();
			visited.assign(n, vector<bool>(n, false));
		}
		// 현재 칸 방문 처리
		visited[y][x] = true;
		// 현재 남아있는 처치 가능한 몬스터 수가 0인 경우 break
		if (!curr_state.remain_mobs) break;

		for (int dir_idx = 0; dir_idx < 4; dir_idx++) {
			nx = x + dx[dir_idx];
			ny = y + dy[dir_idx];

			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (visited[ny][nx]) continue;
			if (gameMap[ny][nx] > curr_state.level) continue;
			npos = { nx, ny };
			routes.push({ npos, curr_state.level, curr_state.exp, curr_state.d + 1, curr_state.remain_mobs });
		}
	}

	cout << playtime;
}