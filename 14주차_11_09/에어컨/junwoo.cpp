#include <string>
#include <vector>
#include <climits>

using namespace std;

// dp[i][t] = i 분에 실내온도가 t일 때 최소 누적 소비전력
// Ex)  dp[3][25] = 30 이라면,
//      3분에 25도가 되도록 조절했을 때 0분부터 3분까지 소비한 최소 전력 30
//      온도 범위 -10 ~ 40이므로 +10 해서 index 조절

int solution(int temperature, int t1, int t2, int a, int b, vector<int> onboard) {
    int T = onboard.size();
    
    // DP 배열 생성 및 초기화
    vector<vector<int>> dp(T, vector<int>(51, INT_MAX));
    
    // 초기 실내온도 = 실외온도
    dp[0][temperature + 10] = 0;
    
    // DP 전이 구현
    //  Case 1. 에어컨 켜서 온도를 1도 변화시키는 경우
    //  Case 2. 에어컨을 켜서 현재 온도를 유지하는 경우
    //  Case 3. 에어컨을 끄는 경우
    
    for (int time = 1; time < T; time++){
        // 이전 시각의 모든 실내온도 확인
        for (int t = 0; t <= 50; t++){
            if (dp[time - 1][t] == INT_MAX){
                // 도달하지 못하는 상태
                continue;
            }
            
            // Case 1. 에어컨 ON - 온도 1도 하강
            if (t > 0){
                dp[time][t-1] = min(dp[time][t-1], dp[time - 1][t] + a);
            }
            
            // Case 2. 에어컨 ON - 온도 1도 상승
            if (t < 50){
                dp[time][t+1] = min(dp[time][t+1], dp[time-1][t] + a);
            }
            
            // Case 3. 에어컨 ON - 현재 온도 유지
            dp[time][t] = min(dp[time][t], dp[time-1][t] + b);
            
            // Case 4. 에어컨 OFF - 실외 온도 방향으로 이동
            int currentTemp = t - 10;
            int nextTemp = currentTemp;
            
            if (currentTemp < temperature){
                nextTemp++;
            }
            else if (currentTemp > temperature){
                nextTemp--;
            }
            
            // 에어컨 OFF 이므로 추가 소비 전력 0
            dp[time][nextTemp + 10] = min(dp[time][nextTemp + 10], dp[time-1][t]);
            
        }
        
        // 승객 탑승 시 쾌적온도 범위 유지
        if (onboard[time] == 1){
            for (int t = 0; t <= 50; t++){
                int currentTemp = t - 10;
                
                if (currentTemp < t1 || currentTemp > t2){
                    dp[time][t] = INT_MAX;
                }
            }
        }
    }
    
    int answer = INT_MAX;
    
    for (int t = 0; t <= 50; t++){
        answer = min(answer, dp[T - 1][t]);
    }
    
    
    return answer;
}
