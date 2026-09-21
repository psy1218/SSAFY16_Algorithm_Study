#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int points[100000];
int st[100000], ed[100000];

int upper_edge(int target){
    int start = 0;
    int end = n;
    while(start<end){
        int mid = (start+end)/2;
        if(target<points[mid]){
            end = mid;
        }
        else{
            start = mid + 1;
        }
    }

    return start;
}

int lower_edge(int target){
    int start = 0;
    int end = n;
    while(start<end){
        int mid = (start+end)/2;
        if(target <= points[mid]){
            end = mid;
        }
        else{
            start = mid + 1;
        }
    }

    return start;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> points[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> st[i] >> ed[i];
    }


    // Please write your code here.
    sort(points, points + n);

    for(int i = 0; i<m; i++){
        cout << upper_edge(ed[i]) - lower_edge(st[i]) <<'\n';
    }


    return 0;
}
