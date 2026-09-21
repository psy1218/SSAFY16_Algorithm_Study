#include <iostream>
#include <queue>
#include <climits>
using namespace std;

int n, m;
int board[100][100];

int dr[4] = {1,-1,0,0};
int dc[4] = {0,0,1,-1};

bool check_edge(int r, int c){
    if(r<n && r>=0 && c<m && c>=0) return true;
    else return false;
}

bool bfs(int low, int high){
    queue<pair<int,int>> q;
    q.push({0,0});
    bool visited[100][100] ={0};
    visited[0][0] = true;
    if(board[0][0] <low || board[0][0] > high) return false;
    if(n == 1 && m == 1) return true;

    while(!q.empty()){
        pair<int,int> cur = q.front();
        q.pop();

        for(int i = 0; i<4; i++){
            int nr = cur.first + dr[i];
            int nc = cur.second + dc[i];

            if(!check_edge(nr, nc)) continue;
            if(board[nr][nc] <low || board[nr][nc] > high) continue;
            if(visited[nr][nc]) continue;
            
            if(nr == n-1 && nc == m-1) return true;
            visited[nr][nc] = true;
            q.push({nr,nc});
        }
    }

    return false;
}

bool check(int limit){
    for(int i = 0; i+limit <= 500; i++){
        if(bfs(i, i+limit)) return true;
    }
    return false;
}

int upper_bound(){
    int start = 0;
    int end = 500;
    int ret = 0;
    while(start<end){
        int mid = (start+end) / 2;
        if(check(mid)){
            ret = mid;
           end = mid; 
        }
        else{
            start = mid + 1;
        }
    }

    return ret;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    // Please write your code here.

    cout << upper_bound();
    return 0;
}
