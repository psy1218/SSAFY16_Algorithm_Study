#include <iostream>
using namespace std;

struct Heap {
	int heap[100001] = { 0 };
	int heap_size = 0;

	bool higherPriority(int a, int b) {
		return heap[a] >= heap[b];
	}

	void swapHeap(int a, int b) {
		int temp = heap[a];
		heap[a] = heap[b];
		heap[b] = temp;
	}

	void push(int data) {
		heap[++heap_size] = data;
		int cur = heap_size;

		while (cur > 1) {
			int parent = cur / 2;
			if (higherPriority(parent, cur)) {
				break;
			}

			swapHeap(parent, cur);
			cur = parent;
		}
	}

	int pop() {
		if (heap_size == 0) {
			return -1;
		}

		int data = heap[1];
		if (heap_size == 1) {
			heap_size--;
			return data;
		}

		heap[1] = heap[heap_size--];
		int cur = 1;

		while (1) {
			int left = cur * 2;
			int right = cur * 2 + 1;
			int best = cur;

			if (left <= heap_size && higherPriority(left, best)) {
				best = left;
			}
			if (right <= heap_size && higherPriority(right, best)) {
				best = right;
			}
			if (cur == best) {
				break;
			}

			swapHeap(best, cur);
			cur = best;
		}

		return data;
	}

	
};

Heap heap;
int main(int argc, char** argv) {

  // 시간 초과 방지용
  ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int test_case;
	int T;
	int N;
	int command;
	int data;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case) {
		cout << "#" << test_case << " ";

		cin >> N;
		heap.heap_size = 0;
		for (int i = 0; i < N; i++) {
			cin >> command;

			if (command == 1) {
				cin >> data;
				heap.push(data);

			}
			else {
				data = heap.pop();
				cout << data << " ";
			}
		}
		cout << "\n";
	}

	return 0;
}
