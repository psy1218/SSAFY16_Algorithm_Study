#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 진출 기준 오름차순 정렬
struct Comp {
    bool operator() (vector<int>& a, vector<int>& b) {
        return a[1] < b[1];
    }
};

int solution(vector<vector<int>> routes) {

    // 진출 기준 오름차순 정렬
    sort(routes.begin(), routes.end(), Comp());

    // 마지막으로 설치된 카메라 위치
    int camera = routes[0][1];
    int answer = 1;
    for (int i = 1; i < routes.size(); i++) {
        if (routes[i][0] > camera) {
            answer++;
            camera = routes[i][1];
        }
    }

    return answer;
}