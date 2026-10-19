#include <string>
#include <vector>
#include <queue>

using namespace std;

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
    bool counting[256] = { 0, };
    bool is_checked[9][256] = { 0, };

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

        unsigned int n_comb;
        int n_idx;

        for (int i = 0; i < static_cast<int>(user_id.size()); i++) {
            n_comb = curr_state.comb | (0b1 << i);
            n_idx = curr_state.curr_idx + 1;

            if ((curr_state.comb >> i) & 0b1) continue;
            if (is_checked[n_idx][n_comb]) continue;
            if (is_banned_id(user_id[i], banned_id[curr_state.curr_idx])) {
                is_checked[n_idx][n_comb] = true;
                q.push({ n_comb, n_idx });
            }
        }
    }

    return answer;
}