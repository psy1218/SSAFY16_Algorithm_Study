#include <iostream>

using namespace std;

int n;
int s[1000];
int b[1000];

int max(int a, int b){
    if (a > b){
        return a;
    }
    return b;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> b[i];
    }

    // Please write your code here.
    int dp[1001][12][10] = {0};
    dp[0][0][0] = 0;

    dp[1][0][0] = 0;
    dp[1][1][0] += s[0];
    dp[1][0][1] += b[0];


    for (int i = 2; i <= n; i++){
        for (int soccer = 0; soccer <= 11; soccer++){
            for (int baseball = 0; baseball <= 9; baseball++){
                
                // 선택하지 않는 경우
                dp[i][soccer][baseball] = dp[i-1][soccer][baseball];

                // 축구 선택
                if (soccer > 0){
                    dp[i][soccer][baseball] = max(dp[i][soccer][baseball], dp[i-1][soccer-1][baseball] + s[i-1]);
                }

                // 야구 선택
                if (baseball > 0){
                    dp[i][soccer][baseball] = max(dp[i][soccer][baseball], dp[i-1][soccer][baseball-1] + b[i-1]);
                }
            }
        }
        
    }

    cout << dp[n][11][9];

    return 0;
}
