#include <iostream>
#include <string>
#include <vector>

using namespace std;

string solution(int n, int k, vector<string> cmd) {
    string answer = "";

    // k는 현재 가리키는 인덱스로 사용
    // 현재 행을 기준으로 이전 행과 다음 행 정보 저장
    vector<int> head(n);
    vector<int> tail(n);
    for (int i = 0; i < n; i++) {
        head[i] = i - 1;
        tail[i] = i + 1;
    }
    tail[n - 1] = -1;

    int curr_head;
    int curr_tail;
    // 이동거리
    int d;
    // 삭제 인덱스 저장
    vector<int> changes;
    // 롤백 인덱스
    int rollback_idx;

    // cmd 만큼 반복
    for (string cmd_elem : cmd) {
        if (cmd_elem[0] == 'D') {
            d = stoi(cmd_elem.substr(2));
            while (d--) {
                k = tail[k];
            }
        }
        else if (cmd_elem[0] == 'U') {
            d = stoi(cmd_elem.substr(2));
            while (d--) {
                k = head[k];
            }
        }
        else if (cmd_elem[0] == 'C') {
            curr_head = head[k];
            curr_tail = tail[k];
            changes.push_back(k);

            if (curr_tail == -1) {
                k = curr_head;
                tail[curr_head] = -1;
            }
            else if (curr_head == -1) {
                k = curr_tail;
                head[curr_tail] = -1;
            }
            else {
                k = curr_tail;
                tail[curr_head] = curr_tail;
                head[curr_tail] = curr_head;
            }
        }
        else if (cmd_elem[0] == 'Z') {
            rollback_idx = changes.back();
            changes.pop_back();

            curr_head = head[rollback_idx];
            curr_tail = tail[rollback_idx];

            if (curr_head != -1) {
                tail[curr_head] = rollback_idx;
            }

            if (curr_tail != -1) {
                head[curr_tail] = rollback_idx;
            }
        }
    }

    // 답 출력
    answer.assign(n, 'O');

    for (int change_idx : changes) {
        answer[change_idx] = 'X';
    }

    return answer;
}