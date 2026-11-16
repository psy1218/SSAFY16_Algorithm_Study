#include <string>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

struct Node{
    int node_id;
    int weight;     // 현재까지 경로 intensity
    
    bool operator<(const Node& other) const{
        return weight > other.weight;
    }
};

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    
    vector<vector<pair<int, int>>> graph(n+1);
    vector<bool> is_gate(n+1, false);
    vector<bool> is_summit(n+1, false);
    
    for (int i = 0; i < paths.size(); i++){
        int a = paths[i][0];
        int b = paths[i][1];
        int w = paths[i][2];
        
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }
    
    for (int i = 0; i < gates.size(); i++){
        is_gate[gates[i]] = true;
    }
    for (int i = 0; i < summits.size(); i++){
        is_summit[summits[i]] = true;
    }
    
    // dijkstra
    vector<int> dijk(n+1, INT_MAX);
    priority_queue<Node> min_pq;
    
    for (int i = 0; i < gates.size(); i++){
        dijk[gates[i]] = 0;
        min_pq.push({gates[i], 0});
    }
    
    while(!min_pq.empty()){
        Node cur_node = min_pq.top();
        min_pq.pop();
        
        int cur_id = cur_node.node_id;
        int cur_intensity = cur_node.weight;
        
        // 더 좋은 경로 찾았을 시 무시
        if (cur_intensity > dijk[cur_id]){
            continue;
        }
        
        // 산봉우리 X
        if (is_summit[cur_id]){
            continue;
        }
        
        for (const auto& n_node: graph[cur_id]){
            int next_id = n_node.first;
            int edge_weight = n_node.second;
            
            // 출입구 경유 X
            if (is_gate[next_id]) continue;
            
            int next_intensity = max(cur_intensity, edge_weight);
            if (next_intensity < dijk[next_id]){
                dijk[next_id] = next_intensity;
                min_pq.push({next_id, next_intensity});
            }
        }
    }
    
    int best_summit = INT_MAX;
    int best_intensity = INT_MAX;
    
    for (int summit: summits){
        if (dijk[summit] < best_intensity || 
           (dijk[summit] == best_intensity && summit < best_summit)){
            best_intensity = dijk[summit];
            best_summit = summit;
        }
    }
    
    return {best_summit, best_intensity};
}
