#include <string>

#define MAX_SIZE 11

using namespace std;

int x, y;
int answer;
bool area[MAX_SIZE][MAX_SIZE][4];

/* 이동 배열 초기화 */
void array_reset() {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            for (int k = 0; k < 4; k++) {
                area[i][j][k] = true;
            }
        }
    }
}


void up() {
    if (y + 1 < MAX_SIZE) {
        if (area[y][x][0] && area[y + 1][x][1]) {
            area[y][x][0] = area[y + 1][x][1] = false;
            answer++;
        }
        
        y++;
    }
}


void down() {
    if (y - 1 >= 0) {
        if (area[y][x][1] && area[y - 1][x][0]) {
            area[y][x][1] = area[y - 1][x][0] = false;
            answer++;
        }
        
        y--;
    }
}


void left() {
    if (x - 1 >= 0) {
        if (area[y][x][2] && area[y][x - 1][3]) {
            area[y][x][2] = area[y][x - 1][3] = false;
            answer++;
        }
        
        x--;
    }
}


void right() {
    if (x + 1 < MAX_SIZE) {
        if (area[y][x][3] && area[y][x + 1][2]) {
            area[y][x][3] = area[y][x + 1][2] = false;
            answer++;
        }
        
        x++;
    }
}



int solution(string dirs) {
    array_reset(); // 배열 초기화
    answer = 0; 
    x = y = 5; // 시작 위치 초기화
    
    int dirs_size = dirs.size();
    for (int i = 0; i < dirs_size; i++) {
        char fw = dirs[i];

        if (fw == 'U') {
            up();
        } else if (fw == 'D') {
            down();
        } else if (fw == 'L') {
            left();
        } else if (fw == 'R') {
            right();
        }
    }
    
    return answer;
}
