#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
// 미사일 최소
// 개구간의 edge는 요격 불가
// 가장 많이 겹치는 부분을 찾아야 한다

// 다음 점이 겹치는 부분이 있는지 없는지(공유하는 구간) 확인\

int overlap_start;
int overlap_end;

bool check(vector<int> b){
    int cur_start = b[0];
    int cur_end = b[1];
    
    // 전 공유 구간의 끝점이 새로운 폭격 미사일의 시작점보다 뒤에 있으면, 겹치는 건 확정
    if(overlap_end > cur_start){
        overlap_start = cur_start;
        if(cur_end < overlap_end){
            //cur_end로 공유 구간 끝점 갱신
            overlap_end = cur_end;
        }
        return true;
    }
    
    else{
        //cur_start로 공유 구간 시작점 갱신
        overlap_start = cur_start;
        //cur_end로 공유 구간 끝점 갱신
        overlap_end = cur_end;
        return false;
    }
    
}


int solution(vector<vector<int>> targets) {
    int answer = 0;
    // 시작점 기준으로 sort
    sort(targets.begin(), targets.end());

    
    overlap_start = targets[0][0];
    overlap_end = targets[0][1];
    answer++;
    for(int i = 1; i<targets.size(); i++){
        if(check(targets[i])){
            continue;
        }
        else answer++;
    }
    return answer;
}
