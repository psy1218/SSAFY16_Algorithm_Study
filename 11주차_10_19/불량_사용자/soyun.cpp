
// 비트마스킹 + dfs
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string>users;
vector<string>banned;

int visited[256] = {0,};

int answer = 0;

bool Check(int i, int ban_cnt){
    if (users[i].size() != banned[ban_cnt].size()) return false;
    
    for(int index=0;index<users[i].size();index++){
        if(banned[ban_cnt][index] == '*') continue;
        if(banned[ban_cnt][index] != users[i][index]) return false;
    }
    
    return true;
}

void dfs(int ban_cnt, int mask){
    if(ban_cnt >= banned.size()){
        if(visited[mask] == 0 ){
            visited[mask] = 1;
            answer++ ;
        }
        return;
    }
    
    for(int i=0;i<users.size();i++){
        if(mask & (1<<i)) continue; 
        
        if(Check(i, ban_cnt)){
            dfs(ban_cnt+1, mask | (1 << i));
        }
    }
}



int solution(vector<string> user_id, vector<string> banned_id){
    
    
    users = user_id;
    banned = banned_id;
    
    int mask = 0;
    
    sort(users.begin(), users.end());
    sort(banned.begin(), banned.end());
    
    dfs(0, mask);
    
    
    return answer;
}

// -> set을 활용해서 같은 경우의 수 중복 저장 안 하기 
// -> 비트마스킹을 활용해서 같은 경우의 수 미리 방문 처리 하기 

// set + dfs 

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set> // 아이디 중복 확인하기 ㅜ

using namespace std;
int res = 0;

set<vector<string>>s;
vector<string>Data;

bool Check(int i, int k, vector<string> user_id, vector<string> banned_id){
    if(user_id[i].size() != banned_id[k].size()) return false;
    
    for(int j=0;j<user_id[i].size();j++){
        if(banned_id[k][j] == '*') continue;
        if(user_id[i][j] != banned_id[k][j]) return false;
    }
    return true;
}

void dfs(int cnt, vector<string> user_id, vector<string> banned_id, vector<int>& visited){
    if(cnt >= banned_id.size()){
        
        //["frodo", "crodo", "abc123"]
        //["crodo", "frodo", "abc123"]
        // 이게 set 에 들어가도 다른 벡터로 인식됨. 순서 맞춰주기!!!! 
        vector<string>Temp = Data;
        sort(Temp.begin(), Temp.end());
        s.insert(Temp);
        return;
    }
    
    
    for(int i=0;i<user_id.size();i++){
        if(visited[i] == 1) continue;
        if(Check(i, cnt, user_id, banned_id)){
            //cout << i << ' ' << cnt<<'\n';
            visited[i] = 1;
            Data.push_back(user_id[i]);
            dfs(cnt + 1, user_id, banned_id, visited);
            visited[i] = 0;
            Data.pop_back();
        }
    }
}


int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;
    vector<int>visited(user_id.size(), 0);
    dfs(0, user_id, banned_id, visited);

    answer = s.size();
    
    return answer;
}



/*
["frodo", "fradi", "crodo", "abc123", "frodoc"]
["fr*d*", "abc1**"]
fr*d* 2
abc1** 1

["frodo", "fradi", "crodo", "abc123", "frodoc"]
["*rodo", "*rodo", "******"]
*rodo 2 
*rodo 2 
****** 2

["frodo", "fradi", "crodo", "abc123", "frodoc"]
["fr*d*", "*rodo", "******", "******"]
fr*d* 2
*rodo 2
f*ado 1
****** 2
****** 2

*/