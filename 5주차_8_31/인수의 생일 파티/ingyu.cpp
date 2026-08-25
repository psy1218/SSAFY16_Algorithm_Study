#include <stdio.h>
#include <queue>
#include <vector>
#include <cstring>
#include <iostream>
#include <set>
#include <iomanip>

using namespace std;
int INF = 10e8;
int N;

int dijkstra_2(int start, vector<vector<pair<int, int>>>& graph, int first_dist[]) {
	int distance[1001];
	//cout << "시작" << "\n";
	fill(distance, distance + 1001, INF);
	distance[start] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, start });
	//cout << "start:" << start << "\n";
	while (!pq.empty()) {
		int dist = pq.top().first;
		int cur = pq.top().second;
		pq.pop();
		if (distance[cur] < dist) {
			continue;
		}
		for (auto ele : graph[cur]) {
			int nxt_dist = ele.first;
			int nxt = ele.second;
			if (dist + nxt_dist < distance[nxt]) {
				distance[nxt] = dist + nxt_dist;
				pq.push({ dist + nxt_dist, nxt });
			}
		}
	}
	for (int i = 0; i < 1001; i++) {
		first_dist[i] = distance[i];
	}
	return 0;
}

int dijkstra_1(int start, vector<vector<pair<int, int>>>& reverse_graph, int second_dist[]) {
	int distance[1001];
	//cout << "시작" << "\n";
	fill(distance, distance + 1001, INF);
	distance[start] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, start });
	//cout << "start:" << start << "\n";
	while (!pq.empty()) {
		int dist = pq.top().first;
		int cur = pq.top().second;
		pq.pop();
		if (distance[cur] < dist) {
			continue;
		}
		for (auto ele : reverse_graph[cur]) {
			int nxt_dist = ele.first;
			int nxt = ele.second;
			if (dist + nxt_dist < distance[nxt]) {
				distance[nxt] = dist + nxt_dist;
				pq.push({ dist + nxt_dist, nxt });
			}
		}
	}
	for (int i = 0; i < 1001; i++) {
		second_dist[i] = distance[i];
	}
	return 0;
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int max_value = 0;
		int N, M, X;
		int first_dist[1001];
		int second_dist[1001];
		cin >> N >> M >> X;
		// 2차원 벡터 정의
		vector<vector<pair<int, int>>> graph(N + 1); // 초기화
		vector<vector<pair<int, int>>> reverse_graph(N + 1); // 초기화2
		for (int j = 0; j < M; j++) {
			int a, b, w;			
			cin >> a >> b >> w;
			//cout << "a:" << a << "\n";
			graph[a].push_back({ w, b }); // 단방향 이므로
			reverse_graph[b].push_back({ w, a }); // 역방향
		}
		dijkstra_1(X, reverse_graph, second_dist);
		dijkstra_2(X, graph, first_dist);
		for (int i = 1; i <= N; i++) {
			int cur_dist = first_dist[i] + second_dist[i];
			if (max_value < cur_dist) {
				max_value = cur_dist;
			}
		}
		cout << "#" << tc << " " << max_value << "\n";
	}

	return 0;
}
