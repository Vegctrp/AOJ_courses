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

struct Diameter{ // 無向木の直径(二点間の最短距離の最大値)
    ll ans = 0;
    Graph G;
    ll rec(ll v, ll parent){
        std::vector<ll> children;
        for(auto e : G.list[v]){
            if(e.first == parent) continue;
            children.push_back(rec(e.first, v) + e.second);
        }
        sort(children.begin(), children.end(), std::greater<ll>());
        if(children.size()==0)return 0;
        else if(children.size()==1){ if(ans < children[0]) ans = children[0]; }
        else { if(ans < children[0]+children[1]) ans = children[0]+children[1]; }
        return children[0];
    }
    ll operator()(Graph G){ this->G=G; rec(0, -1); return ans; }
} Diameter;

int main(){
    ll n,s,t,w;
    cin >> n;
    Graph G(n, false);
    REP(i,n-1){
        cin >> s >> t >> w;
        G.connect(s,t,w);
    }
    cout << Diameter(G) << endl;
}