#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
using namespace std;
pair<bool, int> bfs(int start, int max_intensity, int n, vector<vector<pair<int, int>>> &graph, vector<vector<int>>& paths, vector<int>& gates, vector<int>& summits){ // {false, 0}, {true, 3} 과 같은 형태. 첫번째 원소가 false면 불가능한거고, true면 가능한 경우, true일 경우에 두번째 원소는 가능한것 중에 가장 번호가 낮은 산봉우리
    vector<bool> visit(n + 1, false);
    queue<int> q;
    q.push(start);
    // 멀티소스 bfs. 모든 출입구를 큐에 push한다. 
    for (int g : gates) {      // 모든 출입구를 시작점으로
        q.push(g);
        visit[g] = true;
    }
    int cur;
    unordered_set<int> summits_set;
    int summits_size = summits.size();
    for (int i = 0; i < summits_size; i++){
        summits_set.insert(summits[i]);
    }
    vector<int> answer_summit; // 가능한 산봉우리
    bool flag = false;
    while (!q.empty()){
        cur = q.front();
        q.pop();
        if (summits_set.count(cur)){ // 현재 위치가 정상이라면
            answer_summit.push_back(cur);
            flag = true;
            continue; // 해당 경로에선 깊이 탐색 종료
        }
        for (auto ele : graph[cur]){ // 현재 노드 cur과 연결되어 있는 노드들 탐색
            int nxt = ele.first;
            int w = ele.second;
            if (!visit[nxt] && w <= max_intensity){ // 최대 강도보다 작거나 같을 경우만 통과 가능
                visit[nxt] = true;
                q.push(nxt);
            }
        }
    }
    if (flag){
        sort(answer_summit.begin(), answer_summit.end());    
        return {true, answer_summit[0]};
    }
    else{
        return {false, 0};
    }
}
pair<bool, int> is_possible(int max_intensity, int n, vector<vector<pair<int, int>>> &graph, vector<vector<int>>& paths, vector<int>& gates, vector<int>& summits){ // 최대 강도 = max_intensity 일때 가능한지 여부 확인
    // int gates_size = gates.size();
    // vector<int> possible_summit;
    // bool flag = false;
    // for (int i = 0; i < gates_size; i++){
    //     int start = gates[i];
    //     pair<bool, int> ans = bfs(start, max_intensity, n, graph, paths, gates, summits);
    //     if (ans.first){ // start에서 시작했을때, 도착할 수 있는 산봉우리가 있는지 확인
    //         possible_summit.push_back(ans.second);
    //         flag = true;
    //     }
    // }
    // if (flag){
    //     sort(possible_summit.begin(), possible_summit.end());
    //     return {true, possible_summit[0]};
    // }
    // else{
    //     return {false, 0};
    // }
    return bfs(0, max_intensity, n, graph, paths, gates, summits);   // BFS 한 번만
}
vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer(2, 0);
    vector<vector<pair<int, int>>> graph(n + 1);
    int paths_size = paths.size();
    for (int i = 0; i < paths_size; i++){
        int w = paths[i][2];
        int a = paths[i][0];
        int b = paths[i][1];
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }
    int mid;
    int start = 0;
    int end = 10e8;
    int total_summit;
    while (start <= end){
        mid = (start + end) / 2;
        pair<bool, int> ans = is_possible(mid, n, graph, paths, gates, summits);
        if (ans.first){ // 가능하면
            end = mid - 1;
            total_summit = ans.second; // 가능하면서 가장 번호가 낮은 산봉우리
            answer[0] = total_summit;
            answer[1] = mid;
        }
        else{
            start = mid + 1;
        }
    }
    return answer;
}
