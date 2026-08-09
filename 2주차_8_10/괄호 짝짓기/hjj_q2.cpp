#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    for (int test_case = 1; test_case <= 10; test_case++)
    {
        int n;
        string brackets;

        vector<char> saving;
        char last;
        bool q1, q2, q3, q4;
        int answer = 0;

        cin >> n;
        cin >> brackets;

        // 짝수인 경우만 괄호 검사
        if (n % 2 == 0) {
            for (char bracket : brackets) {
                if (!saving.empty()) {
                    last = saving.back();
                    q1 = (last == '(' && bracket == ')');
                    q2 = (last == '[' && bracket == ']');
                    q3 = (last == '{' && bracket == '}');
                    q4 = (last == '<' && bracket == '>');
                    if (q1 || q2 || q3 || q4) {
                        saving.pop_back();
                        continue;
                    }
                }
                saving.push_back(bracket);
            }
            if (saving.empty()) {
                answer = 1;
            }
        }

        cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}