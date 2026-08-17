#include <iostream>
#include <deque>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    for (int k = 1; k <= 10; k++) {
        int tc;
        cin >> tc;

        deque<int> q;

        for (int i = 0; i < 8; i++) {
            int num;
            cin >> num;
            q.push_back(num);
        }

        int cnt = 1;

        while (q.back() != 0) {
            int cur = q.front();
            q.pop_front();

            int nxt = cur - cnt;

            if (nxt > 0) {
                q.push_back(nxt);

                cnt++;

                if (cnt > 5) {
                    cnt = 1;
                }
            }
            else {
                q.push_back(0);
                break;
            }
        }

        cout << "#" << tc << " ";

        for (int num : q) {
            cout << num << " ";
        }

        cout << '\n';
    }

    return 0;
}
