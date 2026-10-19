#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

struct State {
    int r, c;
    int mask;
    int time;
};

int N, M;
vector<string> board;

int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

// bit mask가 6bit이므로 2^6 = 64
bool visited[50][50][64];

int bfs() {
    queue<State> q;

    // 시작 위치 찾기
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (board[r][c] == '0') {
                q.push({r, c, 0, 0});
                visited[r][c][0] = true;
            }
        }
    }

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (board[cur.r][cur.c] == '1') {
            return cur.time;
        }

        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];

            // 범위 검사
            if (nr < 0 || nr >= N ||
                nc < 0 || nc >= M)
                continue;

            char next = board[nr][nc];

            // 장애물
            if (next == '#') continue;

            int nextMask = cur.mask;

            // 통과 자격 확인
            if (next >= 'A' && next <= 'F') {
                int bit = 1 << (next - 'A');

                if (!(cur.mask & bit))
                    continue;
            }

            // 포네그리프 획득
            if (next >= 'a' && next <= 'f') {
                // 1을 next-'a'의 bit만큼 왼쪽으로 밀겠다는 의미
                nextMask |= 1 << (next - 'a');
            }

            // 방문 여부 확인
            if (visited[nr][nc][nextMask])
                continue;

            visited[nr][nc][nextMask] = true;

            q.push({
                nr,
                nc,
                nextMask,
                cur.time + 1
            });
        }
    }

    return -1;
}

int main() {
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        cin >> N >> M;

        board.resize(N);

        for (int i = 0; i < N; i++) {
            cin >> board[i];
        }

        // 테스트케이스마다 방문 배열 초기화
        memset(visited, false, sizeof(visited));

        cout << "#" << tc << " " << bfs() << '\n';
    }

    return 0;
}
