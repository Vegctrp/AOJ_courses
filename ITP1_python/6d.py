n,m = map(int, input().split())

a = [[0 for _ in range(m)] for _ in range(n)]
b = [0 for _ in range(m)]

for i in range(n):
    inp = list(map(int, input().split()))
    assert len(inp) == m
    for j in range(m):
        a[i][j] = inp[j]
for j in range(m):
    inp = int(input())
    b[j] = inp

c = [sum([a[i][j]*b[j] for j in range(m)]) for i in range(n)]
for i in range(n):
    print(c[i])