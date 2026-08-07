#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
using namespace std;

int main() {

	freopen("input.txt", "r", stdin);

	for (int t = 0;t < 10;t++) {
		int N;
		string res = "";
		char c;

		cin >> N;

		stack<char>Info;

		for (int i = 0;i < N;i++) {
			cin >> c;


			if (c >= '0' && c <= '9') res += c;

			if (c == '(') Info.push(c);
			else if (c == ')') {
				while (1) {
					char temp = Info.top();
					Info.pop();
					if (temp == '(') break;
					res += temp;
				}
			}
			else if (c == '*') {
				// 기존 *가 있으면 먼저 출력
				while (1) {
					char temp = Info.top();
					if (temp != '*') break;
					res += Info.top();
					Info.pop();
				}

				// 새로운 * push
				Info.push(c);
			}
			else if (c == '+') {
				while (1) {
					char temp = Info.top();
					if (temp == '(') break;
					res += temp;
					Info.pop();
				}
				// 새로운 + push
				Info.push(c);

			}
		}

		// 입력이 끝난 후 남아있는 연산자 출력 - 까먹지 말기!!!! 
		while (!Info.empty()) {
			res += Info.top();
			Info.pop();
		}
	
		

		// cout << "#" << t + 1 << " " << res << '\n';

		stack<int>cal;
		for (int i = 0;i < res.size();i++) {
			if (res[i] == '*') {
				int a = cal.top();
				cal.pop();
				int b = cal.top();
				cal.pop();

				cal.push(a * b);
			}
			else if (res[i] == '+') {
				int a = cal.top();
				cal.pop();
				int b = cal.top();
				cal.pop();

				cal.push(a + b);
			}
			else cal.push(res[i] - '0');
		}

		cout << "#" << t + 1 << " " << cal.top() << '\n';

	}

	return 0;
}



/*

(A+(B*C))-(D/E)
ABC*+DE/-


3+(4+5)*6+7
345+6*+7+



*/