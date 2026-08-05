#include <string>
#include <vector>
#include <iostream>

using namespace std;

// LinkedList를 위한 Node
struct Node{
    // params:
    //     prev(int): 현재 Node 바로 이전의 유효한 행 index
    //     next(int): 현재 Node  바로 이후의 유요한 행 index
    //     cur(int): 현재 Node 행 index
    //     valid(bool): 현재 Node(행)이 제거되었는지 판단
    int prev = -1;
    int next = -1;
    int cur = -1;
    bool valid = false;
};

// 복구를 구현하기 위한 스택
struct Stack{
    Node arr[1000000];
    int last;
    
    void init(){ last = -1; }
    
    void push(Node data){ arr[++last] = data; }
    
    Node pop(){ return arr[last--]; }
};

// 표를 의미하는 구조체 객체
struct Table{
    int row_count;  // table 전체 행의 수
    int cur_k;      // 현재 위치한 row의 위치 idx
    int last;       // 현재 table에서 마지막 위치 idx
    Stack stack;    // Restore를 위한 함수
    Node table[1000000];
    
    void init(int n, int k){
        row_count = n;
        cur_k = k;
        last = n-1;
        stack.init();

        for (int i=0; i<row_count; i++){
            table[i].valid = true;
            table[i].cur = i;
            if (i==0){ table[i].next = i+1; }
            else if(i==row_count-1){ table[i].prev = i-1; }
            // Node끼리 서로 연결
            else{
                table[i].next = i+1;
                table[i].prev = i-1;
            }
        }
    }
    
    bool check_last(){
        // summary:
        //     가독성을 위해 만든 함수로 이후 Delete할 때 현재 포인터(k)가 마지막에 위치하는지 판단
        return cur_k == last;
    }
    
    void Down(int offset){
        // summary:
        //      현재 위치에서 offset 만큼 내림
        // params:
        //      offset(int): 얼마나 이동할지 의미하는 값
        while (offset){
            cur_k = table[cur_k].next;
            offset--;
        }
    }
    
    void Up(int offset){
        // summary:
        //      현재 위치에서 offset 만큼 올림
        //      없는 행은 과감히 넘겨야 함
        // params:
        //      offset(int): 얼마나 이동할지 의미하는 값
        
        while (offset){
            cur_k = table[cur_k].prev;
            offset--;
        }
    }
    
    void Delete(){
        // summary:
        //      해당 행을 제거하는 함수
        //      제거 한 후 다음에 존재하는 행으로 이동, 만약 없다면 바로 위 존재하는 행으로 이동
        //      제거 후 prev - next 노드를 이어야 함
        
        // 현재 노드의 prev, next 노드가 무엇인지 확인
        int prev = table[cur_k].prev;
        int next = table[cur_k].next;

        // prev, next node 서로 연결
        table[prev].next = table[next].cur;
        table[next].prev = table[prev].cur;

        // 지우고 stack에 집어넣음
        table[cur_k].valid = false;
        stack.push(table[cur_k]);

        // 마지막이면 포인터(k)를 이전 행으로
        if (check_last()){
            cur_k = prev;
            last = cur_k;
        }
        // 아니면 포인터(k)를 그 다음 행으로
        else{
            cur_k = next;
        }
        

    }
    
    void Restore(){
        // summary:
        //      복구하는 함수
        //      스택에서 node 추출한 후, 추출한 node 기준 prev, node를 다시 수정
        Node restore_node = stack.pop();
        table[restore_node.prev].next = restore_node.cur;
        table[restore_node.next].prev = restore_node.cur;
        table[restore_node.cur].valid = true;

        // 만약 복구되는 행이 현재 포인터(k) 뒤에 위치한다면
        // check_last() 함수를 위해 last를 복구된 행의 idx로 변경
        if (restore_node.cur > last) { last = restore_node.cur; }
    }
    
};

string solution(int n, int k, vector<string> cmd) {
    string answer = "";
    Table t;
    
    // table 객체 초기화
    t.init(n, k);
    
    for (string command: cmd){
        if(command[0] == 'U'){ t.Up(stoi(command.substr(2, size(command)-2))); }
        else if(command[0] == 'D'){ t.Down(stoi(command.substr(2, size(command)-2))); }
        else if(command[0] == 'C'){ t.Delete(); }
        else if(command[0] == 'Z'){ t.Restore(); }
    }
    
    for (int i=0; i<t.row_count; i++){
        if(t.table[i].valid){ answer += 'O'; }
        else{ answer += 'X'; }
    }
    
    return answer;
}
