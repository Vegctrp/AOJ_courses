a, b, c = map(int, input().split())

import heapq

lst = [a, b, c]
heapq.heapify(lst)

d1 = heapq.heappop(lst)
d2 = heapq.heappop(lst)
d3 = heapq.heappop(lst)

print(f"{d1} {d2} {d3}")