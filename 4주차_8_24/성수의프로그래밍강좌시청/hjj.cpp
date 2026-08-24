#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

// k번째 강좌를 시청한 후 실력을 f(k) 라고 표현할 때
// f(k + 1) = (f(k) + M_(k+1)) / 2
// 실력의 변화량을 df 라고 한다면
// df = f(k + 1) - f(k) = (M_(k+1) - f(k)) / 2
// 즉 변화량을 계속 양수로 가져가야 최대 실력을 가질 수 있는 것이며
// 그 조건을 만족하려면, M_(k+1)이 이전 평균보다 커야 한다.
int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);

	int test_case;
	int T;
	scanf_s("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int n, k;
		scanf_s("%d %d", &n, &k);

		float answer = 0.0f;
		priority_queue<int> pq;
		int m;

		for (int i = 0; i < n; i++) {
			scanf_s("%d", &m);
			pq.push(-m);
		}

		for (int j = 0; j < n - k; j++) {
			pq.pop();
		}

		while (!pq.empty()) {
			answer = (answer + (-pq.top())) / 2;
			pq.pop();
		}

		printf("#%d %.6f\n", test_case, answer);
	}
	return 0;
}