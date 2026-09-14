#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <queue>
#include <string>
#include <deque>

using namespace std;

struct pos {
	int y;
	int x;
};

int dxdy[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

int N, M, K;

int x[10000], y[10000];

char d[1000];
int p[1000];

int arr[101][101];

int time = 0;

bool is_valid(int y, int x) {
	return y >= 0 && y < N && x >= 0 && x < N;
}

void move(deque<pos>& dq, char cmd, bool is_apple) {

	// 현재 머리
	pos head = dq.back();

	pos nxt;

	if (cmd == 'R') {
		nxt.y = head.y;
		nxt.x = head.x + 1;
	}
	else if (cmd == 'L') {
		nxt.y = head.y;
		nxt.x = head.x - 1;
	}
	else if (cmd == 'U') {
		nxt.y = head.y - 1;
		nxt.x = head.x;
	}
	else if (cmd == 'D') {
		nxt.y = head.y + 1;
		nxt.x = head.x;
	}

	// 새로운 머리 추가
	dq.push_back(nxt);

	// 사과가 없으면 꼬리 제거
	if (!is_apple) {
		dq.pop_front();
	}

	time++;
}

bool check_bump(deque<pos>& dq) {
	// 머리를 기준으로 몸과 겹치는지 검사
	pos head = dq.back();

	for (int i = 0; i < dq.size() - 1; i++) {

		pos cur = dq[i];

		if (cur.y == head.y && cur.x == head.x) {
			return true;
		}
	}

	return false;
}

bool is_valid_all(deque<pos>& dq) {
	for (auto ele : dq) {

		if (!is_valid(ele.y, ele.x)) {
			return false;
		}
	}

	return true;
}

int main() {
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++)
		cin >> x[i] >> y[i];

	for (int i = 0; i < K; i++)
		cin >> d[i] >> p[i];
	deque<pos> dq;
	pos cur;
	cur.y = 0;
	cur.x = 0;

	dq.push_back(cur);

	memset(arr, 0, sizeof(arr));

	// 사과 위치 저장
	for (int i = 0; i < M; i++) {
		arr[x[i] - 1][y[i] - 1] = 1;
	}

	bool flag = false;

	for (int i = 0; i < K; i++) {

		if (flag)
			break;

		char cmd = d[i];
		int move_size = p[i];

		for (int j = 0; j < move_size; j++) {

			pos head = dq.back();

			int ny = head.y;
			int nx = head.x;

			// 다음 위치 계산
			if (cmd == 'R') {
				nx++;
			}
			else if (cmd == 'L') {
				nx--;
			}
			else if (cmd == 'U') {
				ny--;
			}
			else if (cmd == 'D') {
				ny++;
			}

			// ★ 먼저 범위를 체크해야 함
			// 범위를 벗어난 이동도 1초가 걸림
			if (!is_valid(ny, nx)) {
				time++;
				flag = true;
				break;
			}

			// 사과 확인
			bool is_apple = false;
			if (arr[ny][nx] == 1) {
				is_apple = true;

				//먹은 사과는 사라짐
				arr[ny][nx] = 0;
			}

			// 한 칸 이동
			move(dq, cmd, is_apple);

			//한 칸 움직일 때마다 충돌 체크
			if (check_bump(dq)) {
				flag = true;
				break;
			}
		}
	}

	cout << time;

	return 0;
}
