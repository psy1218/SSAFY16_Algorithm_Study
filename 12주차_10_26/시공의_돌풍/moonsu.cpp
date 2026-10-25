#include <iostream>

using namespace std;

// 기본 정보
int N, M, T;
int answer;
int grid[50][50];

// 확산된 먼지 기록
int temp_grid[50][50];

// 돌풍의 상단, 하단 위치
int upper = -1;
int lower;

// 4방향 탐색
int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };


/* 입출력 최적화 */
void fast_io() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
}


/* 입력 저장 */
void input() {
    cin >> N >> M >> T;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == -1) {
                if (upper == -1) {
                    upper = i;
                } else {
                    lower = i;
                }
            } else {
                answer += grid[i][j];
            }
        }
    }
}


/* 먼지 확산 */
void spread() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            temp_grid[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] <= 0) {
                continue;
            }

            int dust = grid[i][j] / 5;

            for (int k = 0; k < 4; k++) {
                int ny = i + dy[k];
                int nx = j + dx[k];

                if (ny < 0 || ny >= N || nx < 0 || nx >= M) {
                    continue;
                }

                if (grid[ny][nx] == -1) {
                    continue;
                }

                temp_grid[ny][nx] += dust;
                grid[i][j] -= dust;
            }
        }
    }

    // 확산이 끝난 후 각 칸에 반영
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            grid[i][j] += temp_grid[i][j];
        }
    }
}


/* 상단 돌풍 업데이트 */
void update_upper() {
    // 반시계 방향
    for (int i = upper - 1; i > 0; i--) {
        grid[i][0] = grid[i - 1][0];
    }

    for (int j = 0; j < M - 1; j++) {
        grid[0][j] = grid[0][j + 1];
    }

    for (int i = 0; i < upper; i++) {
        grid[i][M - 1] = grid[i + 1][M - 1];
    }

    for (int j = M - 1; j > 1; j--) {
        grid[upper][j] = grid[upper][j - 1];
    }

    grid[upper][1] = 0;
}


/* 하단 돌풍 업데이트 */
void update_lower() {
	// 시계 방향
	for (int i = lower + 1; i < N - 1; i++) {
		grid[i][0] = grid[i + 1][0];
	}
	for (int j = 0; j < M - 1; j++) {
		grid[N - 1][j] = grid[N - 1][j + 1];
	}
	for (int i = N - 1; i > lower; i--) {
		grid[i][M - 1] = grid[i - 1][M - 1];
	}
	for (int j = M - 1; j > 1; j--) {
		grid[lower][j] = grid[lower][j - 1];
	}

	grid[lower][1] = 0;
}


/* 돌풍에 따른 먼지 회전 */
void wind() {
    // 돌풍으로 들어가 사라지는 먼지
    int remove_dust = grid[upper - 1][0] + grid[lower + 1][0];
    answer -= remove_dust;

	// 돌풍에 따른 먼지 회전
    update_upper();
    update_lower();
}


/* 시뮬레이션 수행 */
void solution() {
    for (int i = 0; i < T; i++) {
        spread();
        wind();
    }
}


int main() {
    fast_io();

    // 입력 저장
    input();

    // 시뮬레이션 수행
    solution();

    // 남은 먼지 출력
    cout << answer << "\n";

    return 0;
}