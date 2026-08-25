#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;
    vector<vector<pair<int,int>>> graph(N+1);
    for (int i = 0; i < road.size(); i++){
        int a = road[i][0];
        int b = road[i][1];
        int dist = road[i][2];
        graph[a].push_back({b, dist});
        graph[b].push_back({a, dist});
    }
    queue<pair<int, int>> q;
    vector<int> distance(N+1);
    int INF = 10e8;
    
    fill(distance.begin(), distance.end(), INF);
    int cnt = 0;
    q.push({1, 0});
    distance[1] = 0;
    while (!q.empty()){
        int cur = q.front().first;
        int dist = q.front().second;
        q.pop();
        if (dist > distance[cur]){
            continue;
        }
        
        for (auto i : graph[cur]){
            int nxt = i.first;
            int nxt_dist = i.second + dist;
            if (distance[nxt] != -INF && nxt_dist < distance[nxt]){
                distance[nxt] = nxt_dist;
                q.push({nxt, nxt_dist});
            }
        }
    }
    for (int i = 1; i <= N; i++){
        if (distance[i] <= K){
            cnt++;
        }
    }
    return cnt;
}
