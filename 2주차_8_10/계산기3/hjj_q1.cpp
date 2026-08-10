#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    for (int test_case = 1; test_case <= 10; test_case++)
    {
        // 입력값
        int n;
        string expression;
        // 후위 계산식
        string postfix_expression;

        // 스택(계산식 변형 시 연산자 및 괄호 저장용)
        vector<char> saving;
        // 스택의 마지막 원소
        char last;
        // 스택(후위 계산식 풀이 시 사용)
        vector<int> saving_for_solving;

        // 후위 계산식 계산 시 사용할 변수
        // 스택의 마지막 원소와, 마지막에서 두번째 원소
        int a;
        int b;

        // 정답
        int answer = 0;

        cin >> n;
        cin >> expression;

        // 중위 계산식 -> 후위 계산식 변환
        // 연산자: +, *
        // 연산자 우선순위: * > +
        // 피연산자: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        for (char c : expression) {
            // 숫자면 바로 후위 계산식에 반영
            // 스택 반영할 것 없으므로 continue
            if (int(c) - int('0') >= 0 && int(c) - int('9') <= 0) {
                postfix_expression += c;
                continue;
            }
            // 스택 안에 괄호나 연산자가 있는 경우
            else if (!saving.empty()) {
                // 마지막 요소
                last = saving.back();

                // 현재 닫는 괄호인 경우
                // 1. (반복) 스택 마지막 요소가 여는 괄호일 때까지 스택에서 연산자 꺼내며(제거하며) 후위 계산식에 추가
                // 2. (반복) last는 현재 스택의 마지막 요소로 계속 초기화
                // 3. last가 여는 괄호가 될 경우 반복문 탈출, 여는 괄호는 계산식에 반영하지 않으므로 스택에서 제거
                // 닫는 괄호도 스택에 반영할 것 없으므로 continue
                if (c == ')') {
                    while (last != '(') {
                        postfix_expression += last;
                        saving.pop_back();
                        last = saving.back();
                    }
                    saving.pop_back();
                    continue;
                }
                // 현재 +나 *인 경우
                // 1. (반복) 스택 마지막 요소가 여는 괄호일 때까지 스택에서 연산자 꺼내며(제거하며) 후위 계산식에 추가
                // 1-1. 스택 마지막 요소가 + 이고 현재 *인 경우, *이 더 우선순위가 높으므로 1번 과정 없이 바로 반복에서 탈출
                // 2. (반복) last는 현재 스택의 마지막 요소로 계속 초기화
                // 3. last가 여는 괄호가 될 경우, 또는 스택이 비게 될 경우 반복문 탈출
                // 현재 +나 *는 if문 탈출 후 스택에 추가
                else if (c == '+' || c == '*') {
                    while (last != '(') {
                        // 우선순위 고려 (*가 +보다 먼저 처리되어야 하므로, 해당 순서인 경우 스택에 추가)
                        if (last == '+' && c == '*') {
                            break;
                        }
                        postfix_expression += last;
                        saving.pop_back();
                        if (saving.empty()) {
                            break;
                        }
                        last = saving.back();
                    }
                }
            }
            // 스택이 비어있지 않고, 현재 여는 괄호가 아닌 경우
            // 또는 스택이 비어있고 숫자가 아닌 경우
            saving.push_back(c);
        }
        // 스택의 모든 연산자 후위 계산식에 반영하면서 제거
        while (!saving.empty()) {
            postfix_expression += saving.back();
            saving.pop_back();
        }

        // 중간 확인용 (주석 처리)
        //cout << postfix_expression << endl;

        // 후위 계산식 계산
        for (char c : postfix_expression) {
            // 숫자인 경우 스택에 누적
            if (int(c) - int('0') >= 0 && int(c) - int('9') <= 0) {
                saving_for_solving.push_back(int(c) - int('0'));
            }
            // 연산자인 경우 연산 후 스택에 누적
            else {
                a = saving_for_solving.back();
                saving_for_solving.pop_back();
                b = saving_for_solving.back();
                saving_for_solving.pop_back();

                if (c == '+') {
                    saving_for_solving.push_back(a + b);
                }
                else if (c == '*') {
                    saving_for_solving.push_back(a * b);
                }
            }
        }
        // 정답 도출
        answer = saving_for_solving.back();

        // 결과 확인용 (주석 처리)
        //cout << answer << endl;

        // 실제 출력
        cout << '#' << test_case << " " << answer << endl;
    }
    return 0;
}