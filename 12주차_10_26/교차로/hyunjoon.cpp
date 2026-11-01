
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

int N;
vector<long long> t;
vector<string> w;
vector<long long> ans;

queue<int> road[4];

bool roads_empty() {
    for (int i = 0; i < 4; i++) {
        if (!road[i].empty()) return false;
    }
    return true;
}

int main() {
    cin >> N;

    t.resize(N);
    w.resize(N);
    ans.resize(N, -1);

    for (int i = 0; i < N; i++) {
        cin >> t[i] >> w[i];

        int dir = w[i][0] - 'A';
        road[dir].push(i);
    }

    long long cnt = t[0];

    while (!roads_empty()) {

        // 현재 시각에 대기 중인 차량 확인
        bool exist[4] = {false};
        bool any = false;
        long long next_time = LLONG_MAX;

        for (int i = 0; i < 4; i++) {
            if (road[i].empty()) continue;

            int id = road[i].front();

            if (t[id] <= cnt) {
                exist[i] = true;
                any = true;
            }
            else {
                next_time = min(next_time, t[id]);
            }
        }

        // 대기 중인 차가 없으면 다음 도착 시간으로 이동
        if (!any) {
            cnt = next_time;
            continue;
        }

        // 교착 상태 확인
        if (exist[0] && exist[1] &&
            exist[2] && exist[3]) {
            break;
        }

        // 각 도로별 통과 가능 여부
        bool pass[4] = {false};

        for (int i = 0; i < 4; i++) {
            int right = (i + 3) % 4;

            if (exist[i] && !exist[right]) {
                pass[i] = true;
            }
        }

        // 통과 가능한 차량들을 동시에 처리
        for (int i = 0; i < 4; i++) {
            if (!pass[i]) continue;

            int id = road[i].front();
            ans[id] = cnt;

            road[i].pop();
        }

        cnt++;
    }

    for (int i = 0; i < N; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}

