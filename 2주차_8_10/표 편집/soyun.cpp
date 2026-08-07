#include <string>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

string solution(int n, int k, vector<string> cmd) {
    
    string answer = "";
    
    vector<int> visited(n);

    // 각 행의 바로 위, 바로 아래에 있는 행 번호
    vector<int> up(n);
    vector<int> down(n);

    for (int i = 0; i < n; i++) {
        up[i] = i - 1;
        down[i] = i + 1;
    }

    // 마지막 행 아래에는 행이 없음
    down[n - 1] = -1;
    
    int cur = k;
    stack<int> del;

    for (int i = 0; i < cmd.size(); i++) {

        if (cmd[i] == "C") {
            
            del.push(cur);
            visited[cur] = 1;

            int upper = up[cur];
            int lower = down[cur];

            // 위쪽 행이 있다면 아래쪽 연결 수정
            if (upper != -1) {
                down[upper] = lower;
            }

            // 아래쪽 행이 있다면 위쪽 연결 수정 후 커서 이동
            if (lower != -1) {
                up[lower] = upper;
                cur = lower;
            }
            // 삭제한 행이 마지막 행이면 위쪽 행으로 이동
            else {
                cur = upper;
            }
        }
        
        else if (cmd[i] == "Z") {

            if (del.empty()) continue;
            
            int back = del.top();
            del.pop();

            visited[back] = 0;

            int upper = up[back];
            int lower = down[back];

            // 복구된 행을 다시 위쪽 행과 연결
            if (upper != -1) {
                down[upper] = back;
            }

            // 복구된 행을 다시 아래쪽 행과 연결
            if (lower != -1) {
                up[lower] = back;
            }
        }
        
        else {
            int cnt = 0;
            int move = stoi(cmd[i].substr(2));

            if (cmd[i][0] == 'U') {
                while (1) {
                    cur = up[cur];
                    cnt++;

                    if (cnt == move) break;
                }
            }

            else if (cmd[i][0] == 'D') {
                while (1) {
                    cur = down[cur];
                    cnt++;

                    if (cnt == move) break;
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) answer += "O";
        else answer += "X";
    }
    
    return answer;
}

/*
#include <string>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

string solution(int n, int k, vector<string> cmd) {
    
    string answer = "";
    
    vector<int>visited(n);

    
    int cur = k;
    stack<int>del;
    for(int i=0;i<cmd.size();i++){
        if(cmd[i] == "C"){
        
            
            int last = n-1;
            for(int j=n-1;j>=0;j--){
                if(visited[j] == 0) {
                    last = j;
                    break;
                }
            }
            
            // 마지막 행을 찾고 삭제해야함. 삭제하고 마지막 행 찾으면 틀림. 
            del.push(cur);
            visited[cur] = 1; 
            
            if(cur == last){
                while(1){
                    if(cur < 0) break;
                    if(visited[cur] == 0) break;
                    cur--;
                }
            }
            else{
                while(1){
                    if(cur < 0 || cur >= n) break;
                    if(visited[cur] == 0) break;
                    cur++;
                }
            }
            
        }
        
        else if(cmd[i] == "Z"){
            if(del.empty()) continue;
            
            int back = del.top();
            del.pop();
            visited[back] = 0;
        }
        
        else{
            int cnt = 0;
            if(cmd[i][0] == 'U'){
                while(1){
                    cur--;
                    if(visited[cur] == 0) cnt++;
                    if(cnt == stoi(cmd[i].substr(2))) break;  
                }
            }
            else if(cmd[i][0] == 'D'){
                while(1){
                    cur++;
                    if(visited[cur] == 0) cnt++;
                    if(cnt == stoi(cmd[i].substr(2))) break;  
                }
            }
        }
        
    }
    
    for(int i=0;i<n;i++){
        if(visited[i] == 0) answer += "O";
        else answer += "X";
    }
    
    return answer;
}


/*

8	2	["D 2","C","U 3","C","D 4","C","U 2","Z","Z"]

0 - o
1 - o d
2 - o
3 - o
4 - o d
5 - o
6 - o
7 - o 

4, 1, 7


["D 2","C","U 3","C","D 4","C","U 2","Z","Z","U 1","C"]

0 
1 
2 d
3 
4 d
5 
6
7 


*/