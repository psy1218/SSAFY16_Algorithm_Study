#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool compare(vector<int> a, vector<int> b){
    if(a[1]<b[1]) return 1;
    else return 0;
}


int solution(vector<vector<int>> routes) {
    int answer = 0;
    
    sort(routes.begin(), routes.end(), compare);
    int camera_loc = routes[0][1];
    answer++;
    for(int i = 1; i<routes.size(); i++){
        if(routes[i][0]<=camera_loc && camera_loc<=routes[i][1]){
            continue;
        }
        else {
            camera_loc = routes[i][1];
            answer++;
        }
    }
    return answer;
}
