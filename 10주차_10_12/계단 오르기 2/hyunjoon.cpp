#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
const int NEG = -1e9;
int n;
int coin[1001];
int dp[1001][4];
void solve(){
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < 4; j++) {
            dp[i][j] = NEG;
        }
    }
    dp[1][2] = coin[1];
    dp[2][1] = coin[1] + coin[2];
    dp[2][3] = coin[2];
    for(int i = 3; i<=n; i++){
        dp[i][3] = dp[i-2][3] + coin[i];
        dp[i][2] = max(dp[i-1][3] + coin[i], dp[i-2][2] + coin[i]);
        dp[i][1] = max(dp[i-1][2] + coin[i], dp[i-2][1] + coin[i]);
        dp[i][0] = max(dp[i-1][1] + coin[i], dp[i-2][0] + coin[i]);
        // for(int j = 3; j>=0; j--){
        //     cout << dp[i][j] << ' ';
        // }
        // cout << '\n';
    }
    
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> coin[i];
    }
    int ans = 0;
    if(n<=3){
        for(int i = 1; i<=n; i++){
            ans += coin[i];
        }
        cout << ans;
        return 0;
    }
    // Please write your code here.
    solve();
    for(int i = 0; i<4; i++){
        ans = max(ans, dp[n][i]);
    }
    cout << ans;
    return 0;
}
