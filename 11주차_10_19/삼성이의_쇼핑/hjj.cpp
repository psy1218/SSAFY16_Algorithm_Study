#include <iostream>

using namespace std;

int N;
int price[26];
int satisfy[26];
const int INF = 1'000'000;

struct Receipt {
    int cost = -1;
    unsigned int combination = 0b0;
};
Receipt memoization[26][5001];

Receipt shopping(int index, int s) {
    // 기저 조건
    if (s == 0) return { 0, 0 };
    if (index == 0) return { INF, 0 };

    // 이미 계산한 상태
    if (memoization[index][s].cost != -1) return memoization[index][s];

    // 현재 옷을 선택을 하지 않는 경우
    Receipt answer = shopping(index - 1, s);

    // 현재 옷을 선택한 경우
    if (s >= satisfy[index]) {
        Receipt buy = shopping(index - 1, s - satisfy[index]);

        // 나머지 만족도(s - satisfy[index])를 실제로 만들 수 있을 때, 계산 후 비교
        if (buy.cost != INF) {
            buy.cost += price[index];
            buy.combination |= (1u << (index - 1));

            if (buy.cost < answer.cost) {
                answer = buy;
            }
        }
    }

    // 최소 비용과 그 구매 조합을 함께 저장
    return memoization[index][s] = answer;
}

int main() {
    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; test_case++) {
        int N, M;
        cin >> N >> M;

        // 가능한 최대 만족도
        int max_satisfy = 0;

        // 입력 데이터 처리
        for (int i = 1; i <= M; i++) {
            cin >> price[i] >> satisfy[i];
            max_satisfy += satisfy[i];
        }

        // 초기화
        for (int i = 0; i <= M; i++) {
            for (int s = 0; s <= max_satisfy; s++) {
                memoization[i][s] = { -1, 0 };
            }
        }

        Receipt answer = { 0, 0 };
        int final_satisfy = 0;

        for (int s = max_satisfy; s >= 0; s--) {
            Receipt candidate = shopping(M, s);

            // 해당 만족도(s)를 만들 수 있고, 비용이 예산 조건을 만족하는 경우
            if (candidate.cost != INF && candidate.cost < N) {
                answer = candidate;
                final_satisfy = s;
                break;
            }
        }

        cout << "#" << test_case << " ";
        for (int i = 0; i < M; i++) {
            if ((answer.combination >> i) & 1u) {
                cout << i << " ";
            }
        }
        cout << final_satisfy << "\n";
    }

    return 0;
}