#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int solution(vector<int> heights) {
    sort(heights.begin(), heights.end());

    int n = heights.size();
    int m = n / 2;

    vector<int> diff;

    // 작은 그룹과 큰 그룹의 대응 원소 차이
    for (int i = 0; i < m; i++) {
        diff.push_back(heights[i + m] - heights[i]);
    }

    // 홀수라면 남는 가장 큰 원소를 고려
    if (n % 2 == 1) {
        diff.push_back(heights[n - 1] - heights[m]);
    }

    sort(diff.begin(), diff.end());

    if (n % 2 == 0) {
        return diff[0];
    }

    return diff[1];
}