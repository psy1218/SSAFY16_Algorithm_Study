#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
int points[100000];
int st[100000], ed[100000];

int find_upper_boundary(int* arr, int* arr_end, int elem) {
    int n = arr_end - arr;

    int start = 0;
    int end = n - 1;
    int mid;
    int answer = n;

    while (start <= end) {
        mid = start + (end - start) / 2;

        if (arr[mid] > elem) {
            answer = mid;
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }

    return answer;
}

int find_lower_boundary(int* arr, int* arr_end, int elem) {
    int n = arr_end - arr;

    int start = 0;
    int end = n - 1;
    int mid;
    int answer = n;

    while (start <= end) {
        mid = start + (end - start) / 2;

        if (arr[mid] >= elem) {
            answer = mid;
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }

    return answer;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> points[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> st[i] >> ed[i];
    }

    sort(points, points + n);

    // cout << "직접 만든 함수: " << find_upper_boundary(points, points + n, 59) << "\n";
    // cout << "직접 만든 함수: " << find_lower_boundary(points, points + n, 22) << "\n";

    // for (int i = 0; i < m; i++) {
    //     cout << upper_bound(points, points + n, ed[i]) - lower_bound(points, points + n, st[i]) << "\n";
    // }

    for (int i = 0; i < m; i++) {
        cout << find_upper_boundary(points, points + n, ed[i]) - find_lower_boundary(points, points + n, st[i]) << "\n";
    }

    return 0;
}
