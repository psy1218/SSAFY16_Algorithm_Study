#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, k;
int grid[100][100];
int r, c;

int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,1,-1 };

struct Info {
    int cost;
    int row;
    int col;
};
int res_r, res_c;


// cost는 높을수록, row와 col은 낮을수록 우선순위가 높음. 
struct compare {
    bool operator()(const Info& a, const Info& b) {
        if (a.cost == b.cost) {
            if (a.row == b.row) {
                return a.col > b.col;
            }

            return a.row > b.row;
        }

        return a.cost < b.cost;
    }
};

void dfs_bfs(int r, int c, int k, int cnt) { // K번 반복을 재귀로 반복, bfs를 활용해서 최대값, 행과 열 구하기. 정보는 pq에 저장. 

    if (cnt == k) return;


    priority_queue<Info, vector<Info>, compare>pq; // 최대값, 행과 열 데이터 저장 
    queue<pair<int, int>>q; // 이동할 수 있는 최대값 구하기 
    vector<vector<int>>visited(n + 1, vector<int>(n + 1, 0));

    q.push({ r, c });
    visited[r][c] = 1;

    pq.push({ grid[r][c], r, c });


    int c_cost = grid[r][c]; // x의 값은 최대값 찾을 때까지 고정 

    while (!q.empty()) {
        auto cur = q.front();
        int cr = cur.first;
        int cc = cur.second;
       
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = cr + dx[i];
            int nc = cc + dy[i];

            if (nr < 1 || nr > n || nc < 1 || nc > n) continue;
            if (visited[nr][nc] == 1) continue;
            if (c_cost <= grid[nr][nc]) continue; // x보다 작은곳만 이동 가능 크거나 같으면 이동할 수 없다. 

            q.push({ nr,nc });
            pq.push({ grid[nr][nc], nr, nc });
            visited[nr][nc] = 1;
        }
    }

   
    if (pq.size() == 1) { // 이동 불가할 경우 pq에 자신밖에 안 들어감.
        auto res = pq.top();
        res_r = res.row;
        res_c = res.col;

        return; // 함수 종료 
    }
    else {
        pq.pop(); // top에 자기 자신 = 가장 큰 값이 들어있어서, 자기 자신은 pop 해줘야함. 
        auto res = pq.top();
        res_r = res.row;
        res_c = res.col;
    }

    dfs_bfs(res_r, res_c, k, ++cnt);


}

int main() {
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        for (int j = 1 ; j <= n; j++) {
            cin >> grid[i][j];
        }
    }

    cin >> r >> c;

    dfs_bfs(r, c, k, 0);

    cout << res_r << " " << res_c << "\n";

    return 0;
}
