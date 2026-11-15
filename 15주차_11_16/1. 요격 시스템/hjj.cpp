#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> targets) {
    // 끝점 기준 오름차순 정렬
    sort(
        targets.begin(),
        targets.end(),
        [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        }
    );

    int answer = 0;
    int end = 0;

    for (vector<int> target : targets) {
        int t_start = target[0];
        int t_end = target[1];

        if (s >= end) {
            answer++;
            t_end = e;
        }
    }

    return answer;
}


int main() {
    cout << solution({{4, 5}, {4, 8}, {10, 14}, {11, 13}, {5, 12}, {3, 7}, {1, 4}});
}