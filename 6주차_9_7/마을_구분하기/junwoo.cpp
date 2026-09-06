#include <iostream>
#include <algorithm>

using namespace std;

int n;
int grid[25][25];
bool visited[25][25];

struct Node{
    int r = -1;
    int c = -1;
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

        int size(){
            return q_size;
        }

        void push(int r, int c){
            Node* new_node = new Node;
            new_node->r = r;
            new_node->c = c;

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
            
            if (q_size == 0){
                return {-1, -1, nullptr, nullptr};
            }

            Node* target = head;
            Node result;
            result.r = target->r;
            result.c = target->c;

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

int BFS(int cur_r, int cur_c, int n){
    int count = 0;

    Queue queue;
    queue.push(cur_r, cur_c);
    visited[cur_r][cur_c] = true;
    count++;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (!queue.empty()){
        Node cur_node = queue.pop();
        int cur_r = cur_node.r;
        int cur_c = cur_node.c;

        for (int i = 0; i < 4; i++){
            int nr = cur_r + dr[i];
            int nc = cur_c + dc[i];

            if (nr < 0 || nr >= n || nc < 0 || nc >= n || visited[nr][nc] || !grid[nr][nc]){
                continue;
            }

            visited[nr][nc] = true;
            queue.push(nr, nc);

            count++;

        }

    }
    return count;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            visited[i][j] = false;
        }
    }

    // Please write your code here.
    int n_village = 0;
    int n_people[10001] = {0};

    for (int r = 0; r < n; r++){
        for (int c = 0; c < n; c++){
            if (grid[r][c] == 1 && !visited[r][c]){
                n_people[n_village++] = BFS(r, c, n);
            }
        }
    }

    int* temp = new int[n_village];
    for (int i = 0; i < n_village; i++){
        temp[i] = n_people[i];
    }
    
    sort(temp, temp + n_village);

    cout << n_village << "\n";
    for (int i = 0; i < n_village; i++){
        cout << temp[i] << "\n";
    }

    return 0;
}
