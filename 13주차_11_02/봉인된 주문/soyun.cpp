// 단순 조합은 시간 초과
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 문자열을 주문서에서의 순서(숫자)로 변환
long long stringToNum(string s) {
    long long num = 0;
    long long sum = 0;
    long long cnt = 26;

    // 현재 문자열 길이보다 짧은 문자열들의 개수
    for (int i = 1; i < s.size(); i++) {
        sum += cnt;
        cnt *= 26;
    }

    // 같은 길이의 문자열에서 몇 번째인지 계산
    for (int i = 0; i < s.size(); i++) {
        num = num * 26 + (s[i] - 'a');
    }

    return sum + num + 1;
}

// 주문서 순서(숫자)를 문자열로 변환
string numToString(long long num) {
    int len = 1;
    long long cnt = 26;

    // 해당 숫자가 몇 글자 문자열에 속하는지 확인
    while (num > cnt) {
        num -= cnt;
        cnt *= 26;
        len++;
    }

    // 0부터 시작하는 인덱스로 변경
    num--;

    string result = "";

    // 26진수 형태로 문자열 복원
    for (int i = 0; i < len; i++) {
        char ch = 'a' + (num % 26);
        result += ch;
        num /= 26;
    }

    // 뒤에서부터 계산했으므로 뒤집기
    reverse(result.begin(), result.end());

    return result;
}

string solution(long long n, vector<string> bans) {

    vector<long long> banNum;

    // 삭제된 주문을 숫자로 변환
    for (int i = 0; i < bans.size(); i++) {
        long long num = stringToNum(bans[i]);
        banNum.push_back(num);
    }

    // 삭제된 주문들을 오름차순 정렬
    sort(banNum.begin(), banNum.end());

    // 이진 탐색
    long long left = 1;
    long long right = n + bans.size();

    long long answer = right;

    while (left <= right) {
        long long mid = left + (right - left) / 2;

        // mid 이하에 존재하는 삭제된 주문 개수
        long long banCnt = upper_bound(banNum.begin(), banNum.end(), mid) - banNum.begin();
        // 삭제 후 남아 있는 주문 개수
        long long cnt = mid - banCnt;

        if (cnt >= n) {
            // n번째 주문이 mid 이하에 존재
            answer = mid;
            right = mid - 1;
        }
        else {
            // n번째 주문이 mid보다 뒤에 존재
            left = mid + 1;
        }
    }

    // 찾은 숫자를 문자열로 변환
    return numToString(answer);
}
