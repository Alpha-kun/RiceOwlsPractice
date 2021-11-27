import heapq

while True:
    try :
        a, b = input().split()
        m = {}
        vis = set()
        dis = {}
        pre = {}
        n = int(input())
        for _ in range(n):
            l = input().split()
            # print(l)
            for name1 in l:
                if name1 not in m:
                    m[name1] = set()
                for name2 in l:
                    if name1 != name2:
                        m[name1].add((name2, len(l) - 2))
                        # print(name1, name2, m[name1])
        
        pq = []
        heapq.heappush(pq, (0, a))
        dis[a] = 0
        while len(pq):
            cur = heapq.heappop(pq)
            if cur[1] in vis: 
                continue
            vis.add(cur[1])
            if cur[1] not in m:
                continue
            for nxt in m[cur[1]]:
                if nxt[0] not in dis or dis[nxt[0]] > dis[cur[1]] + nxt[1] + (nxt[0] != b):
                    dis[nxt[0]] = dis[cur[1]] + nxt[1] + (nxt[0] != b)
                    heapq.heappush(pq, (dis[nxt[0]], nxt[0]))
                    pre[nxt[0]] = cur[1]
        
        res = [b]
        while res[-1] in pre:
            res.append(pre[res[-1]])
        
        if res[-1] != a:
            print("impossible")
        else:
            print(dis[b], end="")
            for name in res[::-1]:
                print(" " + name, end="")
            print("") 

    except EOFError:
        break
