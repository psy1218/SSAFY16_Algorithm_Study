#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int>points(100000);
vector<pair<int,int>>lines(100000);

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> points[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> lines[i].first >> lines[i].second;
    }

    sort(points.begin(), points.end());

    for(int i=0;i<m;i++){
        int left = lower_bound(points.begin(), points.end(), lines[i].first) - points.begin(); // lower_bound의 return은 이터레이터라서 begin()을 빼야 인덱스 정보를 얻을 수 있다.
        int right = upper_bound(points.begin(), points.end(), lines[i].second) - points.begin();

        cout << right - left << "\n";
    }

    

    return 0;
}

/*

첫 번째로 떠올린 건, 한 선분에 점들이 존재할 수 있는지 하나씩 확인하는 건데 -> 이러면 시간 초과
점들을 정렬시키고 한 선분의 양 끝을 활용하여 개수 파악한다.
왼쪽보다 이상이고, 오른쪽보다 이하인 구간을 찾아서 빼면 존재하는 개수를 알 수 있다. 

*/
