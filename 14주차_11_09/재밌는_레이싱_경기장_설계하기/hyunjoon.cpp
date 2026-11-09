#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>
using namespace std;

int solution(vector<int> heights) {
    int N = heights.size();
    int half = N / 2;

    sort(heights.begin(), heights.end());

    if (N % 2 == 1) {
        int smallest = INT_MAX;
        int secondSmallest = INT_MAX;

        for (int i = 0; i <= half; i++) {
            int diff = heights[i + half] - heights[i];

            if (diff < smallest) {
                secondSmallest = smallest;
                smallest = diff;
            } else if (diff < secondSmallest) {
                secondSmallest = diff;
            }
        }

        return secondSmallest;
    }

    vector<int> heights_cp(N);
    for (int i = 0; i < half; i++) {
        heights_cp[2 * i] = heights[half + i];
        heights_cp[2 * i + 1] = heights[i];
    }

    int answer = INT_MAX;
    for (int i = 1; i < N; i++) {
        answer = min(answer, abs(heights_cp[i] - heights_cp[i - 1]));
    }

    return answer;
}
