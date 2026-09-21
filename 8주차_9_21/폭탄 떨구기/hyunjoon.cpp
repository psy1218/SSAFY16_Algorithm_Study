#include <iostream>
#include <algorithm>
using namespace std;

int n, k;
int x[50000];

bool check_bomb(int R){
    int idx = 0;
    int cnt = 0;

    while(idx<n){
        cnt++;
        
        int limit = 2 * R + x[idx];

        while(idx<n && x[idx] <= limit){
            idx++;
        }

        if(cnt>k){
            return false;
        }
    }

    return true;
}

int upper_search(){
    int start = 0;
    int end = x[n-1] - x[0];
    int mid = 0;
    int ret = end;
    while(start<=end){
        mid = (start + end) / 2;
        if(check_bomb(mid)){
            ret = mid;
            end = mid-1;
        }

        else{
            start = mid + 1;
        }
    }

    return ret;
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    // Please write your code here.

    sort(x,x+n);

    if(k>=n){
        cout << 0;
        return 0;
    }

    cout << upper_search();
    
    return 0;
}
