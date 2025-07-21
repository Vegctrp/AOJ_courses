n = int(input())

lst = list(map(int, input().split()))
assert len(lst) == n

for i in range(len(lst)):
    if i != 0:
        print(' ', end='')
    print(lst[::-1][i], end="")
print()