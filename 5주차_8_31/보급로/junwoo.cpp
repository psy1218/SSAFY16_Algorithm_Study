#include<iostream>
#include <string>

using namespace std;
const int INF = 1000000000;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int c_to_i(char c) {
	return c - '0';
}

struct Node {
	int r = -1;
	int c = -1;
	int cost = 0;
};

struct PQ {
	Node heap[20001];
	int heap_size = 0;

	bool higherPriority(int a, int b) {
		return heap[a].cost < heap[b].cost;
	}

	void swapHeap(int a, int b) {
		Node temp = heap[a];
		heap[a] = heap[b];
		heap[b] = temp;
	}

	void push(int r, int c, int cost) {
		Node node;
		node.r = r;
		node.c = c;
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
			return { -1, -1, -1 };
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

struct Solution {

	int** graph;
	int N = 0;
	PQ pq;

	void init(int n) {
		N = n;
		graph = new int* [n];
		for (int i = 0; i < n; i++) {
			graph[i] = new int[n] { 0 };
		}

		for (int r = 0; r < n; r++) {
			string line;
			cin >> line;

			for (int c = 0; c < n; c++) {
				graph[r][c] = c_to_i(line[c]);
			}
		}
	}

	int dijkstra(int start_r, int start_c, int end_r, int end_c) {
		int** cost = new int*[N];
		for (int i = 0; i < N; i++) {
			cost[i] = new int[N] {0};
		}
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				cost[r][c] = INF;
			}
		}

		cost[start_r][start_c] = 0;
		pq.push(start_r, start_c, 0);

		while (!pq.empty()) {
			Node cur = pq.pop();
			int cur_r = cur.r;
			int cur_c = cur.c;
			int cur_cost = cur.cost;

			// 이미 더 짧은 경로를 찾은 상태면 무시
			if (cur_cost != cost[cur_r][cur_c]) {
				continue;
			}

			for (int i = 0; i < 4; i++) {
				int nr = cur_r + dr[i];
				int nc = cur_c + dc[i];

				if (nr < 0 || nr >= N || nc < 0 || nc >= N) {
					continue;
				}

				int new_cost = cur_cost + graph[nr][nc];
				if (cost[nr][nc] > new_cost) {
					cost[nr][nc] = new_cost;
					pq.push(nr, nc, new_cost);
				}
			}

		}

		return cost[end_r][end_c];

	}

};

int main(int argc, char** argv)
{
	int test_case;
	int T;
	int answer;

	cin >> T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int N;
		cin >> N;
		
		Solution solution;
		solution.init(N);
		answer = solution.dijkstra(0, 0, N - 1, N - 1);

		cout << "#" << test_case << " " << answer << "\n";

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
