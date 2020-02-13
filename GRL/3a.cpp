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

class lowlink{
    public:
    Graph G; // 無向グラフ
    std::vector<ll> used, ord, low;
    std::vector<ll> articulation; // 連結点
    std::vector<Graph::Edge> bridge; // 橋

    lowlink(Graph G) : G(G){
        used.assign(G.v, 0);
        ord.assign(G.v, 0);
        low.assign(G.v, 0);
    }

    ll dfs(ll idx, ll k, ll parent){
        used[idx] = true;
        ord[idx] = k++;
        low[idx] = ord[idx];
        bool isArticulation = false;
        int child_num = 0;
        for(auto to : G.list[idx]){
            if(!used[to.first]){
                child_num++;
                k = dfs(to.first, k, idx);
                low[idx] = min(low[idx], low[to.first]);
                isArticulation |= (parent != -1 && low[to.first] >= ord[idx]);
                if(ord[idx] < low[to.first]){
                    if(idx < to.first)bridge.push_back(Graph::Edge(idx, to.first, to.second));
                    else bridge.push_back(Graph::Edge(to.first, idx, to.second));
                }
            }
            else if(to.first != parent){
                low[idx] = std::min(low[idx], ord[to.first]);
            }
        }
        isArticulation |= (parent==-1 && child_num>1);
        if(isArticulation) articulation.push_back(idx);
        return k;
    }
    void build(){
        ll k=0;
        for(ll i=0; i<G.v; i++){
            if(!used[i]) k = dfs(i, k, -1);
        }
        std::sort(articulation.begin(), articulation.end());
        std::sort(bridge.begin(), bridge.end(), [](Graph::Edge a, Graph::Edge b){return (a.from==b.from) ? a.to>b.to : a.from>b.from; });
    }
};

int main(){
    ll v,e,s,t;
    cin >> v >> e;
    Graph G(v);
    REP(i,e){
        cin >> s >> t;
        G.connect(s,t);
    }
    lowlink low(G);
    low.build();
    for(auto i : low.articulation){
        cout << i << endl;
    }
}