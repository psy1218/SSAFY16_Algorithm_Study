#include <iostream>
#include <climits>

#define QUE_SIZE 1000000
#define MAX_SIZE 1000001

using namespace std;

int n;

struct Data {
	int num, time;
};

int front, rear;
Data que[QUE_SIZE];

int num[MAX_SIZE];

void fast_io() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
}

int main() {
	fast_io();

	cin >> n;
	fill(num, num + n + 2, INT_MAX);

	front = rear = 0;
	num[n] = 0;
	que[rear++] = { n, 0 };

	int answer = 0;
	while (que[front].num != 0) {
		Data cur = que[front++];

		if (cur.num % 3 == 0 && cur.time + 1 < num[cur.num / 3]) {
			num[cur.num / 3] = cur.time + 1;
			que[rear++] = { cur.num / 3, cur.time + 1 };
		}

		if (cur.num % 2 == 0 && cur.time + 1 < num[cur.num / 2]) {
			num[cur.num / 2] = cur.time + 1;
			que[rear++] = { cur.num / 2, cur.time + 1 };
		}

		if (cur.time + 1 < num[cur.num - 1]) {
			num[cur.num - 1] = cur.time + 1;
			que[rear++] = { cur.num - 1, cur.time + 1 };
		}

		if (cur.time + 1 < num[cur.num + 1]) {
			num[cur.num + 1] = cur.time + 1;
			que[rear++] = { cur.num + 1, cur.time + 1 };
		}
	}

	cout << num[1];
}