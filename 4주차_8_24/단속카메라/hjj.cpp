#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 사용자 정의 정렬 기준
// 두 벡터 a, b에 대해서 a[1]과 b[1] 에 대해 a[1] < b[1]이 되도록 정렬
bool sortBy(vector<int> a, vector<int> b) {
    return a[1] < b[1];
}

int solution(vector<vector<int>> routes) {
    int answer = 0;

    // routes를 도착점의 오름차순으로 정렬
    sort(routes.begin(), routes.end(), sortBy);

    // 정렬 확인용
    //for (vector<int> route : routes) {
    //    cout << route[0] << "\t" << route[1] << "\n";
    //}

    // 정렬된 routes 기준 처음 차량의 도착점에 카메라 설치
    int last_camera = routes[0][1];
    // 하나를 설치했으므로 +1
    answer++;

    // 처음 차량의 도착점에 카메라를 설치했으므로, 처음 차량을 확인하지 않음
    // 이를 뜻하는 것이 idx를 1부터 시작
    for (int idx = 1; idx < routes.size(); idx++) {
        // 만약 현재 차량의 시작점이 현재 카메라 위치보다 더 뒤인 경우 (즉 좌표 기준 더 큰 경우)
        // 카메라를 현재 차량의 도착점에 새로 설치하고, 위치 갱신
        // 새로 설치한 것이므로 +1
        if (last_camera < routes[idx][0]) {
            last_camera = routes[idx][1];
            answer++;
        }
        // 그렇지 않은 경우(즉 카메라를 만날 수 있는 경우) 카메라 위치 갱신 및 카메라 설치 대수 증가 없이 스킵
        else {
            continue;
        }
    }

    return answer;
}