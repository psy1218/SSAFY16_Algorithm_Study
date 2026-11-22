#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> answer;
vector<int> ryan(11, 0);
vector<int> apeach;
int max_diff = 0;

void dfs(int idx, int remain_arrows) {
    // 모든 점수 선택 완료 시
    if (idx == 10) {
        // 남은 화살은 0점에 모두 배분
        ryan[10] = remain_arrows;

        int ryanScore = 0;
        int apeachScore = 0;

        for (int i = 0; i <= 10; i++) {
            int score = 10 - i;

            if (ryan[i] > apeach[i]) {
                ryanScore += score;
            }
            else if (apeach[i] > 0) {
                apeachScore += score;
            }
        }

        int curr_diff = ryanScore - apeachScore;

        if (curr_diff > max_diff) {
            max_diff = curr_diff;
            answer = ryan;
        }
        else if (curr_diff == max_diff && curr_diff > 0) {
            // 낮은 점수에 더 많은 화살을 쏜 경우 우선
            for (int i = 10; i >= 0; i--) {
                if (ryan[i] == answer[i]) continue;

                if (ryan[i] > answer[i]) {
                    answer = ryan;
                }
                break;
            }
        }

        ryan[10] = 0;
        return;
    }

    // 1. 현재 점수 획득
    int needed = apeach[idx] + 1;

    if (remain_arrows >= needed) {
        ryan[idx] = needed;
        dfs(idx + 1, remain_arrows - needed);
        ryan[idx] = 0;
    }

    // 2. 현재 점수 포기
    dfs(idx + 1, remain_arrows);
}

vector<int> solution(int n, vector<int> info) {
    apeach = info;
    answer.clear();
    ryan.assign(11, 0);
    max_diff = 0;

    dfs(0, n);

    if (answer.empty()) return { -1 };

    return answer;
}

int main() {
    // testcase 1: {0,2,2,0,1,0,0,0,0,0,0}
    for (int elem : solution(5, { 2,1,1,1,0,0,0,0,0,0,0 })) {
        cout << elem << " ";
    }
    cout << "\n";
    // testcase 2: {-1}
    for (int elem : solution(5, { 1,0,0,0,0,0,0,0,0,0,0 })) {
        cout << elem << " ";
    }
    cout << "\n";
    // testcase 3: {1,1,2,0,1,2,2,0,0,0,0}
    for (int elem : solution(5, { 0,0,1,2,0,1,1,1,1,1,1 })) {
        cout << elem << " ";
    }
    cout << "\n";
    // testcase 4: {1,1,1,1,1,1,1,1,0,0,2}
    for (int elem : solution(5, { 0,0,0,0,0,0,0,0,3,4,3 })) {
        cout << elem << " ";
    }
    cout << "\n";
}