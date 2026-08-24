#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	int test_case;
	int T;
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int N;
		priority_queue<int> pq;
		int curr;

		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &curr);
			pq.push(curr);
		}

		int cycle = 1;
		int answer = 0;
		while (N) {
			if (cycle != 3) {
				//printf("숫자 %d개가 남았고, %d를 더했음\n", N, pq.top());
				answer += pq.top();
			}
			else {
				//printf("숫자 %d개가 남았고, %d는 건너뜀\n", N, pq.top());
				cycle = 0;
			}
			pq.pop();
			N--;
			cycle++;
		}

		printf("#%d %d\n", test_case, answer);
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}