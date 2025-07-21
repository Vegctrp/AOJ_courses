class UnionFind:
    def __init__(self, n:int):
        self.parent = list(range(n))
        self.size = [1] * n

    def find(self, x:int) -> int:
        if self.parent[x] == x:
            return x
        else:
            self.parent[x] = self.find(self.parent[x])
            return self.parent[x]

    def unite(self, x:int, y:int) -> None:
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return
        if self.size[root_x] < self.size[root_y]:
            self.parent[root_x] = root_y
            self.size[root_y] += self.size[root_x]
            self.size[root_x] = 0
        else:
            self.parent[root_y] = root_x
            self.size[root_x] += self.size[root_y]
            self.size[root_y] = 0

    def same(self, x:int, y:int) -> bool:
        return self.find(x) == self.find(y)
    
n,q = map(int, input().split())
uf = UnionFind(n)
for _ in range(q):
    com,x,y = map(int, input().split())
    if com == 0:
        uf.unite(x,y)
    elif com == 1:
        if uf.same(x,y):
            print("1")
        else:
            print("0")