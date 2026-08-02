#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

int solution(string dirs) {
    int answer = 0;
    int map[21][21] = {0};
    
    queue<pair<int,int>> q;
    q.push(make_pair(10,10));
    for(int i=0; i<dirs.length(); i++){
        pair<int,int> cur = q.front();
        q.pop();
        
        int nc = cur.first;
        int nr = cur.second;
        int road_r = nr;
        int road_c = nc;
        
        if(dirs[i] == 'U'){
            road_c = nc -1;
            nc = nc - 2;
        }
        if(dirs[i] == 'D'){
            road_c = nc + 1;
            nc = nc + 2;
        }
        if(dirs[i] == 'R'){
            road_r = nr +1;
            nr = nr + 2;
        }
        if(dirs[i] == 'L'){
            road_r = nr - 1;
            nr = nr - 2;
        }
        // boudary & visited
        
        if(nc>=0 && nc<21 && nr>=0 && nr<21){
             
            q.push(make_pair(nc,nr));
            if(map[road_c][road_r] == 1) continue;
        
            map[road_c][road_r] = 1;
            answer++;
        
            continue;
        }
        q.push(cur);
        
    }
    
    
    return answer;
}
