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
#include <iomanip>
using namespace std;
int main() {
	int TC;
	cin >> TC;
	for (int i = 1; i <= TC; i++) {
		float n, k;
		cin >> n >> k;
		priority_queue<float, vector<float>, greater<float>> pq;
		int limit = n - k; // 최대 limit갯수만큼 빼야함
		for (int j = 0; j < n; j++) {
			float a;
			cin >> a;
			pq.push(a);
		}
		while (limit != 0) {
			pq.pop();
			limit--;
		}
		float cur = 0; // 성수의 실력
		while (!pq.empty()) {
			float num = pq.top();
			pq.pop();
			cur = (cur + num) / 2;
		}
		cout << "#" << i << " " << fixed << setprecision(6) << cur << endl;
	}
	return 0;
}
