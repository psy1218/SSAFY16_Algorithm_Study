#include <iostream>
#include <vector>

using namespace std;

// (x, y)에 있는 기둥이 설치 조건을 만족하는지 검사
bool can_install_column(
    int x, int y,
    const vector<vector<bool>>& columns,
    const vector<vector<bool>>& beams
) {
    int n = static_cast<int>(columns.size()) - 1;

    // 위쪽으로 벽면을 벗어나는 경우
    if (y >= n) return false;

    // 1. 바닥 위
    if (y == 0) return true;

    // 2. 다른 기둥 위
    if (columns[y - 1][x]) return true;

    // 3. 왼쪽에서 오는 보의 오른쪽 끝 위
    if (x > 0 && beams[y][x - 1]) return true;

    // 4. 오른쪽으로 나가는 보의 왼쪽 끝 위
    if (beams[y][x]) return true;

    return false;
}

// (x, y)에 있는 보가 설치 조건을 만족하는지 검사
bool can_install_beam(
    int x, int y,
    const vector<vector<bool>>& columns,
    const vector<vector<bool>>& beams
) {
    int n = static_cast<int>(columns.size()) - 1;

    // 바닥이거나, 오른쪽으로 벽면을 벗어나는 경우
    if (y == 0 || x >= n) return false;

    // 1. 왼쪽 끝 아래에 기둥이 있음
    if (columns[y - 1][x]) return true;

    // 2. 오른쪽 끝 아래에 기둥이 있음
    if (columns[y - 1][x + 1]) return true;

    // 3. 양쪽 끝이 각각 다른 보와 연결됨
    if (x > 0 && beams[y][x - 1] && beams[y][x + 1])
        return true;

    return false;
}

// 현재 설치된 모든 구조물이 조건을 만족하는지 검사
bool isValid(
    const vector<vector<bool>>& columns,
    const vector<vector<bool>>& beams
) {
    int n = static_cast<int>(columns.size()) - 1;

    for (int y = 0; y <= n; ++y) {
        for (int x = 0; x <= n; ++x) {
            if (columns[y][x] &&
                !can_install_column(x, y, columns, beams)) {
                return false;
            }

            if (beams[y][x] &&
                !can_install_beam(x, y, columns, beams)) {
                return false;
            }
        }
    }

    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    // columns[y][x]: (x, y)에서 위쪽으로 세운 기둥
    // beams[y][x]:   (x, y)에서 오른쪽으로 설치한 보
    vector<vector<bool>> columns(n + 1, vector<bool>(n + 1, false));
    vector<vector<bool>> beams(n + 1, vector<bool>(n + 1, false));

    for (const auto& command : build_frame) {
        int x = command[0];
        int y = command[1];
        int type = command[2];    // 0: 기둥, 1: 보
        int action = command[3];  // 0: 삭제, 1: 설치

        if (action == 1) {
            // 설치: 조건을 만족하지 않으면 명령 무시
            if (type == 0) {
                if (!can_install_column(x, y, columns, beams))
                    continue;

                columns[y][x] = true;
            }
            else {
                if (!can_install_beam(x, y, columns, beams))
                    continue;

                beams[y][x] = true;
            }
        }
        else {
            // 삭제: 먼저 삭제하고, 문제가 생기면 복구
            if (type == 0) {
                columns[y][x] = false;

                if (!isValid(columns, beams))
                    columns[y][x] = true;
            }
            else {
                beams[y][x] = false;

                if (!isValid(columns, beams))
                    beams[y][x] = true;
            }
        }
    }

    vector<vector<int>> answer;

    // x 오름차순 -> y 오름차순 -> 기둥 먼저, 보 나중
    for (int x = 0; x <= n; ++x) {
        for (int y = 0; y <= n; ++y) {
            if (columns[y][x])
                answer.push_back({ x, y, 0 });

            if (beams[y][x])
                answer.push_back({ x, y, 1 });
        }
    }

    return answer;
}

int main() {
    for (vector<int> row : solution(5, { { 1, 0, 0, 1 },{ 1, 1, 1, 1 },{ 2, 1, 0, 1 },{ 2, 2, 1, 1 },{ 5, 0, 0, 1 },{ 5, 1, 0, 1 },{ 4, 2, 1, 1 },{ 3, 2, 1, 1 } })) {
        for (int elem : row) {
            cout << elem << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}