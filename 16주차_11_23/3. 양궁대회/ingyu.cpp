#include <string>
#include <vector>

using namespace std;
vector<int> arr(11, 0);
int n2;
int total_score;
vector<int> total_arr(1, -1);
vector<int> apeach_info;
void dfs(int sum_score, int cur_score, int used, vector<int> win_info){
    // 누적 점수, 현재 탐색하는 과녁 점수, 사용한 화살 갯수, 그때의 과녁에 쏜 화살배열
    if (used > n2){ // 화살을 상한선보다 많이 쐈으므로 불가
        return;
    }
    if (cur_score == -1){ // 마지막이므로 return
        int lion_score = sum_score;
        int apeach_score = 0;
        // 어피치 점수 계산
        for (int k = 0; k <= 10; k++)
            if (win_info[k] == 0 && apeach_info[k] > 0) {
                apeach_score += 10 - k;
            }
        if (lion_score > apeach_score) {
            win_info[10] += n2 - used; // 남은 화살을 0점에 몰아넣고
            int diff = lion_score - apeach_score;
            if (diff > total_score) { 
                total_score = diff; 
                total_arr = win_info; 
            }
            else if (diff == total_score) {
                for (int k = 10; k >= 0; k--) {
                    if (win_info[k] != total_arr[k]) {
                        if (win_info[k] > total_arr[k]) {
                            total_arr = win_info;
                        }
                        break;
                    }
                }
            }
        }
        return;
    }
    int idx = 10 - cur_score;            // arr, win_info는 index 0이 10점
    vector<int> new_info = win_info;
    new_info[idx] = arr[idx];
    dfs(sum_score, cur_score-1, used, win_info);                         // 이 점수 포기
    dfs(sum_score+cur_score, cur_score-1, used+arr[idx], new_info);      // 이 점수 획득
}
vector<int> solution(int n, vector<int> info) {
    n2 = n;
    vector<int> answer;
    apeach_info = info;
    for (int i = 0; i <= 10; i++){
        arr[10-i] = info[10-i] + 1; // 어피치보다 딱 한개 더 많이 맞춰야함
    }
    vector<int> win_info(11, 0);
    dfs(0, 10, 0, win_info);
    return total_arr;
}
