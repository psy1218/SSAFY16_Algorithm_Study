#include <iostream>
#include <vector>
using namespace std;

int n;
int s[1000];
int b[1000];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> b[i];
    }

    // Please write your code here.
    vector<vector<int>> dp(12, vector<int>(10, -1)); // 불가능한 경우는 -1
    // 초기값 초기화
    dp[1][0] = s[0];
    dp[0][1] = b[0];
    dp[0][0] = 0;
    for (int i = 1; i < n; i++){
        int cur_soccer = s[i];
        int cur_baseball = b[i];
        for (int j = 11; j >= 0; j--){
            for (int k = 9; k >= 0; k--){
                if (dp[j][k] != -1){
                    // 축구 인원은 최대 11이므로
                    if (j + 1 <= 11){
                        dp[j+1][k] = max(dp[j+1][k], dp[j][k] + cur_soccer);
                    }
                    // 야구 인원은 최대 9이므로
                    if (k + 1 <= 9){
                        dp[j][k+1] = max(dp[j][k+1], dp[j][k] + cur_baseball);
                    }
                }
            }
        }
    }
    cout << dp[11][9];
    return 0;
}
