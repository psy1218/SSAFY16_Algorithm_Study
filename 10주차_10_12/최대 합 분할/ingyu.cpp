
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

            // 합이 작은 그룹에 추가
            int nd = abs(d - cur);

            next[nd] =
                max(next[nd], dp[d] + max(0, cur - d));
        }

        dp = move(next);
    }

    cout << dp[0];

    return 0;
}
