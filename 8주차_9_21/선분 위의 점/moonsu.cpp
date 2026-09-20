#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
int points[100000];

struct LINE_INFO {
    int s, e;
};

LINE_INFO lines[100000];

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> points[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> lines[i].s >> lines[i].e;
    }

    // Please write your code here.
    sort(points, points + n);

    for (int i = 0; i < m; i++) {
        auto up = upper_bound(points, points + n, lines[i].e);
        auto low = lower_bound(points, points + n, lines[i].s);

        cout << up - low << '\n';
    }


    return 0;
}
