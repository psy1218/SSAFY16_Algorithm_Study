#include <iostream>
using namespace std;

int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

struct Item {
	int r = -1;
	int c = -1;
};

struct Queue {
	int front = 0;
	int rear = 0;
	Item queue[500];

	void init() {
		front = 0;
		rear = 0;
	}

	void push(int r, int c) {
		Item new_item;
		new_item.r = r;
		new_item.c = c;

		queue[rear++] = new_item;

		return;
	}

	Item pop() {
		Item data = queue[front++];

		return data;
	}

	bool empty() {
		if (front == rear) {
			return true;
		}
		return false;
	}
};

struct Monster {
	int level = 0;
};

struct Player {
	int level = 2;
	int exp_point = 0;
	int r = -1;
	int c = -1;

	bool can_level_up() {
		if (exp_point == level) {
			return true;
		}
		return false;
	}

	void level_up() {
		if (can_level_up()) {
			exp_point = 0;
			level++;
		}
	}
};

struct Cell {
	Monster monster;
	bool is_monster = false;
	int dist = 0;
};

struct Game {

	int N = 0;
	Cell grid[21][21];
	Player player;
	int time = 0;

	void init() {
		cin >> N;
		
		// game 판 초기화
		int status = -1;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				cin >> status;

				if (status == 0) {
					continue;
				}
				else if (status == 9) {
					player.r = r;
					player.c = c;
				}
				else {
					grid[r][c].monster.level = status;
					grid[r][c].is_monster = true;
				}
			}
		}
	}

	void debugging() {
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				cout << grid[r][c].is_monster << " ";
			}
			cout << "\n";
		}
	}

	int find_target() {
		bool visited[21][21] = { false };

		Queue queue;
		int r = player.r;
		int c = player.c;

		queue.push(r, c);
		visited[r][c] = true;

		while (!queue.empty()) {
			Item item = queue.pop();
			r = item.r;
			c = item.c;
			int dist = grid[r][c].dist;

			for (int i = 0; i < 4; i++) {
				int nr = r + dr[i];
				int nc = c + dc[i];

				if (nr < 0 || nr >= N || nc < 0 || nc >= N) {
					continue;
				}

				if (grid[nr][nc].monster.level > player.level || visited[nr][nc]) {
					continue;
				}

				queue.push(nr, nc);
				visited[nr][nc] = true;
				grid[nr][nc].dist = dist + 1;

			}
		}

		// monster 찾기
		int target_r = -1;
		int target_c = -1;
		int min_dist = 1000;

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (!grid[r][c].is_monster) {
					grid[r][c].dist = 0;
					continue;
				}

				if (grid[r][c].monster.level >= player.level) {
					grid[r][c].dist = 0;
					continue;
				}

				if (grid[r][c].dist == 0) {
					continue;
				}

				if (min_dist > grid[r][c].dist) {
					min_dist = grid[r][c].dist;
					target_r = r;
					target_c = c;
				}
				grid[r][c].dist = 0;
			}
		}

		if (min_dist != 1000) {
			player.r = target_r;
			player.c = target_c;
		}

		return min_dist;
	}

	void turn() {
		while (true) {
			int dist = find_target();

			if (dist == 1000) {
				break;
			}

			//cout << player.r << " " << player.c << "\n";

			grid[player.r][player.c].is_monster = false;
			grid[player.r][player.c].monster.level = 0;
			player.exp_point++;
			player.level_up();
			time += dist;
		}
	}

};

int main() {

	Game game;
	
	game.init();
	//game.debugging();
	game.turn();

	cout << game.time;

	return 0;
}
