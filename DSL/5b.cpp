#include<stdio.h>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class Rectangles {  // 矩形が入り得る領域のx,yに対してO(xy)
    public:
    ll n, x, y;  // [0,x),[0,y)
    std::vector<ll> xs;  // n番目の長方形の左上のx座標->n*2, 右下のx座標->n*2+1
    std::vector<ll> ys;
    std::vector<std::vector<ll>> ex;

    Rectangles(ll n, ll x, ll y) : n(n), x(x), y(y){
        xs.assign(n*2+1, 0); ys.assign(n*2+1, 0);
        ex.assign(y+1, std::vector<ll>(x+1, 0));
    }

    void push(ll num, ll x1, ll y1, ll x2, ll y2){
        xs[num*2]=x1; xs[num*2+1]=x2;
        ys[num*2]=y1; ys[num*2+1]=y2;
    }
    void build(){
        for(ll i=0; i<n; i++){
            ex[ys[i*2]][xs[i*2]]++;
            ex[ys[i*2+1]][xs[i*2]]--;
            ex[ys[i*2]][xs[i*2+1]]--;
            ex[ys[i*2+1]][xs[i*2+1]]++;
        }
        for(ll xx=0; xx<x; xx++)for(ll yy=0; yy<y; yy++) ex[yy+1][xx] += ex[yy][xx];
        for(ll yy=0; yy<y; yy++)for(ll xx=0; xx<x; xx++) ex[yy][xx+1] += ex[yy][xx];
    }
    ll max_overlap(){
        ll max=-1;
        for(ll xx=0; xx<=x; xx++)for(ll yy=0; yy<=y; yy++)if(ex[yy][xx]>max){
            max = ex[yy][xx];
        }
        return max;
    }
};

int main(){
    ll n, x1, y1, x2, y2;
    cin >> n;
    Rectangles rc(n, 1001, 1001);
    REP(i,n){
        cin >> x1 >> y1 >> x2 >> y2;
        rc.push(i, x1, y1, x2, y2);
    }
    rc.build();
    /*
    REP(y,4){
        REP(x,4)cout << rc.ex[y][x] << " ";
        cout << endl;
    }*/
    cout << rc.max_overlap() << endl;
}