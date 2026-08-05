#include <string>
#include <vector>

using namespace std;

struct Move {
    int front, rear;
    bool is_active;
};

int top;
int stack[1000000];

Move table[1000000];

/* 표 초기값 설정 */
void reset_table(int& n) {
    //table[0] = { 0, 1, true };
    for (int i = 0; i < n; i++) {
        table[i] = { i - 1, i + 1, true };
    }
    //table[n - 1] = { n - 2, n - 1, true };
}


/* 테이블 삭제 */
void delete_table(int& k) {
    table[k].is_active = false;

    table[table[k].front].rear = table[k].rear;
    table[table[k].rear].front = table[k].front;

    // k 뒤에 테이블이 비활성화 되어 있다면 앞으로, 
    // 활성화 되어 있다면 뒤로 이동
    k = (table[table[k].rear].is_active ? table[k].rear : table[k].front);
}


/* 테이블 복구 */
void restore_table(int& k) {
    table[k].is_active = true;
    table[table[k].front].rear = k;
    table[table[k].rear].front = k;
}


/* 최종 결과 반환 */
void answer_table(string& answer, int& n) {
    for (int i = 0; i < n; i++) {
        answer += table[i].is_active ? "O" : "X";
    }
}


string solution(int n, int k, vector<string> cmd) {
    top = 0;
    reset_table(n);

    for (int i = 0; i < cmd.size(); i++) {
        char command = cmd[i][0];

        if (command == 'C') {
            stack[top++] = k;
            delete_table(k);
        }
        else if (command == 'Z') {
            restore_table(stack[--top]);
        }
        else {
            int value = stoi(cmd[i].substr(2));
            if (command == 'U') {
                for (int j = 0; j < value && k > 0; j++) {
                    k = table[k].front;
                }
            }
            else {
                for (int j = 0; j < value && k < n - 1; j++) {
                    k = table[k].rear;
                }
            }
        }
    }

    string answer = "";
    answer_table(answer, n);
    return answer;
}