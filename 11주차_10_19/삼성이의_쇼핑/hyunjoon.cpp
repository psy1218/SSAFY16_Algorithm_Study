
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_M 25
#define MAX_S 5000
#define INF 1000000000

struct cloth_t {
    int p, s;
};

int N, M;
int dp[MAX_M + 1][MAX_S + 1];

vector<cloth_t> cloth;

void solve(int tc) {
    // DP 초기화
    for (int i = 0; i <= M; i++) {
        for (int s = 0; s <= MAX_S; s++) {
            dp[i][s] = INF;
        }
    }

    dp[0][0] = 0;

    // DP 계산
    for (int i = 1; i <= M; i++) {
        int price = cloth[i - 1].p;
        int score = cloth[i - 1].s;

        for (int s = 0; s <= MAX_S; s++) {

            // 현재 옷을 선택하지 않는 경우
            dp[i][s] = dp[i - 1][s];

            // 현재 옷을 선택하는 경우
            if (s >= score && 
                dp[i - 1][s - score] != INF) {

                dp[i][s] = min(
                    dp[i][s],
                    dp[i - 1][s - score] + price
                );
            }
        }
    }

    // 예산 내 최대 만족도 탐색
    int ans = 0;

    for (int s = 0; s <= MAX_S; s++) {
        if (dp[M][s] < N) {
            ans = s;
        }
    }

    // 선택한 옷 역추적
    vector<int> selected;
    int s = ans;

    for (int i = M; i >= 1; i--) {

        // 현재 옷을 선택하지 않은 경우
        if (dp[i][s] == dp[i - 1][s]) {
            continue;
        }

        // 현재 옷을 선택한 경우
        selected.push_back(i - 1);

        s -= cloth[i - 1].s;
    }

    // 오름차순으로 정렬
    reverse(selected.begin(), selected.end());

    // 출력
    cout << "#" << tc;

    for (int idx : selected) {
        cout << " " << idx;
    }

    cout << " " << ans << '\n';
}

int main() {

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        cin >> N >> M;

        cloth.clear();

        for (int i = 0; i < M; i++) {
            int p, s;
            cin >> p >> s;
            cloth.push_back({p, s});
        }

        solve(tc);
    }

    return 0;
}
