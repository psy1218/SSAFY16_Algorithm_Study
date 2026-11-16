
#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;
// 산봉우리 1번만
// 출입구 처음에 한번 끝에 한번
// intensity(휴식 없이 이동해야 하는 가장 긴 시간을 최소로 -> 거리 원소 각각이 최소가 되어야 함

// {to, cost}

vector<pair<int,int>> graph[50002];
vector<int> g_gates;
vector<int> g_summits;
vector<int> answer;

bool check_summit(int cur){
    for(int i = 0; i<g_summits.size(); i++){
        if(g_summits[i] == cur)
            return true;
    }
    return false;
}

void djk(int N){
    vector<int> dist(N+2, INT_MAX);
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    // gate를 시작점으로 해서 전부 pq에 비용 0으로 넣어줌
    for(int i = 0; i<g_gates.size(); i++){
        dist[g_gates[i]] = 0;
        pq.push({0,g_gates[i]});
    }
    int min_intensity = INT_MAX;
    while(!pq.empty()){
        int cur_intensity = pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();
        if(cur_intensity>dist[cur_node]) continue;
        
        for(int i = 0; i<graph[cur_node].size(); i++){
            int next = graph[cur_node][i].first;
            int next_intensity = max(graph[cur_node][i].second, cur_intensity);
            
            if(dist[next]> next_intensity){
                dist[next] = next_intensity;
                // 봉우리인 경우 dist만 갱신
                if(check_summit(next)){
                    min_intensity = min(next_intensity, min_intensity);
                    continue;
                }
                pq.push({dist[next], next});
            }
        }
    }
    
    for(int i = 0; i<g_summits.size(); i++){
        if(dist[g_summits[i]] == min_intensity){
            answer.push_back(g_summits[i]);
            answer.push_back(min_intensity);
            return;
        }
    }
}



vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    
    for(int i = 0; i<paths.size(); i++){
        graph[paths[i][0]].push_back({paths[i][1], paths[i][2]});
        graph[paths[i][1]].push_back({paths[i][0], paths[i][2]});
    }
    g_gates = gates;
    g_summits = summits;
    sort(g_summits.begin(), g_summits.end());
    djk(paths.size());
    return answer;
}
