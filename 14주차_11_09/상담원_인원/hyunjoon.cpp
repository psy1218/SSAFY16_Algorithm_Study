#include <string>
#include <vector>
#include <climits>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
// K -> 유형, n -> 멘토 수
// 1. 멘토 유형별 배치
// 2. 기다린 시간 확인
// 3. 최소인지 비교?
// backtracking(k,n이 작음)
// 상담 순서는 정해져있음(시간 순서별)


int K;
int N;
vector<int> sel;
vector<vector<int>> REQS;

int waiting_time() {
    vector<int> mentor = sel;

    vector<priority_queue<int, vector<int>, greater<int>>> waiting(K);

    int ret_t = 0;

    for (int i = 0; i < REQS.size(); i++) {
        int start_t = REQS[i][0];
        int cost_t = REQS[i][1];
        int kind = REQS[i][2] - 1;

        // 배정되지 않은 멘토가 존재
        if (mentor[kind] > 0) {
            mentor[kind]--;
            waiting[kind].push(start_t + cost_t);
        }
        else {
            int next_time = waiting[kind].top();
            waiting[kind].pop();

            // 실제 상담 시작시간
            int real_start = max(start_t, next_time);

            // 대기시간 누적
            ret_t += real_start - start_t;

            // 새 상담 종료시간
            waiting[kind].push(real_start + cost_t);
        }
    }

    return ret_t;
}
int answer = INT_MAX;
void dfs(int L, int start){
    if(L==N-K){
        answer = min(answer, waiting_time());
        return;
    }
    
    for(int i = start; i<K; i++){
        sel[i]++;
        dfs(L+1, i);
        sel[i]--;
    }
}

int solution(int k, int n, vector<vector<int>> reqs) {
    K = k;
    N = n;
    REQS = reqs;
    // for(int i = 0; i<reqs.size(); i++){
    //     for(int j = 0; j<3; j++){
    //         cout << reqs[i][j]<<'\n';
    //     }
    // }
    sel.assign(K,1);
    dfs(0,0);
    return answer;
}
