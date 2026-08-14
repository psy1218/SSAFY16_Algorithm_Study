#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Car{
    // Car 정보 저장하는 구조체
    int start = -30001;
    int end = 30001;
};

struct PriorityQueue{
    // 우선순위 큐 구현 -> Heap으로 구현
    Car* heap[10001];
    int heap_size = 0;
    
    bool higherPriority(Car* a, Car* b){
        // end 지점을 기준으로 정렬을 진행하는 함수
        // end 지점을 기준으로 하는 이유는 마지막 지점이 더 작은 차량 이후에 나오는 차량들은 모두 end 지점이 더 크거나 같을 것이며
        // 이렇게 정렬 후 카메라의 위치를 end 지점에 설치한 후 이후 차량의 시작점을 비교하여 camera 설치 여부를 조절하면 되기 때문
        return a->end < b->end;
    }
    
    void swapHeap(int a, int b){
        // heap에서 두 차량의 위치를 변경하는 함수
        Car* temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }
    
    void push(Car* car){
        // heap에 차량을 넣는 함수
        heap[++heap_size] = car;
        int cur = heap_size;
        while (cur > 1){
            int parent = cur / 2;
            if (higherPriority(heap[parent], heap[cur])){
                break;
            }
            
            swapHeap(parent, cur);
            cur = parent;
        }
        
    }
    
    Car* pop(){
        // heap 에서 첫 번째 차량(우선순위 가장 높은)을 추출하는 함수
        if (heap_size == 0){  // 차량 없으면 nullptr 반환
            return nullptr;
        }

        // 차량이 있을 때 첫번째 차량이 우선순위 가장 높음
        Car* car = heap[1];

        // heap의 size가 1이면 아래 연산 필요 없이 바로 차량만 넘기면 됨
        if (heap_size == 1){
            heap_size--;
            return car;
        }
        
        heap[1] = heap[heap_size--];
        int cur = 1;
        
        while (1){
            int left = cur * 2;
            int right = cur * 2 + 1;
            int best = cur;
            
            if (left <= heap_size && higherPriority(heap[left], heap[best])){
                best = left;
            }
            if (right <= heap_size && higherPriority(heap[right], heap[best])){
                best = right;
            }
            if (best == cur){
                break;
            }
            
            swapHeap(cur, best);
            cur = best;
        }
        
        return car;
        
    }
    
    Car* top(){
        // heap에서 가장 위에 있는 차량 반환
        if (heap_size == 0){
            return nullptr;
        }
        
        return heap[1];
    }
    
    int size(){
        // heap의 크기 반환
        return heap_size;
    }
    
    bool empty(){
        // heap이 비어있으면 true 비어있지 않으면 false
        if (heap_size == 0){ return true; }
        return false;
    }
};

int solution(vector<vector<int>> routes) {
    int answer = 0;
    PriorityQueue pq;
    
    for (int i = 0; i < routes.size(); i++){
        Car* new_car = new Car;
        new_car->start = routes[i][0];
        new_car->end = routes[i][1];
        
        pq.push(new_car);
    }
    
    int camera = -30001;
    // end 지점을 기준으로 확인하면서 정렬 후 차례대로 pop하며 start지점이 camera 보다 크면
    // camera를 end 지점에 설치
    while (!pq.empty()){
        Car* car = pq.pop();
        if (camera < car->start){
            camera = car->end;
            answer++;
        }
    }
    
    return answer;
}
