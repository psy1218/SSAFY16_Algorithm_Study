int solution(int N, vector<vector<int>> road, int K) {
    int answer = 0;
    const int INF = 1000000000;

    // 인접 행렬
    vector<vector<int>> dist(N, vector<int>(N, INF));

    for (int i = 0; i < N; i++) {
        dist[i][i] = 0;
    }

    // 같은 두 마을 사이에 여러 도로가 존재할 수 있으므로
    // 가장 짧은 도로만 저장
    for (vector<int> info : road) {
        int a = info[0] - 1;
        int b = info[1] - 1;
        int cost = info[2];

        if (dist[a][b] > cost) {
            dist[a][b] = cost;
            dist[b][a] = cost;
        }
    }

    // d[i] = 1번 마을에서 i번 마을까지의 현재 최단거리
    vector<int> d(N, INF);

    // 해당 마을의 최단거리가 확정되었는지
    vector<bool> visited(N, false);

    // 시작점은 1번 마을(index 0)
    d[0] = 0;

    for (int count = 0; count < N; count++) {
        int curr = -1;
        int min_dist = INF;

        // 아직 방문하지 않은 마을 중
        // 시작점으로부터 가장 가까운 마을 선택
        for (int i = 0; i < N; i++) {
            if (!visited[i] && d[i] < min_dist) {
                min_dist = d[i];
                curr = i;
            }
        }

        // 더 이상 갈 수 있는 마을이 없다면 종료
        if (curr == -1) {
            break;
        }

        visited[curr] = true;

        // curr를 거쳐 가는 것이 더 짧은지 검사
        for (int next = 0; next < N; next++) {
            if (dist[curr][next] == INF) {
                continue;
            }

            if (d[next] > d[curr] + dist[curr][next]) {
                d[next] = d[curr] + dist[curr][next];
            }
        }
    }

    // K 이하인 마을 개수
    for (int i = 0; i < N; i++) {
        if (d[i] <= K) {
            answer++;
        }
    }

    return answer;
}