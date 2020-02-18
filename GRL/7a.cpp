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
    std::vector<std::vector<std::pair<ll,ll>>> list;  // 隣接リスト
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

class HopcroftKarp{
    public:
    Graph G;  // 0-(setx-1) , setx-(setx+sety-1)が二部グラフの各頂点集合になっている前提
    ll setx, sety;
    std::vector<ll> dist, match;
    std::vector<bool> visited, vv;

    HopcroftKarp(Graph G, ll x) : G(G), setx(x),sety(G.v-setx), dist(setx,-1), match(sety,-1), visited(setx, false){}

    void bfs(){
        dist.assign(setx, -1);
        std::queue<ll> que;
        for(ll i=0; i<setx; i++)if(!visited[i]){
            que.push(i);
            dist[i]=0;
        }
        while(!que.empty()){
            ll a = que.front(); que.pop();
            for(ll i=0; i<G.list[a].size(); i++){
                ll c = match[G.list[a][i].first - setx];
                if(c>=0 && dist[c]==-1){
                    dist[c] = dist[a] + 1;
                    que.push(c);
                }
            }
        }
    }
    bool dfs(ll a){
        vv[a] = true;
        for(ll i=0; i<G.list[a].size(); i++){
            ll c = match[G.list[a][i].first - setx];
            if(c<0 || (!vv[c] && dist[c]==dist[a]+1 && dfs(c))){
                match[G.list[a][i].first - setx] = a;
                visited[a] = true;
                return true;
            }
        }
        return false;
    }
    ll Bipartite_Matching(){
        ll ret = 0;
        while(true){
            bfs();
            vv.assign(setx, false);
            ll fl = 0;
            for(ll i=0; i<setx; i++){
                if(!visited[i] && dfs(i)) fl++;
            }
            if(fl==0) return ret;
            ret += fl;
        }
    }
};


int main(){
    ll xs,ys,e,x,y;
    cin >> xs >> ys >> e;
    Graph G(xs+ys, true);
    REP(i,e){
        cin >> x >> y;
        G.connect(x,xs+y,1); // 0, ... ,xs-1, 0(xs), ... ,ys-1(xs+ys-1)
    }
    HopcroftKarp hk(G, xs);
    cout << hk.Bipartite_Matching() << endl;
}