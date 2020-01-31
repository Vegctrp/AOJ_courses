#include<stdio.h>
#include<vector>
#include<iostream>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

template <typename Abel=ll> class WeightedUnionFind {
    public:
    std::vector<ll> parent;
    std::vector<ll> sizes;
    std::vector<Abel> diff_weight;
    Abel Abel_unit = 0;                 //可換群の単位元 1
    Abel Abel_plus(Abel a, Abel b){      //可換群の加法 ab
        return a+b;
    }
    Abel Abel_minus(Abel a, Abel b){    //ab^-1
        return a-b;
    }

    WeightedUnionFind(ll N) : parent(N), sizes(N, 1), diff_weight(N) {
        for(ll i=0; i<N; i++){
            parent[i] = i;
            diff_weight[i] = Abel_unit;
        }
    }
    ll find(ll x){     //経路圧縮しながらルート探索
        if(x==parent[x]) return x;
        ll r = find(parent[x]);
        diff_weight[x] = Abel_plus(diff_weight[x], diff_weight[parent[x]]);
        return parent[x]=r;
    }
    bool unite(ll x, ll y, Abel w){ // yがxよりw大きいように結合
        w = Abel_plus(w, weight(x));
        w = Abel_minus(w, weight(y));
        ll x_class = find(x);
        ll y_class = find(y);
        if(x_class == y_class) return false;
        if(sizes[x_class] < sizes[y_class]){
            std::swap(x_class, y_class);
            w = Abel_minus(Abel_unit, w);
        }
        parent[y_class] = x_class;
        sizes[x_class] += sizes[y_class];
        sizes[y_class] = 0;
        diff_weight[y_class] = w;
        return true;
    }
    bool same(ll x, ll y){   // 同じクラスか判定
        return find(x)==find(y);
    }
    ll size(ll x){  //クラスの要素数
        return sizes[find(x)];
    }
    Abel weight(ll x){  // ルートからの距離
        find(x);  // 経路圧縮
        return diff_weight[x];
    }
    Abel diff(ll x, ll y){  // 二点の距離(x,yが違うクラスの場合は未定義)
        return Abel_minus(weight(y), weight(x));
    }
};


int main(){
    WeightedUnionFind<ll> uf(100005);
    int n,q, com, x, y, z;

    cin >> n >> q;
    REP(i,q){
        cin >> com;
        if(com==0){
            cin >> x >> y >> z;
            uf.unite(x,y,z);
        }
        else{
            cin >> x >> y;
            if(uf.find(x)==uf.find(y)){
                cout << uf.diff(x,y) << endl;
            }
            else{
                cout << "?" << endl;
            }
        }
    }
    return 0;
}