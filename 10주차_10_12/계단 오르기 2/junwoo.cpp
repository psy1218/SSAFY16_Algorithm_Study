#include <iostream>

using namespace std;

int n;
int coin[1001];

int max(int a, int b){
    if (a > b){
        return a;
    }
    return b;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> coin[i];
    }

    // Please write your code here.
    int dp[1001][4] = {0};

    dp[1][1] = coin[1];
    dp[2][0] = coin[2];
    dp[2][2] = dp[1][1] + coin[2];

    int answer = 0;
    if (n == 2 || n == 3){
        for (int i = 0; i <= n; i++){
            answer += coin[i];
        }

        cout << answer;
        return 0;
    }

    for (int i = 3; i <= n; i++){        
        for (int k = 0; k < 4; k++){
            // 2층 올라왔을 때
            dp[i][k] = max(dp[i][k], dp[i-2][k] + coin[i]);

            // 1층 올라왔을 때
            if (k >= 1){
                dp[i][k] = max(dp[i][k], dp[i-1][k-1] + coin[i]);
            }
            

        }
    }

    int max_coin = -1;
    for (int k = 0; k < 4; k++){
        if (max_coin < dp[n][k]){
            max_coin = dp[n][k];
        }
    }

    if (n % 2 == 0){
        cout << dp[n][2];
    }
    else{
        cout << dp[n][3];
    }

    return 0;
}
