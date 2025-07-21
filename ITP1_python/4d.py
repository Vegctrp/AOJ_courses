n = int(input())

lst = list(map(int, input().split()))
assert len(lst) == n

print(f"{min(lst)} {max(lst)} {sum(lst)}")