#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
struct pos{
	int x;
	int y;
	int state;
	int dist;
};
int dxdy[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
int n, m;
bool is_valid(int x, int y){
	if (x >= 0 && x < n && y >= 0 && y < m){
		return true;
	}
	return false;
}
int bfs(pos start_pos, vector<vector<char>>& arr){
	queue<pos>q;
	pos cur_pos;
	cur_pos.x = start_pos.x;
	cur_pos.y = start_pos.y;
	cur_pos.state = 0;
	cur_pos.dist = 0;
	q.push(cur_pos);
	bool visited[50][50][64] = {};
	int ans = -1;
	while (!q.empty()){
		pos cur_pos = q.front();
		q.pop();
		if (visited[cur_pos.x][cur_pos.y][cur_pos.state]) {
			continue;
		}
		visited[cur_pos.x][cur_pos.y][cur_pos.state] = true;
		for (int i = 0; i < 4; i++){
			int nx = cur_pos.x + dxdy[i][0];
			int ny = cur_pos.y + dxdy[i][1];
			if (is_valid(nx, ny)){
				pos nxt_pos;
				if (arr[nx][ny] == '.' || arr[nx][ny] == '0'){
					nxt_pos.x = nx;
					nxt_pos.y = ny;
					nxt_pos.state = cur_pos.state;
					nxt_pos.dist = cur_pos.dist + 1;
					q.push(nxt_pos);
				}
				else if(arr[nx][ny] >= 65 && arr[nx][ny] <= 70){ // 포네그리프 바다
					int bit_shift = arr[nx][ny] - 65;
					if ((cur_pos.state & (1 << bit_shift)) != 0){ // 읽은 포네그리프라면
						nxt_pos.x = nx;
						nxt_pos.y = ny;
						nxt_pos.state = cur_pos.state;
						nxt_pos.dist = cur_pos.dist + 1;
						q.push(nxt_pos);
					}

				}
				else if(arr[nx][ny] >= 97 && arr[nx][ny] <= 102){ // 포네그리프
					int bit_shift = arr[nx][ny] - 97;
					nxt_pos.x = nx;
					nxt_pos.y = ny;
					nxt_pos.state = cur_pos.state | (1 << bit_shift);
					nxt_pos.dist = cur_pos.dist + 1;
					q.push(nxt_pos);
				}
				else if (arr[nx][ny] == '1'){
					ans = cur_pos.dist + 1;
					return ans;
				}
			}
		}
	}
	return ans;
}
int main() {
	int T;
	cin >> T;
	pos start_pos;
	for (int tc = 1; tc <= T; tc++){
		cin >> n >> m;
		vector<vector<char>> arr(n, vector<char>(m, -1));
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				cin >> arr[i][j];
				if (arr[i][j] == '0'){
					start_pos.x = i;
					start_pos.y = j;
				}
			}
		}
		cout << "#" << tc << " " << bfs(start_pos, arr) << "\n";
	}

    return 0;
}
