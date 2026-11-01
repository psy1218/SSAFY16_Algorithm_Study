#include <iostream>

using namespace std;

/* 차량 정보 구조체 */
struct Data {
    int time, dir, idx;
};

// 기본 정보
int N;
int answer[200000];


// 명령어 입력 큐
int front, rear;
Data que[200000];


// 교차로별 대기 큐
int road_front[4];
int road_rear[4];
Data road[4][200000];


/* 입출력 최적화 */
void fast_io() {
    cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
}


/* 명령어 입력 저장 */
void input() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int t;
		char w;
		cin >> t >> w;
		que[rear++] = { t, w - 'A', i };
	}
}


/* 각 차로 대기 차량 확인 */
bool ready_check() {
	for (int i = 0; i < 4; i++) {
		if (road_front[i] < road_rear[i]) {
			return true;
		}
	}

	return false;
}


/* 대기 중인 차량 개수 확인 */
int ready_car_cnt() {
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		if (road_front[i] < road_rear[i]) {
			cnt++;
		}
	}

	return cnt;
}


/* 서로 마주 보는 두 도로에만 차량이 있는지 확인 */
bool cross_check() {
	for (int i = 0; i < 4; i++) {
		int right = (i + 2) % 4;
		if (road_front[i] < road_rear[i] && road_front[right] < road_rear[right]) {
			return true;
		}
	}
	return false;
}


/* 시뮬레이션 수행 */
void solution() {
    int now_t = 0;
    while (true) {
        // 각 차로 대기 차량 확인
        if (!ready_check()) {

            // 명령어에 대기 차량이 없을 경우 탐색 중지
            if (front == rear) {
                break;
            }

            now_t = que[front].time;
        }

        // 현재 시각까지 도착한 차량을 각 도로에 배치
        while (front < rear && que[front].time <= now_t) {
            Data cur = que[front++];
            road[cur.dir][road_rear[cur.dir]++] = cur;
        }

        // 차량이 대기 중인 도로 개수
		int cnt = ready_car_cnt();

        // 네 도로가 모두 차 있으면 교착 상태
        if (cnt == 4) {
            break;
        }

        // 서로 마주 보는 두 도로에만 차량이 있는 경우
        if (cnt == 2 && cross_check()) {
            for (int i = 0; i < 4; i++) {
                if (road_front[i] == road_rear[i]) {
                    continue;
                }

                Data cur = road[i][road_front[i]++];
                answer[cur.idx] = now_t;
            }
        }
        // 그 외에는 오른쪽 도로가 비어 있는 차량 한 대 통과
        else {
            for (int i = 0; i < 4; i++) {
                if (road_front[i] == road_rear[i]) {
                    continue;
                }

                int right = (i + 3) % 4;

                if (road_front[right] < road_rear[right]) {
                    continue;
                }

                Data cur = road[i][road_front[i]++];

                answer[cur.idx] = now_t;
                break;
            }
        }

        now_t++;
    }
}



int main() {
    fast_io();

    // 명령어 입력
    input();
    
    fill(answer, answer + N, -1);
	// 시뮬레이션 수행
    solution();
    
    // 입력 순서대로 결과 출력
    for (int i = 0; i < N; i++) {
        cout << answer[i] << "\n";
    }

    return 0;
}