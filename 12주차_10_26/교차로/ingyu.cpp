#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct car {
    int id;
    int request_time;
    char road;
};
int N;
vector<long long> t;
vector<char> w;
vector<queue<car>> q(4); // 교차로에 서기 전에 대기중인 차량들
vector<queue<car>> wait_q(4); // 교차로에서 대기중인 차량들

int main() {
    cin >> N;

    t.resize(N);
    w.resize(N);

    for (int i = 0; i < N; i++) {
        cin >> t[i] >> w[i];
    }

    // Please write your code here.
    for (int i = 0; i < N; i++) {
        car cur_car;
        cur_car.id = i;
        cur_car.request_time = t[i];
        cur_car.road = w[i];
        // cout << cur_car.id << '\n';
        // cout << cur_car.request_time << '\n';
        // cout << cur_car.road << '\n';
        q[w[i] - 'A'].push(cur_car);
    }
    // result[i] = i번째 차량이 교차로를 지난 시각
    vector<int> result(N, -1); // 초기값은 -1로 설정. 
    int time = 0;
    int cnt = 0; // 교차로를 지나간 차량의 갯수
    while (1) {
        if (cnt == N) {
            break; // 모든 차량이 지나갔다면
        }
        // 교차로에 대기 중인 차량이 없다면 다음 차량 진입 시각으로 이동 (반대로, 교차로에 대기 중인 차량이 있다면 시간을 점프하면 안된다.)
        // time을 1씩 증가시키지 않고 점프해야 시간초과가 안생긴다.
        bool all_empty = true;

        for (int i = 0; i < 4; i++) {
            if (!wait_q[i].empty()) {
                all_empty = false;
            }
        }

        if (all_empty) {
            int next_time = -1; // q.front에서 가장 작은 시각이 저장되야함

            for (int i = 0; i < 4; i++) {
                if (!q[i].empty()) {
                    int t = q[i].front().request_time;

                    if (next_time == -1 || t < next_time) { // 점프할 시각이 아직 갱신되지 않았거나, 더 작은 값이 있다면
                        next_time = t;
                    }
                }
            }

            if (next_time != -1 && time < next_time) { // 점프될 시각이 있다면
                time = next_time;
            }
        }


        // 현재 시각 time 기준으로 각 진입할 대기열 큐에 추가
        // 4가지 방향의 모든 도로들을 순회하면서 wait_q에 추가
        for (int i = 0; i < 4; i++) {
            // cout << "q[i].front" << q[i].front().request_time << '\n';
            if (!q[i].empty() && q[i].front().request_time == time) {
                //cout << "q[i].front().request_time:" << q[i].front().request_time << "\n";
                wait_q[i].push(q[i].front());
                q[i].pop();
            }
        }
        int hold_cnt = 0; // 지나갈 수 없는 도로 수. 4가 되면 교착상태 
        // 4방향 도로를 순회하면서 오른쪽 도로에 차량이 없는지 확인
        vector<int> flush_q(4, 0);
        for (int i = 0; i < 4; i++) {
            int j = i - 1; // 즉, j도로는 i도로의 오른쪽 도로
            if (j < 0) {
                j += 4;
            }
            if (!wait_q[i].empty() && wait_q[j].empty()) { // 오른쪽 도로가 비어있다면
                result[wait_q[i].front().id] = time; // 해당 차가 지나간 시각 저장
                flush_q[i] = 1;
                // wait_q[i].pop(); // 지나갈 수 있음.
                cnt++; // 지나간 차량
                // break;
            }
            else if (!wait_q[i].empty() && !wait_q[j].empty()) { // 오른쪽 도로가 비어있다면
                hold_cnt++;
            }
        }
        if (hold_cnt == 4){
            break;
        }
        for (int i = 0; i < 4; i++) {
            if (flush_q[i]) {
                wait_q[i].pop(); // 지나갈 수 있음.
            }
        }
        time++; // 차량이 지나갔던, 지나간 차가 없던, 시간은 흘러간다.
    }
    for (int i = 0; i < N; i++) {
        cout << result[i] << "\n";
    }

    return 0;
}
