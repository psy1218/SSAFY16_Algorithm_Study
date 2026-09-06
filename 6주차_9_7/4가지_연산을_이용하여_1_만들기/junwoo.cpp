#include <iostream>

using namespace std;

int N;

struct Node{
    int data = -1;
    Node* next = nullptr;
    Node* prev = nullptr;
};

class Queue{
    private:
        int q_size = 0;
        Node* head = nullptr;
        Node* tail = nullptr;

    public:
        bool empty(){
            return q_size == 0;
        }

        void push(int data){
            Node* new_node = new Node;
            new_node->data = data;

            if (q_size == 0){
                head = new_node;
                tail = new_node;
            }
            else{
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;
            }

            q_size++;
        }

        Node pop(){
            if (empty()){
                return {-1, nullptr, nullptr};
            }

            Node* target = head;
            Node result;
            result.data = target->data;

            if (q_size == 1){
                head = nullptr;
                tail = nullptr;
            }
            else{
                head = head->next;
                head->prev = nullptr;
            }

            delete target;
            q_size--;

            return result;
        }
};

int main() {
    cin >> N;

    // Please write your code here.
    int dist[1000010] = {-1};
    for (int i = 0; i < 1000010; i++){
        dist[i] = -1;
    }
    Queue queue;

    queue.push(N);
    dist[N] = 0;

    while (!queue.empty()){
        Node cur_node = queue.pop();
        int cur_data = cur_node.data;

        if (cur_data == 1){
            break;
        }

        int temp[4] = {-1, -1, -1, -1};
        temp[0] = cur_data - 1;
        temp[1] = cur_data + 1;
        
        if (cur_data % 2 == 0){
            temp[2] = cur_data / 2;
        }
        if (cur_data % 3 == 0){
            temp[3] = cur_data / 3;
        }

        for (int i = 0; i < 4; i++){
            int n_data = temp[i];
            if (n_data > 1000001 || n_data < 0 || dist[n_data] != -1){
                continue;
            }

            dist[n_data] = dist[cur_data] + 1;
            queue.push(n_data);


        }
    }

    cout << dist[1];


    return 0;
}
