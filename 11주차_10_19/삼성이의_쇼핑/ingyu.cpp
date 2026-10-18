#include<stdio.h>
#include <iostream>
#include <vector>
using namespace std;
int n;
int max_value; // 최대 허용 가격
int ans;
int ans_state;
void dfs(vector<int>& prices, vector<int>& scores,
         int start, int state, int cur_price, int cur_score) {

    if (cur_price > max_value) {
        return;
    }

    if (cur_score > ans) {
        ans = cur_score;
        ans_state = state;
    }

    for (int i = start; i < n; i++) {
        dfs(prices, scores,
            i + 1,
            state | (1 << i),
            cur_price + prices[i],
            cur_score + scores[i]);
    }
}
int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++){
		ans = 0; // 초기화
		ans_state = 0;
		cin >> max_value >> n;
		vector<int> prices(n, 0);
		vector<int> scores(n, 0);
		for (int i = 0; i < n; i++){
			cin >> prices[i] >> scores[i];
		}
		dfs(prices, scores, 0, 0, 0, 0);
		vector<int> clothes;
		for (int i = 0; i < n; i++){
			if ((ans_state & (1 << i)) != 0){
				clothes.push_back(n - 1 - i);
			}
		}

		cout << "#" << tc << " ";
		for (int i = 0; i < n; i++) {
		    if ((ans_state & (1 << i)) != 0) {
		        cout << i << " ";
		    }
		}
		cout << ans << "\n";
	}
	return 0;
}
