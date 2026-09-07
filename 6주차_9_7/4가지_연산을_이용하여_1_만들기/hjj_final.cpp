#include <iostream>
#include <queue>

using namespace std;

int N;

int main() {
    cin >> N;
    static int MAX_NUM = 1000000;

    queue<pair<int, int>> procedure;
    vector<int> saving_min_times(N + 3, MAX_NUM);
    procedure.push({ N, 0 });

    int curr_num;
    int next_num;
    int curr_calculate_times = 0;

    while (!procedure.empty()) {
        curr_num = procedure.front().first;
        curr_calculate_times = procedure.front().second;
        procedure.pop();

        if (curr_num == 1) break;

        // 현재 수가 3의 배수인 경우 3으로 나누기
        if (curr_num % 3 == 0) {
            next_num = curr_num / 3;
            if (saving_min_times[next_num] > curr_calculate_times + 1) {
                saving_min_times[next_num] = curr_calculate_times + 1;
                procedure.push({ next_num, curr_calculate_times + 1 });
            }
        }
        // 현재 수가 2의 배수인 경우 2로 나누기
        if (curr_num % 2 == 0) {
            next_num = curr_num / 2;
            if (saving_min_times[next_num] > curr_calculate_times + 1) {
                saving_min_times[next_num] = curr_calculate_times + 1;
                procedure.push({ next_num, curr_calculate_times + 1 });
            }
        }
        // 현재 수에서 1을 빼기
        if (curr_num > 0) {
            next_num = curr_num - 1;
            if (saving_min_times[next_num] > curr_calculate_times + 1) {
                saving_min_times[next_num] = curr_calculate_times + 1;
                procedure.push({ next_num, curr_calculate_times + 1 });
            }
        }
        // 현재 수에 1을 더하기
        if (curr_num < N + 2) {
            next_num = curr_num + 1;
            if (saving_min_times[next_num] > curr_calculate_times + 1) {
                saving_min_times[next_num] = curr_calculate_times + 1;
                procedure.push({ next_num, curr_calculate_times + 1 });
            }
        }
    }

    cout << curr_calculate_times;
}
