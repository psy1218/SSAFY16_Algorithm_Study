#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <iostream>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;
    // stack을 2개 붙이면 queue 처럼 기능하지 않을까
    // 그런데 우선순위를 판별할 기준이 없음
    // 그냥 priority_queue에 넣으면 해결될까 -> 그런데 몇 번째 원소인지 저장할 수가 없음
    // pair<int, int> 사용? -> 근데 몇 번째 원소였는지까지 판별해서 정렬하는 방법이 있는가

    // 최종 아이디어
    // priorities 의 원소는 1 이상 9 이하이므로
    // 카운팅하는 배열(priority_counting)을 하나 준비한다. 크기 10
    // 그 후 그 배열에 가장 큰 인덱스의 값이 1 이상인 경우, 그 인덱스를 현재 queue에 존재하는 가장 높은 우선순위로 취급
    // 배열의 각 인덱스는 우선순위를 나타내고, 해당 인덱스의 값은 우선순위를 가진 priorities 원소의 개수
    // queue를 하나 선언하고, queue가 빌 때까지 반복한다
    // queue 원소의 자료형은 pair<int, int>로, 각각 우선순위와 인덱스를 나타낸다
    // 우선 queue에 priorities의 index 순서대로 넣는다
    // 그 후 queue에서 front를 저장해놓고 pop 하면서, 만약 .first(우선순위 값)이 가장 높은 우선순위와 같은 경우
    // priority_counting[가장 높은 우선순위] 값에 -- 진행
    // 만약 priority_counting[가장 높은 우선순위]가 0이 될 경우 -> 가장 높은 우선순위 갱신하는 과정 거치기
    // answer++ 처리
    // 그리고 .second(index 값)과 location을 비교한다 -> 같은 경우 answer 리턴하면서 종료
    // 만약 .first 가 가장 높은 우선순위와 다른 경우 다시 queue에 추가

    // 우선순위 별 카운팅하는 배열(priority_counting)
    int priority_counting[10] = { 0 };

    // 카운팅
    for (int i : priorities) {
        priority_counting[i] += 1;
    }

    // 가장 높은 우선순위
    int max_priority = 0;
    for (int i = 0; i < 10; i++) {
        if (i == 0) {
            continue;
        }
        if (priority_counting[i] > 0) {
            max_priority = i;
        }
    }
    // cout << "가장 높은 우선순위" << max_priority << endl;

    // 큐 선언
    queue<pair<int, int>> q;
    // 큐에 원소 추가
    for (int idx = 0; idx < priorities.size(); idx++) {
        q.push({ priorities[idx], idx });
    }

    // 현재 큐의 맨 앞(front) 원소 담아둘 변수 선언
    pair<int, int> curr_pair;

    // 큐가 빌 때까지 진행
    while (!q.empty()) {
        // 현재 큐의 맨 앞 저장
        curr_pair = q.front();
        // 큐에서 맨 앞 제거
        q.pop();

        // 맨 앞 요소의 우선순위 값이 가장 높은 우선순위인 경우
        if (curr_pair.first == max_priority) {
            // 카운팅 -1
            priority_counting[max_priority]--;
            // 만약 가장 높은 우선순위의 카운팅이 0이 될 경우, 다시 갱신
            if (priority_counting[max_priority] == 0) {
                for (int i = 0; i < 10; i++) {
                    if (i == 0) {
                        continue;
                    }
                    if (priority_counting[i] > 0) {
                        max_priority = i;
                    }
                }
            }
            // 프로세스 실행되므로 answer +1
            answer++;
            // 만약 맨 앞 요소의 인덱스가 location과 같은 경우 리턴하고 종료
            if (curr_pair.second == location) {
                return answer;
            }
        }
        // 맨 앞 요소의 우선순위 값이 가장 높은 우선순위가 아닌 경우 다시 큐에 추가하고 반복
        else {
            q.push(curr_pair);
        }
    }

    return answer;
}