#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
int board[100][100];

int dr[4] = { 1,-1,0,0 };
int dc[4] = { 0,0,1,-1 };


bool bfs(int low, int high) {
	
	// 시작점이나 도착점 범위 확인 
	if (board[0][0] < low || board[0][0] > high || board[n - 1][m - 1] < low || board[n - 1][m - 1] > high) return false;

	vector<vector<int>>visited(n, vector<int>(m, 0));

	queue<pair<int, int>>q;

	q.push({ 0,0 });
	visited[0][0] = true;

	while (!q.empty()) {
		auto cur = q.front();
		int cr = cur.first;
		int cc = cur.second;
		q.pop();

		if (cr == n - 1 && cc == m - 1) return true;

		for (int i = 0; i < 4; i++) {
			int nr = cr + dr[i];
			int nc = cc + dc[i];

			if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;

			if (visited[nr][nc]) continue;

			if (board[nr][nc] < low || board[nr][nc] > high) continue;

			visited[nr][nc] = true;
			q.push({ nr,nc });
		}
	}

	return false;
}


bool possible(int D) {

	// low와 high 후보를 만들어서 bfs 돌려서 가능한지 파악. 
	// 얘네는 진짜 높이 후보들 .  두 개씩 짝 지어서 판단. 
	for (int low = 1; low + D <= 500; low++) { 
		
		int high = low + D;

		if (bfs(low, high)) return true;
	}

	return false;

}

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
		}
	}

	// left, right 는 높이가 아니라 최소 차에 대한 후보들임. 그래서 뺐을 때 가장 작은 0 과 최대 500-1 인 499로 left, right 설정.  
	int left = 0;
	int right = 499;

	while (left < right) {
		int mid = (left + right) / 2;

		if (possible(mid)) right = mid;
		else left = mid + 1;
	}

	cout << left;


	return 0;
}
