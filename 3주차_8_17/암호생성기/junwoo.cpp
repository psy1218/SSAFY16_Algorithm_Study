#include <iostream>
using namespace std;

struct Node {
	int value = -1;
	Node* next = nullptr;
};

struct Queue {
	Node* start = nullptr;

	void init(){
		Node* cur = nullptr;

		for (int i = 0; i < 8; i++) {
			Node* node = new Node;
			cin >> node->value;
			node->next = nullptr;
			
			if (start == nullptr) {
				start = node;
				cur = node;
				continue;
			}

			cur->next = node;
			cur = node;
		}
	}

	void push(Node* data) {
		Node* end = start;
		while (end->next != nullptr) {
			end = end->next;
		}

		end->next = data;
	}

	Node* pop() {
		Node* data = start;
		start = data->next;
		data->next = nullptr;

		return data;
	}

	Node* top() {
		return start;
	}
};

int main(int argc, char** argv) {
	int test_num;

	for (int i = 0; i < 10; i++) {
		cin >> test_num;
		Queue queue;
		int clock = 1;

		queue.init();
		while (1) {
			Node* data = queue.pop();
			data->value = max(0, data->value - clock++);
			queue.push(data);

			if (data->value == 0) {
				break;
			}

			if (clock == 6) { clock = 1; }
		}

		cout << "#" << test_num << " ";
		Node* cur = queue.start;
		while (cur != nullptr) {
			cout << cur->value << " ";
			cur = cur->next;
		}
		cout << "\n";

	}
}
