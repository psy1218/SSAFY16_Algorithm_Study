#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <tuple>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;
unordered_map<char, int> dic;
int main() {

	dic['+'] = 0; // 연산기호 우선순위
	dic['*'] = 1; // 숫자가 높을수록 우선순위가 높음 
	for (int i = 1; i <= 10; i++) {
		int n;
		cin >> n;
		string midfix; // 중위표기식
		cin >> midfix; 
		int midfix_len = midfix.length();
		stack<char> opStack;
		string postfix; // 후위표기식
		// 1. 중위 -> 후위 표기식
		for (int j = 0; j < midfix_len; j++) {
			char ch = midfix[j]; // 현재 추가되는 문자(기호, 숫자)
			if (ch >= '0' && ch <= '9') { // 숫자라면
				postfix += ch; // 그냥 후위표기식에 바로 추가해준다.
			}
			else if (ch == '(') {
				opStack.push(ch);
			}
			else if (ch == ')') {
				while (!opStack.empty() && opStack.top() != '(') {
					char top = opStack.top();
					postfix += top;
					opStack.pop();
				}
				if (!opStack.empty() && opStack.top() == '(') {
					opStack.pop(); // 여는 괄호를 삭제하여 벽을 허문다.
				}
			}
			else { // 그 외 연산기호 +, *
				while (!opStack.empty() && opStack.top() != '(' && opStack.top() != ')' && dic[opStack.top()] >= dic[ch]) { // 즉, 기존의 연산기호의 우선순위가 새로 추가되는 기호보다 높을때
					char top = opStack.top();
					postfix += top;
					opStack.pop();
				}
				opStack.push(ch); // 위의 결과가 어떻던 항상 opStack에 추가해줘야 한다.
			}
		}
		// 마저 찌꺼기 기호 처리
		while (!opStack.empty()) { // 즉, 기존의 연산기호의 우선순위가 새로 추가되는 기호보다 높을때
			char top = opStack.top();
			postfix += top;
			opStack.pop();
		}
		// cout << "postfix:" << postfix << endl;
		// 2. 후위 표기식 -> 실제 연산
		int post_len = postfix.length();
		// cout << post_len << endl;
		stack<int> cal_stack;
		for (int j = 0; j < post_len; j++) {
			char ch = postfix[j];
			// cout << ch << endl;
			if (ch >= '0' && ch <= '9') {
				int new_int = ch - '0';
				cal_stack.push(new_int);
				// cout << new_int << "가 추가됨" << endl;
			}
			else {
				int digit1 = cal_stack.top();
				cal_stack.pop();
				int digit2 = cal_stack.top();
				cal_stack.pop();
				// cout << digit1 << "," << digit2 << "가 pop되고" << endl;
				if (ch == '+') {
					int new_int = digit1 + digit2;
					cal_stack.push(new_int);
					// cout << new_int << "가 추가됨" << endl;
				}
				else {
					int new_int = digit1 * digit2;
					cal_stack.push(new_int);
					// cout << digit1 * digit2 << "곱" << endl;
					// cout << new_int << "가 추가됨" << endl;
				}
			}
		}
		int ans = cal_stack.top();
		cout << "#" << i << " " << ans << endl;
	}
	return 0;
}
