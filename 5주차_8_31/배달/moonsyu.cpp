#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct edge_info {
    int dest, dist; // 목적지, 거리
};

vector<edge_info> graph[51];
int visit[51];

struct pq_comp {
    bool operator()(const edge_info& e1, const edge_info& e2) {
        return e1.dist > e2.dist;
    }
};


int solution(int N, vector<vector<int>> road, int K) {
    fill(visit, visit + 51, INT_MAX);

    // 그래프 생성
    for (int i = 0; i < road.size(); i++) {
        int s = road[i][0];
        int e = road[i][1];
        int value = road[i][2];

        graph[s].push_back({ e, value });
        graph[e].push_back({ s, value });
    }

    // pq 및 방문 표시
    priority_queue<edge_info, vector<edge_info>, pq_comp> pq;
    visit[1] = 0;
    pq.push({ 1, 0 });

    // 탐색
    int answer = 0;
    while (!pq.empty()) {
        // pq.top() 데이터 조회
        edge_info data = pq.top();
        pq.pop();

        int dest = data.dest;
        int dist = data.dist;

        // K 시간보다 큰 비용 소요 시 탐색 종료
        if (dist > K) {
            break;
        }

		// 최단거리가 맞다면 방문한 마을 수 증가
        if (visit[dest] == dist) {
            answer++;
        }

        // 각 마을에서 이동 가능한 마을 탐색
        int edge_cnt = graph[dest].size();
        for (auto& edge : graph[dest]) {
            int n_dest = edge.dest;
            int n_dist = edge.dist + dist;

            // 이미 방문한 정보보다 최단거리일 경우 pq.push()
            if (visit[n_dest] > n_dist) {
                visit[n_dest] = n_dist;
                pq.push({ n_dest, n_dist });
            }
        }
    }

    return answer;
}