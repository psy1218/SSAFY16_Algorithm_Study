#include <iostream>

using namespace std;

int n, k;
int grid[100][100];
int r, c;

struct Node{
    int r = -1;
    int c = -1;
    Node* next = nullptr;
    Node* prev = nullptr;
};

struct Cell{
    int r = -1;
    int c = -1;
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
            if (empty()){
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

Cell BFS(int r, int c){
    Queue queue;
    bool visited[100][100] = {false};
    int cur_num = grid[r][c];
    int max_num = -1;
    Cell result;
    result.r = r;
    result.c = c;

    queue.push(r, c);
    visited[r][c] = true;

    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, -1, 0, 1};

    while (!queue.empty()){
        Node cur_node = queue.pop();
        int cur_r = cur_node.r;
        int cur_c = cur_node.c;

        for (int i = 0; i < 4; i++){
            int nr = cur_r + dr[i];
            int nc = cur_c + dc[i];

            if (nr < 0 || nr >= n || nc < 0 || nc >= n || grid[nr][nc] >= cur_num || visited[nr][nc]){
                continue;
            }

            visited[nr][nc] = true;
            queue.push(nr, nc);

            if (grid[nr][nc] > max_num){
                max_num = grid[nr][nc];
                result.r = nr;
                result.c = nc;
            }
            else if(grid[nr][nc] == max_num){
                if (result.r > nr){
                    result.r = nr;
                    result.c = nc;
                }
                else if(result.r == nr && result.c > nc){
                    result.r = nr;
                    result.c = nc;
                }
            }
            
        }

    }

    return result;
}

int main() {
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    cin >> r >> c;
    r--;
    c--;

    // Please write your code here.
    Cell result;
    for (int i = 0; i < k; i++){
        result = BFS(r, c);
        r = result.r;
        c = result.c;

        if (r == -1 || c == -1){
            break;
        }

    }
    
    cout << r+1 << " " << c+1;

    return 0;
}
