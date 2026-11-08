#include <string>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

int K, N;
int answer = INT_MAX;

vector<vector<pair<int, int>>> requests;    // 상담 유형별로 분리한 참가자 요청
vector<vector<int>> waiting;                // 유형별 멘토 수에 따른 대기 시간

int calcWait(int type, int mentorCount){
    priority_queue<int , vector<int>, greater<int>> pq; // MinHeap
    
    for (int i = 0; i < mentorCount; i++){
        pq.push(0); // 멘토들 초기 종료시간 0으로 설정
    }
    
    int totalWait = 0;
    
    for (int i = 0; i < requests[type].size(); i++){
        int a = requests[type][i].first;
        int b = requests[type][i].second;
        
        int earliest = pq.top();
        pq.pop();
        
        int start = max(a, earliest);   // 상담 시작 가능 시간
        totalWait += start - a;
        pq.push(start + b);             // 이후 상담 종료 시간 저장
    }
    
    return totalWait;
}

void dfs(int type, int remaining, int totalWait){
    // params:
    //      type: 현재 멘토를 배정할 상담 유형
    //      remaining: 아직 배정하지 않은 멘토 수
    //      totalWait: 지금까지 배정한 유형들의 대기 시간 합
    
    if (type == K){
        if (remaining == 0){
            answer = min(answer, totalWait);
        }
        return;
    }
    
    // 해당 유형에 배정할 수 있는 최대 멘토 수
    // Ex) K = 3, remaining = 5, type = 0 => 1, 2번 유형에도 최소 한 명씩 배정 필요
    int maxMentors = remaining - (K - type - 1);    // 해당 유형에 배정할 수 있는 최대 멘토 수
    
    for (int m = 1; m <= maxMentors; m++){
        dfs(type + 1, remaining - m, totalWait + waiting[type][m]);
    }
}

int solution(int k, int n, vector<vector<int>> reqs) {
    K = k;
    N = n;
    answer = INT_MAX;
    
    requests.assign(k, {});
    waiting.assign(k, vector<int>(n + 1, 0));
    
    for (int i = 0; i < reqs.size(); i++){
        int a = reqs[i][0];
        int b = reqs[i][1];
        int c = reqs[i][2] - 1;
        
        requests[c].push_back({a, b});
    }
    
    for (int type = 0; type < k; type++){
        for (int m = 1; m <= n; m++){
            waiting[type][m] = calcWait(type, m);
        }
    }
    
    dfs(0, n, 0);
    
    return answer;
}
