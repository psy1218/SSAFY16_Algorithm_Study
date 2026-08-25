#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <tuple>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;
int dxdy[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
int n;
int INF = 1e9;
bool is_valid(int y, int x) {
	return y >= 0 && y < n && x >= 0 && x < n;
}
int bfs(int n, const int arr[][100]) {
	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> q;
	q.push({ arr[0][0], 0, 0 }); // {누적비용, y, x}
	// cout << arr[n - 1][n - 1] << endl;
	bool visit[100][100];
	memset(visit, false, sizeof(visit));
	visit[0][0] = true;
	int distance[100][100];
	memset(distance, INF, sizeof(distance));
	for (int i = 0; i < n; i++) {
		fill(distance[i], distance[i] + n, INF);
	}
	// cout << "거리:" << distance[n - 1][n - 1] << endl;
	distance[0][0] = arr[0][0];
	while (!q.empty()) {
		int cost = get<0>(q.top());
		int y = get<1>(q.top());
		int x = get<2>(q.top());
		q.pop();
		// cout << cost << endl;
		if (distance[y][x] != cost) {
			continue;
		}
		if (y == n - 1 && x == n - 1) {
			return cost;
		}
		// cout << "디버깅" << endl;
		for (int i = 0; i < 4; i++) {
			int dy = dxdy[i][0];
			int dx = dxdy[i][1];
			int ny = y + dy;
			int nx = x + dx;
			// cout << "현 비용:" << cost + arr[ny][nx] << endl;
			if (is_valid(ny, nx) && !visit[ny][nx] && cost + arr[ny][nx] < distance[ny][nx]) {
				// cout << "통과" << endl;
				visit[ny][nx] = true;
				distance[ny][nx] = cost + arr[ny][nx];
				q.push({ cost + arr[ny][nx], ny, nx });
			}
		}
	}
	return 0;
}
int main() {
	int TC;
	cin >> TC;
	for (int i = 1; i <= TC; i++) {
		cin >> n;
		int arr[100][100];
		for (int j = 0; j < n; j++) {
			string str;
			cin >> str;
			for (int k = 0; k < n; k++) {
				int cur = str[k] - '0';
				arr[j][k] = cur;
			}
		}
		int ans = bfs(n, arr);
		cout << "#" << i << " " << ans << endl;
	}
	return 0;
}
