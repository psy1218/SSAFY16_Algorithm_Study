#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Process{
    int loc;
    int rank;
};

struct Queue{
    Process q[100011];
    int front = 0;
    int rear = 0;
    int rank_count[10] = {0};
    int size = 0;
    
    void init(vector<int> priorities){
        for (int i = 0; i < priorities.size(); i++){
            Process new_process;
            new_process.loc = i;
            new_process.rank = priorities[i];
            
            push(new_process);
        }
    }
    
    void push(Process data){
        q[rear++] = data;
        rank_count[data.rank]++;
        size++;
    }
    
    Process pop(){
        if (empty()){
            return {-1, -1};
        }
        
        Process data = q[front++];
        rank_count[data.rank]--;
        size--;
        
        return data;
    }
    
    bool empty(){
        if (size == 0) {
            return true;
        }
        return false;
    }
    
    bool check(Process data){
        for (int i = 9; i > data.rank; i--){
            if (rank_count[i]){
                return false;
            }
        }
        
        return true;
    }
};

int solution(vector<int> priorities, int location) {
    int answer = 0;
    
    Queue queue;
    queue.init(priorities);
    
    while (1){
        Process data = queue.pop();
        if (queue.check(data)){
            if (data.loc == location){ return answer + 1; }
            answer++;
            continue;
        }
        queue.push(data);
        
    }
    
    
    return answer;
}
