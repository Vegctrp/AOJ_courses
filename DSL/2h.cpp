#include<stdio.h>
#include<vector>
#include<iostream>
#include<functional>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

// Mq : Monoid(query) , Mo : Monoid(output), (time, num)

template <typename Mq=ll, typename Mo=std::pair<ll, ll>> class DelayedSegmentTree {
    public:
    using Mqq_func = function<Mq(Mq, Mq)>;
    using Mqo_func = function<Mq(Mq, Mo)>;
    using Moo_func = function<Mo(Mo, Mo)>;
    using Mp_func = function<Mo(Mo, ll)>;
    ll size;
    std::vector<Mq> segment;  // 1-indexed 葉ノードは size ~ 2*size-1
    std::vector<Mo> laz;
    ll time;
    Mq Mq_id; Mo Mo_id;
    Mqq_func Mqq_calc; Mqo_func Mqo_calc; Moo_func Moo_calc; Mp_func Mp_calc;

    DelayedSegmentTree(
                ll N, 
                Mq Mq_id = 0,
                Mo Mo_id = std::make_pair(0, 0),
                Mqq_func Mqq_calc = [](ll a, ll b){return a+b;},
                Mqo_func Mqo_calc = [](ll a, std::pair<ll, ll> b){return a+b.second;},
                Moo_func Moo_calc = [](std::pair<ll, ll> a, std::pair<ll, ll> b){return std::make_pair(std::max(a.first, b.first), a.second+b.second);},
                Mp_func Mp_calc = [](std::pair<ll, ll> a, ll b){return std::make_pair(a.first, a.second*b);}) 
            : size(1), time(1), Mq_id(Mq_id), Mo_id(Mo_id), Mqq_calc(Mqq_calc), Mqo_calc(Mqo_calc), Moo_calc(Moo_calc), Mp_calc(Mp_calc) {
        while(size < N) size <<= 1;
        segment.assign(size*2, Mq_id);
        laz.assign(size*2, Mo_id);
    }

    void build(){  // 全てのノードを再計算
        for(ll k=size-1; k>0; k--) segment[k] = Mqq_calc(segment[k*2], segment[k*2+1]);
    }    
    void build(std::vector<Mq> v){
        for(ll k=0; k<size; k++)segment[k+size]=v[k];
        for(ll k=size-1; k>0; k--) segment[k] = Mqq_calc(segment[k*2], segment[k*2+1]);
    }
    void eval(ll len, ll node){
        if(laz[node] == Mo_id) return;
        if(node*2<size*2){
            laz[node*2] = Moo_calc(laz[node*2], laz[node]);
            laz[node*2+1] = Moo_calc(laz[node*2+1], laz[node]);
        }
        segment[node] = Mqo_calc(segment[node], Mp_calc(laz[node], len));
        laz[node] = Mo_id;
    }
    Mq update(ll a, ll b, Mo x, ll node, ll l, ll r){
        eval(r-l, node);
        if(r <= a || b <= l) return segment[node]; // 範囲外
        if(a <= l && r <= b){  // 包含
            laz[node] = Moo_calc(laz[node], x);
            return Mqo_calc(segment[node], Mp_calc(laz[node], r-l));
        }
        return segment[node] = Mqq_calc(update(a, b, x, node*2, l, (l+r)/2), update(a, b, x, node*2+1, (l+r)/2, r));
    }
    Mq update(ll a, ll b, Mo x){
        time++;
        return update(a,b,x,1,0,size);
    }
    Mq query(ll a, ll b, ll node, ll l, ll r){
        eval(r-l, node);
        if(r <= a || b <= l) return Mq_id;
        if(a <= l && r <= b) return segment[node];
        return Mqq_calc(query(a, b, node*2, l, (l+r)/2), query(a, b, node*2+1, (l+r)/2, r));
    }
    Mq query(ll a, ll b){ // [a, b)の演算結果
        return query(a, b, 1, 0, size);
    }

    Mq operator[](const ll &k) const{
        return segment[k+size];
    }
};

int main(){
    ll n,q, com, s, t, x;

    cin >> n >> q;
    DelayedSegmentTree<ll, std::pair<ll, ll>> dst(
        n, 2147483647, std::make_pair(0, 0),
        [](ll a, ll b){return std::min(a,b);},
        [](ll a, std::pair<ll, ll> b){return a+b.second;},
        [](std::pair<ll, ll> a, std::pair<ll, ll> b){
            return std::make_pair(std::max(a.first, b.first), a.second+b.second);
        },
        [](std::pair<ll, ll> a, ll b){
            return std::make_pair(a.first, a.second);
        });
    std::vector<ll> a; a.assign(dst.size, 0);
    dst.build(a);
    REP(i,q){
        cin >> com;
        if(com==0){
            cin >> s >> t >> x;
            dst.update(s, t+1, std::make_pair(dst.time, x));
        }
        else{
            cin >> s >> t;
            cout << dst.query(s,t+1) << endl;
        }
        //for(auto j : dst.segment) if(j==2147483647)cout<<"x"; else cout<<j;
        //cout << "###" << endl;
        //for(auto j : dst.laz) cout << j.first << " " << j.second << "  ";
        //cout << "######" << endl;
    }
    return 0;
}