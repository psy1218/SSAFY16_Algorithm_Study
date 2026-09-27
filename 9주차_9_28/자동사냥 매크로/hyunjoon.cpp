#if 01
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int board[20][20];

struct player {
	pair<int, int> loc;
	int level = 2;
	int exp = 0;
}typedef player_T;

int N;
int M;

player_T player;

int dr[4] = { -1, 0,1,0 };
int dc[4] = { 0,-1,0,1 };

int ans = 0;
bool check_edge(int r, int c) {
	if (r >= 0 && r < N && c >= 0 && c < N) return true;
	else return false;
}

void hunt(int r, int c) {
	// exp 증가
	player.exp++;
	// 레벨업 가능한지 확인
	if (player.exp == player.level) {
		player.level++;
		player.exp = 0;
	}
	// 플레이어 위치 update
	player.loc = { r, c };
	// 몬스터 삭제
	board[r][c] = 0;
}

// board_cp를 flood fill 해주는 bfs
bool bfs() {
	queue<pair<int, int>> q;
	//vector<vector<bool>> visited(N, vector<bool>(N, 0));
	vector<vector<int>> board_cp(N, vector<int>(N, INT_MAX));

	int shortest = INT_MAX;
	q.push(player.loc);
	board_cp[player.loc.first][player.loc.second] = 0;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		if (board[cur.first][cur.second] < player.level && board[cur.first][cur.second] != 9 &&
			board[cur.first][cur.second] != 0) {
			if (shortest > board_cp[cur.first][cur.second]) {
				shortest = board_cp[cur.first][cur.second];
			}
		}

		for (int i = 0; i < 4; i++) {
			int nr = dr[i] + cur.first;
			int nc = dc[i] + cur.second;
			// edge 검사
			if (!check_edge(nr, nc)) continue;
			if (board_cp[nr][nc] <= board_cp[cur.first][cur.second] + 1) continue;
			//if(visited[nr][nc]) continue;
			// player의 레벨보다 더 높으면 이동 불가
			if (board[nr][nc] > player.level) continue;
			board_cp[nr][nc] = board_cp[cur.first][cur.second] + 1;
			q.push({ nr,nc });
		}
	}
	/*---------- debug print ---------------*/
	if (shortest == INT_MAX) return false;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// board에 몬스터가 있는 위치이고, board_cp에 shortest가 적혀져 있는 칸이면
			if (board[i][j] != 0 && board[i][j] < player.level && board_cp[i][j] == shortest) {
				hunt(i, j);
				ans += shortest;
				return true;
			}
		}
	}
}

int main(void) {
	//(void)freopen("자동사냥매크로.txt", "r", stdin);
	cin >> N;
	pair<int, int> start;
	// inputdata
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if (board[i][j] >= 1 && board[i][j] <= 6) {
				M++;
			}
			if (board[i][j] == 9) {
				player.loc = { i,j };
				board[i][j] = 0;
			}
		}
	}

	while (bfs()){
	}
	cout << ans;
}


#endif
