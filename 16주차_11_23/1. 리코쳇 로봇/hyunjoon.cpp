#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <climits>
using namespace std;
// G로 가야 함
// R에서 시작
int N, M;

int dr[4] = {0,0,1,-1};
int dc[4] = {1,-1,0,0};

bool edge_check(int r, int c){
    if(r>=0 && r<N && c>=0 && c<M){
        return true;
    }
    else return false;
}

int solution(vector<string> board) {
    int answer = 0;
    N = board.size();
    M = board[0].length();
    pair<int,int> start, goal;
    vector<vector<int>> dist(N,vector<int>(M,INT_MAX));
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            if(board[i][j] == 'R'){
                start = {i,j};
            }
            else if(board[i][j] == 'G'){
                goal = {i,j};
            }
        }
    }
    
    queue<pair<int,int>> q;
    
    q.push(start);
    dist[start.first][start.second] = 0;
    
    cout << goal.first << ' ' << goal.second << '\n';
    while(!q.empty()){
        pair<int,int> cur;
        cur = q.front();
        q.pop();
        
        if(goal == cur) return dist[cur.first][cur.second];
        for(int d = 0; d<4; d++){
            int nr = cur.first;
            int nc = cur.second;
            // 벽 만나거나, 장애물 만나면 멈춤
           while(edge_check(nr,nc) && board[nr][nc] != 'D'){
                nr = nr + dr[d];
                nc = nc + dc[d];
            }
            // 그 전 칸으로 nr,nc를 되돌림(로봇이 위치해야 할 장애물 혹은 벽 전 칸)
            nr = nr - dr[d];
            nc = nc - dc[d];
            
            // 더 적은 횟수로 동일한 곳 도착하면 갱신
            if(dist[nr][nc] > dist[cur.first][cur.second] + 1 ){
                dist[nr][nc] = dist[cur.first][cur.second] + 1 ;
                q.push({nr,nc});
            }
        }
    }
    return -1;
}
