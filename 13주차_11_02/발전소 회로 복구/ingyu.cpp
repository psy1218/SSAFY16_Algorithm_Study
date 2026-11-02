
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n, m;
// DFS에서 사용할 전역 변수
int panelCount;
vector<vector<int>> travelTime;
vector<int> pre_required;
vector<vector<int>> memo;

bool is_valid(int y, int x){
    return y >= 0 && y < n && x >= 0 && x < m;
}
// 시작 위치에서 모든 칸까지 최단 거리 계산(bfs)
vector<vector<int>> bfs(
    vector<string>& grid,
    int startRow,
    int startCol
) {
    int n = grid.size();
    int m = grid[0].size();

    // -1은 아직 방문하지 않았거나 도달할 수 없는 칸
    // dist[r][c] = 시작위치에서 (r, c) 까지 도달하는데 걸린 최소 시간
    vector<vector<int>> dist(n, vector<int>(m, -1));

    queue<pair<int, int>> q;

    dist[startRow][startCol] = 0;
    q.push({startRow, startCol});

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();

        // 상하좌우 탐색
        for (int d = 0; d < 4; d++) {
            int nr = row + dr[d];
            int nc = col + dc[d];

            // 격자 범위를 벗어나면 제외
            if (!is_valid(nr, nc))
                continue;

            // 벽이면 이동 불가능
            if (grid[nr][nc] == '#')
                continue;

            // 이미 방문한 칸이면 제외
            if (dist[nr][nc] != -1)
                continue;

            // 최단 거리 갱신
            dist[nr][nc] = dist[row][col] + 1;

            q.push({nr, nc});
        }
    }

    return dist;
}


// activatedMask : 현재 활성화된 패널, currentPanel : 현재 위치한 패널
int dfs(int activatedMask, int currentPanel) {

    // 모든 패널을 활성화했다면 종료
    if (activatedMask == (1 << panelCount) - 1) { // panelCount=5라면 0b100000 - 1 = 0b11111 = FULL이 됨.
        return 0;
    }

    // 이미 계산한 상태라면 저장된 값 반환
    int result = memo[activatedMask][currentPanel];;
    if (result != -1) {
        return result;
    }

    memo[activatedMask][currentPanel] = INF;

    // 다음에 활성화할 패널 탐색
    for (int next = 0; next < panelCount; next++) {
        int nextBit = 1 << next;
        // 이미 활성화된 패널이면 제외
        if (activatedMask & nextBit) // 활성화되지 않은 패널이라면 0이 됨
            continue;

        // 선행 조건을 만족하지 못하면 제외
        if ((activatedMask & pre_required[next])
            != pre_required[next])
            continue;

        // 이동할 수 없는 패널이면 제외
        if (travelTime[currentPanel][next] == INF)
            continue;
            
        // 여기까지 왔으면 memo[activatedMask][currentPanel] 는 갱신해야 하는 값임
        // 다음 패널을 활성화
        int nextMask = activatedMask | nextBit;
        // 다음 상태에서 남은 최소 시간
        int remain= dfs(nextMask, next);
        if (remain == INF)
            continue;

        // 이동 시간 + 이후 최소 시간
        int totalTime = travelTime[currentPanel][next] + remain;

        memo[activatedMask][currentPanel] = min(memo[activatedMask][currentPanel], totalTime);
    }

    return memo[activatedMask][currentPanel];
}


int solution(
    int h,
    vector<string> grid,
    vector<vector<int>> panels,
    vector<vector<int>> seqs
) {
    panelCount = panels.size();

    n = grid.size();
    m = grid[0].size();

    // 엘리베이터 위치 찾기
    int elevatorRow = -1;
    int elevatorCol = -1;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {

            if (grid[r][c] == '@') {
                elevatorRow = r;
                elevatorCol = c;
                break;
            }
        }
    }

    // 엘리베이터에서 모든 칸까지 최단 거리
    vector<vector<int>> elevatorDist = bfs(grid, elevatorRow, elevatorCol);

    // 패널 사이의 최단 이동 시간 계산
    // travelTime[i][j] = i패널에서 j패널까지 이동하는데 걸리는 시간
    travelTime.assign(panelCount, vector<int>(panelCount, INF));

    for (int i = 0; i < panelCount; i++) {
        int startFloor = panels[i][0];
        int startRow = panels[i][1] - 1;
        int startCol = panels[i][2] - 1;

        // i번 패널에서 모든 칸까지 BFS
        // 같은 층이 아니라면 i번 패널에서 엘리베이터까지 거리를 구하는데 쓰일수도 있고
        // 같은 층이라면 i번 패널에서 바로 j번 패널까지 이동하는데 거리를 구하는데 쓰일수도 있음.
        vector<vector<int>> dist = bfs(grid, startRow, startCol);

        for (int j = 0; j < panelCount; j++) {
            int targetFloor = panels[j][0];
            int targetRow = panels[j][1] - 1;
            int targetCol = panels[j][2] - 1;

            // 같은 층에 있는 경우. 엘리베이터까지의 거리를 계산할 필요가 없음.
            if (startFloor == targetFloor) {
                if (dist[targetRow][targetCol] != -1) {
                    travelTime[i][j] = dist[targetRow][targetCol];
                }
            }

            // 서로 다른 층에 있는 경우
            else {
                // 출발 패널에서 엘리베이터 거리
                int toElevator = dist[elevatorRow][elevatorCol];
                // 엘리베이터에서 도착 패널까지 거리
                int fromElevator = elevatorDist[targetRow][targetCol];
                // 엘리베이터 이동 시간
                int floorTime = abs(startFloor - targetFloor);

                if (toElevator != -1 && fromElevator != -1) {
                    // 즉, i패널에서 j패널까지 이동하는데 3가지 경로 길이의 합으로 이루어짐.
                    travelTime[i][j] = toElevator + floorTime + fromElevator;
                }
            }
        }
    }

    // 선행 활성화 조건 저장
    // pre_required[target] = target패널을 활성화하기 위한 조건. 비트마스크로 표현한다.
    // ex) pre_required[4] = 0b10011 라면 4번 패널을 활성화하기 위해선 1,2,5번 패널을 먼저 활성화 해야한다.
    pre_required.assign(panelCount, 0);
    for (auto seq : seqs) {
        int before = seq[0] - 1; // 활성화 조건 패널
        int after = seq[1] - 1; // 활성화 되는 패널

        pre_required[after] |= (1 << before);
    }

    // 메모이제이션 배열 초기화.
    // memo[mask][cur] = 현재 위치 cur에서 남은 패널을 모두 활성화하는 데 필요한 최소 시간
    memo.assign(1 << panelCount, vector<int>(panelCount, -1)); // 모든 활성화된 패널 상태의 경우의 수는 1 << panelCount = 2**panelCount 이기 때문 

    // 1번 패널 위치에서 출발. 아직 활성화된 패널은 없음 주의. (1패널 위치에서 출발해도 1패널이 활성화되었다는 보장이 없음.)
    return dfs(0, 0);
}
