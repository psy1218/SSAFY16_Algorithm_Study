#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Monster_Info {
	int dist;
	int row;
	int col;
};

int dr[4] = { 1,-1,0,0 };
int dc[4] = { 0,0,1,-1 };

int N;
vector<vector<int>>board;
int f_level = 2, f_exp = 0; // 변수 exp라는 이름이 표준 라이브러리의 std::exp() 함수와 충돌
int fighter_r, fighter_c;
int answer = 0;

//vector<Monster_Info>Monster;
vector<vector<int>>dist;

//bool compare(Monster_Info &a, Monster_Info& b) {
//	return a.level < b.level;
//}

void Input() {

	cin >> N;
	board.assign(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			if (board[i][j] == 9) {
				fighter_r = i;
				fighter_c = j;
			}
		}
	}

	//sort(Monster.begin(), Monster.end(), compare);
}

// 우선순위 if 문 구현 잘 생각하기  - if와 return 조건 잘 생각하기 
struct cmp {
	bool operator()( Monster_Info& a, Monster_Info& b) {
		if (a.dist == b.dist) {
			if (a.row == b.row) return a.col > b.col;

			return a.row > b.row;
		}

		return a.dist > b.dist;
	}
};

priority_queue<Monster_Info, vector<Monster_Info>, cmp>passible;


void bfs(int r, int c) {
	// fighter의 이동 
	queue<pair<int, int>>q;
	dist.assign(N, vector<int>(N, -1));

	// 시작점도 0으로 처리해주기 
	board[r][c] = 0;
	q.push({ r , c });
	dist[r][c] = 0;

	while (!q.empty()) {
		auto cur = q.front();
		int cr = cur.first;
		int cc = cur.second;
		q.pop();

		// 몬스터 존재 여부 확인하고, 사냥할 수 있는지 파악 후 큐에 넣기 
		// 잡을 수 있으면 모든 몬스터의 exp 는 1 증가 
		if (board[cr][cc] != 0 && board[cr][cc] != 9) {
			if (board[cr][cc] < f_level) passible.push({ dist[cr][cc], cr, cc });
		}

		for (int i = 0; i < 4; i++) {
			int nr = cr + dr[i];
			int nc = cc + dc[i];

			if (nr < 0 || nr >= N || nc < 0 || nc >= N)continue;
			if (dist[nr][nc] != -1) continue;
			if (board[nr][nc] > f_level) continue;

			q.push({ nr, nc });
			dist[nr][nc] = dist[cr][cc] + 1;
		}
	}


}

void Game(){

	while (1) {

		bfs(fighter_r, fighter_c); // 파이터가 이동하면서, 몬스터와의 거리, 좌표, 사냥 가능 여부 파악 

		if (passible.empty()) break; // 가능한게 없으면 종료 

    // top이 조건을 충족시키는 값 
		auto goal = passible.top();
		fighter_r = goal.row;
		fighter_c = goal.col;

		f_exp++;
		answer += goal.dist;
		board[fighter_r][fighter_c] = 0;

		if (f_exp == f_level) {
			f_exp = 0;
			f_level++;
		}

		while (!passible.empty()) {
			passible.pop();
		}
			
	}

}


void Output() {

	cout << answer << "\n";
}


int main() {

	Input();

	Game();

	Output();

	return 0;
}






// ----------------------------------





//#include <iostream>
//#include <queue>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//struct Monster_Info {
//	int level;
//	int row;
//	int col;
//};
//
//int dr[4] = { 1,-1,0,0 };
//int dc[4] = { 0,0,1,-1 };
//
//int N;
//vector<vector<int>>board;
//int f_level = 2, exp = 0;
//int fighter_r, fighter_c;
//int answer = 0;
//
//vector<Monster_Info>Monster;
//
//void Input() {
//
//	cin >> N;
//	board.assign(N, vector<int>(N));
//
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			cin >> board[i][j];
//			if (board[i][j] == 9) {
//				fighter_r = i;
//				fighter_c = j;
//			}
//			else if (board[i][j] != 0) {
//				Monster.push_back({ board[i][j], i, j });
//			}
//		}
//	}
//
//	sort(Monster.begin(), Monster.end());
//}
//
//struct cmp {
//	bool operater(Monster_Info &a, Monster_Info &b) {
//		if (a.col == b.col) a.row > b.row;
//		
//		return a.col > b.col;
//	}
//};
//
//
//void bfs() {
//	// fighter의 이동 
//	queue<pair<int, int>>q;
//	vector<vector<int>>visited(N, vector<int>(N, 0));
//
//	q.push({ fighter_r , fighter_c });
//	visited[fighter_r][fighter_c] = 1;
//
//	while (!q.empty()) {
//		auto cur = q.front();
//		int cr = cur.first;
//		int cc = cur.second;
//		q.pop();
//
//		
//
//		for (int i = 0; i < 4; i++) {
//			int nr = cr + dr[i];
//			int nc = cc + dc[i];
//
//			if (nr < 0 || nr >= N || nc < 0 || nc >= N)continue;
//			if (visited[nr][nc]) continue; // 재탐색할 때 처리 방법 생각하기
//			if (board[nr][nc] < f_level) continue;
//
//			q.push({nr, nc });
//			visited[nr][nc] = 1;
//		}
//	}
//}
//
//
//void Game() {
//
//	int start_index = 0;
//
//	while (1) {
//		
//		// 몬스터 레벨보다 크면 잡을 수 있는 queue -> 무슨 레벨이든 잡으면 1exp 증가 
//		priority_queue<Monster_Info, vector<Monster_Info, cmp>>passible;
//		for (int i = start_index; i < Monster.size(); i++) {
//			if (Monster[i].level < f_level) {
//				passible.push({ Monster[i].level, Monster[i].row, Monster[i].col });
//			}
//			else {
//				start_index = i;
//				continue;
//			}
//		}	
//
//		bfs();
//	}
//
//}
//
//
//
//void Output() {
//
//	cout << answer << "\n";
//}
//
//
//int main() {
//
//	Input();
//
//	Game();
//
//	Output();
//
//	return 0;
//}
