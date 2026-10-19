#include <string>
#include <vector>
#include <set>

using namespace std;

set<int> result;

bool match(string user, string banned){
    if (user.size() != banned.size()){
        return false;
    }
    
    for (int i = 0; i < user.size(); i++){
        if (banned[i] != '*' && user[i] != banned[i]){
            return false;
        }
    }
    
    return true;
}

void dfs(int idx, int mask,
        vector<string>& user_id,
        vector<string>& banned_id){
    if (idx == banned_id.size()){
        result.insert(mask);
        return;
    }
    
    for (int i = 0; i < user_id.size(); i++){
        // 이미 선택했으면 건너뛰기
        if (mask & (1 << i)){
            continue;
        }
        
        if (!match(user_id[i], banned_id[idx])){
            continue;
        }
        
        dfs(idx + 1, mask | (1 << i), user_id, banned_id);
        
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    result.clear();
    
    dfs(0, 0, user_id, banned_id);
    
    return result.size();
}
