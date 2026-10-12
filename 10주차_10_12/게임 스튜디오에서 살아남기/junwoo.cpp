#include <iostream>

using namespace std;

int n;
const long long MOD = 1000000007LL;

int power(int num, int up){
    int answer = 1;
    for (int i = 0; i < up; i++){
        answer *= num;
    }

    return answer;
}

int main() {
    cin >> n;

    // Please write your code here.
    // 전체, 선택한 평가값, T의 수
    long long dp[1001][3][3] = {0};

    // 0: G, 1: B, 2: T
    dp[1][0][0] = 1;
    dp[1][1][0] = 1;
    dp[1][2][1] = 1;

    for (int i = 2; i <= n; i++){
        // 선택한 알바벳
        for (int rate = 0; rate < 3; rate++){
            for (int k = 0; k < 3; k++){
                // G일 때
                if (rate == 0){
                    // k 값은 변화 X
                    dp[i][rate][k] = dp[i-1][0][k] + dp[i-1][1][k] + dp[i-1][2][k];
                }
                // B일 때
                if (rate == 1){
                    // k값은 변화 X
                    dp[i][rate][k] = dp[i-1][0][k] + dp[i-1][1][k] + dp[i-1][2][k];
                    
                    if (i == 3 && k == 0){
                        dp[i][rate][k] -= 1; // BBB 제거
                    }

                    if (i >= 4){
                        dp[i][rate][k] -= dp[i-3][0][k] + dp[i-3][2][k];    // GBB, TBB 제거
                    }
                }
                if (rate == 2){
                    // k값 1 추가
                    if (k == 0){
                        continue;
                    }
                    dp[i][rate][k] = dp[i-1][0][k-1] + dp[i-1][1][k-1] + dp[i-1][2][k-1];
                }

                dp[i][rate][k] = (dp[i][rate][k] + MOD) % MOD;
            }
        }
    }
    
    long long answer = 0;
    for (int rate = 0; rate < 3; rate++){
        for (int k = 0; k < 3; k++){
            answer += dp[n][rate][k];
            answer %= MOD;
        }
    }

    cout << answer;

    return 0;
}
