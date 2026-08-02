#include <string>
#include <set>
#include <iostream>
using namespace std;

pair<pair<int,int>, pair<int,int>> xy(char option, int x, int y){
    pair<pair<int,int>, pair<int,int>> temp;
    
    if(option == 'U'){
        temp = {{x,y},{x,y+1}};
    }
    if(option == 'D'){
        temp = {{x,y},{x,y-1}};
    }
    if(option == 'L'){
        temp = {{x,y},{x-1,y}};
    }
    if(option == 'R'){
        temp = {{x,y},{x+1,y}};
    }
    
    return temp;
}

int solution(string dirs) {
    int answer = 0;
    
    set<pair<pair<int,int>, pair<int,int>>>visited;
    
    int x1 = 0, y1 = 0, nx, ny;
    for(int i=0;i<dirs.size();i++){ 

        // 출발지, 도착 지점 위치
        pair<pair<int,int>, pair<int,int>>road = xy(dirs[i], x1,y1);
        
        //cout << i << " || " << road.first.first << " " << road.first.second << " "  << road.second.first << " " << road.second.second << '\n';
        
        // 도착 지점 범위 확인 
        if( road.second.first < -5 || road.second.first > 5 || road.second.second < -5 || road.second.second > 5) continue; // x,y 둘 다 범위 확인 
        nx = road.second.first;
        ny = road.second.second;
        
        if(visited.count(road) == 0){ // visited 에 없으면 경로 추가
            answer++;
            
            // 왕복 경로 추가 
            visited.insert({{x1,y1}, {nx,ny}});
            visited.insert({{nx,ny}, {x1,y1}});
        }
        
        // 목적지를 출발지로 변경 
        x1 = nx;
        y1 = ny;
    }
    
    
    return answer;
}

// 초기 생각 -> vector 활용해서 출발지, 이동 지점 pair로 (양방향) 저장해서 for문으로 방문했는지 확인
// 개선안 -> set 활용해서 정렬된 원소들을 빠르게 접근해서 방문했는지 찾기. 지금 범위가 작아서 vector도 괜찮지만 커지면 시간초과. 