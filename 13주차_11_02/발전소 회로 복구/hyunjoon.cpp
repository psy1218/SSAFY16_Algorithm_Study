
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <iostream>
#include <cmath>

using namespace std;

#define MAX_K 15
#define INF 1000000000

int DIST[1 << MAX_K][MAX_K];

vector<pair<int,int>> node[16];
vector<vector<int>> Panel;
vector<string> GRID;

int H, N, M, K;
int need[16];

int dr[4] = {0, 0, -1, 1};
int dc[4] = {1, -1, 0, 0};

bool edge_check(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < M;
}

// 패널 -> 패널 BFS
int bfs_pannel(pair<int,int> start, pair<int,int> end) {
    if (start == end) return 0;

    queue<pair<int,int>> q;
    vector<vector<int>> dist(N, vector<int>(M, -1));

    dist[start.first][start.second] = 0;
    q.push(start);

    while (!q.empty()) {
        pair<int,int> cur = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = dr[i] + cur.first;
            int nc = dc[i] + cur.second;

            if (!edge_check(nr, nc)) continue;
            if (GRID[nr][nc] == '#') continue;
            if (dist[nr][nc] != -1) continue;

            dist[nr][nc] = dist[cur.first][cur.second] + 1;

            if (nr == end.first && nc == end.second) {
                return dist[nr][nc];
            }

            q.push({nr, nc});
        }
    }

    return INF;
}

// 패널 -> 엘리베이터 BFS
int bfs_elev(pair<int,int> start) {
    queue<pair<int,int>> q;
    vector<vector<int>> dist(N, vector<int>(M, -1));

    dist[start.first][start.second] = 0;
    q.push(start);

    while (!q.empty()) {
        pair<int,int> cur = q.front();
        q.pop();

        if (GRID[cur.first][cur.second] == '@') {
            return dist[cur.first][cur.second];
        }

        for (int i = 0; i < 4; i++) {
            int nr = dr[i] + cur.first;
            int nc = dc[i] + cur.second;

            if (!edge_check(nr, nc)) continue;
            if (GRID[nr][nc] == '#') continue;
            if (dist[nr][nc] != -1) continue;

            dist[nr][nc] = dist[cur.first][cur.second] + 1;
            q.push({nr, nc});
        }
    }

    return INF;
}

// 패널 간 거리 그래프 생성
void cal_dist() {
    int elev_dist[16];

    for (int i = 0; i < K; i++) {
        pair<int,int> p = {
            Panel[i][1] - 1,
            Panel[i][2] - 1
        };

        elev_dist[i] = bfs_elev(p);
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            int min_dist;

            pair<int,int> start_pannel = {
                Panel[i][1] - 1,
                Panel[i][2] - 1
            };

            pair<int,int> end_pannel = {
                Panel[j][1] - 1,
                Panel[j][2] - 1
            };

            int start_height = Panel[i][0];
            int end_height = Panel[j][0];

            if (i == j) {
                min_dist = 0;
            }
            else if (start_height == end_height) {
                min_dist = bfs_pannel(start_pannel, end_pannel);
            }
            else {
                min_dist = elev_dist[i]
                    + abs(start_height - end_height)
                    + elev_dist[j];
            }

            if (min_dist >= INF) continue;

            node[i].push_back({j, min_dist});
        }
    }
}

int solution(int h, vector<string> grid,
             vector<vector<int>> panels,
             vector<vector<int>> seqs) {

    H = h;
    N = grid.size();
    M = grid[0].length();
    K = panels.size();

    GRID = grid;
    Panel = panels;

    for (int i = 0; i < K; i++) {
        node[i].clear();
        need[i] = 0;
    }

    cal_dist();

    // 선행 활성화 조건 비트마스킹
    for (int i = 0; i < seqs.size(); i++) {
        int a = seqs[i][0] - 1;
        int b = seqs[i][1] - 1;

        need[b] |= (1 << a);
    }

    // 다익스트라 거리 초기화
    for (int i = 0; i < (1 << K); i++) {
        for (int j = 0; j < K; j++) {
            DIST[i][j] = INF;
        }
    }

    // {cost, {mask, 현재 패널}}
    priority_queue<
        pair<int, pair<int,int>>,
        vector<pair<int, pair<int,int>>>,
        greater<pair<int, pair<int,int>>>
    > pq;

    // 1번 패널 위치에서 출발, 활성화된 패널은 없음
    DIST[0][0] = 0;
    pq.push({0, {0, 0}});

    int full_mask = (1 << K) - 1;

    while (!pq.empty()) {
        int cur_cost = pq.top().first;
        int mask = pq.top().second.first;
        int cur = pq.top().second.second;
        pq.pop();

        if (DIST[mask][cur] < cur_cost) continue;

        // 모든 패널 활성화 완료
        if (mask == full_mask) {
            return cur_cost;
        }

        for (int i = 0; i < node[cur].size(); i++) {
            int next = node[cur][i].first;
            int cost = node[cur][i].second;

            // 이미 활성화한 패널
            if (mask & (1 << next)) continue;

            // 선행 활성화 조건 미충족
            if ((mask & need[next]) != need[next]) continue;

            int next_mask = mask | (1 << next);
            int next_cost = cur_cost + cost;

            if (DIST[next_mask][next] > next_cost) {
                DIST[next_mask][next] = next_cost;
                pq.push({next_cost, {next_mask, next}});
            }
        }
    }

    return -1;
}
