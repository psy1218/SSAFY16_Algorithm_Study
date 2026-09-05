#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct max_num{
    int num, r, c;
}typedef max_num_t;

int n, k;
int grid[100][100];
int r, c;

int dr[4] = {1,-1,0,0};
int dc[4] = {0,0,1,-1};



bool edge_check(int y, int x){
    if(y>=0 && y<n && x>=0 && x<n) return true;
    else return false;
}

max_num_t bfs(int start_r, int start_c){
    queue<pair<int,int>> q;
    
    q.push({start_r, start_c});
    
    bool visited[101][101] = {0};

    int x = grid[start_r][start_c];
    visited[start_r][start_c] = true;
    max_num_t max_num= {-1, start_r, start_c};
    while(!q.empty()){
        pair<int,int> cur = q.front();
        q.pop();
    
        for(int i = 0; i<4; i++){
            int nr = cur.first + dr[i];
            int nc = cur.second + dc[i];

            if(!edge_check(nr,nc)) {
                continue;
            }

            if(visited[nr][nc]) {
                continue;}
            // 격자가 x보다 더 크면 이동 불가
            if(grid[nr][nc] >= x) {
                continue;
            }

            visited[nr][nc] = true;

            // 여기까지 오면 일단 다음 격자로는 가는거임
            q.push({nr,nc});
            // 이번 bfs에서 최대값 update
            if(grid[nr][nc]>max_num.num){
                max_num.num = grid[nr][nc];
                max_num.r = nr;
                max_num.c = nc;
            }
            // 최댓값과 같은 값이면 행 -> 열 순으로 검사
            else if(grid[nr][nc] == max_num.num){
                // max_num의 행이 더 클 경우
                if(max_num.r > nr){
                    max_num.r = nr;
                    max_num.c = nc;
                }
                // max_num의 행이 같을 경우 (열 비교)
                else if(max_num.r == nr){
                    if(max_num.c > nc){
                        max_num.c = nc;
                    }
                }
            }
        }
    }
    return max_num;
}

int main() {
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    cin >> r >> c;
    r--;
    c--;
    // Please write your code here.
    // 초기값 넣기
    max_num_t ans={grid[r][c], r, c};
    for(int i = 0; i<k; i++){
        max_num_t cur;
        cur = bfs(ans.r, ans.c);
        // 더 이상 안 움직일 때
        if(cur.r == ans.r && cur.c == ans.c) break;
        ans = cur;
        //cout <<"seq"<< i << ' '<<ans.num <<" | "<< ans.r << ' '<<ans.c << '\n';
    }

    cout << ans.r+1 << ' ' << ans.c+1;
    return 0;
}
