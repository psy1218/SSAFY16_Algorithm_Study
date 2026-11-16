#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> targets) {
    sort(targets.begin(), targets.end(), [](vector<int> a, vector<int> b){
        return a[1] < b[1];
    });
        
    int answer = 1;
    int coord = targets[0][1];
    
    for (int idx = 1; idx < targets.size(); idx++){
        if (targets[idx][0] < coord){
            continue;
        }
        
        answer++;
        coord = targets[idx][1];
    }
    
    return answer;
}
