#include<iostream>

using namespace std;
const int INF = 1000000000;

struct Node {
	int node_idx = 0;
	int cost = 0;
};

struct PQ {
	Node heap[30001];
	int heap_size = 0;

	void init() {
		heap_size = 0;
	}

	bool higherPriority(int a, int b) {
		return heap[a].cost < heap[b].cost;
	}

	void swapHeap(int a, int b) {
		Node temp = heap[a];
		heap[a] = heap[b];
		heap[b] = temp;
	}

	void push(int node_idx, int cost) {
		Node node;
		node.node_idx = node_idx;
		node.cost = cost;

		heap[++heap_size] = node;
		int cur = heap_size;

		while (cur > 1) {
			int parent = cur / 2;
			if (higherPriority(parent, cur)) {
				break;
			}

			swapHeap(parent, cur);
			cur = parent;
		}
	}

	Node pop() {
		if (heap_size == 0) {
			return { -1, -1 };
		}

		Node data = heap[1];

		if (heap_size == 1) {
			heap_size--;
			return data;
		}

		heap[1] = heap[heap_size--];
		int cur = 1;
		while (1) {
			int left = cur * 2;
			int right = cur * 2 + 1;
			int best = cur;

			if (left <= heap_size && higherPriority(left, best)) {
				best = left;
			}
			if (right <= heap_size && higherPriority(right, best)) {
				best = right;
			}
			if (best == cur) {
				break;
			}

			swapHeap(best, cur);
			cur = best;
		}

		return data;
	}

	bool empty() {
		if (heap_size == 0) {
			return true;
		}
		return false;
	}

};

struct Birthday {
	int N;
	int M;
	int graph[1001][1001] = { 0 };
	int reverse_graph[1001][1001] = { 0 };
	PQ pq;
	int dijk[1001];

	void init(int n, int m) {
		N = n;
		M = m;

		for (int i = 0; i < m; i++) {
			int a;
			int b;
			int c;
			cin >> a >> b >> c;

			if (graph[a][b] == 0 || graph[a][b] > c) {
				graph[a][b] = c;
				reverse_graph[b][a] = c;
			}
			
		}
	}

	void clear() {
		for (int r = 0; r <= N; r++) {
			for (int c = 0; c <= N; c++) {
				graph[r][c] = 0;
				reverse_graph[r][c] = 0;
			}
		}
	}

	void dijkstra(int start_node, int g[1001][1001]) {
		for (int i = 0; i < 1001; i++) {
			dijk[i] = INF;
		}

		pq.init();

		dijk[start_node] = 0;
		pq.push(start_node, 0);

		while (!pq.empty()) {
			Node cur = pq.pop();
			int cur_node = cur.node_idx;
			int cur_cost = cur.cost;

			if (cur_cost != dijk[cur_node]) {
				continue;
			}

			for (int n_node = 1; n_node < N + 1; n_node++) {
				if (g[cur_node][n_node] == 0) {
					continue;
				}

				int new_cost = cur_cost + g[cur_node][n_node];
				if (dijk[n_node] > new_cost) {
					dijk[n_node] = new_cost;
					pq.push(n_node, new_cost);
				}
			}
		}
	}
};

Birthday birth;
int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{

		int N;
		int M;
		int X;
		
		int max_val = 0;
		int max_node = 0;
		int dijk[1001] = { 0 };

		cin >> N >> M >> X;
		birth.init(N, M);

		int answer = 0;
		birth.dijkstra(X, birth.graph);
		for (int i = 1; i < N + 1; i++) {
			dijk[i] += birth.dijk[i];
		}

		birth.dijkstra(X, birth.reverse_graph);
		for (int i = 1; i < N + 1; i++) {
			dijk[i] += birth.dijk[i];
		}

		for (int i = 1; i < N + 1; i++) {
			if (max_val < dijk[i]) {
				max_val = dijk[i];
			}
		}

		cout << "#" << test_case << " " << max_val << "\n";
		birth.clear();

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
