#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

vector<long long> dx = { 0, 0, -1, 1 };
vector<long long> dy = { -1, 1, 0, 0 };

int main() {
	int tc;
	cin >> tc;

	for (int i = 0; i < tc; i++) {
		int n;
		cin >> n;

		vector<vector<long long>> graph(n, vector<long long>(n));
		for (int j = 0; j < n; j++) {
			string num;
			cin >> num;

			for (int k = 0; k < num.size(); k++) {
				graph[j][k] = num[k] - '0';
			}
		}

		// 각 이동 비용을 저장하는 2차원 배열
		vector<vector<long long>> visit(n, vector<long long>(n, INT_MAX));
		visit[0][0] = graph[0][0];

		queue<pair<long long, long long>> que;
		que.push({ 0, 0 });

		long long y, x;
		while (!que.empty()) {
			y = que.front().first;
			x = que.front().second;
			que.pop();

			// 상하좌우 이동
			for (int j = 0; j < 4; j++) {
				long long next_y = y + dy[j];
				long long next_x = x + dx[j];
				if (next_y >= 0 && next_y < n && next_x >= 0 && next_x < n) {
					long long next_cost = visit[y][x] + graph[next_y][next_x];
					if (visit[next_y][next_x] > next_cost) {
						visit[next_y][next_x] = next_cost;
						que.push({ next_y, next_x });
					}
				}
			}

		}

		// 도착지에 저장된 비용 출력
		cout << "#" << i + 1 << " " << visit[n - 1][n - 1] << "\n";
	}
}