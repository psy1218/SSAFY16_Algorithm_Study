#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <tuple>
#include <cstring>

using namespace std;
int n = 8;
int k = 2;
vector<string> cmd = { "D 2","C","U 3","C","D 4","C","U 2","Z","Z" };
string solution(int n, int k, vector<string> cmd) {
	string answer = "";
	for (int i = 0; i < n; i++) {
		answer += "O";
	}
	vector<tuple<int, int, int>> deleted;
	int cur = k; // 현재 커서 위치
	// down = [1, 2, 3 , ... , n-1, -1]
	// up = [-1, 0, 1, 2, ... , n-1]
    vector<int> down(n);
    vector<int> up(n);
	for (int i = 1; i <= n - 1; i++) {
		down[i - 1] = i;
	}
	down[n - 1] = -1;
	for (int i = 0; i < n - 1; i++) {
		up[i + 1] = i;
	}
	up[0] = -1;
	for (int i = 0; i < cmd.size(); i++) {
        char command = cmd[i][0];
		if (command == 'U' || command == 'D') {
			// cout << result[0] << " " << result[1] << endl;
			int move_size = stoi(cmd[i].substr(2));
			// cout << move_size << "움직인 크기" << endl;
			if (command == 'D') {
				for (int j = 0; j < move_size; j++) {
					cur = down[cur];
					// cout << cur << "로 내려감" << endl;
				}
			}
			else if (command == 'U') {
				for (int j = 0; j < move_size; j++) {
					cur = up[cur];
					// cout << cur << "로 올라감" << endl;
				}
			}
		}
		else { // 삭제/복구
			// cout << result[0] << endl;
			if (command == 'C') { // 삭제. 복구를 위해서, 스택을 이용해서 최근에 삭제한 인덱스일수록 위에 존재하게 해야함
				// cout << cur << "번째를 삭제함" << endl;
				answer[cur] = 'X';
				if (down[cur] == -1) { // 현재 커서 위치가 마지막이라면
					deleted.push_back({ cur, down[cur], up[cur] }); // 먼저 스택에 삭제된 인덱스를 push하고
					cur = up[cur]; // 위로 이동한 다음에
					down[cur] = -1; // 현재의 커서 다음이 -1이 되도록 하면 현재 커서가 마지막 위치가 됨
				}
				else {
					deleted.push_back({ cur, down[cur], up[cur] });
					int temp = up[cur];
                    cur = down[cur]; 
                    if (temp != -1) down[temp] = cur; // temp가 -1이 아닐 때만 접근하도록 수정
                    up[cur] = temp;
				}
			}
			else { // 복구
				int restored = get<0>(deleted.back());
				int restored_down = get<1>(deleted.back());
				int restored_up = get<2>(deleted.back());
				deleted.pop_back();
				down[restored] = restored_down;
				up[restored] = restored_up;
				if (restored_down != -1)
					up[restored_down] = restored;

				if (restored_up != -1)
					down[restored_up] = restored;
				answer[restored] = 'O';
				// cout << restored << "번째를 복구함" << endl;
			}
		}
		// cout << "현재 cur 위치:" << cur << endl;
	}
	return answer;
}
int main() {
	cout << solution(n, k, cmd);
	return 0;
}
