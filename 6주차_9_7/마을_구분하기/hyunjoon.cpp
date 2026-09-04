#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N;
int grid[25][25];
bool visited[25][25];

vector<int> village;

// dir vector
int dr[4] = {1,-1,0,0};
int dc[4] = {0,0,1,-1};

bool edge_check(int r, int c){
    if(r<N && r>=0 && c<N && c>=0) return true;
    else return false;
}

// 모든 격자를 방문했는지 검사 후, 방문하지 않은 격자는 bfs 시작점으로 잡아보기
int bfs(int r, int c){
    int cnt = 0;
    queue<pair<int,int>> q;
    q.push({r,c});
    visited[r][c] = true;
    cnt++;
    while(!q.empty()){
        pair<int,int> cur = q.front();
        q.pop();

        for(int i = 0; i<4; i++){
            int nr = cur.first + dr[i];
            int nc = cur.second + dc[i];

            if(!edge_check(nr,nc)) continue;
            
            // 벽이면 continue
            if(!grid[nr][nc]) continue;
            // 방문했으면 continue
            if(visited[nr][nc]) continue;
            
            // 방문한 적 없고 벽 아니면
            visited[nr][nc] = true;
            cnt++;
            q.push({nr,nc});
        }
    }
    
    return cnt;
}

bool cmp(int a, int b){
    if(a>b) return false;
    else return true;
}

int main() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }


    int group_num = 1;
    int seq = 0;
    // Please write your code here.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if((!visited[i][j]) && grid[i][j]){
                village.push_back(bfs(i,j));
                group_num++;
            }
        }
    }
    // 오름차순 정렬
    sort(village.begin(),village.end(),cmp);
    // 답 출력
    cout << village.size() << '\n';
    for(int i = 0; i<village.size(); i++){
        cout << village[i] << '\n';
    }

    return 0;
}
