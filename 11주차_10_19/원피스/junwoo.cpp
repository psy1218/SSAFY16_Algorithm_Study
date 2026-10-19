#include<iostream>
#include <queue>
#include <string>
using namespace std;

struct State {
	int r;
	int c;
	int mask;
	int dist;
};

int N;
int M;
string board[50];
bool visited[50][50][64];

int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

int bfs(int sr, int sc) {
	queue<State> q;

	q.push({ sr, sc, 0, 0 });
	visited[sr][sc][0] = true;

	while (!q.empty()) {
		State cur = q.front();
		q.pop();

		int r = cur.r;
		int c = cur.c;
		int mask = cur.mask;
		int dist = cur.dist;

		if (board[r][c] == '1') {
			return dist;
		}

		for (int d = 0; d < 4; d++) {
			int nr = r + dr[d];
			int nc = c + dc[d];

			if (nr < 0 || nr >= N || nc < 0 || nc >= M) {
				continue;
			}

			char cell = board[nr][nc];

			if (cell == '#') {
				continue;
			}

			int nextMask = mask;

			// 포네그리프 획득
			if (cell >= 'a' && cell <= 'f') {
				int bit = cell - 'a';
				nextMask |= (1 << bit);
			}

			// 포네그리프가 필요한 바다
			if (cell >= 'A' && cell <= 'F') {
				int bit = cell - 'A';

				if (!(mask & (1 << bit))) {
					continue;
				}
			}

			if (visited[nr][nc][nextMask]) {
				continue;
			}

			visited[nr][nc][nextMask] = true;
			q.push({ nr, nc, nextMask, dist + 1 });

		}
	}

	return -1;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N >> M;
		int sr = 0;
		int sc = 0;

		for (int r = 0; r < N; r++) {
			cin >> board[r];

			for (int c = 0; c < M; c++) {
				if (board[r][c] == '0') {
					sr = r;
					sc = c;
				}
			}
		}

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				for (int mask = 0; mask < 64; mask++) {
					visited[r][c][mask] = false;
				}
			}
		}

		cout << "#" << test_case << " " << bfs(sr, sc) << "\n";


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
