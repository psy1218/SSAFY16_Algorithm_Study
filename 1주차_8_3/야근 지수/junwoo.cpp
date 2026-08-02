#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

long long solution(int n, vector<int> works) {
    long long answer = 0;
    priority_queue<int> pq(works.begin(), works.end());
    
    while (n > 0){
        int max_work = pq.top();
        pq.pop();
        pq.push(max(0, max_work-1));
        n--;
    }
    
    while (!pq.empty()){
        int cur_work = pq.top();
        pq.pop();
        answer += cur_work * cur_work;
    }
    
    
    return answer;
}
