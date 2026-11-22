import heapq
def solution(board):
    answer = 0
    # 최초에 큐에 R의 좌표넣고, 최초로 D로 도달하게되는 dist를 출력.
    # is_valid구현, D아닌곳만 큐에 추가
    # 동서남북 방향으로 빔을 쏘고, 멈추게되는 위치를 return
    row = len(board[0])
    col = len(board)
    start = (0, 0)
    goal = (0, 0)
    for i in range(col):
        for j in range(row):
            if board[i][j] == "R":
                start = (i, j) # 시작 위치
            if board[i][j] == "G":
                goal = (i, j) # 시작 위치
    def is_valid(x, y):
        return x >= 0 and x < col and y >= 0 and y < row
    dx = [1, -1, 0, 0] # dx[0], dy[0] = 1, 0 이면 남쪽 / -1, 0 이면 북쪽 / 0, 1 이면 동쪽 / 0, -1 이면 서족 
    dy = [0, 0, 1, -1]
    def beam(x, y): # 0,1,2,3 은 남,북,동,서
        result = [] # 동서남북 4가지 방면에 대한 모든 결과가 저장된다.
        for d in range(4):
            dx2, dy2 = dx[d], dy[d] # (x, y)에서 계속 dx2, dy2 방향으로 이동
            nx, ny = x, y
            while is_valid(nx, ny):
                nx += dx2
                ny += dy2
                if not is_valid(nx, ny): # 벽에 닿아도 결과에 추가.
                    result.append([nx-dx2, ny-dy2])
                    break
                if board[nx][ny] == "D": # 이 방향으로 이동한 값이 장애물이라면
                    result.append([nx-dx2, ny-dy2]) # 반대 방향으로 한칸만 리와인드
                    break
        return result
    # 다익스트라
    queue = []
    heapq.heappush(queue, (0, start[0], start[1]))
    INF = float('inf')
    distance = [[INF for i in range(row)] for j in range(col)]
    distance[start[0]][start[1]] = 0 # 시작지점은 거리 0
    while queue:
        dist, x, y = heapq.heappop(queue)
        if dist != distance[x][y]:
            continue # 더미데이터이므로
        res = beam(x, y) # x, y에서 이동할수 있는 위치 (4가지 방향에 대해)
        for i in res:
            nxt_x, nxt_y = i
            if dist+1 < distance[nxt_x][nxt_y]: # 더 작은 거리로 갱신되면 갱신
                distance[nxt_x][nxt_y] = dist+1
                heapq.heappush(queue, (dist+1, nxt_x, nxt_y))
    answer = distance[goal[0]][goal[1]]
    if answer == INF:
        answer = -1
    else:
        pass
    return answer
