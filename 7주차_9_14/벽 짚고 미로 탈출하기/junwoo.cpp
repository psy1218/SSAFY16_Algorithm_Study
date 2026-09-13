#include <iostream>

using namespace std;

int N;
int x, y;
char grid[101][101];
int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};
bool visited[101][101][4];

// 정면에 벽있을 경우
bool inRange(int r, int c){
    return 1 <= r && r <= N && 1 <= c && c <= N;
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
    // 처음에는 오른쪽을 바라봄
    int dir = 0;
    int cnt = 0;

    while (true){
        if (visited[x][y][dir]){
            cout << -1;
            return 0;
        }

        visited[x][y][dir] = true;

        // 정면 위치
        int nx = x + dr[dir];
        int ny = y + dc[dir];

        // Case 1: 정면이 격자 밖이면 한 칸 이동해서 탈출
        if (!inRange(nx, ny)){
            cnt++;
            cout << cnt;
            return 0;
        }

        // Step1
        // 정면에 벽이 있다면 반시계 방향 회전
        if (grid[nx][ny] == '#'){
            dir = (dir + 1) % 4;
            continue;
        }

        // 정면 이동 가능
        // 이동한 위치에서 오른쪽 방향 확인
        int rightDir = (dir + 3) % 4;
        int rx = nx + dr[rightDir];
        int ry = ny + dc[rightDir];

        // Case2: 정면 이동 후 오른쪽 벽 존재
        if (inRange(rx, ry) && grid[rx][ry] == '#'){
            x = nx;
            y = ny;
            cnt++;
        }

        // Case3: 오른쪽 벽 없음
        else{
            x = nx;
            y = ny;
            cnt++;

            dir = rightDir;
            int nnx = x + dr[dir];
            int nny = y + dc[dir];

            cnt++;

            if (!inRange(nnx, nny)){
                cout << cnt;
                return 0;
            }

            x = nnx;
            y = nny;
        }
    }

    return 0;
}
