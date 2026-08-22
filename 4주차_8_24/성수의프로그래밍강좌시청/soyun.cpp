#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

//	freopen("input.txt", "r", stdin);

	int T, N, K;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N >> K;
		vector<float>nums(N);
		for (int i = 0; i < N; i++) {
			cin >> nums[i];
		}

		sort(nums.begin(), nums.end());

		float res = 0;
		for (int i = N - K; i < N;i++) {
			res = (res + nums[i]) / 2;
		}

		cout << "#" << t << " " << float(res) << "\n";
	}

	return 0;
}
