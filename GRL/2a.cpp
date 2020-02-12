#include<stdio.h>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<queue>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class Graph{
    public:
    typedef struct Edge{
        ll from, to, cost;
        Edge(ll f, ll t, ll c): from(f),to(t),cost(c){}
    } Edge;

    bool isDirected;
    ll INF = 1LL << 62;
    ll v; // 頂点数
    std::vector<Edge> edges;  // 辺のリスト
    std::vector<std::vector<std::pair<ll,ll>>> list;  // 隣接リスト
    //std::vector<std::vector<ll>> matrix; // 隣接行列

    Graph(ll n, bool isDirected=false) : isDirected(isDirected) { init(n); }
    void init(ll n){
        v=n;
        edges.clear();
        list.assign(n, std::vector<std::pair<ll,ll>>());
        //matrix.assign(n, std::vector<ll>(n, INF));
    }
    void connect(ll from, ll to){
        con(from, to, 1);
        if(!isDirected) con(to, from, 1);
    }
    void connect(ll from, ll to, ll cost){
        con(from, to, cost);
        if(!isDirected) con(to, from, cost);
    }
    void con(ll from, ll to, ll cost){
        edges.push_back(Edge(from,to,cost));
        list[from].push_back(std::make_pair(to, cost));
        //matrix[from][to] = cost;
    }
};

class UnionFind {
    public:
    std::vector<ll> parent;
    std::vector<ll> sizes;
    UnionFind(ll N) : parent(N), sizes(N, 1) {
        for(ll i=0; i<N; i++) parent[i]=i;
    }
    ll find(ll x){
        if(x==parent[x]) return x;
        return parent[x]=find(parent[x]);
    }
    void unite(ll x, ll y){
        ll x_class = find(x);
        ll y_class = find(y);
        if(x_class == y_class) return;
        if(sizes[x_class] < sizes[y_class])std::swap(x_class, y_class);
        parent[y_class] = x_class;
        sizes[x_class] += sizes[y_class];
        sizes[y_class] = 0;
    }
    bool same(ll x, ll y){
        return find(x)==find(y);
    }
    ll size(ll x){
        return sizes[find(x)];
    }
};

Graph Kruskal(Graph G){
    Graph ans(G.v, false);
    UnionFind uf(G.v);
    std::vector<Graph::Edge> edges = G.edges;
    sort(edges.begin(), edges.end(), [](Graph::Edge a, Graph::Edge b){return a.cost<b.cost;} );
    for(ll i=0; i<edges.size(); i++){
        if(!uf.same(edges[i].from, edges[i].to)){
            uf.unite(edges[i].from, edges[i].to);
            ans.connect(edges[i].from, edges[i].to, edges[i].cost);
        }
    }
    return ans;
}

Graph Prim(Graph G){
    Graph ans(G.v, false);
    std::vector<bool> visited(G.v, false);
    std::priority_queue<std::pair<ll,std::pair<ll,ll>>, std::vector<std::pair<ll,std::pair<ll,ll>>>, std::greater<std::pair<ll,std::pair<ll,ll>>>> que;
    que.push(std::make_pair(0, std::make_pair(0,0)));  //頂点0からスタート
    //visited[0] = true;

    while(!que.empty()){
        std::pair<ll,std::pair<ll,ll>> p = que.top();
        ll cost = p.first;
        ll from = p.second.first;
        ll to = p.second.second;
        que.pop();
        if(visited[to])continue;
        visited[to] = true;
        if(from!=to) ans.connect(from, to, cost);
        for(auto i : G.list[to]) que.push(std::make_pair(i.second, std::make_pair(to, i.first)));
    }
    return ans;
}

int main(){
    ll v,e;
    cin >> v >> e;
    ll s,t,w;
    Graph G(v, false);
    REP(i,e){
        cin >> s >> t >> w;
        G.connect(s,t,w);
    }
    //Graph sp = Kruskal(G);
    Graph sp = Prim(G);
    ll ans=0;
    for(auto i : sp.edges){
        ans += i.cost;
    }
    cout << ans/2 << endl;
}