#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;

        priority_queue<int> pq;

        cout << "#" << tc;

        for (int i = 0; i < N; i++) {
            int cmd;
            cin >> cmd;

            if (cmd == 1) {
                int x;
                cin >> x;

                pq.push(x);
            }
            else if (cmd == 2) {
                if (pq.empty()) {
                    cout << " " << -1;
                }
                else {
                    cout << " " << pq.top();
                    pq.pop();
                }
            }
        }

        cout << '\n';
    }

    return 0;
}
