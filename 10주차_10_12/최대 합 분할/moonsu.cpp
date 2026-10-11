#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

int n;
int arr[100];

int main() {
    cin >> n;

    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        sum += abs(arr[i]);
    }

    // Please write your code here.

        // 음수인 차이도 배열 인덱스로 표현하기 위한 보정값
    int offset = sum;
    const long long NEG = numeric_limits<long long>::lowest();

    // dp[d + offset]: 합의 차이가 d일 때 A의 최대 합
    vector<long long> dp(2 * sum + 1, NEG);
    dp[offset] = 0;

    int range = 0;

    for (int i = 0; i < n; i++) {
        int x = arr[i];

        // 현재 수를 C에 넣으면 기존 상태가 유지됨
        vector<long long> next_dp = dp;

        for (int d = -range; d <= range; d++) {
            long long current = dp[d + offset];

            if (current == NEG) {
                continue;
            }

            // A에 넣기: 차이와 A의 합이 모두 x만큼 증가
            next_dp[d + x + offset] = max(
                next_dp[d + x + offset],
                current + x
            );

            // B에 넣기: 차이는 x만큼 감소하고 A의 합은 유지
            next_dp[d - x + offset] = max(
                next_dp[d - x + offset],
                current
            );
        }

        dp.swap(next_dp);
        range += abs(x);
    }

    // 차이가 0이면 A와 B의 합이 같음
    cout << dp[offset] << '\n';

    return 0;
}
