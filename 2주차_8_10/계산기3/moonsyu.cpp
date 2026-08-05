#include <iostream>

using namespace std;

int n;
int top;
char stack[10000];


/* 중위 -> 후위 표현식 변환 */
string in_to_postfix(string input) {
	string result = "";
    for (int i = 0; i < n; i++) {
        if (input[i] == '(') { // '('이면 스택에 push
            stack[top++] = input[i];
        } else if (input[i] == '*') {// '*'일 때
            // * 보다 우선순위가 낮은 연산자들을
            // stack에서 pop 후 result에 추가
            while (!(stack[top - 1] == '+' || stack[top - 1] == '(')) {
                result += stack[--top];
            }

            // 이후 stack에 * push
            stack[top++] = input[i];
        } else if (input[i] == ')') { // ')'일 때
            // '('가 나올 때까지 
            // stack에서 pop 후 result에 추가
            while (stack[--top] != '(') {
                result += stack[top];
            }
        } else if (input[i] == '+') { // '+'일 때
            // stack이 비어 있거나 '('가 나올 때까지
            // stack에서 pop 후 result에 추가
            while (!(top == 0 || stack[top - 1] == '(')) {
                result += stack[--top];
            }

            // 이후 stack에 + push
            stack[top++] = input[i];
        } else { // 그 외에는 모두 숫자이므로 result에 추가
            result += input[i];
        }
    }

    return result;
}


long long answer[10000];
long long output(string postfix) {
    top = 0;
    for (int i = 0; i < postfix.size(); i++) {
        if (postfix[i] == '*') {
            answer[top - 2] = answer[top - 2] * answer[top - 1];
            top--;
        }
        else if (postfix[i] == '+') {
            answer[top - 2] = answer[top - 2] + answer[top - 1];
            top--;
        }
        else {
            answer[top++] = postfix[i] - '0';
        }
    }

    return answer[0];
}


int main() {

    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int tc = 10;
    for (int t = 1; t <= tc; t++) {
        cin >> n;

        // 중위 표현식 입력
        string input;
        cin >> input;

        cout << "#" << t << " " << output(in_to_postfix(input)) << endl;
    }
}