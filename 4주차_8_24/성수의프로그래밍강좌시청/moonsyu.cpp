#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Comp {
	bool operator()(double& a, double& b) {
		return a < b;
	}
};

double grade[200];

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
		int n, k;
		cin >> n >> k;

		for (int i = 0; i < n; i++) {
			cin >> grade[i];
		}

		sort(grade, grade + n, Comp());

		double answer = 0;
		for (int i = n - k; i < n; i++) {
			answer = (answer + grade[i]) / 2.0;
		}

		cout << "#" << t << " " << fixed << setprecision(6) << answer << "\n";
	}
}