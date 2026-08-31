#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int grid[25][25];

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};  

vector<int>res;

void bfs(int x, int y){
    int cnt = 1;
    queue<pair<int,int>>q;
    q.push({x,y});
    grid[x][y] = 0;

    while(!q.empty()){
        auto cur = q.front();
        int cx = cur.first;
        int cy = cur.second;
        q.pop();

        for(int i=0;i<4;i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if(grid[nx][ny] == 1){
                cnt++;
                q.push({nx,ny});
                grid[nx][ny] = 0;
            }

        }
    }

    res.push_back(cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    for(int i =0;i<n;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j] == 1) bfs(i,j);
        }
    }

    sort(res.begin(), res.end());

    cout << res.size() << "\n";
    for(int i=0;i<res.size();i++){
        cout << res[i] << "\n";
    }
    
    return 0;
}
