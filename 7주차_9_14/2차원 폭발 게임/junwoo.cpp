#include <iostream>

using namespace std;

int N, M, K;
int grid[100][100];

// 폭탄 제거
bool explode(){
    bool boom[100][100] = {};
    bool exploded = false;

    // 각 열 검사
    for (int col = 0; col < N; col++){
        int row = 0;

        while (row < N){
            // 빈 공간
            if (grid[row][col] == 0){
                row++;
                continue;
            }

            int start = row;
            int value = grid[row][col];

            // 같은 폭탄 몇 개 연속인지 확인
            while (row < N && grid[row][col] == value){
                row++;
            }
            int cnt = row - start;

            if (cnt >= M){
                exploded = true;

                for (int r = start; r < row; r++){
                    boom[r][col] = true;
                }
            }
        }
    }

    // 동시 제거
    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            if (boom[r][c]){
                grid[r][c] = 0;
            }
        }
    }
    return exploded;
}

void gravity(){
    int temp[100][100] = {};

    for (int col = 0; col < N; col++){
        int writeRow = N - 1;

        // 밑에서부터 폭탄 채움
        for (int row = N - 1; row >= 0; row--){
            if (grid[row][col] != 0){
                temp[writeRow][col] = grid[row][col];
                writeRow--;
            }
        }
    }

    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            grid[r][c] = temp[r][c];
        }
    }
}

void rotate(){
    int temp[100][100] = {};
    
    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            temp[c][N - 1 - r] = grid[r][c];
        }
    }

    for (int r = 0; r < N; r++){
        for (int c = 0; c < N; c++){
            grid[r][c] = temp[r][c];
        }
    }

    gravity();
}

void explodeAll(){
    while (explode()){
        gravity();
    }
}

int main() {
    cin >> N >> M >> K;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    for (int k = 0; k < K; k++){
        explodeAll();
        rotate();
    }

    explodeAll();

    int answer = 0;
    for (int r = 0; r < N; r++){
        for (int c = 0 ; c < N; c++){
            if (grid[r][c] != 0){
                answer++;
            }
        }
    }
    cout << answer;

    return 0;
}
