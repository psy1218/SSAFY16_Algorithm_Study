#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;

const int DIGIT_NUM = 26;

long long num_of_spell(string& s) {
    int s_len = s.length();
    long long res = 0;

    for (int i = 0; i < s_len; i++) {
        res += (pow(DIGIT_NUM, i) * (s[(s_len - 1) - i] - 'a' + 1));
    }

    return res;
}


string solution(long long n, vector<string> bans) {
    string answer = "";
    long long skip = 0;
    long long second_skip = 0;
    long long final_n = n;
    priority_queue<long long> pq;

    for (string elem : bans) {
        //cout << "현재 n, num_of_spell(elem): " << n << " " << num_of_spell(elem) << "\n";
        if (n >= num_of_spell(elem)) skip++;
        else pq.push(-(num_of_spell(elem) - n));
    }

    final_n += skip;
    while (!pq.empty()) {
        if (skip + pq.top() < 0) break;
        else {
            skip++;
            final_n++;
            pq.pop();
        }
    }

    while (final_n != 0) {
        final_n--;
        answer += char('a' + final_n % DIGIT_NUM);
        final_n /= DIGIT_NUM;
    }
    reverse(answer.begin(), answer.end());

    return answer;
}


//int main() {
//    // testcase 1
//    cout << "test1 " << solution(30, {"d", "e", "bb", "aa", "ae"}) << "\n";
//    // testcase 2
//    cout << "test2 " << solution(7388, { "gqk", "kdn", "jxj", "jxi", "fug", "jxg", "ewq", "len", "bhc" }) << "\n";
//    // testcase 3
//    cout << "test3 " << solution(26, { }) << "\n";
//}