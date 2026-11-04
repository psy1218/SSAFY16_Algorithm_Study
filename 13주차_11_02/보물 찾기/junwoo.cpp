#include <string>
#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

extern int excavate(int);

int solution(vector<int> depth, int money) {
    
    int n = depth.size();
    
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> choice(n, vector<int>(n, 0));
    
    // 구간 길이
    for (int len = 1; len <= n; len++){
        for (int l = 0; l + len - 1 < n; l++){
            int r = l + len - 1;
            
            dp[l][r] = INT_MAX;
            
            // 처음 굴착할 열 선택
            for (int k = l; k <= r; k++){
                int leftCost = (k > l) ? dp[l][k-1] : 0;
                int rightCost = (k < r) ? dp[k+1][r] : 0;
                
                int cost = depth[k] + max(leftCost, rightCost);
                
                if (cost < dp[l][r]){
                    dp[l][r] = cost;
                    choice[l][r] = k;
                }
            }
        }
    }
    
    int left = 0;
    int right = n - 1;
    
    while (left <= right){
        int mid = choice[left][right];
        
        int result = excavate(mid + 1);
        
        if (result == 0){
            return mid + 1;
        }
        else if (result == -1){
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    
    return 0;
}
