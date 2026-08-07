#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
using namespace std;

int main() {

	freopen("input.txt", "r", stdin);

	int T = 10;
	for (int t = 0;t < T;t++) {
		int N, flag = 1;
		char c;
		stack<char>Info;

		cin >> N;

		for (int i = 0;i < N;i++) {
			cin >> c;
			if (c == '{' || c == '[' || c == '(' || c == '<') {
				Info.push(c);
			}
			else {
				if (Info.empty()) {
					flag = 0;
					continue;
				}

				char Front = Info.top();
				if (c == '}' && Front != '{') flag = 0;
				if (c == ']' && Front != '[') flag = 0;
				if (c == '>' && Front != '<') flag = 0;
				if (c == ')' && Front != '(') flag = 0;

				Info.pop();
			}
		}

		cout << '#' << t + 1 << " " << flag << "\n";

	}
	return 0;
}

// 여는 괄호 나오고 닫는 괄호 나올 때 가장 마지막으로 열었던 괄호가 나와야함. 