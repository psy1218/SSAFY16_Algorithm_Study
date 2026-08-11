#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

bool cmp(int a, int b){
    
    return a > b;
}

int solution(vector<int> priorities, int location) {
    
    int answer = 0;
    
    queue<pair<int,int>>q;
    for(int i=0;i<priorities.size();i++){
        q.push({priorities[i], i});
    }
    
    int index = 0;
    sort(priorities.begin(), priorities.end(), cmp);
    
    while(!q.empty()){
        auto cur = q.front();
        int cur_value = cur.first;
        int cur_index = cur.second;
        
        if(priorities[index] == cur_value){
            q.pop();
            answer++;
            index++;
            
            if(cur_index == location) {
            return answer;
            }
        }
        else{
            q.pop();
            q.push(cur);
        }
               
    }
 
    return answer;
}


/*

처음에 우선순위 큐로 풀 계획이었음.
[1, 1, 9, 1, 9, 1]
9,-2
9,-4
1,0
1,-1
1,-3
1,-5

-> 이렇게 pq에 들어가있으면 현재 내 값이 9,4 일 때 다음 1의 인덱스는 5가 되는 처리되어야함.
과정 구현 아이디어.. 마땅히 좋은게 생각이 안 남. while 문 밖에 생각이 안 남.
그래서 그냥 큐랑 정렬 사용해서  비교하면서 결과 출력할 수 있도록 함. 




[2, 1, 3, 2]

3 2 2 1

[1, 1, 9, 1, 1, 1]

9 1 1 1 1 1

*/