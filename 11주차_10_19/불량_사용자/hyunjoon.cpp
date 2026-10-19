#include <string>
#include <vector>
#include <set>
using namespace std;

vector<string> users;
vector<string> banned;

set<int> result;

bool check(string user, string mask){
    if(user.length() != mask.length()){
        return false;
    }
    
    for(int i = 0; i<user.length(); i++){
        if(mask[i] == '*') continue;    
        
        if(user[i] != mask[i]){
            return false;
        }
    }
    
    return true;
}

void dfs(int L, int mask){
    if(L==banned.size()){
        result.insert(mask);
        return;
    }
    
    for(int i = 0; i<users.size(); i++){
        // visited와 같음
        if(mask & (1<<i)) continue;
        
        if(!check(users[i], banned[L])) continue;
        
        dfs(L+1, mask|(1<<i));
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    users = user_id;
    banned = banned_id;
    
    dfs(0,0);
    
    return result.size();
}
