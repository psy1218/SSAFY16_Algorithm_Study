#include <iostream>
#include <stack>
#include <string>

using namespace std;

// 우선순위 계산 함수
int priority(char c) {
    if (c == '+' || c == '-')
        return 1;

    if (c == '*' || c == '/')
        return 2;

    return 0;
}

int main() {

    for (int t = 1; t <= 10; t++) {

        int n;
        string str;

        cin >> n >> str;
      // 식 변환
        stack<char> op;
        string back = "";

        for (int i = 0; i < n; i++) {

            char cur = str[i];

            // 숫자
            if (cur >= '0' && cur <= '9') {
                back.push_back(cur);
            }

            // ( 만나면 push
            else if (cur == '(') {
                op.push(cur);
            }

            // )
            else if (cur == ')') {

                while (!op.empty() && op.top() != '(') {
                    back.push_back(op.top());
                    op.pop();
                }

                // '(' 제거
                op.pop();
            }

            // 연산자
            else {

                while (!op.empty() &&
                       op.top() != '(' &&
                       priority(op.top()) >= priority(cur)) {

                    back.push_back(op.top());
                    op.pop();
                }

                op.push(cur);
            }
        }

        // 남은 연산자 전부 출력
        while (!op.empty()) {
            back.push_back(op.top());
            op.pop();
        }

    // 식 계산

        stack<int> num;

        for (char cur : back) {

            // 숫자
            if (cur >= '0' && cur <= '9') {

                // char  int
                num.push(cur - '0');
            }

            // 연산자
            else {

                // 첫 번째 pop = 오른쪽 숫자
                int b = num.top();
                num.pop();

                // 두 번째 pop = 왼쪽 숫자
                int a = num.top();
                num.pop();

                if (cur == '+') {
                    num.push(a + b);
                }
                else if (cur == '*') {
                    num.push(a * b);
                }
            }
        }


        cout << "#" << t << " " << num.top() << '\n';
    }

    return 0;
}
