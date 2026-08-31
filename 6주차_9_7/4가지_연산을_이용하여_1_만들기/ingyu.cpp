#include <iostream>
#include <queue>
using namespace std;

int N;
bool visit[1'000'001];
int main() {
    cin >> N;

    // Please write your code here.
    queue<pair<int, int>> q;
    q.push({0, N});
    while (!q.empty()){
        int cal = q.front().first;
        int cur = q.front().second;
        if (cur == 1){
            cout << cal;
            break;
        }
        q.pop();
        if (!visit[cur - 1] ){
            visit[cur - 1] = true;
            q.push({cal + 1, cur - 1});
        }
        if (!visit[cur + 1]){
            visit[cur + 1] = true;
            q.push({cal + 1, cur + 1});
        }
        if (cur % 2 == 0 && !visit[cur / 2]){
            visit[cur / 2] = true;
            q.push({cal + 1, cur / 2});
        }
        if (cur % 3 == 0 && !visit[cur / 3]){
            visit[cur / 3] = true;
            q.push({cal + 1, cur / 3});
        }
    }
    return 0;
}
