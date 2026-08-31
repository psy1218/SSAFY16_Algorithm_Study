#include <iostream>
#include <algorithm>

using namespace std;

int n;
int grid[25][25];

// 4방향 탐색
int dy[] = { -1, 0, 1, 0 };
int dx[] = { 0, 1, 0, -1 };

/* dfs 탐색 */
int dfs(int y, int x) {
    int result = 1;
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];

        // 범위 확인
        if (ny < 0 || ny >= n || nx < 0 || nx >= n) {
            continue;
        }

        // 방문 가능 시 방문 처리 및 dfs 탐색
        if (grid[ny][nx]) {
            grid[ny][nx] = 0;
            result += dfs(ny, nx);
        }
    }

    return result;
}


int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // 마을 구분 및 인구 수 계산
    int group_cnt = 0;
    int people_cnt[25 * 25];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j]) {
                grid[i][j] = 0;
                people_cnt[group_cnt++] = dfs(i, j);
            }
        }
    }

	// 결과 출력
    cout << group_cnt << endl;
    sort(people_cnt, people_cnt + group_cnt);
    for (int i = 0; i < group_cnt; i++) {
        cout << people_cnt[i] << endl;
    }

    return 0;
}
