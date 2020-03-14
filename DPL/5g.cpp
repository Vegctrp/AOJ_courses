#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

static const ull mod = 1000000007;
ull modpow(ull p, ull q, ull m=mod){
    ull ans = 1;
    p = p % m;
    for(ull i = 1ULL<<(sizeof(ull)*8-1); i>0; i>>=1){
        if(q&i) ans *= (ans*p)%m;
        else ans *= ans;
        ans %= m;
    }
    return ans;
}

#define MAX 2005
long long fac[MAX], finv[MAX], inv[MAX];

void Com_init(){ //##O(MAX)##
    fac[0] = fac[1] = 1; // x!
    finv[0] = finv[1] = 1; // (x!)^-1
    inv[1] = 1; //x^-1
    for(int i=2;i<MAX;i++){
        fac[i] = (fac[i-1] * i) % mod;
        inv[i] = mod - inv[mod%i] * (mod/i) % mod;
        finv[i] = finv[i-1] * inv[i] % mod;
    }
}
long long Combination(int n, int k){ //calc nCk, max=n, ##O(1)##
    if(n<k || (n<0||k<0))return 0;
    return fac[n] * (finv[k] * finv[n-k] % mod) % mod;
}

ll bell_number(ll n, ll k){ // 区別できるn個のボールを区別できないk個以下の箱に分割する方法の数
    if(n==0) return 1;
    k = min(k,n);
    Com_init();
    ll ret = 0;
    std::vector<ll> pref(k+1);
    pref[0] = 1;
    for(int i=1;i<=k; i++){
        if(i&1) pref[i] = pref[i-1] - finv[i];
        else pref[i] = pref[i-1] + finv[i];
        pref[i] = (pref[i] + mod) % mod;
    }
    for(int i=1; i<=k; i++){
        ret += (((modpow(i,n) * finv[i]) % mod) * pref[k-i])%mod;
        ret %= mod;
    }
    return ret;
}

int main(){
    Com_init();
    ll n,k;
    cin>>n>>k;
    cout<<bell_number(n,k)<<endl;
    return 0;
}