
def call(n:int):
    i = 1
    check_num(i, n)

def check_num(i:int, n:int, x:int=0):
    for i in range(i, n+1):
        x = i
        if x%3 == 0:
            print(f" {i}", end="")
            continue
        include3(i, n, x)
    print()

def include3(i:int, n:int, x:int):
    if x%10==3:
        print(f" {i}", end="")
        return
    x //= 10
    if x:
        include3(i,n,x)
        return
    

n = int(input())
call(n)