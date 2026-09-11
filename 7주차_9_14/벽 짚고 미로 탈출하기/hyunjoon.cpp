#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

int N;
int x, y;
char grid[101][101];
bool visited[101][101][4];

// 반시계방향
int dr[4] = {0,-1,0,1};
int dc[4] = {1,0,-1,0};


struct player{
    int r,c,dir;
}typedef player_t;

player_t player;

bool check_edge(int r, int c){
    if(r>0 && r<=N && c>0 && c<=N) return true;
    else return false;
}

bool check_esc(int r, int c){
    if(r>N || r<=0 || c>N || c<=0) return true;
    else return false;
}

int cnt;

void solve(int r, int c){
    int dir = 0;

    while(true){
        if(visited[r][c][dir]){
            cnt = -1;
            return;
        }
        visited[r][c][dir] = true;
        
        int nr = r + dr[dir];
        int nc = c + dc[dir];

        if(!check_edge(nr,nc)){
            cnt++;
            return;
        }


        if(grid[nr][nc] == '#'){
            dir = (dir+1)%4;
            continue;
        }
        // 앞이 .인 경우 이동
        r = nr;
        c = nc;
        cnt++;

        // nr,nc의 오른쪽 칸
        int right_dir = (dir+3)%4;
        int rr= r + dr[right_dir];
        int cr = c + dc[right_dir];

        // 오른쪽이 벽이면 그대로 
        if(!check_edge(rr,cr)){
            cnt++;
            return;
        }

        // 오른쪽이 .이면?
        if(grid[rr][cr]=='.'){
            dir = right_dir;
            r = rr;
            c = cr;
            cnt++;
        }

    }
}

int main() {
    cin >> N;
    cin >> x >> y;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    
    solve(x,y);

    cout << cnt;
    return 0;
}
