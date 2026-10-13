#include <iostream>
#include <algorithm>
using namespace std;

int n;
int s[1000];
int b[1000];
int dp[1001][12][10];

int solve(){
    for(int i = 0; i<=n; i++){
        for(int j = 0; j<=11; j++){
            for(int k = 0; k<=9; k++){
                // 아무것도 선택 안하는 경우
                dp[i][j][k] = -1;
            }
        }
    }
    dp[0][0][0] = 0;
    for(int i = 0; i<=n; i++){
        for(int j = 0; j<=11; j++){
            for(int k = 0; k<=9; k++){
                if (dp[i][j][k] == -1) continue;
                // 아무것도 선택 안하는 경우
                dp[i+1][j][k] = max(dp[i][j][k], dp[i+1][j][k]);
                // 축구팀으로 선택하는 경우
                if(j<11){
                dp[i+1][j+1][k] = max(dp[i+1][j+1][k], dp[i][j][k]+s[i]);
                }
                // 야구팀으로 선택하는 경우
                if(k<9){
                dp[i+1][j][k+1] = max(dp[i+1][j][k+1], dp[i][j][k]+b[i]);
                }
            }
        }
    }

    return dp[n][11][9];
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> b[i];
    }

    // Please write your code here.
    cout << solve();
    return 0;
}
