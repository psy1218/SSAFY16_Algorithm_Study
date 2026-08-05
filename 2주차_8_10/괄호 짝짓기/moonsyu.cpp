#include <iostream>

using namespace std;

int stack_top = 0;
char stack[100000];


int main() {

	cin.tie(nullptr);
	ios::sync_with_stdio(false);


	int tc = 10;
	for (int t = 1; t <= tc; t++) {
		int n;
		cin >> n;

		string input;
		cin >> input;

		int answer = 1;
		for (int i = 0; i < n; i++) {
			char c = input[i];
			// 여는 괄호일 경우 스택에 push
			if (c == '(' || c == '[' || c == '{' || c == '<') {
				stack[stack_top++] = c;
			}
			// 닫는 괄호일 경우
			else if (c == ')' || c == ']' || c == '}' || c == '>') {
				// stack이 비어있으면 유효하지 않음
				if (!stack_top) {
					answer = 0;
					break;
				}

				// 괄호의 짝이 맞는지 확인
				char top = stack[stack_top - 1];
				if (top == '(' && c == ')' ||
					top == '[' && c == ']' ||
					top == '{' && c == '}' ||
					top == '<' && c == '>') {
					stack_top--;
				}
				else {
					answer = 0;
					break;
				}
			}
		}

		cout << "#" << t << " " << answer << "\n";
	}
}