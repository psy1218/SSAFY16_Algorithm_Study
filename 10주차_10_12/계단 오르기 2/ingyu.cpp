#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n;
int coin[1001];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> coin[i]; // i층에 있는 코인의 수
    }
    vector<vector<int>> dp(n+1, vector<int>(4, -1)); // dp[i][j] = i층에 도착했을때, 1칸 이동을 j번 했을때 최대 동전 갯수
    // Please write your code here.
    dp[0][0] = 0; // 0층이 있다고 가정 (이 값이 있어야 1,2층에 진입가능). 그리고 이때는 무조건 chance를 0번 사용함
    for (int i = 1; i <= n; i++){ // i층에 도달했을때 가능한 최대 동전 갯수
        // 2층 올라가기
        if (i - 2 >= 0){
            for (int j = 0; j <= 3; j++){
                if (dp[i - 2][j] != -1){ // i - 2층에 도달 가능 + j번 chance를 쓰는게 가능한 경우
                    dp[i][j] = max(dp[i][j], dp[i - 2][j] + coin[i]); // i번째 층에 있는 코인까지 쓸어담아야 함
                }
            }
            
        }
        // 1층 올라가기
        if (i - 1 >= 0){
            for (int j = 1; j <= 3; j++){ // i층 까지 도달했을때 chance를 1~3번 사용했을 경우. i-1층 까지 도달했을때는 chance를 0~2번 사용했어야 함. 
                if (dp[i - 1][j - 1] != -1){ // i - 2층에 도달 가능 + j번 chance를 쓰는게 가능한 경우
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + coin[i]); // i번째 층에 있는 코인까지 쓸어담아야 함
                }
            }
            
        }
    }
    int max_value = 0;
    for (int i = 0; i <= 3; i++){
        max_value = max(max_value, dp[n][i]);
    }
    cout << max_value;
    return 0;
}
