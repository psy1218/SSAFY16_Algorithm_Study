#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
int point[100000];

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> point[i];
	}
	int start[100000];
	int end[100000];
	for (int i = 0; i < m; i++) {
		cin >> start[i] >> end[i];
	}

	sort(point, point + n);
	vector<int> ans(m);
	// 1. 각 선분의 start 이상인 점의 인덱스 idx1와, end 초과인 점의 인덱스 idx2를 구한다.
	// 예를들어, [22, 59] 구간에서 start=22, end=59 이므로, idx1 = 1, idx2 = 3 (초과 인덱스) 이다.
	// 2. 즉, 해당 구간에 존재하는 점의 갯수 = idx2 - idx1 이다. 
	// 3. 각 선분을 순회하면서 해당 선분에 속하는 점의 갯수를 구하고 저장하면 된다.
	for (int i = 0; i < m; i++) {
		int st = start[i];
		int ed = end[i];
		int idx1 = lower_bound(point, point + n, st) - point;
		int idx2 = upper_bound(point, point + n, ed) - point;
		int cnt = idx2 - idx1;
		ans[i] = cnt;
	}

	for (auto ele : ans) {
		cout << ele << "\n";
	}
	return 0;
}
