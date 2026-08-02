#include <string>
#include <queue>

using namespace std;

long long solution(int n, vector<int> works) {
    long long answer = 0;
    
    priority_queue<int>pq;   
    for(int i=0;i<works.size();i++) pq.push(works[i]);
    
    for(int i=0;i<n;i++){
        int Max = pq.top();
        pq.pop();
        if(Max - 1 > 0) pq.push(Max-1); // 작업량 양수만 처리 
        if(pq.empty()) return 0; // works의 길이는 1 이상이니까 처음부터 빈 배열은 없으니까 for문의 끝단에 있어도 됨. 
    }
    
    while(!pq.empty()){
        long cur = pq.top();
        answer += cur*cur;
        pq.pop();
    }
    
    return answer;
}
