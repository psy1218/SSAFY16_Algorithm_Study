#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

int N, M, K;
int numbers_2d[100][100];
bool bomb() {
    bool is_bombed = false;
    for (int i = 0; i < N; i++) { // 모든 열에 대해서 탐색
        for (int j = 0; j < N - M + 1; j++) { // 모든 구간(길이=K)에 대해서 탐색
            int prev = numbers_2d[j][i]; // i번째 열의 j번째 행
            if (prev == 0) {
                continue; // 해당 값이 폭탄이 아니라면 pass
            }
            int flag = false; // 다음 반복문(M번)을 반복해도 false로 남아있다면 k번 연속적이란 뜻
            int cnt = 0; // 이게 M개 이상 반복되어야 함.
            int last_idx = 0;
            for (int p = j; p < N; p++) { 
                int cur = numbers_2d[p][i];
                if (prev != cur) { 
                    flag = true;
                    break;
                }
                else {
                    last_idx = p;
                    cnt++;
                }
            }
            if (cnt >= M) { // M번 이상 연속됐으면
                is_bombed = true;
                for (int p = j; p <= last_idx; p++) { // 한 구간의 모든 값에 대해서 탐색
                    numbers_2d[p][i] = 0; // 0이 되면 폭탄이 터진것으로 간주
                }
            }
        }
    }
    return is_bombed;
}
void gravity() {
    for (int i = 0; i < N; i++) { // 모든 열에 대해서 탐색
        stack<int> col_stack;
        for (int j = 0; j < N; j++) { // 모든 행에 대해서 탐색
            if (numbers_2d[j][i] != 0) {
                col_stack.push(numbers_2d[j][i]);
            }
        }
        // 먼저 해당 열을 모두 비워줘야 함
        for (int j = 0; j < N; j++) { // 모든 행에 대해서 탐색
            numbers_2d[j][i] = 0;
        }
        int cnt = N - 1;
        while (!col_stack.empty()) {
            int cur = col_stack.top();
            col_stack.pop();
            numbers_2d[cnt][i] = cur;
            cnt--; // cnt는 음수가 될 일이 없으므로 빼주기만 해줘도 된다.
        }
        // 즉 해당 열의 값을 모두 비우고, 기존에 해당 열에 있던 값을 stack을 이용해 아래부터 차곡차곡 쌓아주는 과정.
    }
}
void rotate() {
    int numbers_2d_tmp[100][100];
    memset(numbers_2d_tmp, 0, sizeof(numbers_2d_tmp));
    for (int b = 0; b < N; b++) { // 모든 열에 대해서 탐색
        for (int a = 0; a < N; a++) { // 모든 행에 대해서 탐색
            numbers_2d_tmp[b][N - 1 - a] = numbers_2d[a][b];
        }
    }
    // numbers_2d = numbers_2d_tmp; // 회전된 배열 덮어씌우기
    // c언어에서는 모든 원소를 하나하나 대입시켜줘야 함
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            numbers_2d[i][j] = numbers_2d_tmp[i][j];
        }
    }
}
void debug() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << numbers_2d[i][j] << " ";
        }
        cout << "\n";
    }
}
int main() {
    cin >> N >> M >> K;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> numbers_2d[i][j];
        }
    }

    // Please write your code here.
    for (int i = 0; i < K; i++) {
        // K 번 터지고 회전하는 과정을 반복
        //cout << "폭탄 터짐" << "\n";
        // bomb(); // 폭탄 터짐
        //debug();
        //cout << "중력" << "\n";
        // gravity(); // 중력에 의해 떨어짐
        //debug();
        //cout << "회전" << "\n";
        while (bomb()) { // 안터질때까지 폭파->중력 반복
            gravity(); // 중력에 의해 떨어짐
            // a++;
            // cout << "a:" << a << "\n";
        }
        rotate(); // 90도 시계방향 회전
        //debug();
        //cout << "중력" << "\n";
        gravity(); // 중력에 의해 떨어짐
        //debug();
        //cout << i + 1 << "번째 과정" << "\n";
        // debug();
    }
    // cout << "flag!" << "\n";
    int a = 0;
    // k번 폭파&회전 을 반복시켰으니, 더이상 안터질때까지 폭파&중력 반복
    while (bomb()) { // 안터질때까지 폭파->중력 반복
        gravity(); // 중력에 의해 떨어짐
        // a++;
        // cout << "a:" << a << "\n";
    }
    int cnt = 0; // 폭탄갯수
    // cout << "최종 상태" << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            //cout << numbers_2d[i][j] << " ";
            if (numbers_2d[i][j] != 0) {
                cnt++;
            }
        }
        //cout << "\n";
    }
    cout << cnt;
    return 0;
}
