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

template<typename FLOWTYPE, typename COSTTYPE> class PrimalDual{
    public:
    FlowGraph<FLOWTYPE,COSTTYPE> G;
    std::vector<COSTTYPE> pot, dist;
    std::vector<ll> prevv, preve;
    COSTTYPE res = 0;
    FLOWTYPE fl;
    PrimalDual(FlowGraph<FLOWTYPE,COSTTYPE> G) : G(G), pot(G.v,0), dist(G.v,-1), prevv(G.v, 0), preve(G.v, 0){}

    COSTTYPE MinCostFlow(ll s, ll t, FLOWTYPE f){
        fl = f;
        while(fl > 0){
            std::priority_queue<std::pair<COSTTYPE, ll>, std::vector<std::pair<COSTTYPE,ll>>, std::greater<std::pair<COSTTYPE,ll>>> que;
            dist.assign(G.v,-1);
            dist[s] = 0;
            que.push(std::make_pair(0,s));
            while(!que.empty()){ //dijkstra
                std::pair<COSTTYPE,ll> p = que.top(); que.pop();
                ll v = p.second;
                if(dist[v] < p.first)continue;
                for(ll i=0; i<G.list[v].size(); i++){
                    ll eid = G.list[v][i];
                    auto e = G.edges[eid];
                    if(e.from==v && e.cap > 0 && (dist[e.to]<0 || dist[e.to]>dist[v]+e.cost+pot[v]-pot[e.to])){
                        dist[e.to] = dist[v] + e.cost + pot[v] - pot[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        que.push(std::make_pair(dist[e.to], e.to));
                    }
                }
            }
            if(dist[t]<0) return -1;
            for(ll v=0; v<G.v; v++) pot[v] += dist[v];
            FLOWTYPE d = fl;
            for(ll v=t; v!=s; v=prevv[v]) d = std::min(d, G.edges[G.list[prevv[v]][preve[v]]].cap);
            fl -= d;
            res += pot[t] * d;
            for(ll v=t; v!=s; v=prevv[v]){
                ll eid = G.list[prevv[v]][preve[v]];
                ll reid = G.list[G.edges[eid].to][G.edges[eid].tp];
                G.edges[eid].cap -= d;
                G.edges[reid].cap += d;
            }
        }
        return res;
    }
};

int main(){
    ll v,e,f;
    cin >> v >> e >> f;
    FlowGraph<ll,ll> G(v,true);
    ll u,vv,c,d;
    REP(i,e){
        cin >> u >> vv >> c >> d;
        G.add_edge(u,vv,c,d);
    }
    PrimalDual<ll,ll> pd(G);
    cout << pd.MinCostFlow(0,v-1,f) << endl;
}