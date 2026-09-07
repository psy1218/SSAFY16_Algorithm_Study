#include <iostream>
#include <queue>
#include <climits>
#include <vector>
using namespace std;

int N;

int n[2] = {1,-1};

vector<int> visited;

void bfs(){
    queue<int> q;
    q.push(N);
    visited[N] = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        // N=1 도달시 loop break
        if(cur == 1) break;

        for(int i = 0; i<4; i++){
            int now = 0;
            if(i>=0 && i<2){
                now = cur + n[i];
            }
            if(i == 2 && cur%2 == 0){
                now = cur / 2;
            }
            if(i == 3 && cur%3 == 0){
                now = cur / 3;
            }
            // edge
            if(now >= N+3 || now<0) continue;
            if(!now) continue;
            // visited
            if(visited[now]<= (visited[cur]+1)) continue;
            visited[now] = visited[cur] + 1;
            q.push(now);
        }
    }
}


int main() {
    cin >> N;
    
    // Please write your code here.
    visited.assign(N+4,INT_MAX);
    bfs();
    cout << visited[1];
    return 0;
}
