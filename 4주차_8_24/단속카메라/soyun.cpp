#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(vector<int>& a, vector<int>& b){
    if(a[1] == b[1]) return a[0] > b[0];
    
    return a[1] < b[1];
}

int solution(vector<vector<int>> routes) {
    int answer = 1;
    
    sort(routes.begin(), routes.end(), compare);
    
    for(int i=0;i<routes.size();i++){
        cout << routes[i][0] << " " << routes[i][1] << "\n";
    }
    
    int cur = routes[0][1];
    for(int i=1;i<routes.size();i++){
        if(routes[i][0] <= cur)  continue;
        else {
            answer++;
            cur = routes[i][1];
        }
        
    }
    
    return answer;
} 

/*

[[-20,-15], [-14,-5], [-18,-13], [-5,-3]]	
[-20,-15] [-18,-13] [-14,-5] [-5,-3]

[-20,-15] [-18,-16] [-14,-5] [-5,-3]
[-18,-16] [-20,-15] [-14,-5] [-5,-3]


*/


/*

[[-20,-15], [-14,-5], [-18,-13], [-5,-3]]	
[-20,-15] [-18,-13] [-14,-5] [-5,-3]
[3,5] [5,14] [13,18] [15,20]

[5,3] [14,5] [18,13] [20,15]
[-5,3] [14,5] [18,13] [20,15]

[-20,-15] [-18,-13] [-13,-10]
*/


// #include <string>
// #include <vector>
// #include <algorithm>

// using namespace std;

// bool compare(const vector<int>& a, const vector<int>& b){
//     if (a[1] == b[1]) return a[0] < b[0];
//     return a[1] < b[1];
// }

// bool compare1(const vector<int>& a, const vector<int>& b){
//     if (a[0] == b[0]) return a[1] < b[1];
//     return a[0] < b[0];
// }

// int solution(vector<vector<int>> routes) {
//     int answer = 0;
//     int cnt = 1;
    
//     if(routes[0][0] < routes[0][1]){
//         sort(routes.begin(), routes.end(), compare);

//         // 진입/진출 순서도 생각

//         int std = routes[0][1];
//         for(int i=1;i<routes.size();i++){
//             if(std < routes[i][0]) {
//                 cnt++;
//                 std = routes[i][1];
//             }
//         }
//     }
//     else{
//         sort(routes.begin(), routes.end(), compare1);

//         // 진입/진출 순서도 생각

//         int std = routes[0][0];
//         for(int i=1;i<routes.size();i++){
//             if(std < routes[i][1]) {
//                 cnt++;
//                 std = routes[i][0];
//             }
//         }
        
//     }
    
//     answer = cnt;
//     return answer;
// }

// #include <string>
// #include <vector>
// #include <algorithm>

// using namespace std;

// bool compare(const vector<int>& a, const vector<int>& b){
//     if (a[1] == b[1]) return a[0] < a[1];
//     return a[1] < b[1];
// }

// int solution(vector<vector<int>> routes) {
//     int answer = 0;
    
//     sort(routes.begin(), routes.end(), compare);
    
//     // 진입/진출 순서도 생각
    
//     int std = routes[0][1];
//     int cnt = 1;
//     for(int i=1;i<routes.size();i++){
//         if(std < routes[i][0]) {
//             cnt++;
//             std = routes[i][1];
//         }
//     }
    
//     answer = cnt;
//     return answer;
// }

/*
[[-20,-15], [-14,-5], [-18,-13], [-5,-3]]	
[-20,-15] [-18,-13] [-14,-5] [-5,-3]
[3,5] [5,14] [13,18] [15,20]

[5,3] [14,5] [18,13] [20,15]
[-5,3] [14,5] [18,13] [20,15]

[-20,-15] [-18,-13] [-13,-10]
*/
