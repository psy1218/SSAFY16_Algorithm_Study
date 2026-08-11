#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	for (int t = 0;t < 10;t++) {
		
		queue<int>q;
		int a, num;
		cin >> a;
		for (int i = 0;i < 8;i++) {
			cin >> num;
			q.push(num);
		}

		int flag = 0;
		while (1) {
			// 중단 조건문
			if (flag == 1) break;

			for(int k = 1;k <= 5 ; k++) {
				int cur = q.front();
				q.pop();

				if (cur - k <= 0) {
					q.push(0);
					flag = 1;
					break;
				}
				else q.push(cur - k);
			}
		}


	
		cout << '#' << t + 1 << " ";
		while (!q.empty()) {
			cout << q.front() << " ";
			q.pop();
		}
		cout << "\n";
	}


	return 0;
}