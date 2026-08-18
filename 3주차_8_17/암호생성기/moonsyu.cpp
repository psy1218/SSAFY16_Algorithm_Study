#include <iostream>
#include <climits>

#define QUEUE_SIZE 100

using namespace std;


int front, rear;
int que[QUEUE_SIZE];

/* 입출력 최적화 */
void optimize_io() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}

int main() {

	optimize_io();

	int tc = 10;
	for (int t = 1; t <= tc; t++) {
		int trash;
		cin >> trash;

		int min_divide = INT_MAX;
		front = rear = 0;
		for (int i = 0; i < 8; i++) {
			cin >> que[rear++];
			min_divide = min(min_divide, (que[rear - 1] - 1) / 15);
		}

		for (int i = front; i < rear; i++) {
			que[i] -= min_divide * 15;
		}

		while (true) {

			// 원형 큐 구현
			front %= QUEUE_SIZE;
			rear %= QUEUE_SIZE;

			// 암호문 생성 규칙에 따라 계산
			int clac_num = que[front] - ((front++) % 5 + 1);
			if (clac_num <= 0) {
				que[rear++] = 0;
				break;
			}
			else {
				que[rear++] = clac_num;
			}
		}

		cout << "#" << t << " ";
		for (int i = front; i < rear; i++) {
			cout << que[i % QUEUE_SIZE] << " ";
		}
		cout << "\n";
	}
}