#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

bool is_valid(int x, int y, int is_bo, vector<vector<vector<int>>>& visit){
    if (is_bo == 0){ // 기둥 설치
        if (y == 1){ // 바닥이라면 (오프셋 적용했으므로 y=1이 바닥)
            return true;
        }
        else if (visit[x-1][y][1] || visit[x][y][1]){ // 보 위라면
            return true;
        }
        else if (visit[x][y-1][0]){ // 기둥 위라면
            return true;
        }
        else{ // 설치조건을 만족하지 못함
            return false;
            
        }
    }
    else if (is_bo == 1){ // 보 설치
        if (visit[x][y-1][0] || visit[x+1][y-1][0]){ // 한쪽 끝 부분이 기둥위에 있거나
            return true;
        }
        else if (visit[x-1][y][1] && visit[x+1][y][1]){ // 양쪽 끝 부분이 다른 보와 동시에 연결되어 있거나
            return true;
        }
        else{ // 설치조건을 만족하지 못함
            return false;
            
        }
    }
}
bool can_delete(int x, int y, int is_bo, vector<vector<vector<int>>>& visit){
    visit[x][y][is_bo] = 0; // 일단 삭제해 본다
    bool flag = true;

    if (is_bo == 0){ // 기둥 삭제
        if (visit[x][y+1][0] && !is_valid(x, y+1, 0, visit)) flag = false;   // 위의 기둥 (의존 기둥)
        if (visit[x][y+1][1] && !is_valid(x, y+1, 1, visit)) flag = false;   // 위 오른쪽 보 (의존 보)
        if (visit[x-1][y+1][1] && !is_valid(x-1, y+1, 1, visit)) flag = false; // 위 왼쪽 보 (의존 보)
    }
    else{ // 보 삭제
        if (visit[x][y][0] && !is_valid(x, y, 0, visit)) flag = false;       // 왼쪽 끝 위의 기둥
        if (visit[x+1][y][0] && !is_valid(x+1, y, 0, visit)) flag = false;   // 오른쪽 끝 위의 기둥
        if (visit[x-1][y][1] && !is_valid(x-1, y, 1, visit)) flag = false;   // 왼쪽 보
        if (visit[x+1][y][1] && !is_valid(x+1, y, 1, visit)) flag = false;   // 오른쪽 보
    }

    visit[x][y][is_bo] = 1; // 원상복구 (실제 삭제는 메인 루프에서)
    return flag;
}
vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    vector<vector<vector<int>>> visit(
        n+3, vector<vector<int>>(n+3, vector<int>(2, 0))
    );
    // visit[3][2][1] = 1;
    for (auto ele : build_frame){
        int x = ele[0] + 1; // 오프셋
        int y = ele[1] + 1;

        if (ele[2] == 0){ // 기둥이라면
            if (ele[3] == 1){ // 설치라면
                if (is_valid(x, y, 0, visit)) visit[x][y][0] = 1; // 설치
            }
            else if (ele[3] == 0){ // 삭제라면
                if (can_delete(x, y, 0, visit)) visit[x][y][0] = 0; // 삭제
            }
        }
        else if (ele[2] == 1){ // 보라면
            if (ele[3] == 1){ // 설치라면
                if (is_valid(x, y, 1, visit)) visit[x][y][1] = 1; // 설치
            }
            else if (ele[3] == 0){ // 삭제라면
                if (can_delete(x, y, 1, visit)) visit[x][y][1] = 0; // 삭제
            }
        }
    }
    // 애초에 x가 작은것부터, 그 다음 y가 작은것부터, 그 다음 기둥인것부터 순서대로 push하면 정렬이 따로 필요없음 
    for (int x = 1; x <= n + 1; x++){
        for (int y = 1; y <= n + 1; y++){
            for (int a = 0; a < 2; a++){
                if (visit[x][y][a]) answer.push_back({x - 1, y - 1, a});
            }
        }
    }
    return answer;
}
