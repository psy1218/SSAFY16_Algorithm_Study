#include<iostream>

using namespace std;

struct PriorityQueue{
    int n;
    int* heap;
    int heap_size = 0;

    void init(int N){
        n = N;
        heap = new int[N+1];
    }

    bool higherPriority(int a, int b){
        return a > b;
    }

    void swapHeap(int a, int b){
        int temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }

    void push(int cost){
        heap[++heap_size] = cost;
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

    int pop(){
        if (empty()){
            return -1;
        }

        int cost = heap[1];
        if (heap_size == 1){
            heap_size--;
            return cost;
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
            if (cur == best){
                break;
            }

            swapHeap(best, cur);
            cur = best;
        }

        return cost;
    }

    int size(){
        return heap_size;
    }

    bool empty(){
        if (heap_size == 0){
            return true;
        }
        return false;
    }

    int top(){
        if (empty()){
            return -1;
        }
        return heap[1];
    }
};

int main(int argc, char** argv)
{
	int test_case;
	int T;
    int N;
	int cloth_cost;

	freopen("C:/Users/SSAFY/Desktop/Junwoo/coding_test/SWEA/input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int answer = 0;
        int clock = 0;
        PriorityQueue pq;
		cin >> N;
        pq.init(N);

        for (int i = 0; i < N; i++){
            cin >> cloth_cost;
            pq.push(cloth_cost);
        }

        while (!pq.empty()){
            clock++;
            int cur_cost = pq.pop();
            if (clock % 3 == 0){
                continue;
            }

            // cout << pq.top() << "\n";
            answer += cur_cost;
            // cout << cur_cost << " ";
        }
        // cout << "\n";
        cout << "#" << test_case << " " << answer << "\n";

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
