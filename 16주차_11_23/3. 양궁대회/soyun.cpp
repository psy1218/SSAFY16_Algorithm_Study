
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxDiff = 0;

vector<int> apeach;
vector<int> lion;
vector<int> answer;

// 라이언과 어피치 점수 차이 계산
void calculate() {
    int a = 0;
    int b = 0;

    for (int i = 0; i <= 10; i++) {
        if (apeach[i] == 0 && lion[i] == 0) continue;

        if (lion[i] > apeach[i]) {
            a += 10 - i;
        }
        else {
            b += 10 - i;
        }
    }

    int diff = a - b;

    // 라이언이 이기지 못하면 제외
    if (diff <= 0) return;

    if (diff > maxDiff) {
        maxDiff = diff;
        answer = lion;
    }
    else if (diff == maxDiff) {

        // 점수 차이가 같으면 낮은 점수에 화살이 많은 경우 선택
        for (int i = 10; i >= 0; i--) {
            if (lion[i] > answer[i]) {
                answer = lion;
                break;
            }
            else if (lion[i] < answer[i]) {
                break;
            }
        }
    }
}

// 점수별 화살 배정 DFS
void dfs(int idx, int remain) {

    // 남은 화살은 0점에 모두 배정
    if (idx == 10) {
        lion[10] = remain;
        calculate();
        lion[10] = 0;
        return;
    }

    // 어피치보다 1발 더 쏴야 점수 획득
    int cnt = apeach[idx] + 1;

    // 현재 점수를 획득하는 경우
    if (remain >= cnt) {
        lion[idx] = cnt;
        dfs(idx + 1, remain - cnt);
        lion[idx] = 0; // 백트래킹
    }

    // 현재 점수를 포기하는 경우
    dfs(idx + 1, remain);
}

vector<int> solution(int n, vector<int> info) {

    apeach = info;
    lion.assign(11, 0);
    answer = {-1};
    maxDiff = 0;

    dfs(0, n);

    return answer;
}
