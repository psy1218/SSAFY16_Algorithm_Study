#include <string>
#include <vector>


using namespace std;

int num_cnt[50001];

long long solution(int n, vector<int> works) {    
    int max_num = 0;
    int work_size = works.size();
    
    // 각 작업 시간을 인덱스로 개수 카운팅
    for (int i = 0; i < work_size; i++) {
        num_cnt[works[i]]++;
        max_num = max(max_num, works[i]);
    }
    
    // 최대 -> 최소 작업 시간 순으로 업데이트
    long long answer = 0;
    for (int i = max_num; i >= 1; i--) {
        if (num_cnt[i] && n) { // 작업 시간 업데이트
            n--;
            num_cnt[i - 1]++;
            num_cnt[i++]--;
        }
        
        if (!n) { // 작업 종료 시 남은 작업의 피로도 계산
            answer += i * i * num_cnt[i];
        }
    }
    
    return answer;
}
