#include <iostream>
#include <string>
#include <stack>

using namespace std;

// 스택 내부에서의 연산자 우선순위 (in-stack priority)
int get_isp(char op) {
    if (op == '*') return 2;
    if (op == '+') return 1;
    if (op == '(') return 0;
    return -1;
}

// 스택으로 들어갈 때의 연산자 우선순위 (incoming priority)
int get_icp(char op) {
    if (op == '*') return 2;
    if (op == '+') return 1;
    if (op == '(') return 3; // 여는 괄호는 들어갈 때 우선순위가 가장 높음
    return -1;
}

int main() {
    // 입출력 속도 향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 총 10개의 테스트 케이스 처리
    for (int t = 1; t <= 10; ++t) {
        int len;
        string infix;
        cin >> len >> infix;

        string postfix = "";
        stack<char> opStack;

        // 1. 중위 표기식을 후위 표기식으로 변환
        for (int i = 0; i < len; i++) {
            char ch = infix[i];

            // 피연산자(숫자)인 경우 그대로 결과 문자열에 추가
            if (ch >= '0' && ch <= '9') {
                postfix += ch;
            } 
            // 닫는 괄호인 경우 여는 괄호가 나올 때까지 pop
            else if (ch == ')') {
                while (!opStack.empty() && opStack.top() != '(') {
                    postfix += opStack.top();
                    opStack.pop();
                }
                if (!opStack.empty()) opStack.pop(); // '(' 제거
            } 
            // 연산자(+, *) 또는 여는 괄호('(')인 경우
            else {
                while (!opStack.empty() && get_isp(opStack.top()) >= get_icp(ch)) {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.push(ch);
            }
        }
        
        // 스택에 남은 연산자들 모두 처리
        while (!opStack.empty()) {
            postfix += opStack.top();
            opStack.pop();
        }

        // 2. 후위 표기식 계산
        stack<long long> valStack; // 곱셈 과정에서 값이 커질 수 있으므로 안전하게 long long 사용
        for (int i = 0; i < postfix.length(); i++) {
            char ch = postfix[i];

            // 피연산자(숫자)인 경우 스택에 push
            if (ch >= '0' && ch <= '9') {
                valStack.push(ch - '0');
            } 
            // 연산자인 경우 스택에서 두 개의 값을 꺼내어 계산
            else {
                long long b = valStack.top(); valStack.pop();
                long long a = valStack.top(); valStack.pop();

                if (ch == '+') {
                    valStack.push(a + b);
                } else if (ch == '*') {
                    valStack.push(a * b);
                }
            }
        }

        // 결과 출력
        cout << "#" << t << " " << valStack.top() << "\n";
    }

    return 0;
}
