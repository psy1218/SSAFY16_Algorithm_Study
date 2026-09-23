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
		ps.level++;
		if (ps.level <= 7) ps.remain_mobs += monsters[ps.level - 1];
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
	visited[user_state.pos.y][user_state.pos.x] = true;

	queue<playerState> routes;
	routes.push(user_state);

	int target_monster_min_d = -1;
	int mx = 20;
	int my = 20;

	playerState curr_state;
	int x, y;
	int nx, ny;
	Pos npos;

	while (!routes.empty()) {
		curr_state = routes.front();
		routes.pop();

		x = curr_state.pos.x;
		y = curr_state.pos.y;

		// 처치 가능 몬스터 탐색 성공
		// 최초 성공 이후부터, 탐색 성공 시마다 문제 조건에 맞는 최적 몬스터 좌표로 초기화
		if (gameMap[y][x] < curr_state.level && gameMap[y][x] != 0) {
			// 최초 탐색 성공 시
			if (target_monster_min_d == -1) {
				target_monster_min_d = curr_state.d;
				mx = x;
				my = y;
			}
			// 이후 탐색 성공 시
			else {
				// 현재 저장된 최적 몬스터 좌표보다 y 좌표가 더 작은 곳에 존재할 경우
				if (my > y) {
					mx = x;
					my = y;
				}
				// 현재 저장된 최적 몬스터 좌표와 y 좌표가 같을 때
				else if (my == y) {
					// 현재 저장된 최적 몬스터 좌표보다 x 좌표가 더 작은 곳에 존재할 경우
					if (mx > x) {
						mx = x;
						my = y;
					}
				}
			}
		}

		// 다음 이동할 경로 저장
		for (int dir_idx = 0; dir_idx < 4; dir_idx++) {
			nx = x + dx[dir_idx];
			ny = y + dy[dir_idx];

			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (visited[ny][nx]) continue;
			if (gameMap[ny][nx] > curr_state.level) continue;
			npos = { nx, ny };
			routes.push({ npos, curr_state.level, curr_state.exp, curr_state.d + 1, curr_state.remain_mobs });
			visited[ny][nx] = true;
		}

		// 몬스터 처치 로직
		// A. 현재 상태 체크 (하나라도 해당 시 바로 continue)
		// 1. 현재 이동 가능한 경로가 비어있다
		// 1-1. 처치 가능한 몬스터를 찾지 못했다
		// 2. 현재 이동 가능한 경로가 존재한다
		// 2-1. 처치 가능한 몬스터를 찾지 못했거나, 아직 탐색할 곳이 남아있다
		if (routes.empty()) {
			if (target_monster_min_d == -1) continue;
		}
		else if (target_monster_min_d == -1 || target_monster_min_d >= routes.front().d) continue;

		// B. A의 조건들 중 어떤 것도 해당되지 않는다면, 몬스터를 처치하면서 다음 탐색 시작
		// 1. 현재 위치를 몬스터 위치로 변경
		// 2. 몬스터 칸 빈칸으로 전환
		// 3. 남아있는 몬스터 수 -1
		// 4. 유저의 경험치 증가 +1
		// 5. 이동거리 만큼 플레이 시간 증가
		// 6. 현재 경험치에 따른 레벨업 처리(lvlup())
		curr_state.pos.x = mx;
		curr_state.pos.y = my;
		gameMap[my][mx] = 0;
		curr_state.remain_mobs--;
		curr_state.exp++;
		playtime += curr_state.d;
		lvlup(curr_state);
		// 각종 초기화
		// 1. 이동거리 초기화
		// 2. 처치 가능 몬스터까지 최소 거리(target_monster_min_d) 초기화
		// 3. 최적 몬스터 좌표 초기화(mx, my)
		// 4. 경로 큐 초기화
		// 5. 방문기록 초기화 (clear(), assign())
		curr_state.d = 0;
		target_monster_min_d = -1;
		mx = 20;
		my = 20;
		while (!routes.empty()) routes.pop();
		routes.push(curr_state);
		visited.clear();
		visited.assign(n, vector<bool>(n, false));
		visited[curr_state.pos.y][curr_state.pos.x] = true;

		// 확인용
		//std::cout << "몬스터 처치 (x = " << curr_state.pos.x << ", y = " << curr_state.pos.y << "), 현재 레벨" << curr_state.level << ", 현재 지난 시간 : " << playtime << ", 남은 몬스터 수 : " << curr_state.remain_mobs << "\n";
	}

	// 출력
	std::cout << playtime;
}