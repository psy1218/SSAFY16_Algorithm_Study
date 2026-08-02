#include <string>
#include <vector>
#include <queue>

using namespace std;

long long solution(int n, vector<int> works) {
    long long answer = 0;
    priority_queue<int> pq;
    int tmp_num = 0;

    for (int x : works) {
        pq.push(x);
    }

    for (long long i = 0; i < n; i++) {
        tmp_num = pq.top();
        if (tmp_num == 0) {
            return 0;
        }
        pq.pop();
        pq.push(tmp_num - 1);
    }

    while (!pq.empty()) {
        tmp_num = pq.top();
        answer += tmp_num * tmp_num;
        pq.pop();
    }

    return answer;
}