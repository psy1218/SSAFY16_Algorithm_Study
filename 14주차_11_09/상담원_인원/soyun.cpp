
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

int K, N;
int answer = 1e9;

struct Info {
    int num;    // 참가자 번호
    int start;  // 상담 요청 시각
    int time;   // 상담 소요 시간
    int type;   // 상담 유형
};

struct compare {
    bool operator()(const Info &a, const Info &b) {
        return a.start > b.start;
    }
};

// 유형별 상담 요청
priority_queue<Info, vector<Info>, compare> pq[6];

// 유형별 멘토 수에 따른 대기 시간
int waitCost[6][21];


// 멘토 cnt명일 때 총 대기 시간 계산
int calculate(int type, int cnt) {

    // 멘토별 상담 종료 시각
    vector<int> mentor(cnt, 0);

    // 원본 우선순위 큐 복사
    auto temp = pq[type];

    int totalWait = 0;

    while (!temp.empty()) {

        Info cur = temp.top();
        temp.pop();

        // 가장 빨리 상담이 끝나는 멘토 찾기
        int idx = 0;

        for (int i = 1; i < cnt; i++) {
            if (mentor[i] < mentor[idx]) {
                idx = i;
            }
        }

        // 실제 상담 시작 시각 
        // 참가자가 상담 요청한 시간 vs 멘토가 상담 시작할 수 있는 시간 
        // -> MAX: 상담 시작 시간 = 더 늦은 시간 선택 
        int startTime = max(cur.start, mentor[idx]);

        // 기다린 시간 누적
        // 상담 가능한 시간보다 참가 신청한 시간이 더 빠르면 0이 된다. 
        // = 기다리지 않는다. 
        totalWait += startTime - cur.start;

        // 상담 종료 시각 갱신
        mentor[idx] = startTime + cur.time;
    }

    return totalWait;
}


// 유형별 멘토 인원 배정 - 멘토 N명을 K개의 상담 유형 조합 찾기 
// 상담 유형 , 남은 멘토 수, 총대기 시간 
void dfs(int type, int remain, int total) {

    // 모든 유형에 멘토 배정 완료
    if (type == K + 1) {

        // 멘토를 정확히 N명 배정한 경우
        if (remain == 0) {
            answer = min(answer, total);
        }

        return;
    }

    // 현재 유형에 배정할 멘토 수 결정
    for (int cnt = 1; cnt <= remain; cnt++) {

        // 남은 유형에도 최소 1명씩 배정해야 함
        // 현재 멘토 수와 배부 가능한 멘토 비교 = 모든 유형에 멘토 한 명씩 있어야함. 
        if (remain - cnt < K - type) continue;

        dfs(
            type + 1,                    // 다음 상담 유형
            remain - cnt,                // 남은 멘토 수
            total + waitCost[type][cnt]  // 누적 대기 시간
        );
    }
}


int solution(int k, int n, vector<vector<int>> reqs) {

    K = k;
    N = n;
    answer = INT_MAX;

    // 유형별 우선순위 큐 초기화
    for (int i = 1; i <= K; i++) {
        pq[i] = priority_queue<Info, vector<Info>, compare>();
    }

    // 상담 요청을 유형별로 분류
    for (int i = 0; i < reqs.size(); i++) {

        pq[reqs[i][2]].push({
            i,
            reqs[i][0],
            reqs[i][1],
            reqs[i][2]
        });
    }

    // 유형별 멘토 수에 따른 대기 시간 계산
    for (int type = 1; type <= K; type++) {

        for (int cnt = 1; cnt <= N; cnt++) {
            waitCost[type][cnt] = calculate(type, cnt);
        }
    }

    // 가능한 멘토 배정 조합 탐색
    dfs(1, N, 0);

    return answer;
}
