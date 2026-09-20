#include <iostream>

#define MAX_SIZE 50

using namespace std;

// 맵 정보 구조체
struct MAP_INFO {
	bool is_ground;
	int dir, limit;
};

int n, m; // 맵 크기
MAP_INFO map[MAX_SIZE][MAX_SIZE]; // 맵 정보

// 좌표 정보 구조체
struct Pair {
	int y, x;
};

Pair now; // 스노우맨 위치
Pair end; // 목표 위치

/* 입출력 최적화 */
void fast_io() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
}


/* 맵 입력 */
void input_map() {
	int input;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {

			cin >> input;
			if (input == 1) {
				map[i][j].is_ground = true;
			} else if (input == 2) {
				now = { i, j };
			} else if (input == 3) {
				map[i][j].is_ground = true;
				end = { i, j };
			}
		}
	}
}


int main() {
	fast_io();

	cin >> n >> m;
	input_map();


}