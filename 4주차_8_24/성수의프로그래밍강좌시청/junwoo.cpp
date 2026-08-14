#include<iostream>

using namespace std;

struct PriorityQueue{

    float heap[300] = {0};
    int heap_size = 0;

    bool higherPriority(int a, int b){
        return heap[a] > heap[b];
    }

    void swapHeap(int a, int b){
        float temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }

    void push(float data){
        heap[++heap_size] = data;
        int cur = heap_size;

        while (cur > 1){
            int parent = cur / 2;
            if (higherPriority(parent, cur)){
                break;
            }

            swapHeap(parent, cur);
            cur = parent;
        }
    }

    float pop(){
        if (empty()){
            return -1;
        }

        float data = heap[1];
        if (heap_size == 1){
            heap_size--;
            return data;
        }

        heap[1] = heap[heap_size--];
        int cur = 1;

        while (1){
            int left = cur * 2;
            int right = cur * 2 + 1;
            int best = cur;

            if (left <= heap_size && higherPriority(left, best)){
                best = left;
            }
            if (right <= heap_size && higherPriority(right, best)){
                best = right;
            }
            if (best == cur){
                break;
            }

            swapHeap(best, cur);
            cur = best;
        }

        return data;
    }

    bool empty(){
        if (heap_size == 0){
            return true;
        }
        return false;
    }

    float top(){
        if (heap_size == 0){
            return -1;
        }
        return heap[1];
    }
};

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{

		int N;
        int K;
        PriorityQueue max_heap;
        PriorityQueue min_heap;
        float lecture = 0;
        float answer = 0;

        cin >> N >> K;

        for (int i = 0; i < N; i++){
            cin >> lecture;
            max_heap.push(lecture);
        }

        for (int i = 0; i < K; i++){
            min_heap.push(-max_heap.pop());
        }

        while (!min_heap.empty()){
            float new_lecture = -min_heap.pop();

            answer = (answer + new_lecture) / 2;
        }
        
        cout << "#" << test_case << " " << answer << "\n";

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
