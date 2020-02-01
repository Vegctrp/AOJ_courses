#include<stdio.h>
#include<iostream>

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

int main(){
    ull m,n;
    cin >> m >> n;
    cout << modpow(m,n) << endl;
}