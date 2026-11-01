#if 01

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int dr[4] = { -1, 0,1,0 }; 
int dc[4] = { 0,1,0,-1 };

int R, C;
vector<vector<int>> map;
vector<pair<int, int>> cleaner;


void enfect() {
    
    vector<vector<int>> map_tmp(R, vector<int>(C, 0));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int cnt = 0;
            if (map[i][j] > 0) {
                for (int dir = 0; dir < 4; dir++) {
                    int nr = i + dr[dir];
                    int nc = j + dc[dir];
                    // edge
                    if (nr >= R || nr < 0 || nc >= C || nc < 0) continue;
                    // 공청기
                    if (map[nr][nc] < 0) continue;
                    // 빈 칸
                    map_tmp[nr][nc] += map[i][j] / 5;
                    cnt++;
                }
                map_tmp[i][j] += map[i][j] - (map[i][j] / 5) * cnt;
            }
        }
    }
    map_tmp[cleaner[0].first][cleaner[0].second] = -1;
    map_tmp[cleaner[1].first][cleaner[1].second] = -1;
    map = map_tmp;
    return;
}

void clean_up() {
    int r = cleaner[0].first; // 위쪽 공기청정기 행 위치

    // 1. 위에서 아래로 당기기 (왼쪽 변)
    for (int i = r - 1; i > 0; i--) map[i][0] = map[i - 1][0];

    // 2. 오른쪽에서 왼쪽으로 당기기 (위쪽 변)
    for (int i = 0; i < C - 1; i++) map[0][i] = map[0][i + 1];

    // 3. 아래에서 위로 당기기 (오른쪽 변)
    for (int i = 0; i < r; i++) map[i][C - 1] = map[i + 1][C - 1];

    // 4. 왼쪽에서 오른쪽으로 당기기 (아랫쪽 변 - 공기청정기 있는 줄)
    for (int i = C - 1; i > 1; i--) map[r][i] = map[r][i - 1];

    // 5. 공기청정기에서 나온 맑은 공기 세팅
    map[r][1] = 0;
}

void clean_down() {
    int r = cleaner[1].first; // 아래쪽 공기청정기 행 위치

    // 1. 아래에서 위로 당기기 (왼쪽 변)
    for (int i = r + 1; i < R - 1; i++) map[i][0] = map[i + 1][0];

    // 2. 오른쪽에서 왼쪽으로 당기기 (아래쪽 변)
    for (int i = 0; i < C - 1; i++) map[R - 1][i] = map[R - 1][i + 1];

    // 3. 위에서 아래로 당기기 (오른쪽 변)
    for (int i = R - 1; i > r; i--) map[i][C - 1] = map[i - 1][C - 1];

    // 4. 왼쪽에서 오른쪽으로 당기기 (위쪽 변 - 공기청정기 있는 줄)
    for (int i = C - 1; i > 1; i--) map[r][i] = map[r][i - 1];

    // 5. 공기청정기에서 나온 맑은 공기 세팅
    map[r][1] = 0;
}

void solve() {

    // 1번 동작(미세먼지 확산)
    enfect();

    // 2번 동작(공기 청정)
    clean_up();
    clean_down();
}

int main(void) {
    //(void)freopen("b17144.txt", "r", stdin);
    int T;
    cin >> R >> C >> T;
    map.assign(R, vector<int>(C, 0));

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> map[i][j];
            if (map[i][j] == -1) {
                cleaner.push_back(make_pair(i, j));
            }
        }
    }

    while (T--) {
        solve();
    }

    int ans = 2;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            ans += map[i][j];
        }
    }

    cout << ans;


    return 0;
}


#endif
