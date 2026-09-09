#include <iostream>
#include <cstring>

using namespace std;

int N;
int x, y;
int right_x, right_y;
int right_dir;
char grid[101][101];
bool visit[101][101][4];
int dxdy[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; // 오른쪽, 아래, 왼쪽, 위 순서. 즉 시계 방향


bool possible(int y, int x) {
    if (grid[y][x] != '#') {
        return true;
    }
    else {
        return false;
    }
}
bool is_right_wall(int ny, int nx, int dir) { // 현재의 방향 정보까지 있어야 한다.
    // 다음 칸에서 오른쪽에 벽이 있는지 여부 반환
    right_dir = (dir + 1) % 4; // 즉, 0, 1,2, 3 으로 보장됨
    // 다음 칸 기준으로 오른쪽 방향의 칸. 이 칸이 벽이어야 함
    int ny2 = ny + dxdy[right_dir][0];
    int nx2 = nx + dxdy[right_dir][1];
    right_y = ny2;
    right_x = nx2;
    //cout << "grid[ny2][nx2]:" << grid[ny2][nx2] << "\n";
    // 추가. 이 영역이 범위 밖일 수도 있기 때문..
    if (ny2 < 0 || ny2 >= N || nx2 < 0 || nx2 >= N) {
        return false;
    }
    if (grid[ny2][nx2] == '#') {
        return true;
    }
    else {
        return false;
    }
}
void go_straight(int ny, int nx) {
    // y, x 는 전역변수이므로
    y = ny;
    x = nx;
}
bool is_valid(int y, int x) {
    return y >= 0 && y < N && x >= 0 && x < N;
}
int main() {
    cin >> N;
    cin >> y >> x;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    // 내 기준 좌표는 0-based 이므로
    x--;
    y--;

    int dir = 0; // 최초엔 오른쪽 방향
    int time = 0; // 현재 시각
    memset(visit, false, sizeof(visit));
    bool flag = false;
    bool rotate_flag = false;
    while (1) {
        if (!visit[y][x][dir]) {
            visit[y][x][dir] = true; // 현재 좌표, 방향일 때. 
        }
        else {
            flag = true;
            break; // 이미 방문한곳을 또 방문하면 순환이 생기므로
        }
        if (!rotate_flag) {  // 만약 반시계방향으로 회전만 한것이라면 시간을 아직 증가시키면 안 됨
            time++; // 한 번 loop 돌때마다 시간 증가 시키고 봄
        }
        else {
            rotate_flag = false; // 다시 false 로 되돌려줘야 무한루프에 안 걸림
        }
        // 다음 방향
        int dy = dxdy[dir][0];
        int dx = dxdy[dir][1];
        int ny = y + dy;
        int nx = x + dx;
        if (!is_valid(ny, nx)) { // 격자 밖으로 빠져나갈 수 있으므로 종료.
            break;
        }
        // 다음 칸이 격자 밖이 아닌 경우. 즉, 탈출이 아직 불가능한 경우
        // 여기까지 왔으면 격자 안의 칸임 (ny, nx) 가
        if (possible(ny, nx)) {
            // 다음 칸이 이동가능한 칸인 경우.
            // 여기서도 2가지로 분기된다. 
            // 1. 앞으로 이동한 칸의 오른쪽에 벽이 있을 경우
            // 2. 그렇지 않을 경우
            if (is_right_wall(ny, nx, dir)) {
                go_straight(ny, nx); // 직진
            }
            else {
                // 이 경우엔 현재 벽 (y, x) 을 기준으로 한바퀴 시계방향으로 돌아야 함
                // 근데 여기서 다음에 위치할 좌표는, 오른쪽 벽 여부 판별할때 활용됨
                // 그냥 현재 좌표를 그 좌표로 이동시키면 됨.
                time++; // 회저할때는 시간이 1 더 쓰임
                if (!is_valid(right_y, right_x)) {
                    break;
                }

                y = right_y;
                x = right_x;
                dir = right_dir; // 한 바퀴 돌았을때의 그 방향을 기억해야함.
                
            }
        }
        else {
            rotate_flag = false;
            // 만약 이동이 불가하면
            dir--;
            if (dir < 0) {
                dir = 3; // -1 이라면 3으로 복귀
            }
            rotate_flag = true; // 다음 while loop에서 시간 안먹음
        }

    }
    if (flag) {
        cout << -1;
    }
    else {
        cout << time;
    }

    return 0;
}
