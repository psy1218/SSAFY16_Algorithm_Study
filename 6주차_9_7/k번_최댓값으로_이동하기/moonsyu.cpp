#include <iostream>
#include <algorithm>

using namespace std;

int n, k;
int grid[100][100];
int r, c;

// 좌표 기록용 구조체
struct Pair {
    int y, x;
};

// 오름차순 정렬 구조체
struct Pair_comp {
    bool operator()(Pair& p1, Pair& p2) {
        if (p1.y == p2.y) {
            return p1.x < p2.x;
        }

        return p1.y < p2.y;
    }
};

// 최대 숫자 및 해당 숫자의 좌표 기록 용 배열
int max_num;
int num_cnt;
Pair num_list[10000];

// 방문 정보 구조체
struct visit_info {
    int time;
};

// 방문 정보
visit_info visit[100][100];

// bfs용 큐
int front, rear;
Pair que[10000];

// 4방향 탐색용
int dy[] = { -1, 0, 1, 0 };
int dx[] = { 0, 1, 0, -1 };

int main() {
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    cin >> r >> c;

    // Please write your code here.
    int num = grid[r - 1][c - 1];
    int answer_y = r - 1, answer_x = c - 1;

    for (int i = 1; i <= k; i++) {
        max_num = 0;
        num_cnt = 0;
        front = rear = 0;
        que[rear++] = { answer_y, answer_x };
        visit[answer_y][answer_x].time = i;

        while (front < rear) {
            Pair cur = que[front++];
            int y = cur.y;
            int x = cur.x;

            for (int j = 0; j < 4; j++) {
                int ny = y + dy[j];
                int nx = x + dx[j];

                if (ny < 0 || ny >= n || nx < 0 || nx >= n) {
                    continue;
                }

                // 아직 방문하지 않은 노드면서
                // 기준 값 보다 작은 노드일 경우
                if (visit[ny][nx].time != i && grid[ny][nx] < num) {
                    // cout << "init " << "\n\n";
                    visit[ny][nx].time = i;

                    if (grid[ny][nx] > max_num) {
                        max_num = grid[ny][nx];
                        num_cnt = 0;
                        num_list[num_cnt++] = { ny, nx };
                    }
                    else if (grid[ny][nx] == max_num) {
                        num_list[num_cnt++] = { ny, nx };
                    }

                    que[rear++] = { ny, nx };
                }
            }
        }


        // 더이상 이동이 불가능 하다면
        if (!num_cnt) {
            break;
        }

        // 좌표 오름차순 정렬
        sort(num_list, num_list + num_cnt, Pair_comp());


        // i번째 num 갱신
        num = max_num;
        answer_y = num_list[0].y;
        answer_x = num_list[0].x;

    }

    cout << answer_y + 1 << " " << answer_x + 1;

    return 0;
}
