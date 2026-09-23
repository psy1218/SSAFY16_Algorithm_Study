#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Pos {
	int x;
	int y;
};

struct playerState {
	Pos pos;
	int level = 2;
	int exp = 0;
	int d = 0;
};

void lvlup(playerState& ps) {
	if (ps.exp >= ps.level) {
		ps.exp -= ps.level;
		ps.level++;
	}
}

int main() {
	int n;
	cin >> n;

	vector<vector<int>> gameMap(n, vector<int>(n));
	int monsters[10] = { 0, };
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
			gameMap[y][x] = 0;
			curr_state.exp++;
			playtime += curr_state.d;
			curr_state.d = 0;
			lvlup(curr_state);
			while (!routes.empty()) routes.pop();
			visited.clear();
			visited.assign(n, vector<bool>(n, false));
		}
		visited[y][x] = true;

		int curr_able_to_hunting_monsters = 0;
		for (int i = 1; i < curr_state.level; i++) curr_able_to_hunting_monsters++;
		if (!curr_able_to_hunting_monsters) break;

		for (int dir_idx = 0; dir_idx < 4; dir_idx++) {
			nx = x + dx[dir_idx];
			ny = y + dy[dir_idx];

			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (visited[ny][nx]) continue;
			if (gameMap[ny][nx] > curr_state.level) continue;
			npos = { nx, ny };
			routes.push({ npos, curr_state.level, curr_state.exp, curr_state.d + 1 });
		}
	}

	cout << playtime;
}