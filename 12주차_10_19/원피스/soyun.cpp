#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<char>>board;
int visited[51][51][64]; // 방문했는지 여부 확인 및 포네그리프 비트 파악 
						 // 2의 6승 -> 비트마스킹 = 64 (a~f)

int N, M;

int dr[4] = { 1,-1,0,0 };
int dc[4] = { 0,0,1,-1 };

struct Info{
	int r;
	int c;
	int dist; // 실제로 이동하는 경로  -> 퍼는 경로 
	int mask;
};

int bfs(int row, int col) {
	queue<Info>q;
	q.push({ row,col, 0, 0 });
	visited[row][col][0] = 1;

	while (!q.empty()) {
		auto cur = q.front();
		int cr = cur.r;
		int cc = cur.c;
		int cd = cur.dist;
		int cm = cur.mask;
		q.pop();

		if (board[cr][cc] == '1') {
			return cd;
		}

		for (int i = 0; i < 4; i++) {
			int nr = cr + dr[i];
			int nc = cc + dc[i];

			if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
			if (board[nr][nc] == '#')continue;

			// 대문자일 경우
			if (board[nr][nc] >= 'A' && board[nr][nc] <= 'F') {
				if (!(cm & (1 << (int)(board[nr][nc] - 'A')))) continue;
			}

			// 소문자일 경우 
			int nm = cm;
			if (board[nr][nc] >= 'a' && board[nr][nc] <= 'f') {
				nm = cm | (1 << (int)(board[nr][nc] - 'a'));
			}

			if (visited[nr][nc][nm]) continue; // 이미 방문한 포네그리프도 패스! 

			q.push({ nr,nc,cd + 1,nm });
			visited[nr][nc][nm] = 1;
		}

	}

	return -1;
}

int main() {

	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
	
		int answer = 0;

		cin >> N >> M;

		board.assign(N, vector<char>(M));
		
		int start_r = 0;
		int start_c = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> board[i][j];
				if (board[i][j] == '0') {
					start_r = i;
					start_c = j;
				}
			}
		}

		for (int i = 0; i < 51; i++) {
			for (int j = 0; j < 51; j++) {
				for (int k = 0; k < 64; k++) {
					visited[i][j][k] = 0;
				}
			}
		}

		answer = bfs(start_r, start_c);

		cout << "#" << t << " " << answer << '\n';
	}

	return 0;
}

/*

3
1 7
f0.F..1
5 5
0#c#a
eEDEe
#d#.C
#A.Ec
#..e1
3 6
#b####
a0ABC1
#c####

*/