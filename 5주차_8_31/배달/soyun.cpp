#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

vector<vector<pair<int,int>>>graph;
vector<int>dist;

void Input(int N, vector<vector<int> > road){
    graph.assign(N+1, vector<pair<int,int>>());
    
    
    for(int i=0;i<road.size();i++){
        graph[road[i][0]].push_back({road[i][1], road[i][2]});
        graph[road[i][1]].push_back({road[i][0], road[i][2]});  
    }
    
    // for(int i=0;i<graph.size();i++){
    //     for(auto it : graph[i]){
    //         cout<< i << " " << it.first << " " << it.second << "\n";
    //     }
    // }
}

void dijkstra(int N){
    dist.assign(N+1, INT_MAX);
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>pq;
    dist[1] = 0;
    pq.push({0,1});
    
    while(!pq.empty()){
        auto cur = pq.top();
        int cx = cur.second;
        int cc = cur.first;
        pq.pop();
        
        if(dist[cx] < cc ) continue;
        
        for(int i = 0 ; i<graph[cx].size();i++){
            int nx = graph[cx][i].first;
            int nc = graph[cx][i].second;
            
            if(dist[nx] > cc + nc){
                dist[nx] = cc + nc;
                pq.push({cc+nc, nx});
            }
        }
        
    }
    
    
}

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;

    Input(N, road);
    dijkstra(N);
    
    for(int i=1;i<dist.size();i++){
        if(dist[i] <=K) answer++;
    }

    return answer;
}
