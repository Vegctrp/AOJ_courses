from collections.abc import Callable
from typing import TypeVar, Generic

T = TypeVar("T")
class WeightedUnionFind(Generic[T]):
    """Weighted Union-Find.

    各木の根の重みは0(id)であることが保証されている.
    """

    def __init__(
        self,
        n:int,
        abel_id:T,
        abel_calc:Callable[[T,T],T],
        abel_calc_inv:Callable[[T,T],T],
    ) -> None:
        self.parent = list(range(n))
        self.size = [1] * n
        self.weight = [abel_id] * n
        self.abel_id = abel_id
        self.abel_calc = abel_calc
        self.abel_calc_inv = abel_calc_inv

    def find(self, x:int) -> int:
        """xの親を返す. 経路圧縮を行う."""
        if self.parent[x] == x:
            return x
        r = self.find(self.parent[x])
        self.weight[x] = self.abel_calc(self.weight[x], self.weight[self.parent[x]])
        self.parent[x] = r
        return self.parent[x]

    def unite(self, x:int, y:int, w:T) -> bool:
        """yがxよりw大きいように結合.

        結合後の木の根の重みは0(id)のまま.
        結合に成功した場合はTrue, 矛盾が生じた場合はFalseを返す.
        """
        root_x = self.find(x)
        root_y = self.find(y)
        w = self.abel_calc(w, self.get_weight(x))
        w = self.abel_calc_inv(w, self.get_weight(y))
        if root_x == root_y:
            return (self.abel_calc_inv(self.weight[y],self.weight[x]) == w)
        if self.size[root_x] < self.size[root_y]:
            root_x, root_y = root_y, root_x
            w = self.abel_calc_inv(self.abel_id, w)
        self.parent[root_y] = root_x
        self.size[root_x] += self.size[root_y]
        self.size[root_y] = 0
        self.weight[root_y] = w
        return True

    def same(self, x:int, y:int) -> bool:
        return self.find(x) == self.find(y)

    def get_size(self, x:int) -> int:
        """xが属する木のサイズを返す."""
        return self.size[self.find(x)]

    def get_weight(self, x:int) -> T:
        self.find(x)
        if self.parent[self.parent[x]] != self.parent[x]:
            msg = "node x should be compressed"
            raise ValueError(msg)
        return self.weight[x]

    def diff(self, x:int, y:int) -> T:
        return self.abel_calc_inv(self.get_weight(y), self.get_weight(x))

    def show_internal_state(self) -> None:
        print("#####################")
        print("Parent:", self.parent)
        print("Size:", self.size)
        print("Weight:", self.weight)
        print("#####################")


n, q = map(int, input().split())
wuf = WeightedUnionFind(n, 0, lambda x, y: x + y, lambda x, y: x - y)
for _ in range(q):
    inplst = list(map(int, input().split()))
    com = inplst[0]
    if com == 0:
        x,y,w = inplst[1], inplst[2], inplst[3]
        wuf.unite(x,y,w)
        #wuf.show_internal_state()
    elif com == 1:
        x,y = inplst[1], inplst[2]
        if not wuf.same(x,y):
            print("?")
        else:
            print(wuf.diff(x,y))