#include<stdio.h>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll n,t,l,r;
    cin >> n >> t;
    std::vector<ll> list(t+1);
    REP(i,n){
        cin >> l >> r;
        list[l]++; list[r]--;
    }
    ll ans=list[0];
    REP(i,t){
        list[i+1] += list[i];
        if(ans < list[i+1]) ans=list[i+1];
    }
    //REP(i,t+1)cout << list[i] << " ";
    //cout << endl;
    cout << ans << endl;
}