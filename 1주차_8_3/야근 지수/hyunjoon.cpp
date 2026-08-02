#include <string>
#include <vector>
#include <queue>

using namespace std;

long long solution(int n, vector<int> works) {
    long long answer = 0;
    
    // 백트래킹..?
    
    // 그리디
    priority_queue<int> pq;
    
    for(int i = 0; i<works.size(); i++){
        pq.push(works[i]);
    }
    
    for(int i = 0; i<n; i++){
        int max = pq.top();
        if(max>0){
        pq.pop();
        max--;
        pq.push(max);
        }
    }
    
    
    while(!pq.empty()){
        answer += pq.top()*pq.top();
        pq.pop();
    }
    
    return answer;
}
