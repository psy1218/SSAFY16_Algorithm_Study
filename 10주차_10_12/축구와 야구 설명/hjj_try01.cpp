#include <iostream>

using namespace std;

const int INABLE = -100'000'000;
int n;
int s[1000];
int b[1000];
int memoization[1001][12][10];

// [메인 아이디어]
// 
// 1. 중단 조건
// s + b = 20
// 
// 2. s >= 12 or b >= 10 이면 return 0
// 
// 3. 누구를 뽑았는지 기록해야 하는가? -> 맞다
// 그러지 않으면 중복으로 뽑을 수 있다
// 더 정확하게는, '선택'을 진행했는가 여부를 기록하는 것이 맞을듯
// 
// 4. 선택의 기준
// 현재 index의 학생을
// a) 축구 팀으로 뽑는다
// b) 야구 팀으로 뽑는다
// c) 뽑지 않는다
// - a) 나 b) 는 둘 중 max가 되는 것을 뽑으면 된다. 즉 max(s[index], b[index])
// - s나 b 크기를 확인해가며 진행할 것
// - memoization이 필요한가? -> 모르겠음
// 
int recursive(int students, int st, int bt) {
    if (students < (st + bt)) return INABLE;
    if (st < 0 || bt < 0) return INABLE;
    if (st == 0 && bt == 0) return 0;

    students--;
    return max(
        recursive(students, st, bt),
        max(s[students] + recursive(students, st - 1, bt), b[students] + recursive(students, st, bt - 1))
    );
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> b[i];
    }

    for (int i = 0; i < 1001; i++) {
        for (int j = 0; j < 12; j++) {
            for (int k = 0; k < 10; k++) {
                memoization[i][j][k] = -1;
            }
        }
    }

    cout << recursive(n, 11, 9);

    return 0;
}