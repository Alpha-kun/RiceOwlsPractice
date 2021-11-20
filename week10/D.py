import heapq

n, m, k = map(int, input().split())

quu = []
heapq.heappush(quu, ['Jane Eyre', k])
for i in range(n):
    input_list = input().split()
    k = int(input_list[-1])
    s = ' '.join(input_list[:-1:])[1: -1]
    # print(s)
    heapq.heappush(quu, [s, k])

book_list = []
for i in range(m):
    input_list = input().split()
    t = int(input_list[0])
    k = int(input_list[-1])
    s = ' '.join(input_list[1: -1])[1: -1]
    # print(s)
    book_list.append([t, s, k])

book_list.sort()
now_time = 0
now = heapq.heappop(quu)
now_reading = now[0]
finish_time = now_time + now[1]
i = 0

while now_reading != 'Jane Eyre':
    # print(now_reading)
    now_time = finish_time
    while i < len(book_list) and book_list[i][0] <= finish_time:
        heapq.heappush(quu, [book_list[i][1], book_list[i][2]])
        i += 1
    now = heapq.heappop(quu)
    now_reading = now[0]
    finish_time = now_time + now[1]

print(finish_time)
