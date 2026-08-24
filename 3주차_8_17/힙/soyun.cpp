#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;



int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	//freopen("input.txt", "r", stdin);

	int T, N, num;
	cin >> T;
	
	for (int t = 1;t <= T;t++) {
		cin >> N;

		priority_queue<int>pq;

		cout << "#" << t << " ";
		for (int n = 0;n < N;n++) {
			cin >> num;
			if (num == 1) {
				cin >> num;
				pq.push(num);
			}
			else {
				if (pq.empty()) cout << -1 << " ";
				else {
					cout << pq.top() << " ";
					pq.pop();
				}
			}
		}
		cout << "\n";
	}

	return 0;
}
