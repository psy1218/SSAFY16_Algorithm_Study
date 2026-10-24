#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct car{
    long long t;
    char w;
    int number;
};

int N;
vector<car>Info;
long long Time = 0;

queue<int>A; // 북
queue<int>B; // 동
queue<int>C; // 남
queue<int>D; // 서 

vector<int>res;


void Input(){
        
    cin >> N;

    for(int i=0;i<N;i++){
        long long t;
        char w;
        cin >> t >> w;
        Info.push_back({t, w, i});
    }

    //sort(Info.begin(), Info.end());
}

void Output(){

    for(auto it : res){
        cout << it << "\n";
    }
}

void Insert(int n){
    if(Info[n].w == 'A') A.push(Info[n].number);
    if(Info[n].w == 'B') B.push(Info[n].number);
    if(Info[n].w == 'C') C.push(Info[n].number);
    if(Info[n].w == 'D') D.push(Info[n].number);
}

void Insert_debug(int n){
    if(Info[n].w == 'A') {
        cout << "A교차로 진입: " << Info[n].number << "\n";
        A.push(Info[n].number);
    }
    if(Info[n].w == 'B') {
        cout << "B교차로 진입: " << Info[n].number << "\n";
        B.push(Info[n].number);
    }
    if(Info[n].w == 'C') {
        cout << "C교차로 진입: " << Info[n].number << "\n";
        C.push(Info[n].number);
    }
    if(Info[n].w == 'D') {
        cout << "D교차로 진입: " << Info[n].number << "\n";
        D.push(Info[n].number);
    }
}

void Right_Check(){

    vector<int>flag(4, 0);

    // 오른쪽에 차량이 없다고 바로 빠져나가면 안 됨. 동서남북 다 본 후에, 가능한 차량만 빠져나가야함. 바로 처리하면 다음 차량에 영향을 줌. 
    if(!A.empty() && D.empty()) flag[0] = 1;
    if(!B.empty() && A.empty()) flag[1] = 1;
    if(!C.empty() && B.empty()) flag[2] = 1;
    if(!D.empty() && C.empty()) flag[3] = 1;

    int num = 0 ; // 차량 번호 

    if(flag[0] == 1) {
        num = A.front(); 
        res[num] = Time;
        A.pop(); 
    }
    if(flag[1] == 1) {
        num = B.front(); 
        res[num] = Time;
        B.pop(); 
    }
    if(flag[2] == 1) {
        num = C.front(); 
        res[num] = Time;
        C.pop(); 
    }
    if(flag[3] == 1) {
        num = D.front(); 
        res[num] = Time;
        D.pop(); 
    }
    
}


void full(){
    while(!A.empty()){
        res[A.front()] = -1;
        A.pop();
    }

    while(!B.empty()){
        res[B.front()] = -1;
        B.pop();
    }

    while(!C.empty()){
        res[C.front()] = -1;
        C.pop();
    }

    while(!D.empty()){
        res[D.front()] = -1;
        D.pop();
    }
}

void exist(){

    cout << "\nA 차량 : ";
    if(!A.empty()){
        cout << A.front() << " ";
    }
    cout << "\nB 차량 : ";
    if(!B.empty()){
        cout << B.front()  << " ";
    }
    cout << "\nC 차량 : ";
    if(!C.empty()){
        cout << C.front()  << " ";
    }
    cout << "\nD 차량 : ";
    if(!D.empty()){
        cout << D.front()  << " ";
    }
    cout << "\n";
}

void Func(){

    Time = Info[0].t;
    int index = 0;

    res.assign(N, -1); // 교차로 full이 되더라도, 진입하기 전 차량들도 -1이 되어야 해서 미리 -1 로 set . 

    // timer
    while(1){
        // 교차로에 차량이 전부 있을 떄 
        if (!A.empty() && !B.empty() && !C.empty() && !D.empty()) {
            //cout << "FULL\n" ; 
            full();
            break;
        }

        // 차량 삽입 -> index 범위 넘어가도 while 중단 x : 왜냐하면 교차로 빠져나오는 시간도 재야함.
        if(index < N) {
            // 교차로 진입 시간과 현재 시간이 동일하면, 교차로 queue에 삽입.
            if(Time == Info[index].t){
                // 동일한 시간에 여러 차량이 들어올 경우 while 문 
                while(1){
                    if(index >= N ) break;
                    if(Time != Info[index].t) break;

                    Insert(index);        
                    //Insert_debug(index);

                    index++;
                }
            }
        }

        //cout << "Time: " << Time << "\n";
        //exist();

        // 4교차로를 검사하면서 오른쪽에 차가 있는지 검사.
        Right_Check();

        Time++;
        //Output();

        // 모든 차량이 진입을 다 했으면서, 교차로에 차량이 다 빠져나가면
        if (index >= N && A.empty() && B.empty() && C.empty() && D.empty()) break;

        // 차량이 다 진입 안 했는데, 교차로에 차량이 다 빠져나가면 -> 그 다음 차량 시간으로 건너뛰기 해야함. Time++ 은 시간초과 -> 하나씩 살펴봐야함. 
        // 차량이 2대인데 시간초가 10억이면 10억 기다려야함. 차량이 최대 200,000임. 최대로 1초씩 들어온다고 해도 이건 괜찮음.  
        if (index < N && A.empty() && B.empty() && C.empty() && D.empty()) Time = Info[index].t;
    }

}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Input();

    Func();

    Output();
    return 0;
}


/*

입력

6
0 A
0 B
0 C
2 D
2 C
4 B
출력

0
1
2
4
3
4



예제 2
입력

6
0 A
0 C
1 A
1 B
1 C
1 D
출력

0
0
-1
-1
-1
-1

  0         1   
  1         3
        6       4 
  2         5
*/
