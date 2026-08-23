#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

int main(int argc, char** argv)
{
	// cin, cout을 사용했더니 실행 시간 초과가 발생
	// 따라서 scanf, printf로 대체
	// scanf_s를 사용하는 것이 권장되나, SWEA에서는 scanf_s 사용이 불가하여 scanf 사용

	// cin, cout과 버퍼를 공유하지 않음
	ios_base::sync_with_stdio(false);

	int test_case;
	int T;
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		printf("#%d ", test_case);

		// 커맨드 수
		int num_of_cmd;
		scanf("%d", &num_of_cmd);

		// 커맨드 타입 (1, 2)
		int cmd_type;
		// 커맨드 타입 1인 경우 추가할 원소
		int x;

		// max heap을 우선순위 큐로 구현
		priority_queue<int> max_heap;

		// 모든 커맨드를 실행할 때까지 반복
		while (num_of_cmd > 0) {
			scanf("%d", &cmd_type);

			// 커맨드 타입 1(원소 추가)인 경우
			if (cmd_type == 1) {
				scanf("%d", &x);
				max_heap.push(x);
			}
			// 커맨드 타입 2(최상단 노드 삭제)인 경우
			else {
				if (max_heap.empty()) {
					printf("-1 ");
				}
				else {
					printf("%d ", max_heap.top());
					max_heap.pop();
				}
			}

			// 커맨드수 -1
			num_of_cmd--;
		}
		printf("\n");
	}

	return 0;
}