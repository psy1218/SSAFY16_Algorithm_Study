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
int main() {
	int TC;
	cin >> TC;
	for (int i = 1; i <= TC; i++) {
		int n;
		cin >> n;
		priority_queue<int, vector<int>, greater<int>> pq;
		int tmp;
		for (int j = 0; j < n; j++) {
			int a;
			cin >> a;
			pq.push(a);
		}
		int sum = 0; // 지불할 총 비용
		// 우선 순위 큐 안의 요소 갯수를 3의 배수로 만들어주는 과정
		if (n % 3 == 1) {
			tmp = pq.top();
			pq.pop();
			sum += tmp;
		}
		else if (n % 3 == 2) {
			tmp = pq.top();
			pq.pop();
			sum += tmp;

			tmp = pq.top();
			pq.pop();
			sum += tmp;
		}
		else {
			// 이땐 그냥 통과
		}
		// 비용 구하기
		int cnt = 0;
		while (!pq.empty()) {
			tmp = pq.top();
			pq.pop();
			// cout << tmp << endl;
			if (cnt % 3 != 0) {
				sum += tmp;
			}
			cnt++;
		}
		cout << "#" << i << " " << sum << endl;
	}
	return 0;
}
