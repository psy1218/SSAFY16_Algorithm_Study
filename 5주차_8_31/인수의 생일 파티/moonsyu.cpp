#include <vector>
#include <queue>
#include <climits>
#include <iostream>

using namespace std;

// 간선 정보 구조체
struct edge_info {
	int dest, dist;
};

// 간선 정보
vector<edge_info> graph[1001];
vector<edge_info> reverse_graph[1001];

// PQ 비교 구조체
struct pq_comp {
	bool operator()(const edge_info& e1, const edge_info& e2) {
		return e1.dist > e2.dist; // 거리 기반 탐색
	}
};

// 방문 정보
int visit[1001];
int reverse_visit[1001];

/* 입력 최적화 */
void fast_io() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
}


/* 다익스트라 알고리즘 */
void dijk(vector<edge_info> now_graph[], int now_visit[], int s) {
	priority_queue<edge_info, vector<edge_info>, pq_comp> pq;
	now_visit[s] = 0;
	pq.push({ s, 0 });

	while (!pq.empty()) {
		edge_info data = pq.top();
		pq.pop();

		int dest = data.dest;
		int dist = data.dist;

		for (auto& edge : now_graph[dest]) {
			int n_dest = edge.dest;
			int n_dist = edge.dist + dist;

			if (now_visit[n_dest] > n_dist) {
				now_visit[n_dest] = n_dist;
				pq.push({ n_dest, n_dist });
			}
		}
	}
}


int main() {
	// 입출력 최적화
	fast_io();

	int tc;
	cin >> tc;

	for (int t = 1; t <= tc; t++) {
		int n, m, x;
		cin >> n >> m >> x;

		// 기본 정보 초기화
		fill(visit, visit + 1001, INT_MAX);
		fill(reverse_visit, reverse_visit + 1001, INT_MAX);
		for (int i = 0; i <= n; i++) {
			graph[i].clear();
			reverse_graph[i].clear();
		}

		// 간선 정보 입력
		for (int i = 0; i < m; i++) {
			int s, e, t;
			cin >> s >> e >> t;

			graph[s].push_back({ e, t });
			reverse_graph[e].push_back({ s, t });
		}

		// 최단 거리 탐색 및 기록
		dijk(graph, visit, x);
		dijk(reverse_graph, reverse_visit, x);

		// 최단 거리 중 가장 큰 값 찾기
		int answer = 0;
		for (int i = 0; i <= n; i++) {
			answer = max(answer, visit[i] + reverse_visit[i]);
		}

		cout << "#" << t << " " << answer << "\n";
	}
}