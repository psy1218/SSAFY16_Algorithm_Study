#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int grid[25][25];

int dxdy[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
int visit[25][25];

bool is_valid(int y, int x){
    return y >= 0 && y < n && x >= 0 & x < n;
}
int bfs(int start_y, int start_x){
    queue<pair<int, int>> q;
    q.push({start_y, start_x});
    visit[start_y][start_x] = true;
    int cnt = 1;
    while (!q.empty()){
        int cur_y = q.front().first;
        int cur_x = q.front().second;
        q.pop();
        for (auto ele : dxdy){
            int dy = ele[0];
            int dx = ele[1];
            int ny = cur_y + dy;
            int nx = cur_x + dx;
            if (is_valid(ny, nx) && !visit[ny][nx] && grid[ny][nx] == 1){
                visit[ny][nx] = true;
                q.push({ny, nx});
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    cin >> n;

    memset(visit, false, sizeof(visit)); // visit초기화 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    int city_cnt = 0; // 마을 갯수
    vector<int> arr; // 각 마을에 사는 사람 수
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1 && !visit[i][j]){
                int cur_city = bfs(i, j);
                city_cnt++;
                arr.push_back(cur_city);
                //cout << "cur_city:" << cur_city << "\n";
            }
        }
    }
    sort(arr.begin(), arr.end());
    cout << city_cnt << "\n";
    for (auto ele : arr){
        cout << ele << "\n";
    }

    return 0;
}
