#include <iostream>
#include <algorithm>

using namespace std;

int n;
int s[1000];
int b[1000];

long long dp[12][10];

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> s[i] >> b[i];
    }

    // dp[f][k]: 축구팀 f명, 야구팀 k명의 최대 능력 합
    for (int f = 0; f <= 11; f++) {
        for (int k = 0; k <= 9; k++) {
            dp[f][k] = -1;
        }
    }
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int f = 11; f >= 0; f--) {
            for (int k = 9; k >= 0; k--) {
                // 현재 학생을 축구팀에 선발
                if (f > 0 && dp[f - 1][k] != -1) {
                    dp[f][k] = max(
                        dp[f][k],
                        dp[f - 1][k] + s[i]
                    );
                }

                // 현재 학생을 야구팀에 선발
                if (k > 0 && dp[f][k - 1] != -1) {
                    dp[f][k] = max(
                        dp[f][k],
                        dp[f][k - 1] + b[i]
                    );
                }

                // 선발하지 않는 경우는 기존 값 유지
            }
        }
    }

    cout << dp[11][9] << '\n';

    return 0;
}