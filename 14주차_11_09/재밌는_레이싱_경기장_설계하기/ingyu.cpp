#include <bits/stdc++.h>
using namespace std;

int solution(vector<int> heights) {
    int n = heights.size();
    sort(heights.begin(), heights.end());
    int m = n / 2;

    vector<long long> gaps;
    for (int i = 0; i + m < n; i++)
        gaps.push_back((long long)heights[i + m] - heights[i]);

    sort(gaps.begin(), gaps.end());

    if (n % 2 == 0) return (int)gaps[0];   // 짝수: 최솟값
    return (int)gaps[1];                   // 홀수: 두 번째로 작은 값 (gap 개수 = m+1 ≥ 2)
}
