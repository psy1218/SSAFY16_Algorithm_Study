
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int n;
int arr[100];

int main() {
    cin >> n;

    int sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        sum += arr[i];
    }

    vector<int> dp(sum + 1, -1);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        int cur = arr[i];

        vector<int> next = dp;

        for (int d = 0; d <= sum; d++) {
            if (dp[d] == -1) continue;

            // A, B 중 합이 큰 그룹에 추가
            if (d + cur <= sum) {
                next[d + cur] =
                    max(next[d + cur], dp[d] + cur);
            }
            // A, B 중 합이 작은 그룹에 추가
            if (cur <= d){ // 큰 그룹과 작은 그룹이 관계역전되지 않음
                int nd = d - cur; // 차이가 줄어듦
                next[nd] =
                    max(next[nd], dp[d]);
            }
            else{ // 작은 그룹이 큰 그룹이 됨
                int nd = cur - d;
                next[nd] =
                    max(next[nd], dp[d] + nd);
            }
        }

        dp = move(next);
    }

    cout << dp[0];

    return 0;
}
