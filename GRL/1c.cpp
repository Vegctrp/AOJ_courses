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

std::vector<std::vector<ll>> WarshallFloyd(Graph G, ll inf){
    std::vector<std::vector<ll>> matrix;
    matrix.assign(G.v, std::vector<ll>(G.v, inf));
    for(ll i=0; i<G.v; i++)matrix[i][i]=0;     // 負閉路が存在する場合matrix[i][i]が0でなくなる
    for(auto i : G.edges){ matrix[i.from][i.to] = i.cost; }
    for(ll k=0; k<G.v; k++)for(ll i=0; i<G.v; i++)for(ll j=0; j<G.v; j++){
        if(matrix[i][k]==inf || matrix[k][j]==inf) continue;
        matrix[i][j] = std::min(matrix[i][j], matrix[i][k]+matrix[k][j]);
    }
    return matrix;
}

int main(){
    int v,e, s,t,d;
    cin >> v >> e;
    Graph gr(v, true);
    REP(i,e){
        cin >> s >> t >> d;
        gr.connect(s,t,d);
    }
    ll inf = 1LL<<62;
    std::vector<std::vector<ll>> ans = WarshallFloyd(gr, inf);
    bool negative = false;
    REP(i,v)if(ans[i][i]!=0)negative=true;
    if(negative){cout<< "NEGATIVE CYCLE"<<endl; return 0;}
    for(auto i : ans){
        REP(j,v){
            if(i[j]==inf) cout << "INF";
            else cout << i[j];
            if(j!=v-1)cout << " ";
            else cout << endl;
        }
    }
}