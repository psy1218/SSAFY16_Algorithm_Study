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
        if (ban_nums[i] <= recovered_order_idx) { // 즉, n이 아니라, 앞에서 밀려나게 된 주문번호 기준으로 비교한다. 중간에 삭제된 주문들 때문에 뒤로 밀려나는 효과가 있기 때문.  
            // recovered_order_idx가 뒤로 밀려남에 따라, 원래는 범위 밖에 있던 새로운 ban이 내 앞 영역으로 들어오는 상황이 발생할 수 있기 때문에 n이 아니라, 갱신되는 recovered_order_idx 와 비교한다.
            recovered_order_idx++;
        } 
        else {
            break;
        }
    }
    answer = find_order(recovered_order_idx);
    return answer;
}
