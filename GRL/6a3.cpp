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

template<typename FLOWTYPE> class Dinic{ // 最大流 maxO(EV^2)
    public:
    FlowGraph<FLOWTYPE,ll> G;
    std::vector<ll> level, iter;
    Dinic(FlowGraph<FLOWTYPE,ll> G) : G(G){}

    void bfs(ll s){
        level.assign(G.v, -1);
        level[s] = 0;
        std::queue<ll> que; que.push(s);
        while(!que.empty()){
            ll v = que.front(); que.pop();
            for(ll i=0; i<G.list[v].size(); i++){
                FlowGraph<ll,ll>::Edge e = G.edges[G.list[v][i]];
                if(level[e.to]<0 && e.cap>0){
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }
    FLOWTYPE dfs(ll v, ll t, ll fl){
        if(v==t)return fl;
        for(ll i=iter[v]; i<G.list[v].size(); i++){
            iter[v] += 1;
            FlowGraph<ll, ll>::Edge e = G.edges[G.list[v][i]];
            FlowGraph<ll, ll>::Edge re = G.edges[G.list[e.to][e.tp]];
            if(level[v] < level[e.to] && e.cap>0){
                FLOWTYPE d = dfs(e.to, t, std::min(fl, e.cap));
                if(d>0){
                    G.edges[G.list[v][i]].cap -= d;
                    G.edges[G.list[e.to][e.tp]].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    FLOWTYPE max_flow(ll s, ll t){
        level.assign(G.v, -1);
        iter.assign(G.v, 0);
        FLOWTYPE flow = 0;
        while(true){
            bfs(s);
            if(level[t] < 0) return flow;
            iter.assign(G.v, 0);
            FLOWTYPE f = dfs(s,t,1LL<<62);
            if(f>0) flow += f;
        }
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
    Dinic<ll> ff(G);
    cout << ff.max_flow(0,v-1) << endl;
    return 0;
}