#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<vector<int>> targets) {
    int answer = 0;
    sort(targets.begin(), targets.end(), [](const vector<int>& a, const vector<int>& b) {
        if (a[1] == b[1]) {
            return a[0] < b[0]; // 두 번째 원소가 같다면 첫 번째 원소 기준 오름차순
        }
        return a[1] < b[1];     // 두 번째 원소 기준 오름차순
    });
    int prev = targets[0][1]; // 첫번째 미사일을 요격했다고 가정
    int idx = 1;
    int cnt = 1; // 필요한 요격 미사일 수
    int max_cnt = targets.size();
    while (idx < max_cnt){
        while (idx < max_cnt && targets[idx][0] < prev){
            idx++;
        }
        // 모든 미사일을 확인했다면 종료
        if (idx >= max_cnt) break;
        cnt++;
        prev = targets[idx][1]; // 다음 미사일의 끝구간으로 갱신
    }
    answer = cnt;
    return answer;
    
}
