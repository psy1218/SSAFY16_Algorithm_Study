#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n;
int main() {
    cin >> n;

    // Please write your code here.
    vector<vector<vector<long long>>> dp(n+1, vector<vector<long long>>(3, vector<long long>(3, 0)));
    // 1번째 날에 G를 받았을 경우
    dp[1][0][0] = 1;
    // 1번째 날에 B를 받았을 경우
    dp[1][1][0] = 1;
    // 1번째 날에 T를 받았을 경우
    dp[1][0][1] = 1;
    if (n == 1){
        cout << 3;
        return 0;
    }
    long long mod = pow(10, 9) + 7;
    for (int i = 2; i <= n; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                if (dp[i-1][j][k] != 0){
                    // i번째 날에 G를 받았을 경우
                    dp[i][0][k] += dp[i-1][j][k]; // 기존 경우의수를 누적. 연속된 B카운트는 0으로 초기화
                    dp[i][0][k] %= mod;
                    // i번째 날에 B를 받았을 경우
                    if (j + 1 <= 2){ // 현재 누적된 B갯수까지 포함하여 3보다 작아야 함
                        dp[i][j+1][k] += dp[i-1][j][k]; // 기존 경우의수를 누적
                        dp[i][j+1][k] %= mod;
                    }
                    // i번째 날에 T를 받았을 경우
                    if (k + 1 <= 2){ // 현재 누적된 T갯수까지 포함하여 3보다 작아야 함
                        // B 누적횟수 초기화 주의
                        dp[i][0][k+1] += dp[i-1][j][k]; // 기존 경우의수를 누적
                        dp[i][0][k+1] %= mod;
                    }
                    // if (k + 1 <= 2){ // 현재 누적된 T갯수까지 포함하여 3보다 작아야 함
                    //     dp[i][j][k+1] += dp[i-1][j][k]; // 기존 경우의수를 누적
                    // }
                }
            }
        }
    }
    long long sum = 0;
    for (int j = 0; j < 3; j++){
        for (int k = 0; k < 3; k++){
            if (dp[n][j][k] != 0){
                sum += dp[n][j][k];
            }
        }
    }
    
    cout << sum % mod;
    return 0;
}
