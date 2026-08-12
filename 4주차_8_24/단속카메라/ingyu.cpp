#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> routes) {
    sort(routes.begin(), routes.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    });

    deque<vector<int>> q(routes.begin(), routes.end());

    int cnt = 0;

    while (!q.empty()) {
        vector<int> cur_car = q.front();
        q.pop_front();

        int cur_start_time = cur_car[1];

        if (q.empty()) {
            cnt++;
            break;
        }

        while (!q.empty() && q.front()[0] <= cur_start_time) {
            q.pop_front();
        }

        cnt++;
    }

    return cnt;
}
