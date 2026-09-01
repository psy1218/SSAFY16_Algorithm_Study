#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N;

void q_push(queue<pair<int, int>>&q, vector<int>& visited, int num, int cnt) {
    visited[num] = 1;
    q.push({ num, ++cnt });
}

int bfs(int N, int cnt) {

    queue<pair<int, int>>q;
    vector<int>visited(1000001, 0);
    q.push({ N, cnt });
    visited[N] = 1;

    int count = 0;

    /*
    
    15 5 4 2 1

    */

    while (!q.empty()) {

        auto cur = q.front();
        int cur_num = cur.first;
        int cur_cnt = cur.second;
        q.pop();

        if (cur_num == 1) {
            count = cur_cnt;
            break;
        }

        int add_num = 0;
        if (visited[cur_num + 1] == 0) q_push(q, visited, cur_num + 1, cur_cnt);
          
        if (visited[cur_num - 1] == 0) q_push(q, visited, cur_num - 1, cur_cnt);
        
        if (cur_num % 2 == 0 && visited[cur_num / 2] == 0)  q_push(q, visited, cur_num / 2, cur_cnt);

        if (cur_num % 3 == 0 && visited[cur_num / 3] == 0)  q_push(q, visited, cur_num / 3, cur_cnt);
    }

    return count;
}

int main() {
    cin >> N;

    int res = bfs(N, 0);

    cout << res << "\n";

    return 0;
}



/*


=> dp 로 이전의 값을  활용해서 최소 연산을 구하려고 했음.
=> 근데 +1 연산도 있어서 이전의 값 말고도 이후의 값도 필요로 함.

17 18 6 2 1
17 18 9 3 1
17 16 8 4 2 1

=> 위의 예제를 보면, -1 한 거보다, +1 한게 더 최소 비용임.
=> 그래서 이후의 값도 필요하기 때문에 dp 보다는 다른 방향으로 생각하는게 좋을 거 같음.

=> 그래서 경우의 수를 count 와 함께 push함!!


15 16 8 4 2 1
15 5 4 2 1

11 12 6 2 1
11 10 5 6 2 1

1 3 18 17
1 3 15 1 1

1 2 4 8
1 3 9 8

1 3 9 8

5 6 3 1
5 4 2 1

6 2 1

7 8 4 2 1
7 6 3 1

10 5 4 2 1
10 9 3 1

12 6 2 1
12 6 3 1

18 9 3 1
18 6 2 1



13


1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23
0 1 1 2 4 3 4 4 3 4  4  4  5


1 2 3
4 5 6








*/
