#include <iostream>
#include <vector>
using namespace std;

const int INF = 1000000000;

struct Node {
    int cost = 0;
    int idx = -1;
};

struct PQ {
    Node heap[1001];
    int heap_size = 0;

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
        node.idx = node_idx;
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
            if (cur == best) {
                break;
            }

            swapHeap(cur, best);
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

struct Deliver {

    int N;
    int K;
    int** graph;
    PQ pq;

    void init(int n, vector<vector<int>> road, int k) {
        N = n;
        K = k;

        graph = new int* [n + 1];
        for (int i = 0; i < n + 1; i++) {
            graph[i] = new int[n + 1] { 0 };
        }

        for (int r = 0; r < road.size(); r++) {
            int a = road[r][0];
            int b = road[r][1];
            int cost = road[r][2];
            
            if (graph[a][b] == 0 || graph[a][b] > cost) {
                graph[a][b] = cost;
                graph[b][a] = cost;
            }
        }
    }

    int dijkstra(int start_node) {
        int count = 0;

        int dijk[101];
        for (int i = 0; i < 101; i++) {
            dijk[i] = INF;
        }
        dijk[start_node] = 0;
        pq.push(start_node, 0);

        while (!pq.empty()) {
            Node cur = pq.pop();

            int cur_node = cur.idx;
            int cur_cost = cur.cost;

            // 이미 더 짧은 경로를 찾은 상태면 무시
            if (cur_cost != dijk[cur_node]) {
                continue;
            }

            for (int n_node = 1; n_node < N + 1; n_node++) {
                if (graph[n_node][cur_node] == 0) {
                    continue;
                }

                int new_cost = cur_cost + graph[n_node][cur_node];
                if (dijk[n_node] > new_cost) {
                    dijk[n_node] = new_cost;
                    pq.push(n_node, new_cost);
                }
            }
        }

        for (int idx = 1; idx < N + 1; idx++) {
            if (dijk[idx] <= K) {
                count++;
            }
        }
        
        return count;
    }
};

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;

    Deliver deliver;
    deliver.init(N, road, K);
    answer = deliver.dijkstra(1);

    // for (int i = 0; i < N+1; i++){
    //     for (int j = 0; j < N+1; j++){
    //         cout << deliver.graph[i][j] << " ";
    //     }
    //     cout << "\n";
    // }


    return answer;
}
