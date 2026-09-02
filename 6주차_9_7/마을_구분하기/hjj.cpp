#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int grid[26][26];
bool visited[26][26] = { 0, };

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

int findTown(int x, int y) {
    visited[y][x] = 1;
    int people = 1;

    int nx, ny;
    for (int dir_idx = 0; dir_idx < 4; dir_idx++) {
        nx = x + dx[dir_idx];
        ny = y + dy[dir_idx];

        if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
            continue;
        }
        if (visited[ny][nx]) {
            continue;
        }
        if (!grid[ny][nx]) {
            continue;
        }

        people += findTown(nx, ny);
    }

    return people;
}

int main() {
    cin >> n;
    vector<int> town;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] && !visited[i][j]) town.push_back(findTown(j, i));
        }
    }

    sort(town.begin(), town.end());

    cout << town.size() << "\n";
    for (int num : town) {
        cout << num << "\n";
    }

    return 0;
}
