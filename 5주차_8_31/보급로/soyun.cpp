#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

char board[100][100];
int Map[100][100];
int dist[100][100];

struct Info{
	int cost;
	int x;
	int y;
};

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

void Input(int N) {

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			cin >> board[i][j];
		}
	}

	for (int i = 0;i < N;i++) {
		for (int j = 0;j < N;j++) {
			Map[i][j] = (int)(board[i][j] - '0');
		}
	}

}

struct compare {
	bool operator()(Info& a, Info& b) {
		return a.cost > b.cost;// a를 더 큰 값으로 설정하면 a의 우선순위가 낮아짐.
							   // 더 큰 a의 우선순위를 낮춰 최소순으로 pq가 정렬됨. 
                  // 난 반대로 a.cost < b.cost 로 해서 우선순위가 완전 반대로 되어서 시간초과 뜸. 
	}
};


void min_time(int N) {
	priority_queue<Info, vector<Info>, compare>pq;
	fill(dist[0], dist[0] + 100 * 100, INT_MAX); // 정적 배열 요소 채우기 

	pq.push({ 0,0,0 });
	dist[0][0] = 0;

	while (!pq.empty()) {
		auto cur = pq.top();
		int cc = cur.cost;
		int cx = cur.x;
		int cy = cur.y;
		pq.pop();

		if (cc > dist[cx][cy]) continue; // 예전에 측정한 cost가 현재 cost 보다 작으면 탐색 안 해도 됨.
										// 갱신 조건 잘 걸었으면 없어도 되지만, 쓸데없는 노드를 계속 탐색함.
										// => 시간 낭비 

		for (int i = 0;i < 4;i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];


			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue; 

			if (dist[nx][ny] > Map[nx][ny] + cc) {
				dist[nx][ny] = Map[nx][ny] + cc;
				pq.push({ Map[nx][ny] + cc,nx,ny });
			}
		}
	}
	 

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;
	for (int t = 1;t <= T;t++) {

		int N;
		cin >> N;

		Input(N);
		min_time(N);

		cout << "#" << t << " " << dist[N-1][N-1] << "\n";
	}

	return 0;
}




/*
board
0100
1110
1011
1010

dist

0   1     1   1
1   2     2   1
100 100 100   2
100 100 100   2

Map
011
011
010

dist
 0  1  2
 0  1  2
 0  1  1

*/

/*

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Info {
	int x;
	int y;
	int cost;
};

int T, N;
vector<vector<char>>board;
vector<vector<int>>Map;
vector<vector<int>>dist;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

struct compare {
	bool operator()(Info& a,Info& b) {
		return a.cost > b.cost;
	}
};

void dijkstra(int X, int Y, int COST) {
	priority_queue<Info, vector<Info>, compare>pq;
	pq.push({X, Y, COST});

	dist.assign(N, vector<int>(N, INT_MAX));
	dist[X][Y] = COST;

	while (!pq.empty()) {
		auto cur = pq.top();
		int cx = cur.x;
		int cy = cur.y;
		int cc = cur.cost;
		pq.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (cc > dist[cx][cy]) continue;
			if (nx < 0 || nx >= N || ny < 0 || ny >= N)	continue;

			if (dist[nx][ny] > Map[nx][ny] + cc) {
				dist[nx][ny] = Map[nx][ny] + cc;
				pq.push({ nx, ny, Map[nx][ny] + cc });
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	//freopen("input.txt", "r", stdin);

	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> N;

		board.assign(N, vector<char>(N));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> board[i][j];
			}
		}

		Map.assign(N, vector<int>(N, 0));

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				Map[i][j] = board[i][j] - '0';
			}
		}


		dijkstra(0, 0, 0);

		//for (int i = 0; i < N; i++) {
		//	for (int j = 0; j < N; j++) {
		//		cout << dist[i][j] << " ";
		//	}
		//	cout << '\n';
		//}

		cout << "#" << t << " " << dist[N - 1][N - 1] << '\n';
	}

	return 0;
}

 ===================
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int T, N;
vector<vector<char>>board;
vector<vector<int>>dist;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

void bfs(int x, int y) {
	queue<pair<int, int>>q;
	q.push({ x,y });

	dist.assign(N, vector<int>(N, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dist[i][j] = board[i][j] - '0';
		}
	}


	while (!q.empty()) {
		auto cur = q.front();
		int cx = cur.first;
		int cy = cur.second;
		q.pop();
		board[x][y] = '.';

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];

			if (nx < 0 || nx >= N || ny < 0 || ny >= N)	continue;
			if (board[nx][ny] == '.') continue;
			dist[nx][ny] += dist[cx][cy];
			board[nx][ny] = '.';
			q.push({ nx,ny });
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	freopen("input.txt", "r", stdin);

	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> N;

		board.assign(N, vector<char>(N));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> board[i][j];
			}
		}

		board[N - 1][N - 1] = 'G';

		bfs(0, 0);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << dist[i][j] << " ";
			}
			cout << '\n';
		}

		cout << "#" << t << " " << dist[N - 1][N - 1] << '\n';
	}

	return 0;
}

*/
