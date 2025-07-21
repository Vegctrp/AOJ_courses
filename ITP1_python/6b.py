matrix = [[0 for _ in range(13)] for _ in range(4)]
suits = ['S', 'H', 'C', 'D']

n = int(input())

for _ in range(n):
    s, num = input().split()
    num = int(num)

    for i in range(4):
        if suits[i] == s:
            matrix[i][num-1] = 1

for i in range(4):
    for j in range(13):
        if matrix[i][j] == 0:
            print(suits[i], j+1)
