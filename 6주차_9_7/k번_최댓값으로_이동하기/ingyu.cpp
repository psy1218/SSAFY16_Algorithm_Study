#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

int n, k;
int grid[100][100];
int r, c;
int dxdy[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
bool is_valid(int y, int x){
    return y >= 0 && y < n && x >= 0 && x < n;
}
vector<int> max_vector;
void bfs(int start_y, int start_x, priority_queue<tuple<int, int, int>>& pq){
    queue<tuple<int, int, int>> q;
    q.push({grid[start_y][start_x], start_y, start_x}); // {배열값, y, x}
    bool visit[100][100] = {};
    visit[start_y][start_x] = true;
    int limit= grid[start_y][start_x];
    int max_value = 0;
    while (!q.empty()){
        int cur = get<0>(q.front());
        int cur_y = get<1>(q.front());
        int cur_x = get<2>(q.front());
        q.pop();
        for (auto ele : dxdy){
            int dy = ele[0];
            int dx = ele[1];
            int ny = cur_y + dy;
            int nx = cur_x + dx;
            if (is_valid(ny, nx) && !visit[ny][nx] && grid[ny][nx] < limit){
                visit[ny][nx] = true;
                q.push({grid[ny][nx], ny, nx});
                pq.push({grid[ny][nx], -ny, -nx}); // 우큐는 push
            }
        }
    }  
}
int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    cin >> r >> c;

    int cur;
    int cur_y = r - 1;
    int cur_x = c - 1;
    for (int i = 0; i < k; i++){
        priority_queue<tuple<int, int, int>> pq; // 오름차순 정렬. pq 새로 정의
        bfs(cur_y, cur_x, pq); // 새로운 위치에서 bfs 시작
        if (pq.empty()) {
            break;
        }
        else{
            cur = get<0>(pq.top());
            cur_y = -get<1>(pq.top());
            cur_x = -get<2>(pq.top());
            pq.pop();
        }
    }
    cout << cur_y + 1 << " " << cur_x + 1;
    return 0;
}
