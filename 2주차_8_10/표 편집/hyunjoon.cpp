#include <string>
#include <iostream>
#include <stack>
#include <tuple>
#include <vector>
using namespace std;

string solution(int n, int k, vector<string> cmd) {
    string answer(n,'O');
    
    // 삭제/복구를 위한 stack
    stack<tuple<int,int,int>> s_delete_idx;
    
    // 유사 linked list
    vector<int> prev(n,0), next(n,0);
    
    // 생성
    for(int i = 0; i<n; i++){
        prev[i] = i-1;
        next[i] = i+1;
    }
    next[n-1] = -1;
    int cur = k;
    for(int i = 0; i<cmd.size(); i++){
        if(cmd[i][0]=='U'){
            int x = stoi(cmd[i].substr(2));
            while(x--){
                cur = prev[cur];
            }
        }
        if(cmd[i][0]=='D'){
            int x = stoi(cmd[i].substr(2));
            while(x--){
                cur = next[cur];
            }
        }
        if(cmd[i][0] == 'C'){
            // 삭제
            s_delete_idx.push({cur,prev[cur],next[cur]});
            answer[cur] = 'X';
            
            // 끝일 때 체크
       if (prev[cur] != -1)
            next[prev[cur]] = next[cur];

        if (next[cur] != -1)
          prev[next[cur]] = prev[cur];
            
            // 맨 마지막 칸인지 확인
            if(next[cur] != -1 ) cur = next[cur];
            else cur = prev[cur];
        }
        if(cmd[i][0] == 'Z'){
            auto [idx, p, n] = s_delete_idx.top();
            s_delete_idx.pop();
            if (p != -1)
                next[p] = idx;

            if (n != -1)
                prev[n] = idx;
            
            answer[idx] = 'O';
        }
        
    }
    
    
    return answer;
}
