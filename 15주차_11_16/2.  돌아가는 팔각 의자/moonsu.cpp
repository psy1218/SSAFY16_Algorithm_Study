#include <iostream>
#include <string>


using namespace std;

/* 인접 리스트용 구조체 */
struct DATA {
	int left_idx;
	int right_idx;
};

DATA now_info[4];
string chair_info[4];

int k;
int n, d;

/* 빠른 입출력 설정 */
void fast_io() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}


/* 데이터 입력 함수 */
void input_data() {
	for (int i = 0; i < 4; i++) {
		cin >> chair_info[i];

		now_info[i].left_idx = 6;
		now_info[i].right_idx = 2;
	}

	cin >> k;
}


/* 오른쪽 원판 회전 */
void right_rotate(int idx, int dir) {
	if (idx < 3) {
		if (chair_info[idx][now_info[idx].right_idx] != chair_info[idx + 1][now_info[idx + 1].left_idx]) {
			right_rotate(idx + 1, -dir);
		}
	}

	// 회전 방향에 따라 인덱스 변경
	if (dir == 1) { // 시계 방향
		now_info[idx].left_idx = (now_info[idx].left_idx + 7) % 8;
		now_info[idx].right_idx = (now_info[idx].right_idx + 7) % 8;
	} else { // 반시계 방향
		now_info[idx].left_idx = (now_info[idx].left_idx + 1) % 8;
		now_info[idx].right_idx = (now_info[idx].right_idx + 1) % 8;
	}
}


/* 중복 회전 제거 */
void rollback_chair(int idx, int dir) {
	if (dir == 1) { // 시계 방향
		now_info[idx].left_idx = (now_info[idx].left_idx + 7) % 8;
		now_info[idx].right_idx = (now_info[idx].right_idx + 7) % 8;
	}
	else { // 반시계 방향
		now_info[idx].left_idx = (now_info[idx].left_idx + 1) % 8;
		now_info[idx].right_idx = (now_info[idx].right_idx + 1) % 8;
	}
}


/* 왼쪽 원판 회전 */
void left_rotate(int idx, int dir) {
	if (idx > 0) {
		if (chair_info[idx][now_info[idx].left_idx] != chair_info[idx - 1][now_info[idx - 1].right_idx]) {
			left_rotate(idx - 1, -dir);
		}
	}

	// 회전 방향에 따라 인덱스 변경
	if (dir == 1) { // 시계 방향
		now_info[idx].left_idx = (now_info[idx].left_idx + 7) % 8;
		now_info[idx].right_idx = (now_info[idx].right_idx + 7) % 8;
	} else { // 반시계 방향
		now_info[idx].left_idx = (now_info[idx].left_idx + 1) % 8;
		now_info[idx].right_idx = (now_info[idx].right_idx + 1) % 8;
	}
}


/* 결과 출력 */
void output_data() {
	int score = 0;
	for (int i = 0; i < 4; i++) {
		if (chair_info[i][(now_info[i].left_idx + 2) % 8] == '1') {
			score += (1 << i) * 1;
		}
	}

	cout << score << "\n";
}


int main() {
	// 빠른 입출력 설정
	fast_io();

	// 데이터 입력
	input_data();

	// 명령어 입력 후 회전 처리
	for (int i = 0; i < k; i++) {
		cin >> n >> d;
		right_rotate(n - 1, d);
		rollback_chair(n - 1, -d);
		left_rotate(n - 1, d);
	}

	// 결과 출력
	output_data();
}