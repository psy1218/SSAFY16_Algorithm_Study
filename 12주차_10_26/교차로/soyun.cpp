#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// 동 = 0 서 = 1 남 = 2  북 = 3
int dr[4] = {0,0,1,-1};
int dc[4] = {1,-1,0,0};

int H, W;
vector<vector<char>>grid;
vector<pair<int,int>>start_pos;

int start_d = 0;
int start_r = 0;
int start_c = 0;
int goal_r = 0;
int goal_c = 0;

vector<char>cmd;


bool path(int nr, int nc){
    if(nr < 0 || nr >= H || nc < 0 || nc >= W) return false;

    return true;
}

void Input(){
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            cin >> grid[i][j];
        }
    }
}

// 
bool compare(pair<int,int>& a, pair<int,int>&b){
    if(a.first == b.first) return a.second > b.second;
    return a.first > b.first;
}

// 중복 방문이 불가능하며, 2칸씩 이동 하기 때문에 3면이 막혀있어야함. 
void Start(){
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(grid[i][j] == '.') continue;
            
            int wall_cnt = 0;
            for(int index =0;index<4;index++){
                int nr = i + dr[index];
                int nc = j + dc[index];

                if(path(nr, nc) == false) {
                    wall_cnt++;
                    continue;
                } 
                if(grid[nr][nc] == '.') wall_cnt++;
            }

            if(wall_cnt == 3) start_pos.push_back({i, j});
        }
    }

    if(start_pos.size() != 2) cout << " error : start point \n" ;
    else{
        sort(start_pos.begin(), start_pos.end(), compare);
        start_r = start_pos[0].first;
        start_c = start_pos[0].second;
        goal_r = start_pos[1].first;
        goal_c = start_pos[1].second;
    }
}

int direction(int row, int col){
    for(int i=0;i<4;i++){
        int nr = row + dr[i];
        int nc = col + dc[i];

        if(path(nr, nc) == false) continue;
        if(grid[nr][nc] == '.') continue;

        return i;
    }
}

char Start_Direct(int start_r, int start_c){

    start_d = direction(start_r, start_c);

    if(start_d == 0) return '>';
    if(start_d == 1) return '<';
    if(start_d == 2) return 'v';
    if(start_d == 3) return '^';
}

char left_right(int cur_d, int next_d){

    if((cur_d == 0 && next_d == 3) ||
       (cur_d == 1 && next_d == 2) ||
       (cur_d == 2 && next_d == 0) ||
       (cur_d == 3 && next_d == 1)) return 'L';
    
    return 'R';
}

void commond(){
    int cur_direction = start_d;
    int cur_row = start_r;
    int cur_col = start_c;

    grid[cur_row][cur_col] = '.';

    while(1){
        if(cur_row == goal_r && cur_col == goal_c) break;
        
        int next_direction = direction(cur_row, cur_col);

        // 지금 방향과 다음 방향이 다를 때, 회전을 시켜줘야함. 
        if(cur_direction != next_direction){
            
            cmd.push_back(left_right(cur_direction, next_direction));
            cur_direction = next_direction;
        }

        // 목적지가 아니라면, 2칸 이동하면서 방문 처리 - 위에서 회전처리를 다 했기 때문에, 목적지 찾을 때까지 계속 2칸씩 직진하면 됨.
        for(int i=0;i<2;i++){
            cur_row += dr[cur_direction];
            cur_col += dc[cur_direction];

            grid[cur_row][cur_col] = '.';
        }
        cmd.push_back('A');
    }
}

int main(){

    cin >> H >> W;
    grid.assign(H, vector<char>(W, ' '));

    Input();

    Start();
    cout << start_r + 1 << " " << start_c + 1 << "\n";

    char start_direction = Start_Direct(start_r, start_c);
    cout << start_direction << "\n";

    commond();
    for(int i=0;i<cmd.size();i++){
        cout << cmd[i];
    }

    return 0;
}

/*
// cur, next 방향 제대로 구현 못 함. 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 동 서 남 북 
int dr[4] = {0,0,1,-1};
int dc[4] = {1,-1,0,0};

struct Info{
    int cur_direct;
    int next_r;
    int next_c;
};

int H, W;
vector<vector<char>> grid;

vector<pair<int,int>>start_pos;
char direct_char;
vector<char>cmd;

bool compare(pair<int,int>& a, pair<int,int>& b){
    if(a.first == b.first) return a.second > b.second;

    return a.first > b.first;
}

void find_start(){

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {

            if(grid[i][j] == '.') continue;

            int wall_cnt = 0;
            for(int n_i=0;n_i<4;n_i++){
                int nr = i + dr[n_i];
                int nc = j + dc[n_i];

                if (nr < 0 || nr >= H || nc < 0 || nc >= W) {
                    wall_cnt++;
                    continue;
                }
                if (grid[nr][nc] == '.') wall_cnt++;
            }

            if(wall_cnt == 3){
                start_pos.push_back({i,j});
            }
        }
    }

    sort(start_pos.begin(), start_pos.end(), compare);

    for(int i=0;i<start_pos.size();i++){
        cout << start_pos[i].first << " " << start_pos[i].second << "\n";
    }

}

Info direction(int row, int col){
    Info information;

    for(int i=0;i<4;i++){
        int nr = row + dr[i];
        int nc = col + dc[i];

        if (nr < 0 || nr >= H || nc < 0 || nc >= W) continue;
        if (grid[nr][nc] == '.') continue;

        gird[nr][nc] = '.';
        if(i == 0) information = { 0, nr, nc};
        if(i == 1) information = { 1, nr, nc};
        if(i == 2) information = { 2, nr, nc};
        if(i == 3) information = { 3, nr, nc};

        return information;
    }
}

// 동 서 남 북
char start_direct(int num){
    
        if(num == 0) return '>';
        if(num == 1) return '<';
        if(num == 2) return 'v';
        if(num == 3) return '^';
}

char left_right(Info direct, int cr, int cc){

    int cd = direct.cur_direct;
    int nr = direct.next_r;
    int nc = direct.next_r;

    if(if cd == 1 && )
}

void commond(){

    int cur_r = start_pos[0].first;
    int cur_c = start_pos[0].second;
    int goal_r = start_pos[1].first;
    int goal_c = start_pos[1].second;


    while(1){
        if(cur_r == goal_r && cur_c == goal_c) break;

        Info direct = direction(cur_r, cur_c);

        int cd = direct.cur_direct;
        int nr = direct.next_r;
        int nc = direct.next_r;

        if(cd != temp){
            cmd.push_back(left_right(direct, cur_r, cur_c));
        }


        if 
    }
}

int main() {
    cin >> H >> W;

    grid.resize(H, vector<char>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];
        }
    }

    find_start();

    int start_r = start_pos[0].first;
    int start_c = start_pos[0].second;

    cout << start_r  + 1 << " " << start_c + 1 << "\n";

    Info temp = direction(start_r, start_c);
    direct_char = start_direct(temp.cur_direct);
    cout << direct_char << "\n";

    commond();

    return 0;
}

*/

/*


####..#.
...#..#.
####..#.
#...#...
#####...

*/


