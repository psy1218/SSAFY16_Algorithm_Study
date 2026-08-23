#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

vector<int> M;

bool desc(int a, int b) {
	if (a > b) return 1;
	else return 0;
}

bool aesc(int a, int b) {
	if (a > b) return 0;
	else return 1;
}

int main(void) {
	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++) {
		
		int N, K;
		cin >> N >> K;

		// 초기화
		M.clear();

		// 성수의 실력
		float A = 0;
		for (int i = 0; i < N; i++) {
			int tmp;
			cin >> tmp;
			M.push_back(tmp);
		}
		sort(M.begin(), M.end(), desc);

		for (int i = K-1; i >= 0; i--) {
			A = (A + M[i]) / 2;
		}
		
		cout << "#" << test_case << ": ";
		printf("%.8f\n", A);
	}
}
