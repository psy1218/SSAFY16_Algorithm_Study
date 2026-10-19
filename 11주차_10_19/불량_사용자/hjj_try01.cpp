#include <string>
#include <vector>
#include <queue>

using namespace std;
bool counting[260] = { 0, };

struct Status {
    unsigned int comb;
    int curr_idx;
};

bool is_banned_id(string a, string b) {
    if (a.length() != b.length()) return false;
    for (int i = 0; i < a.length(); i++) {
        if (b[i] == '*') continue;
        if (a[i] != b[i]) return false;
    }
    return true;
}

int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;

    if (static_cast<int>(user_id.size()) == static_cast<int>(banned_id.size())) return 1;

    queue<Status> q;
    q.push({ 0b0, 0 });

    Status curr_state;
    while (!q.empty()) {
        curr_state = q.front();
        q.pop();

        if (curr_state.curr_idx == static_cast<int>(banned_id.size())) {
            if (!counting[(int)curr_state.comb]) {
                counting[(int)curr_state.comb] = true;
                answer++;
            }
            continue;
        }

        for (int i = 0; i < static_cast<int>(user_id.size()); i++) {
            if (!((curr_state.comb >> i) ^ 0b1)) continue;
            if (is_banned_id(user_id[i], banned_id[curr_state.curr_idx])) {
                q.push({ curr_state.comb | (0b1 << i), curr_state.curr_idx + 1 });
            }
        }
    }

    return answer;
}