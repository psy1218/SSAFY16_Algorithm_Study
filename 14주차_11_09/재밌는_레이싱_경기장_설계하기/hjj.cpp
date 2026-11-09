#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int solution(vector<int> heights) {
    // 우선 정렬
    sort(heights.begin(), heights.end());

    int n = heights.size();
    int mid = n / 2;

    // 차이 저장
    vector<int> diffs;

    // 작은 그룹과 큰 그룹의 대응 원소 차이
    // {0, 1, 2, 3, 4, 5} -> [3] - [0], [4] - [1], [5] - [2]
    for (int i = 0; i < mid; i++) {
        diffs.push_back(heights[i + mid] - heights[i]);
    }

    // 홀수라면 남는 가장 큰 원소를 고려
    // [2] - [0], [3] - [1] 은 추가되어있음
    // [4] - [2] 추가해야 함
    if (n % 2 == 1) {
        diffs.push_back(heights[n - 1] - heights[mid]);
    }

    // 차이들을 정렬
    sort(diffs.begin(), diffs.end());

    if (n % 2 == 0) return diffs[0];
    else return diffs[1];
}


int main() {
    // test case 1: 4
    cout << solution({ 1, 8, 5 }) << "\n";
    // test case 2: 5
    cout << solution({ 11, 6, 4, 11 }) << "\n";
    // test case 3: 0
    cout << solution({ 9, 9, 9, 9, 30 }) << "\n";
    // test case 4: 5
    cout << solution({ 1, 2, 4, 7, 11 }) << "\n";
    // test case 5: 6
    cout << solution({ 1, 2, 4, 7, 11, 16 }) << "\n";
}