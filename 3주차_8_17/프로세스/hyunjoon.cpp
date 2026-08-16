#include <string>
#include <vector>
#include <queue>

using namespace std;

// 실행 대기 큐 안에 더 높은 우선순위가 있는지 확인
bool prior_check(queue<pair<int,int>> task_q, int target_prior){
    while(!task_q.empty()){
        pair <int,int> cur = task_q.front();
        task_q.pop();
// 현재 큐에서 꺼낸 프로세스보다 더 큰 우선순위 있으면 true return 후 종료
        if(cur.second > target_prior){
          return true;        
        }
    }
    return false; 
}



int solution(vector<int> priorities, int location) {
    int answer = 0;
    
    queue <pair<int,int>> task_q;    
    // task queue에 first = idx번호, second = 우선순위 넣기
    for(int i = 0; i<priorities.size(); i++){
        task_q.push(make_pair(i,priorities[i]));
    }
    
    while(!task_q.empty()){
        // 대기중인 프로세스 하나 꺼냄
        pair<int,int> cur = task_q.front();
        task_q.pop();
        // 우선순위 높은 프로세스 있는지 판단
        // 존재하면 다시 큐에 push
        if(prior_check(task_q, cur.second)){
            task_q.push(cur);
        }
        // if문에 안걸리면 excute 된것이므로 push 안해주고 count 올림
        else{
            answer++;
            if(cur.first == location) break;
        }
    }
    
    return answer;
}
