#include <string>
#include <iostream>
using namespace std;

int solution(string dirs) {
    int answer = 0;
    
    int y = 0;
    int x = 0;
    int dy[4] = {1, 0, -1, 0};
    int dx[4] = {0, 1, 0, -1};
    bool visited[11][11][4] = {false};
    
    for (char commands: dirs){
        int direction_id;
        if (commands == 'U'){ direction_id = 0; }
        else if (commands == 'R'){ direction_id = 1; }
        else if (commands == 'D'){ direction_id = 2; }
        else if (commands == 'L'){ direction_id = 3; }
        
        int next_y = y + dy[direction_id];
        int next_x = x + dx[direction_id];
        
        if (next_y < -5 || next_y > 5 || next_x < -5 || next_x > 5){
            continue;
        }
        
        if (visited[y+5][x+5][direction_id] == false){ answer++; }
        visited[y+5][x+5][direction_id] = true;
        visited[next_y+5][next_x+5][(direction_id+2)%4] = true;
        
        y = next_y;
        x = next_x;
        
    }
    
    return answer;
}
