#include <string>
#include <vector>

#define MAX_N 100

using namespace std;

int board[MAX_N+1][MAX_N+1][2];
int N;

bool check_rule(){
    for(int i = 0; i<=N; i++){
        for(int j = 0; j<=N; j++){
            // 기둥
            if(board[i][j][0] == 1){
                // 바닥인 경우
                bool ground = i == 0;
                // 보의 한쪽 끝 부분인 경우
                
                bool pillar_on_bo = (board[i][j-1][1] == 1 || board[i][j][1] == 1);
                // 기둥 위인 경우
                // out of bound 가능성??
                bool pillar_on_pillar = (i==0)||(board[i-1][j][0] == 1);
                if(!ground && !pillar_on_bo && !pillar_on_pillar) return false;
            }
            // 보
            if(board[i][j][1] == 1){
                // 기둥 위인 경우
                bool pillar_on_bo = i>0 && (board[i-1][j][0] == 1 || board[i-1][j+1][0] == 1);
                // 양 끝이 보인 경우
                bool bo_btw_bo = j>0 && (board[i][j-1][1] == 1 && board[i][j+1][1] == 1);
                if(!pillar_on_bo && !bo_btw_bo) return false;
            }
        }
    }
    
    return true;
}


vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    N = n;
    
    for(int i = 0; i<build_frame.size(); i++){
        int x = build_frame[i][0];
        int y = build_frame[i][1];
        
        int a = build_frame[i][2];
        int b = build_frame[i][3];
        
        // 실행 전 상태 저장
        int before = board[y][x][a];
        
        // 일단 넣기
        board[y][x][a] = b;
        
        // 검사 후 false면 원복
        if(!check_rule()){
            board[y][x][a] = before;
        }
    }
    
    // 답 산출
    for (int x = 0; x <= N; x++) {
        for (int y = 0; y <= N; y++) {
            for (int a = 0; a < 2; a++) {
                if (board[y][x][a]) {
                    answer.push_back({x, y, a});
                }
            }
        }
    }
    return answer;
}
