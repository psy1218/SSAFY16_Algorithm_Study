#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
int arr[4][8]; // arr[i][0] = 12시, arr[i][1] = 1시, ..., arr[i][7] = 11시
void go_rotate(int num, int d) { // num번째 테이블을 회전
    int new_arr[4][8];
    if (d == 1) { // 시계 방향
        new_arr[num][0] = arr[num][7];
        for (int i = 0; i < 7; i++) { 
            new_arr[num][i + 1] = arr[num][i];
        }
    }
    if (d == -1) { // 반시계 방향
        new_arr[num][7] = arr[num][0];
        for (int i = 0; i < 7; i++) { 
            new_arr[num][i] = arr[num][i + 1];
        }
    }
    // override
    for (int i = 0; i < 8; i++) {
        arr[num][i] = new_arr[num][i];
    }
}
int main() {
    // Please write your code here.
    for (int i = 0; i < 4; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < 8; j++) {
            arr[i][j] = str[j] - '0';
        }
    }
    //for (int i = 0; i < 4; i++) {
    //    for (int j = 0; j < 8; j++) {
    //        cout << arr[i][j] * 100 << "\n";
    //    }
    //}
    int k, n, d;
    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> n >> d; // d=1이면 시계, -1이면 반시계
        int cur = n - 1; // 최초 전파 테이블. 0-based 이므로 -1
        int nxt = cur;
        bool is_rotate[4] = { false };
        is_rotate[cur] = true; // 현재 테이블은 무조건 회전시켜야 함
        while (1) { // 왼쪽으로 전파
            nxt = nxt - 1; // 왼쪽
            if (nxt < 0) { // 다음 테이블이 음수라면 없는 테이블
                break;
            }
            if (arr[nxt][2] != arr[nxt+1][6]) {
                is_rotate[nxt] = true; // 다음 테이블도 회전해야함
                continue; // 다음 테이블도 전파
            }
            else {
                break;
            }
        }
        nxt = cur;   // 다시 초기화
        while (1) { // 오른쪽으로 전파
            nxt = nxt + 1; // 오른쪽
            if (nxt >= 4) { // 다음 테이블이 음수라면 없는 테이블
                break;
            }
            if (arr[nxt][6] != arr[nxt-1][2]) {
                is_rotate[nxt] = true; // 다음 테이블도 회전해야함
                continue; // 다음 테이블도 전파
            }
            else {
                break;
            }
        }
        // 한번에 회전 flush
        // cur번째 테이블 먼저 회전
        go_rotate(cur, d); // d = 방향. 1이면 시계, -1이면 반시계
        int nxt_d = d;
        nxt = cur;
        while (1) { // 왼쪽으로 전파
            nxt = nxt - 1; // 왼쪽
            nxt_d = -nxt_d; // 반전
            if (nxt < 0) { // 다음 테이블이 음수라면 없는 테이블
                break;
            }
            if (is_rotate[nxt]) {
                go_rotate(nxt, nxt_d);
                continue; // 다음 테이블도 전파
            }
            else {
                break;
            }
        }
        nxt_d = d;
        nxt = cur;
        while (1) { // 오른쪽으로 전파
            nxt = nxt + 1; // 오른쪽
            nxt_d = -nxt_d; // 반전
            if (nxt >= 4) { // 다음 테이블이 음수라면 없는 테이블
                break;
            }
            if (is_rotate[nxt]) {
                go_rotate(nxt, nxt_d);
                continue; // 다음 테이블도 전파
            }
            else {
                break;
            }
        }
    }
    int answer = 0;
    for (int i = 0; i < 4; i++) {
        if (arr[i][0] == 1) {
            answer += pow(2, i);
        }
    }
    cout << answer;
    return 0;
}
