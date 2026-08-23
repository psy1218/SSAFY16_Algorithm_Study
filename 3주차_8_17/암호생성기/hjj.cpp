#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;

	for (int i = 1; i <= 10; i++)
	{
		// 테스트케이스 숫자 입력
		cin >> test_case;

		// 큐 준비
		queue<int> q;
		// 문제 조건에 따라 큐의 맨 앞 숫자를 감소시킬 숫자 정의
		int reduce_num = 1;

		// 큐에 데이터 입력
		for (int j = 1; j <= 8; j++)
		{
			int q_num;
			cin >> q_num;
			q.push(q_num);
		}

		// 큐의 맨 뒤가 0일 때까지 반복
		while (q.back() != 0)
		{
			// 현재 큐의 맨 앞 추출
			int curr = q.front();
			q.pop();

			// 조건에 맞게 값을 낮춘 후, 0보다 작게된 경우 0으로 고정
			curr -= reduce_num;
			if (curr < 0) curr = 0;

			// 큐에 데이터 입력
			q.push(curr);
			// 감소시킬 숫자는 매 루프마다 +1
			// 그러나 5까지만 증가해야 하므로, 5보다 크게 될 경우 1로 초기화
			reduce_num++;
			if (reduce_num > 5) reduce_num = 1;
		}

		// 출력
		cout << "#" << test_case << " ";
		while (!q.empty()) {
			cout << q.front() << " ";
			q.pop();
		}
		cout << endl;
	}
	return 0;
}