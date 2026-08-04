#include <iostream>
// #include <cstdio>
using namespace std;

// char형 스택
struct Cstack {
    char arr[100];
    int last;

    void init(){
        last = -1;
    }

    // Push 함수
    void push(char data){
        arr[++last] = data;
    }

    // Empty 함수
    bool empty(){
        if (last == -1){
            return true;
        }
        return false;
    }

    // Pop 함수
    char pop(){
        if (empty()){
            return '!';
        }
        return arr[last--];
    }

    // Size 함수
    int size(){
        return last + 1;
    }

    // Top 함수
    char top(){
        if (empty()){
            return '!';
        }
        return arr[last];
    }
};

// int형 스택
struct Istack {
    int arr[100];
    int last;

    void init(){
        last = -1;
    }

    // Push 함수
    void push(int data){
        arr[++last] = data;
    }

    // Empty 함수
    bool empty(){
        if (last == -1){
            return true;
        }
        return false;
    }

    // Pop 함수
    int pop(){
        if (empty()){
            return -1;
        }
        return arr[last--];
    }

    // Size 함수
    int size(){
        return last + 1;
    }

    // Top 함수
    int top(){
        if (empty()){
            return -1;
        }
        return arr[last];
    }
};

int map_operator(char oper){
    // summary: 
    //      oper의 비교를 위한 숫자 맵핑 함수
    // params: 
    //      oper(char): operator
    // return:
    //      result(int): (: 1 / +: 2 / *: 3
    if (oper == '('){ return 1; }
    if (oper == '+'){ return 2; }
    if (oper == '*'){ return 3; }

    return 0;
}

bool rank_operator(char oper1, char oper2){
    // summary: 
    //      oper1과 oper2간 우선순위를 비교하는 함수
    // params: 
    //      oper1(char): 현재 연산자
    //      oper2(char): 스택에 있는 연산자
    // return:
    //      result(bool): oper1 > oper2이면 true, 반대면 false

    return map_operator(oper1) > map_operator(oper2);
}

int ctoi(char num){
    // summary:
    //      char num을 int형으로 변환하는 함수
    // params:
    //      num(char): char형 숫자
    // return:
    //      result(int): 변환한 int형 숫자
    return num - '0';
}

int calculate(int num1, int num2, char oper){
    // summary:
    //      num1과 num2 계산하는 함수
    // params:
    //      num1(int): 숫자 1
    //      num2(int): 숫자 2
    //      oper(char): 연산자
    // return:
    //      result(int): 계산한 결과
    if (oper == '+') {return num1 + num2;}
    if (oper == '*') {return num1 * num2;}
}

int main(int argc, char** argv)
{
	int test_case;
	int T = 0;
    // freopen("C:/Users/SSAFY/Desktop/Junwoo/coding_test/SWEA/input.txt", "r", stdin);
    

    string equation;
    string postfix;
    int eq_len;
    
    while (cin >> eq_len >> equation) {
        // 초기화
        T++;
        postfix = "";
        Cstack s_operator;
        Istack s_num;
        char cur_oper;
        int num1;
        int num2;

        s_operator.init();
        s_num.init();

        // 후위연산식 변경
        for (int i=0; i<eq_len; i++){
            // 숫자면 postfix에 그대로 추가
            if ('0' <= equation[i] && equation[i] <= '9'){
                postfix += equation[i];
                continue;
            }
            // 그 외엔 stack에 operator 추가 (우선순위 고려 필요)
            // s_operator 비어있으면 operator 추가
            if (s_operator.empty()){
                s_operator.push(equation[i]);
                continue;
            }
            // 비어 있지 않을 때
            // '('면 그냥 push
            if (equation[i] == '('){
                s_operator.push(equation[i]);
            }
            // ')'면 '('가 나올 때까지 pop()
            else if (equation[i] == ')'){
                while(s_operator.top() != '('){ postfix += s_operator.pop(); }
                s_operator.pop();   // '(' 남아있는 것 제거
            }
            // 나머지는 우선순위 고려해서 우선 순위 높으면 push 아니면 높아질때까지 pop() [단, 비게 될 경우 push]
            else{
                while(!s_operator.empty() && !rank_operator(equation[i], s_operator.top())){ postfix += s_operator.pop(); }
                s_operator.push(equation[i]);
            }
            
        }
        while(!s_operator.empty()){
            postfix += s_operator.pop();
        }

        // 후위연산식 계산
        for (char c: postfix){
            // 숫자일 때는 계속 push
            if ('0' <= c && c <= '9'){
                s_num.push(ctoi(c));
                continue;
            }

            // 연산자일 때는 앞에 2개 계산 후 계산 값 push
            num1 = s_num.pop();
            num2 = s_num.pop();
            s_num.push(calculate(num1, num2, c));
        }

        cout << "#" << T << " " << s_num.pop() << "\n";
    }  
}
