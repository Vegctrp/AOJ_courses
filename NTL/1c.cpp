#include<stdio.h>
#include<iostream>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

ll gcd(ll p, ll q){
    if(p < q)std::swap(p,q);
    if(p % q == 0) return q;
    else return gcd(q, p%q);
}

ll lcm(ll p, ll q){
    return p*q/gcd(p,q);
}

int main(){
    int n;
    int a[11];
    cin >> n;
    REP(i,n)cin >> a[i];
    ll ans=a[0];
    REP(i,n-1){
        ans = lcm(ans, a[i+1]);
    }
    cout << ans << endl;
}