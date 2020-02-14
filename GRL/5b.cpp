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
    std::pair<ll,ll> vs;
    Graph G;
    std::pair<ll,ll> rec(ll v, ll parent){
        std::vector<std::pair<ll,ll>> children; // cost, v
        for(auto e : G.list[v]){
            if(e.first == parent) continue;
            std::pair<ll,ll> chm = rec(e.first, v);
            children.push_back(std::make_pair(chm.first + e.second, chm.second));
        }
        sort(children.begin(), children.end(), [](std::pair<ll,ll> a, std::pair<ll,ll> b){if(a.first==b.first){return a.second>b.second;} return a.first>b.first; } );
        if(children.size()==0)return std::make_pair(0, v);
        else if(children.size()==1){ if(ans < children[0].first) {ans = children[0].first; vs = std::make_pair(v, children[0].second); }  }
        else {
            if(ans < children[0].first + children[1].first) {
                ans = children[0].first + children[1].first;
                vs = std::make_pair(children[0].second, children[1].second);
            } 
        }
        return children[0];
    }
    std::pair<ll,ll> makepair(Graph G){ this->G=G; rec(0,-1); return vs; }
    ll operator()(Graph G){ this->G=G; rec(0, -1); return ans; }
} Diameter;

struct Height{  // 無向木における各点の高さ
    ll ans=0;
    std::vector<ll> md;
    Graph G;
    void rec(ll v, ll parent, ll dist){
        if(md[v]<dist)md[v] = dist;
        for(auto e : G.list[v]){
            if(e.first == parent)continue;
            rec(e.first, v, dist+e.second);
        }
    }
    std::vector<ll> operator()(Graph G){
        this->G=G;
        md.assign(G.v, -1);
        std::pair<ll,ll> dias = Diameter.makepair(G);
        rec(dias.first, -1, 0); rec(dias.second, -1, 0);
        return md;
    }
} Height;

int main(){
    ll n,s,t,w;
    cin >> n;
    Graph G(n, false);
    REP(i,n-1){
        cin >> s >> t >> w;
        G.connect(s,t,w);
    }
    //cout << Diameter(G) << endl;
    //std::pair<ll,ll> a = Diameter.makepair(G);
    //cout << a.first << " " << a.second << endl;
    for(auto i : Height(G)) cout << i << endl;
}