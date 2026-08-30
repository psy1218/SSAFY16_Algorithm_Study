#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<pair<int,int>> graph[50+1];

vector<int> dijk(int start, int N){
    // 현재까지의 cost 누적합 중 가장 작은 걸 넣음
    
    vector<int> dist(N+1, INT_MAX);
    priority_queue<
        pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[start] = 0;
    pq.push({start,0});
    
    while(!pq.empty()){
        int cur = pq.top().first;
        int cost = pq.top().second;
        pq.pop();
        
        if(cost > dist[cur]) continue;
        
        for(int i = 0; i<graph[cur].size(); i++){
            int next = graph[cur][i].first;
            int n_cost = graph[cur][i].second + cost;
            
            if(n_cost<dist[next]){
                dist[next] = n_cost;
                pq.push({next, n_cost});
            }
        }
    }
    
    
    return dist;
}

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;
    
    // graph에 data 넣기
    for(int i = 0; i<road.size(); i++){
        graph[road[i][0]].push_back({road[i][1], road[i][2]});
        graph[road[i][1]].push_back({road[i][0], road[i][2]});
    }
    // 모든 노드에 대해 다익스트라
    vector<int> dist = dijk(1,N);
    
    for(int i = 1; i<=N; i++){
        if(dist[i]<=K){
            answer++;
        }
    }
    
    return answer;
}
