#include <string>
#include <vector>
#include <iostream>
using namespace std;

// 같은 점수에 똑같이 쐈을 시 -> 더 많이 해당 점수에 맞춘 사람이 점수를 획득
int N;

vector<int> score(11,0);
vector<int> answer;
vector<int> info;

int diff_max = -1;
void dfs(int L, int remain) {
    if (L == 10) {  // 0점 칸
        score[10] = remain;
        int diff = 0;
        for(int i = 0; i<11; i++){
            if(info[i] < score[i]){
                diff += (10-i);
            }
            else if (info[i] > score[i] || (info[i] == score[i] && info[i] != 0 && score[i] != 0)){
                diff -= (10-i);
            }
        }
        
        if(diff<=0 || diff<diff_max) return;
        
        if(diff_max < diff && diff > 0) {
            diff_max = diff;
            answer = score;
        }
        else if(diff_max == diff){
            for(int i = 10; i>=0; i--){
                if(score[i] < answer[i]){
                    return;
                }
                if(score[i] > answer[i]){
                    break;
                }
            }
            
            diff_max = diff;
            answer = score;
        }
        return;
    }

    int need = info[L] + 1;

    // 이 칸의 점수를 가져가는 경우
    if (remain >= need) {
        score[L] = need;
        dfs(L + 1, remain - need);
    }

    // 이 칸에 0발 쏘는 경우
    score[L] = 0;
    dfs(L + 1, remain);
}

vector<int> solution(int n, vector<int> a) {
    N = n;
    info = a;
    
    dfs(0,n);
    if(diff_max == -1){ 
        answer.assign(1,-1);
    }
    return answer;
}
