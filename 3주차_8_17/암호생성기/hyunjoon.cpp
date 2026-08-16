#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<queue>

using namespace std;

#define N 8

bool flag = 0;
queue<int> solve(queue<int> p) {
	for (int i = 1; i <= 5; i++) {
		int cur = 0;
		cur = p.front();
		p.pop();
		if (cur - i <= 0) {
			p.push(0);
			flag = 1;
			return p;
		}
		else {
			p.push(cur - i);
		}
	}

	return p;
}


int main(int argc, char** argv)
{
	(void)freopen("swea1225.txt", "r", stdin);
	int test_case;
	for (test_case = 1; test_case <= 10; ++test_case)
	{
		int T = 0;
		flag = false;
		cin >> T;
		cout << '#' << T << ' ';
		queue<int> password;
		for (int i = 0; i < 8; i++) {
			int num = 0;
			cin >> num;
			password.push(num);
		}

		for (;;) {
			password = solve(password);
			if (flag) break;
		}

		for (int i = 0; i < 8; i++) {
			cout << password.front() << ' ';
			password.pop();
		}

		cout << '\n';
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
