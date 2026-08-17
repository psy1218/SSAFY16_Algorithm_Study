#include <string>
#include <vector>
#include <deque>
#include <utility>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;

    deque<pair<int, int>> q;
    vector<pair<int, int>> result;

    for (int i = 0; i < priorities.size(); i++) {
        q.push_back({priorities[i], i});
    }

    while (!q.empty()) {
        int cur_prior = q.front().first;
        int cur_idx = q.front().second;
        q.pop_front();

        bool flag = false;

        for (auto i : q) {
            int prior = i.first;
            int idx = i.second;

            // 더 우선순위가 큰 프로세스가 있다면
            if (cur_prior < prior) {
                flag = true;
                break;
            }
        }

        if (flag) {
            q.push_back({cur_prior, cur_idx});
        }
        else {
            // 우선순위가 더 큰게 없다면 실행
            result.push_back({cur_prior, cur_idx});
        }
    }

    for (int i = 0; i < result.size(); i++) {
        int cur_idx = result[i].second;

        if (cur_idx == location) {
            answer = i + 1;
            break;
        }
    }

    return answer;
}
