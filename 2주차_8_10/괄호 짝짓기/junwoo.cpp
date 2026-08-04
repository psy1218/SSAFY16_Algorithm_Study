#include <iostream>
using namespace std;

// Stack 구현
struct stack {
    char arr[10000];
    int last;

    void init() {
        last = -1;
    }

    void push(char data){
        arr[++last] = data;
    }

    bool empty(){
        return (last < 0);
    }

    char pop() {
        if (empty()) {
            return '!';
        }

        return arr[last--];
    }

    int size() {
        return last + 1;
    }

    int top() {
        if (empty()) { return '!'; }
        return arr[last];
    }
};

int main(int argc, char** argv)
{
	int test_case;
	int T = 0;

  string line;
  int str_len;
  
  while (cin >> str_len >> line) {
      T++;

      stack s;    // stack 선언
      s.init();   // stack 초기화

      for (int i=0; i < str_len; i++){
          // stack 비어 있으면 데이터 push
          if (s.empty() == '!'){
              s.push(line[i]);
              continue;
          }

          // 비어 있지 않을 때, stack의 탑과 같으면 pop()
          if (s.top() == '(' && line[i] == ')'){
              s.pop();
          }
          else if (s.top() == '[' && line[i] == ']'){
              s.pop();
          }
          else if (s.top() == '{' && line[i] == '}'){
              s.pop();
          }
          else if (s.top() == '<' && line[i] == '>'){
              s.pop();
          }
          // 다르면 push()
          else {
              s.push(line[i]);
          }

      }

      cout << "#" << T << " ";
      if (!s.empty()) {
          cout << "0\n";
      }
      else {
          cout << "1\n";
      }

  }

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
