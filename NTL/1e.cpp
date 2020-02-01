#include<stdio.h>
#include<vector>
#include<iostream>
#include<map>
#include<tuple>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

std::vector<ll> extended_gcd(ll a, ll b){ //ax+by=zとなる(x,y,z)
    ll s=0;
    ll old_s=1;
    ll t=1;
    ll old_t=0;
    ll r=b;
    ll old_r=a;
    while(r){
        long q =old_r / r;
        std::swap(s, old_s); s-=q*old_s;
        std::swap(t, old_t); t-=q*old_t;
        std::swap(r, old_r); r-=q*old_r;
    }
    std::vector<ll> ans = {old_r, old_s, old_t};
    return ans;
}

int main(){
    ll a,b;
    cin >> a >> b;
    auto ans = extended_gcd(a,b);
    cout << ans[1] << " " << ans[2] << endl;
}