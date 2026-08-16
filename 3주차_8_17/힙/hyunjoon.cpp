#include<iostream>
using namespace std;

#define MAX_N (100000 + 1)

int heap_Idx = 0;


void swap(int* a, int* b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}

// heap_Idx는 insert할 때 마다 하나씩 늘어남
void h_insert(int num, int *heap) {
	int Idx = ++heap_Idx;
	heap[Idx] = num;
	// 인덱스가 1이 아니고(최상위 노드), 넣으려는 숫자가 지금 노드의 부모보다 크면 swap
	while ((Idx != 1) && (num > heap[Idx / 2])) {
		swap(&heap[Idx], &heap[Idx / 2]);
		Idx = Idx / 2;
	}
}
// 가장 큰 수를 삭제시키고 heap을 재정렬한다
int h_delete(int *heap) {
	if (heap[1] == 0) return -1;
	int result = heap[1];
	heap[1] = heap[heap_Idx];
	heap[heap_Idx] = 0;
	heap_Idx--;
	int parent = 1;
	int child = 0;
	while (1) {
		child = parent * 2;
		// 자식 노드 중 오른쪽 큰지 왼쪽 큰지
		if (child + 1 <= heap_Idx && heap[child] < heap[child + 1]) child++;
		if (child > heap_Idx || heap[child] < heap[parent]) break;
		swap(&heap[child], &heap[parent]);
		parent = child;
	}
	return result;
}

int main(int argc, char** argv)
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int test_case;
	int T;
	
	//freopen("input.txt", "r", stdin);
	cin >> T;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cout << "#" << test_case << ' ';
		int heap[MAX_N] = {0};
		heap_Idx = 0;
		int N;
		cin >> N;
		for (int i = 0; i < N; i++) {
			int mode = 0;
			cin >> mode;

			if (mode == 1) {
				int num = 0;
				cin >> num;

				h_insert(num, heap);
			}

			if (mode == 2) {
				int ans = h_delete(heap);
				cout << ans << ' ';
			}

		}
		cout << '\n';

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
