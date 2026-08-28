#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<pair<int, int>>>board;
vector<int>dist;
vector<int>info;

vector<vector<pair<int, int>>>reverse_board;
// board 원래 방향 그래프 / reverse_board 간선을 뒤집은 그래프
// board 간선 관리를 따로 만들어서 역추적 가능.
// board 하나에 뒤집은 간선 추가했으면 양방향임. 

void Input(int N, int M, int X) {

	board.assign(N + 1, {});
	reverse_board.assign(N + 1, {});

	int start, goal, cost;

	for (int i = 0; i < M; i++) {
		cin >> start >> goal >> cost;
		board[start].push_back({ goal, cost });
		reverse_board[goal].push_back({ start, cost });
	}
}

void dijkstra(vector<vector<pair<int, int>>>& board, int X, int N) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq;
	dist.assign(N + 1, INT_MAX);

	pq.push({ 0, X });
	dist[X] = 0;

	while (!pq.empty()) {
		auto cur = pq.top();
		int cur_cost = cur.first;
		int cur_pos = cur.second;
		pq.pop();

		if (dist[cur_pos] < cur_cost) continue;

		for (int i = 0; i < board[cur_pos].size(); i++) {
			int next_pos = board[cur_pos][i].first;
			int next_cost = board[cur_pos][i].second;

			if (dist[next_pos] > next_cost + cur_cost) {
				dist[next_pos] = next_cost + cur_cost;
				pq.push({ next_cost + cur_cost , next_pos });
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		info[i] += dist[i];
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {

		int N, M, X;
		cin >> N >> M >> X;

		Input(N, M, X);

		info.assign(N + 1, 0);

		
		dijkstra(board, X, N); // 각 노드의 dijkstra
		dijkstra(reverse_board, X, N);

		sort(info.begin(), info.end());
		int answer = info[N];

		cout << "#" << t << " " << answer << "\n";
	}

	return 0;
}


/*

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<pair<int, int>>>board;
vector<int>dist;
vector<int>info;

void Input(int N, int M, int X) {

	board.assign(N + 1, {});


	int start, goal, cost;

	for (int i = 0; i < M; i++) {
		cin >> start >> goal >> cost;
		board[start].push_back({ goal, cost });
	}
}

void dijkstra(int start, int X, int N) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq;
	dist.assign(N+1, INT_MAX);

	pq.push({ 0, start });
	dist[start] = 0;

	while (!pq.empty()) {
		auto cur = pq.top();
		int cur_cost = cur.first;
		int cur_pos = cur.second;
		pq.pop();

		if (dist[cur_pos] < cur_cost) continue;

		for (int i = 0; i < board[cur_pos].size(); i++) {
			int next_pos = board[cur_pos][i].first;
			int next_cost = board[cur_pos][i].second;

			if (dist[next_pos] > next_cost + cur_cost) {
				dist[next_pos] = next_cost + cur_cost;
				pq.push({ next_cost + cur_cost , next_pos });
			}
		}
	}

	if (start == X) {
		for (int i = 1; i <= N; i++) {
			info[i] += dist[i];
		}
	}
	else {
		info[start] += dist[X];
	}
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {

		int N, M, X;
		cin >> N >> M >> X;

		Input(N, M, X);

		info.assign(N + 1, 0);

		for (int i = 1; i <= N; i++) {
			dijkstra(i, X, N); // 각 노드의 dijkstra
		}

		sort(info.begin(), info.end());
		int answer = info[N];

		 cout << "#" << t << " " << answer << "\n";
	}

	return 0;
}



*/
