import heapq

N, M, K = map(int, input().split())
edge_L = [[] for i in range(N)]

for i in range(M):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    edge_L[a].append(b)
    edge_L[b].append(a)

dist_L = [-1] * N
hq = []

cnt = 0
ans_L = []

for i in range(K):
    p, h = map(int, input().split())
    p -= 1
    heapq.heappush(hq, (-h, p))
    dist_L[p] = h
    cnt += 1
    ans_L.append(p+1)

while hq and cnt < N:
    now_hp, now_pos = heapq.heappop(hq)
    now_hp *= -1

    if dist_L[now_pos] > now_hp : continue

    for next_ in edge_L[now_pos]:
        if dist_L[next_] < now_hp - 1:
            if dist_L[next_] == -1: 
                cnt += 1
                ans_L.append(next_ + 1)
            dist_L[next_] = now_hp - 1
            if dist_L[next_] != 0: heapq.heappush(hq, (-(now_hp - 1), next_))

print(cnt)
ans_L.sort()
print(*ans_L)