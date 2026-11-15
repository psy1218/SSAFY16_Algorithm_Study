#include <iostream>
#include <string>

using namespace std;

// 각 의자의 초기 상태. 입력 이후 변경하지 않음
int chair[4][8];
// 시계 방향 기준 회전량. 항상 0~7로 유지
int rotation[4] = { 0 };

// n번째 의자의 현재 pos 위치에 있는 사람의 지역을 반환
// pos: 0 = 위쪽, 2 = 오른쪽, 6 = 왼쪽
int getState(int n, int pos) {
    int originalIndex = (pos - rotation[n] + 8) % 8;
    return chair[n][originalIndex];
}

void rotate(int target, int direction) {
    // 이번 요청에서 각 의자가 회전할 방향
    // 1: 시계 방향, -1: 반시계 방향, 0: 회전하지 않음
    int dir[4] = { 0 };
    dir[target] = direction;

    // 1. target에서 왼쪽으로 회전 전파 여부 확인
    for (int i = target; i > 0; --i) {
        // 왼쪽 의자의 오른쪽 자리와 현재 의자의 왼쪽 자리 비교
        if (getState(i - 1, 2) == getState(i, 6)) {
            break;
        }

        dir[i - 1] = -dir[i];
    }

    // 2. target에서 오른쪽으로 회전 전파 여부 확인
    for (int i = target; i < 3; ++i) {
        // 현재 의자의 오른쪽 자리와 오른쪽 의자의 왼쪽 자리 비교
        if (getState(i, 2) == getState(i + 1, 6)) {
            break;
        }

        dir[i + 1] = -dir[i];
    }

    // 3. 모든 회전 방향을 결정한 뒤 회전량 갱신
    for (int i = 0; i < 4; ++i) {
        rotation[i] = (rotation[i] + dir[i] + 8) % 8;
    }
}

int main() {
    // 각 의자의 초기 상태 입력
    for (int i = 0; i < 4; ++i) {
        string seats;
        cin >> seats;

        for (int j = 0; j < 8; ++j) {
            chair[i][j] = seats[j] - '0';
        }
    }

    int k;
    cin >> k;

    while (k--) {
        int n, d;
        cin >> n >> d;

        // 입력 의자 번호는 1~4, 배열 인덱스는 0~3
        rotate(n - 1, d);
    }

    int answer = 0;

    for (int i = 0; i < 4; ++i) {
        // 현재 12시 방향에 남쪽 지방 사람이 앉아 있는 경우
        if (getState(i, 0) == 1) {
            answer += (1 << i);  // 1, 2, 4, 8
        }
    }

    cout << answer << '\n';

    return 0;
}