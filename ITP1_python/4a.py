a,b = map(int, input().split())

d,r,f = a//b, a%b, a/b
print(f"{d} {r} {f:.5f}")