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

class FordFulkerson{
    public:
    typedef struct El{
        ll to, cost, rev; // rev : toの隣接リストにおける辺の番号
        El(ll t, ll c, ll r): to(t),cost(c),rev(r){}
    } El;

    Graph G;
    std::vector<bool> visited;
    std::vector<std::vector<El>> flow, remain;

    FordFulkerson(Graph G) : G(G), visited(G.v, false){
        flow.assign(G.v, std::vector<El>());
        remain.assign(G.v, std::vector<El>());
        for(auto e : G.edges){
            flow[e.from].push_back(El(e.to, 0, flow[e.to].size()));
            flow[e.to].push_back(El(e.from, -1, flow[e.from].size()-1));  // 流れないはずの辺
            remain[e.from].push_back(El(e.to, e.cost, remain[e.to].size()));
            remain[e.to].push_back(El(e.from, 0, remain[e.from].size()-1));
        }
    }
    ll dfs(ll v, ll t, ll fl){
        if(v==t) return fl;
        visited[v] = true;
        for(ll i=0; i<remain[v].size(); i++){
            // edge : remain[v][i]
            if(!visited[remain[v][i].to] && remain[v][i].cost>0){
                ll d = dfs(remain[v][i].to, t, std::min(fl, remain[v][i].cost));
                if(d>0){
                    remain[v][i].cost -= d;
                    remain[remain[v][i].to][remain[v][i].rev].cost += d;
                    if(flow[v][i].cost == -1){
                        if(flow[flow[v][i].to][flow[v][i].rev].cost >= d) flow[flow[v][i].to][flow[v][i].rev].cost -= d;
                        else{ cout << "error" << endl;}
                    }
                    flow[v][i].cost += d;
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
            ll f = dfs(s, t, 1LL<<62);
            if(f==0) break;
            flow += f;
        }
        return flow;
    }
};

int main(){
    ll v,e,u,vv,c;
    cin >> v >> e;
    Graph G(v, true);
    REP(i,e){
        cin >> u >> vv >> c;
        G.connect(u,vv,c);
    }
    FordFulkerson ff(G);
    cout << ff.max_flow(0,v-1) << endl;
    return 0;
}