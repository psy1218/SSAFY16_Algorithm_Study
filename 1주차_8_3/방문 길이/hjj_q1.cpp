#include <iostream>
#include <array>
#include <set>
using namespace std;

int solution(string dirs) {
    int answer = 0;

    array<int, 2> curr = { 0, 0 };
    array<int, 2> next = { 0, 0 };
    array<int, 4> path;
    set<array<int, 4>> movements;

    for (char cmd : dirs) {
		// next 초기화
		next = curr;

        // next 계산
        if (cmd == 'R')
        {
            if (curr[0] == 5) {
                continue;
            }
            next[0] = curr[0] + 1;

        }
        else if (cmd == 'L')
        {
            if (curr[0] == -5) {
                continue;
            }
            next[0] = curr[0] - 1;

        }
        else if (cmd == 'U')
        {
            if (curr[1] == 5) {
                continue;
            }
            next[1] = curr[1] + 1;

        }
        else if (cmd == 'D')
        {
            if (curr[1] == -5) {
                continue;
            }
            next[1] = curr[1] - 1;

        }

        // 경로 생성
        if (curr < next) {
            path = { curr[0], curr[1], next[0], next[1] };
        }
        else {
            path = { next[0], next[1], curr[0], curr[1] };
        }

        // 경로 비교. 존재하지 않을 경우만 insert 및 answer++
        if (movements.count(path) == 0) {
            movements.insert(path);
            answer++;
        }

        // 현재 좌표 갱신
        curr = next;
    }

    return answer;
}