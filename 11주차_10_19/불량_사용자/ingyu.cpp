
#include <string>
#include <vector>
#include <set>

using namespace std;

bool check(string user, string banned) {
    int user_len = user.length();
    int banned_len = banned.length();

    if (user_len != banned_len) {
        return false;
    }

    for (int i = 0; i < user_len; i++) {
        if (banned[i] == '*') {
            continue;
        }

        if (user[i] != banned[i]) {
            return false;
        }
    }

    return true;
}

// depth는 매칭된 불량 사용자 수
void dfs(vector<string>& user_id,
         vector<string>& banned_id,
         int user_state,
         int depth,
         set<int>& result) {

    // 모든 불량 사용자와 매칭 완료했으므로 탐색 종료
    if (depth == banned_id.size()) {
        // 모든 불량 사용자에 대해서 매칭을 성공했을때의 매칭된 
        // 유저 상태가 user_state (1이면 매칭된것)
        result.insert(user_state); // set배열이기 때문에 중복되어도 상관없음.
        return;
    }

    for (int i = 0; i < user_id.size(); i++) {
        // 이미 선택한 사용자라면 건너뛰기
        if (user_state & (1 << i)) {
            continue;
        }
        // 현재 불량 사용자와 매칭되는지 확인
        if (check(user_id[i], banned_id[depth])) {
            dfs(user_id, banned_id,
                user_state | (1 << i),
                depth + 1,
                result);
        }
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {

    set<int> result;

    dfs(user_id, banned_id, 0, 0, result);

    return result.size();
}
