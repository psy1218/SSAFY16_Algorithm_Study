#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define MAX_N 30

int H, W;

char D[MAX_N][MAX_N]; // 선로의 맵을 나타내는 2차원 문자열 배열입니다.

const int dir[4][2] = {
    {-1, 0}, // 북쪽으로 이동합니다.
    {0,  1}, // 동쪽으로 이동합니다.
    {1,  0}, // 남쪽으로 이동합니다.
    {0,  -1} // 서쪽으로 이동합니다.
};

// 주어진 좌표가 선로 위에 있는지 확인합니다.
bool is_in_path (int i, int j) {
    return 0 <= i && i < H && 0 <= j && j < W && D[i][j] == '#';
}

int main() {
    cin >> H >> W; // 높이(H)와 너비(W)를 입력받습니다.

    for (int i = 0; i < H; i++) {
        cin >> D[i];
     } // 선로의 상태를 입력받습니다.

    int si, sj, direction; // 시작 위치(si, sj)와 방향(direction)을 저장할 변수입니다.

    // 선로의 시작점과 방향을 찾습니다.
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (!is_in_path(i, j)) continue; // 선로가 아니면 무시합니다.

            int cnt = 0, dirIdx = -1;
            for (int d = 0; d < 4; d++) {
                int ni = i + dir[d][0];
                int nj = j + dir[d][1];
                if (is_in_path(ni, nj)) {
                    cnt++;
                    dirIdx = d;
                }
            }

            if (cnt == 1) { // 시작점을 찾았습니다.
                si = i; sj = j; direction = dirIdx;
            }
        }
    }

    // 시작 위치와 방향을 출력합니다.
    cout << si + 1 << " " << sj + 1 << "\n";
    cout << "^>v<"[direction] << "\n";

    vector<vector<bool>> visited(H, vector<bool>(W)); // 방문한 위치를 추적합니다.
    string commands; // 이동 명령어를 저장할 문자열입니다.

    // 선로를 따라 이동하며 명령어를 생성합니다.
    while (true) {
        int cnt = 0, target_direction = -1;
        for (int d = 0; d < 4; d++) {
            int ni = si + dir[d][0];
            int nj = sj + dir[d][1];
            if (is_in_path(ni, nj) && !visited[ni][nj]) {
                cnt++;
                target_direction = d;
            }
        }

        if (cnt == 0) break; // 더 이상 갈 수 있는 경로가 없으면 종료합니다.

        int diff = (target_direction - direction + 4) % 4;
        if (diff == 1) commands += 'R'; // 오른쪽으로 회전합니다.
        else if (diff == 3) commands += 'L'; // 왼쪽으로 회전합니다.
        direction = target_direction;

        commands += 'A'; // 전진합니다.
        for (int rep = 0; rep < 2; rep++) {
            si += dir[direction][0];
            sj += dir[direction][1];
            visited[si][sj] = true; // 방문 표시를 합니다.
        }
    }

    cout << commands << "\n"; // 생성된 명령어를 출력합니다.
    return 0;
}

