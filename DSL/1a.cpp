#include<stdio.h>
#include<vector>
#include<iostream>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class UnionFind {
    public:
    std::vector<ll> parent;
    std::vector<ll> sizes;
    UnionFind(ll N) : parent(N), sizes(N, 1) {
        for(ll i=0; i<N; i++) parent[i]=i;
    }
    ll find(ll x){
        if(x==parent[x]) return x;
        return parent[x]=find(parent[x]);
    }
    void unite(ll x, ll y){
        ll x_class = find(x);
        ll y_class = find(y);
        if(x_class == y_class) return;
        if(sizes[x_class] < sizes[y_class])std::swap(x_class, y_class);
        parent[y_class] = x_class;
        sizes[x_class] += sizes[y_class];
        sizes[y_class] = 0;
    }
    bool same(ll x, ll y){
        return find(x)==find(y);
    }
    ll size(ll x){
        return sizes[find(x)];
    }
};


int main(){
    UnionFind uf(10005);
    int n,q, com, x, y;

    cin >> n >> q;
    REP(i,q){
        cin >> com >> x >> y;
        if(com==0){
            uf.unite(x,y);
        }
        else{
            cout << uf.same(x,y) << endl;
        }
        //REP(i,13)cout << uf.parent[i] << " ";
        //cout << endl;
    }
}