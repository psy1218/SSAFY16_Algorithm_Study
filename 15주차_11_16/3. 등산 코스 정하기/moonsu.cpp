#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_INT 10000001

using namespace std;

// 그래프 정보
struct Edge_Data {
    int summit, node, cost;
};

// pq 정렬 구조체
struct PQ_Comp {
    bool operator()(Edge_Data& p1, Edge_Data& p2) {
        if (p1.cost == p2.cost) {
            return p1.summit > p2.summit;
        }

        return p1.cost > p2.cost;
    }
};

// 등산로 정보
vector<Edge_Data> graph[50001];

// 코스트, node 번호 기준 오름차순 정렬
priority_queue<Edge_Data, vector<Edge_Data>, PQ_Comp> pq;


struct visit_log {
    int summit, value;
};

// 노드 방문 표기
visit_log visit_node[50001];

// 출 입구 여부
bool gate_info[50001];

//--------------------------------------------------

/* 출/입구 및 산봉우리 여부 초기화 */
void reset_info(int& n, vector<vector<int>>& paths, vector<int>& gates, vector<int>& summits) {
    // 출/입구 및 방문 정보 초기화
    fill(gate_info, gate_info + n + 1, false);
    fill(visit_node, visit_node + n + 1, visit_log{ 0, MAX_INT });

    // 등산로 정보 입력
    for (const auto& path : paths) {
        graph[path[0]].push_back({ 0, path[1], path[2] });
        graph[path[1]].push_back({ 0, path[0], path[2] });
    }

    // 출/입구 여부 기록
    for (const auto& gate_num : gates) {
        gate_info[gate_num] = true;
    }
}


/*
* 최단 경로의 출/입구 탐색
* 산봉우리 -> 출/입구
*/
Edge_Data dijkstra() {
    while (!pq.empty()) {
        auto [summit, node, intensity] = pq.top();
        pq.pop();

        // 출/입구에 도착 했을 경우 탐색 중지
        if (gate_info[node]) {
            return { summit, node, intensity };
        }

        // 등산로 탐색
        for (auto& graph_info : graph[node]) {
            int pre_value = visit_node[graph_info.node].value;
            int now_value = max(intensity, graph_info.cost);

            if (pre_value > now_value) {
                visit_node[graph_info.node] = { summit, now_value };
                pq.push({ summit, graph_info.node, now_value });
            }
            else if (pre_value == now_value &&
                visit_node[graph_info.node].summit > summit) {
                visit_node[graph_info.node] = { summit, now_value };
                pq.push({ summit, graph_info.node, now_value });
            }
        }
    }
}


vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    // 모든 정보 초기화
    reset_info(n, paths, gates, summits);

    for (auto& summit : summits) {
        // 현재 산봉우리 정보 저장        
        pq.push({ summit, summit, 0 });
        visit_node[summit] = { summit, 0 };
    }

    // 출/입구 까지 최적의 intensity 탐색
    auto [summit, node, intensity] = dijkstra();

    vector<int> answer(2);
    answer[0] = summit;
    answer[1] = intensity;

    return answer;
}