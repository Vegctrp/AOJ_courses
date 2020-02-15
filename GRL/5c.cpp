#include<stdio.h>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<queue>
#include<set>

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
    std::vector<std::vector<std::pair<ll,ll>>> list;  // 隣接リスト v,cost
    //std::vector<std::vector<ll>> matrix; // 隣接行列

    Graph() : isDirected(false){ init(0); }
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

class LowestCommonAncestor{ // 根付き木の最小共通祖先(ダブリング) 構築O(VlogV) query O(logV)
    public:
    int LOG = 1;
    Graph G;
    std::vector<ll> depth;
    std::vector<std::vector<ll>> table; // table[k][v] : vから2^k回親をたどったnode

    LowestCommonAncestor(Graph G) : G(G), depth(G.v, 0){
        ll val = 1;
        while(val < G.v) {val <<= 1; LOG++;}
        table.assign(LOG, std::vector<ll>(G.v, -1));
    }
    void dfs(ll idx, ll parent, ll dep){
        table[0][idx] = parent;
        depth[idx] = dep;
        for(auto to : G.list[idx]){
            if(to.first != parent) dfs(to.first, idx, dep+1);
        }
    }
    void build(){
        dfs(0, -1, 0);
        for(ll k=0; k+1<LOG; k++){
            for(ll i=0; i<table[k].size(); i++){
                if(table[k][i] == -1) table[k+1][i] = -1;
                else table[k+1][i] = table[k][table[k][i]];
            }
        }
    }
    ll query(ll u, ll v){
        if(depth[u] > depth[v]) std::swap(u,v);
        for(ll i=LOG-1; i>=0; i--){
            if(((depth[v] - depth[u]) >> i ) & 1) v = table[i][v];
        }
        if(u==v) return u;
        for(ll i=LOG-1; i>=0; i--){
            if(table[i][u] != table[i][v]){
                u = table[i][u];
                v = table[i][v];
            }
        }
        return table[0][u];
    }
};

int main(){
    ll n,q,k,c,u,v;
    cin >> n;
    Graph G(n, false);
    REP(i,n){
        cin >> k;
        REP(j,k){
            cin >> c;
            G.connect(i, c);
        }
    }
    LowestCommonAncestor lca(G);
    lca.build();
    cin >> q;
    REP(i,q){
        cin >> u >> v;
        cout << lca.query(u,v) << endl;
    }
    return 0;
}