#include <iostream>
#include <algorithm>

using namespace std;

struct Comp {
	bool operator()(long long& a, long long& b) {
		return a > b;
	}
};

long long clothes[100000];

void optimize_io() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
}

int main() {
	optimize_io();

	int tc;
	cin >> tc;

	for (int t = 1; t <= tc; t++) {
		int n;
		cin >> n;

		for (int i = 0; i < n; i++) {
			cin >> clothes[i];
		}

		sort(clothes, clothes + n, Comp());

		long long answer = 0;
		for (int i = 0; i < n; i++) {
			answer += ((i + 1) % 3 ? clothes[i] : 0);
		}

		cout << "#" << t << " " << answer << "\n";
	}
}