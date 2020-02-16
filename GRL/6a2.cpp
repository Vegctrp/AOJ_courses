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


template<typename FLOWTYPE, typename COSTTYPE> class FlowGraph{
    public:
    typedef struct Edge{
        ll id, from, fp, to, tp;
        FLOWTYPE cap, icap;
        COSTTYPE cost;
        Edge(ll from, ll fp, ll to, ll tp, FLOWTYPE cap, COSTTYPE cost, ll id=-1)
                : id(id), from(from), fp(fp), to(to), tp(tp), cap(cap), icap(cap), cost(cost){}
    } Edge;

    bool isDirected;
    ll v;
    std::vector<Edge> edges;
    std::vector<std::vector<ll>> list;

    FlowGraph() : isDirected(false) { init(0); }
    FlowGraph(ll n, bool isDirected=false) : isDirected(isDirected) { init(n); }

    void init(ll n){
        v = n;
        edges.clear();
        list.assign(n, std::vector<ll>());
    }
    void add_edge(ll from, ll to, FLOWTYPE cap, COSTTYPE cost){
        edges.push_back(Edge(from, list[from].size(), to, list[to].size()+1, cap, cost, edges.size()));
        list[from].push_back(edges.size()-1);
        list[to].push_back(edges.size()-1);
        edges.push_back(Edge(to, list[to].size(), from, list[from].size()-1, 0, -cost, edges.size()));
        list[from].push_back(edges.size()-1);
        list[to].push_back(edges.size()-1);
    }
    void add_undirected_edge(ll from, ll to, FLOWTYPE cap, COSTTYPE cost){
        edges.push_back(Edge(from, list[from].size(), to, list[to].size()+1, cap, cost, edges.size()));
        list[from].push_back(edges.size()-1);
        list[to].push_back(edges.size()-1);
        edges.push_back(Edge(to, list[to].size(), from, list[from].size()-1, cap, cost, edges.size()));
        list[from].push_back(edges.size()-1);
        list[to].push_back(edges.size()-1);
    }
};

template<typename FLOWTYPE> class FordFulkerson{ // 最大流 maxO(maxflow*|E|)
    public:
    FlowGraph<FLOWTYPE,ll> G;
    std::vector<bool> visited;
    FordFulkerson(FlowGraph<ll,ll> G) : G(G){}
    FLOWTYPE dfs(ll v, ll t, FLOWTYPE fl){
        if(v==t) return fl;
        visited[v] = true;
        for(ll i=0; i<G.list[v].size(); i++){
            FlowGraph<ll,ll>::Edge e = G.edges[G.list[v][i]];
            if(!visited[e.to] && e.cap>0){
                FLOWTYPE d = dfs(e.to, t, std::min(fl, e.cap));  // std::min(FLOWTYPE, FLOWTYPE)
                if(d > 0){  // FLOWTYPE > FLOWTYPE
                    G.edges[G.list[v][i]].cap -= d;   // FLOWTYPE - FLOWTYPE
                    G.edges[G.list[e.to][e.tp]].cap += d;  // FLOWTYPE + FLOWTYPE
                    return d;
                }
            }
        }
        return 0;
    }
    ll max_flow(ll s, ll t){
        ll flow = 0;
        while(true){
            visited.assign(G.v, false);
            ll f = dfs(s,t,1LL<<62);
            if(f==0)break;
            flow += f;
        }
        return flow;
    }
};

int main(){
    ll v,e,u,vv,c;
    cin >> v >> e;
    FlowGraph<ll,ll> G(v, true);
    REP(i,e){
        cin >> u >> vv >> c;
        G.add_edge(u,vv,c,1);
    }
    FordFulkerson<ll> ff(G);
    cout << ff.max_flow(0,v-1) << endl;
    return 0;
}