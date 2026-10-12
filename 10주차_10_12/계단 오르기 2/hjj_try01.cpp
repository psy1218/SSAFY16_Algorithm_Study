#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int coin[1001];
vector<vector<int>> memoization(1001, vector<int>(4, 0));

int climb(int index, int one_step_remains) {
    int answer;

    if (index == 1 && one_step_remains >= 1) {
        answer = coin[1];
        if (!memoization[1][one_step_remains]) memoization[1][one_step_remains] = answer;
        return memoization[1][one_step_remains];
    }
    else if (index == 1) return -INT_MAX;
    else if (index == 2) {
        if (one_step_remains >= 2) answer = coin[1] + coin[2];
        else answer = coin[2];

        if (!memoization[2][one_step_remains]) memoization[2][one_step_remains] = answer;
        return memoization[2][one_step_remains];
    }

    if (!memoization[index - 2][one_step_remains]) memoization[index - 2][one_step_remains] = climb(index - 2, one_step_remains) + coin[index];
    if (one_step_remains >= 1) {
        if (!memoization[index - 1][one_step_remains - 1]) memoization[index - 1][one_step_remains - 1] = climb(index - 1, one_step_remains - 1) + coin[index];
    }

    if (one_step_remains >= 1) return max(memoization[index - 2][one_step_remains], memoization[index - 1][one_step_remains - 1]);
    else return memoization[index - 2][one_step_remains];
}

// f(n) = {f(n - 1) + coin[n], f(n - 2) + coin[n]}   one_step_remains >= 1
//      = {f(n - 2) + coin[n]}                       one_step_remains = 0   

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> coin[i];
    }

    cout << climb(n, 3);

    return 0;
}
