#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

vector<vector<int>> map;
vector<vector<int>> dist;
int N;

int dr[4] = { 0,1,0,-1 };
int dc[4] = { 1,0,-1,0 };

bool edge_check(int r, int c) {
	if (r >= 0 && r < N && c >= 0 && c < N) return true;
	else return false;
}

int dfs() {
	queue<pair<int, int>> q;
	q.push({ 0,0 });
	dist.assign(N, vector<int>(N, INT_MAX));
	dist[0][0] = 0;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		int cost = dist[cur.first][cur.second];

		for (int i = 0; i < 4; i++) {
			int nr = dr[i] + cur.first;
			int nc = dc[i] + cur.second;
			if (!edge_check(nr, nc)) continue;
			int n_cost = map[nr][nc] + cost;

			if (n_cost < dist[nr][nc]) {
				dist[nr][nc] = n_cost;
				q.push({ nr,nc });
			}
		}
	}

	return dist[N-1][N-1];
}

int main(void) {
	//(void)freopen("swea1249.txt", "r", stdin);
	int T = 0;
	cin >> T;
	for (int test_case = 1; test_case <= T; test_case++) {
		cin >> N;
		map.assign(N, vector<int>(N, 0));
		for (int i = 0; i < N; i++) {
			string s;
			cin >> s;
			for (char j = 0; j < N; j++) {
				map[i][j] = (int)(s[j]-'0');
			}
		}
		cout <<"#"<<test_case <<" "<< dfs() << '\n';
	}
}
