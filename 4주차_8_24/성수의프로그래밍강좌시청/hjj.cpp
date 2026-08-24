#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

// k번째 강좌를 시청한 후 실력을 f(k) 라고 표현할 때
// f(k + 1) = (f(k) + M_(k+1)) / 2
// 
// 해당 풀이의 밑바탕: 상위 k개의 강좌를 오름차순으로 수강해야 한다
// 증명되어야 하는 것
// 1. 왜 상위 k개를 골라야 하는가
// 2. 왜 k개가 오름차순이어야 하는가 (즉, 왜 실력이 낮게 오르는 것부터 들어야 하는가)
// 
// [1번 증명]
// 실력을 최대로 올리는 어떤 최적의 k개의 강의를 골랐다고 가정
// k개 강의 중 실력을 x 만큼 올리는 강의가 있고
// 그 외의 강의(n - k개 강의) 중 실력을 y 만큼 올리는 강의가 있는데
// x <= y 라고 가정한다.
// 그럼 x나 y를 수강하기 이전의 실력을 S라고 할 때
// S_x = (S + x) / 2, S_y = (S + y) / 2 이고
// 두 실력의 차 S_y - S_x = (y - x) / 2 >= 0 이다. (x <= y 이므로)
// 그리고 이후 공통적으로 실력을 z 만큼 올리는 강의를 수강할 경우
// S_xz = (S_x + z) / 2, S_yz = (S_y + z) / 2 이고
// 두 실력의 차 S_yz - S_xz = (S_y - S_x) / 2 = (y - x) / 4 >= 0 이다.
// 
// 따라서 x 대신 y를 시청할 때 더 실력이 높아진다는 것은
// 현재 고른 k개의 강의는 최적의 경우가 아니므로 모순
// 그러므로 이 모순을 해결하는 방향으로 나아가다 보면, 상위 k개를 고르게 됨
// 
// [2번 증명]
// k개의 강좌 중 실력을 각각 a, b씩 올리는 강의가 있다고 할 때
// a <= b 라고 한다면, 수강 전 실력 S에 대해서
// a -> b 순으로 수강할 때와 b -> a 순으로 수강할 때의 실력을 구하면
// S_ab = (S_a + b) / 2 = ((S + a) / 2 + b) / 2 = (S + a + 2b) / 4
// S_ba = (S_b + a) / 2 = ((S + b) / 2 + a) / 2 = (S + b + 2a) / 4
// 두 실력의 차 S_ab - S_ba = (b - a) / 4 >= 0 이다. (a <= b 이므로)
// 
// 따라서 a -> b 순서로 들어야 더 실력이 높아지므로
// 이를 계속 교환해나가면 k개를 오름차순으로 정렬하는 꼴이 된다.
//
int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);

	int test_case;
	int T;
	scanf_s("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		// n, k 입력
		int n, k;
		scanf_s("%d %d", &n, &k);

		// 정답은 소수점 형태이므로 float 자료형 이용
		float answer = 0.0f;

		// 상위 k개 추출을 위해 pq를 사용했는데
		// 고정된 입력 데이터를 사용하는 경우 해당 데이터를 정렬한 후 사용하는 것이 더 효율적
		priority_queue<int> pq;
		// 수열 m 입력 버퍼
		int m;

		// pq 에 수열 m 추가
		// pq.top을 할 시 작은 숫자부터 빼기 위해 음수로 저장
		for (int i = 0; i < n; i++) {
			scanf_s("%d", &m);
			pq.push(-m);
		}

		// n - k 개 숫자들 제거
		for (int j = 0; j < n - k; j++) {
			pq.pop();
		}

		// pq가 빌 때까지 연산 수행
		while (!pq.empty()) {
			// 연산 수행 시 다시 양수로 돌리는 점 주의
			answer = (answer + (-pq.top())) / 2;
			pq.pop();
		}

		// 답 출력
		printf("#%d %.6f\n", test_case, answer);
	}
	return 0;
}