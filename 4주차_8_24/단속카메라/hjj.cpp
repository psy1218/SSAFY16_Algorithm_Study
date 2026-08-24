#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> routes) {
    int answer = 0;
    int points[60001];

    int start_for_search = -1;
    int end_for_search = -1;

    int start = 0;
    int end = 0;
    for (vector<int> route : routes) {
        start = route[0] + 30000;
        end = route[1] + 30000;

        if (start_for_search == -1) {
            start_for_search = start;
        }
        else if (start_for_search > start) {
            start_for_search = start;
        }

        if (end_for_search == -1) {
            end_for_search = end;
        }
        else if (end_for_search < end) {
            end_for_search = end;
        }

        for (int i = start; i <= end; i++) {
            points[i]++;
        }
    }

    printf("%d %d\n", start_for_search, end_for_search);
    for (int j = start_for_search; j <= end_for_search; j++) {
        printf("%d ", points[j]);
    }

    return answer;
}