#include <iostream>

using namespace std;

int n;
int s[1000];
int b[1000];
int memoization[1001][12][10];
// 불가능한 경우 INABLE
// 모든 능력을 100'000 으로 고정하고, 최대 N(1'000)개 뽑았을 시에 음수
const int INABLE = -100'000'000;

// [메인 아이디어]
// 
// 1. 중단 조건
// st == 0 && bt == 0 이면 return 0
// students < (st + bt) 이면 불가능한 경우이므로 return INABLE
// 
// 2. 누구를 뽑았는지 기록해야 하는가?
// -> 기록하지 않아도 된다. 각 학생들에 대해서 선택을 진행하므로
// 현재 학생에 대한 선택을 완료하면,
// 그 학생까지 선택한 경우들 중에서 가장 최대가 되는 경우를 저장(메모이제이션)
// 
// 3. 선택의 기준
// 현재 index의 학생을
// a) 축구 팀으로 뽑는다
// b) 야구 팀으로 뽑는다
// c) 뽑지 않는다
// - 모든 경우들 중 max가 되는 것을 뽑으면 된다.
// - st 나 bt 크기를 확인해가며 진행할 것
// - memoization이 필요한가? -> 모르겠음 -> 사용
// 
int recursive(int students, int st, int bt) {
    // visual studio 버퍼 오류 잡는 용도
    if (st >= 12 || bt >= 10) return -1;
    // 현재 골라야하는 학생 수가, 선발해야 하는 학생 수보다 적은 경우 -> 불가능
    if (students < (st + bt)) return INABLE;
    // 모두 선발한 경우 중단
    if (st == 0 && bt == 0) return 0;

    // 메모이제이션
    if (memoization[students][st][bt] != -1) return memoization[students][st][bt];

    // s[]나 b[]를 참조하기 위한 인덱스 (현재 학생의 인덱스)
    int idx = students - 1;

    // 선택을 진행할 때, 최댓값만 판단한다
    // 즉, max 연산을 한다

    // c) 현재 학생을 뽑지 않는다
    int answer = recursive(students - 1, st, bt);

    // a) 축구 팀에 남은 인원이 있어서, 현재 학생을 축구 팀으로 뽑는다
    if (st > 0) {
        answer = max(answer, s[idx] + recursive(students - 1, st - 1, bt));
    }

    // b) 야구 팀에 남은 인원이 있어서, 현재 학생을 야구 팀으로 뽑는다
    if (bt > 0) {
        answer = max(answer, b[idx] + recursive(students - 1, st, bt - 1));
    }

    // 메모이제이션 + 리턴
    return memoization[students][st][bt] = answer;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> b[i];
    }

    // 초기화
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