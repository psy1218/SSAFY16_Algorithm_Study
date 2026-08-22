#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;
    queue<pair<int, int>> q;
    priority_queue<pair<int, int>> pq;
    int q_len = priorities.size();
    for (int i = 0; i < q_len; i++){
        q.push({priorities[i], i});
        pq.push({priorities[i], i});
    }
    int seq = 0; // pop될때마다 1씩 증가. 즉, pop된 요소의 인덱스
    while (!q.empty()){
        int cur_pq_top = pq.top().first;
        int cur_q_front = q.front().first;
        if (cur_pq_top == cur_q_front){
            seq++;
            if (q.front().second == location){ // 찾고자 하는 위치라면
                answer = seq;
                break;
            }
            pq.pop();
            q.pop();
        }
        else{
            pair<int, int> tmp = q.front();
            q.pop();
            q.push(tmp);
        }
    }
    return answer;
}
