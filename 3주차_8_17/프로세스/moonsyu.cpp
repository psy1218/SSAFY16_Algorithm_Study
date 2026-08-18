#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 프로세스 정보 구조체
struct Process_info {
    int order;
    bool is_know;
};

// 프로세스 큐
int front, rear;
Process_info que[1000000];


int solution(vector<int> priorities, int location) {
    // 큐에 프로세스 정보 할당
    for (int i = 0; i < priorities.size(); i++) {
        que[rear++] = { priorities[i], i == location };
    }

    // 주어진 프로세스의 우선순위 정렬 (오름차순)
    sort(priorities.begin(), priorities.end());

    int answer = 0;
    while (front < rear) {
        auto [order, is_know] = que[front++];

        // 현재 프로세스의 우선순위가 가장 높을 경우
        if (priorities.back() == order) {
            answer++;
            priorities.pop_back();

            // 찾고자 했던 프로세스라면 탐색 종료
            if (is_know) {
                break;
            }
        }
        else {
            que[rear++] = { order, is_know };
        }
    }

    return answer;
}