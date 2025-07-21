info = [[[0 for _ in range(10)] for _ in range(3)] for _ in range(4)]

def update(info,b,f,r,v):
    info[b-1][f-1][r-1] += v
    return info

def show(info):
    for b in range(4):
        for f in range(3):
            for r in range(10):
                print(f" {info[b][f][r]}", end="")
            print()
        if b != 3:
            print("#"*20)

n = int(input())

for _ in range(n):
    b,f,r,v = map(int, input().split())
    info = update(info, b,f,r,v)
show(info)