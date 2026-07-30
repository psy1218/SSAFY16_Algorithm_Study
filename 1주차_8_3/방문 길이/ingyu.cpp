#include <string>

using namespace std;

bool is_valid(int y, int x) {
    return y >= 0 && y <= 10 && x >= 0 && x <= 10;
}

int solution(string dirs) {
    int answer = 0;

    // 0: L, 1: R, 2: U, 3: D
    int visited[11][11][4] = {};

    int x = 5;
    int y = 5;

    for (int i = 0; i < dirs.length(); i++) {
        char cmd = dirs[i];

        if (cmd == 'L') {
            int nextX = x - 1;
            int nextY = y;

            if (is_valid(nextY, nextX)) {
                // 처음 지나가는 길인지 확인
                if (visited[y][x][0] == 0) {
                    answer++;
                }

                // 현재 위치에서 왼쪽
                visited[y][x][0] = 1;

                // 도착 위치에서 오른쪽
                visited[nextY][nextX][1] = 1;

                x = nextX;
                y = nextY;
            }
        }
        else if (cmd == 'R') {
            int nextX = x + 1;
            int nextY = y;

            if (is_valid(nextY, nextX)) {
                if (visited[y][x][1] == 0) {
                    answer++;
                }

                // 현재 위치에서 오른쪽
                visited[y][x][1] = 1;

                // 도착 위치에서 왼쪽
                visited[nextY][nextX][0] = 1;

                x = nextX;
                y = nextY;
            }
        }
        else if (cmd == 'U') {
            int nextX = x;
            int nextY = y - 1;

            if (is_valid(nextY, nextX)) {
                if (visited[y][x][2] == 0) {
                    answer++;
                }

                // 현재 위치에서 위쪽
                visited[y][x][2] = 1;

                // 도착 위치에서 아래쪽
                visited[nextY][nextX][3] = 1;

                x = nextX;
                y = nextY;
            }
        }
        else if (cmd == 'D') {
            int nextX = x;
            int nextY = y + 1;

            if (is_valid(nextY, nextX)) {
                if (visited[y][x][3] == 0) {
                    answer++;
                }

                // 현재 위치에서 아래쪽
                visited[y][x][3] = 1;

                // 도착 위치에서 위쪽
                visited[nextY][nextX][2] = 1;

                x = nextX;
                y = nextY;
            }
        }
    }

    return answer;
}
