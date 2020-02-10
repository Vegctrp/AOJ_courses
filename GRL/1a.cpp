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
    ll INF = 1 << 30;
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

std::vector<ll> Dijkstra(Graph G, ll start, ll inf){ // 点startから各点への最短経路長
    ll INF = inf;
    std::vector<ll> dist(G.v, INF);
    std::priority_queue<std::pair<ll,ll>, std::vector<std::pair<ll,ll>>, std::greater<std::pair<ll,ll>>> que;
    dist[start] = 0;
    que.push(std::make_pair(0, start));

    while(!que.empty()){
        std::pair<ll,ll> p = que.top();
        que.pop();
        if(dist[p.second] < p.first) continue;
        for(auto i : G.list[p.second]){
            if(dist[i.first] > dist[p.second] + i.second){
                dist[i.first] = dist[p.second] + i.second;
                que.push(std::make_pair(dist[i.first], i.first));
            }
        }
    }
    return dist;
}

int main(){
    int v,e,r, s,t,d;
    cin >> v >> e >> r;
    Graph gr(v, true);
    REP(i,e){
        cin >> s >> t >> d;
        gr.connect(s,t,d);
    }
    std::vector<ll> ans = Dijkstra(gr, r, 1<<30);
    for(auto i : ans){
        if(i==(1<<30)) cout << "INF" << endl;
        else cout << i << endl;
    }
}