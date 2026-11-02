#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
long long find_order_idx(string ban){
    int ban_size = ban.size();
    int idx = 0; // 마지막 자릿수 인덱스
    long long total_value = 0;
    while (idx < ban_size) {
        char cur = ban[idx]; // a ~ z
        int cur_value = cur - 96; // 'a' = 97이기 때문에, 'a' = 1로 판별하려면 96을 빼야함
        total_value = total_value * 26 + cur_value;
        idx++;
    }
    return total_value;
}
string find_order(long long order_idx){
    vector<char> arr;
    string ans = "";
    while (order_idx > 0){
        order_idx--;
        int cur = order_idx % 26;
        order_idx /= 26;
        arr.push_back('a'+cur);
    }
    while (!arr.empty()){
        char cur = arr.back();
        arr.pop_back();
        ans += cur;
    }
    return ans;
}
string solution(long long n, vector<string> bans) {
    string answer = "";
    int bans_size = bans.size();
    long long recovered_order_idx = n;
    
    vector<long long> ban_nums;
    for (int i = 0; i < bans_size; i++) {
        ban_nums.push_back(find_order_idx(bans[i]));
    }
    sort(ban_nums.begin(), ban_nums.end());
    
    for (int i = 0; i < bans_size; i++) {
        if (ban_nums[i] <= recovered_order_idx) {
            recovered_order_idx++;
        } 
        else {
            break;
        }
    }
    answer = find_order(recovered_order_idx);
    return answer;
}
