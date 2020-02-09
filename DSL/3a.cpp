#include<stdio.h>
#include<vector>
#include<iostream>
#include<functional>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll n,s,x;
    vector<ll> list;
    cin >> n >> s;
    REP(i,n){
        cin >> x;
        list.push_back(x);
    }
    ll l=0, r=0;
    ll ans = 1<<30;
    ll stat = 0;
    for(l=0; l<n; l++){
        if(l!=0) stat -= list[l-1];
        if(r<l){ r=l; stat=0; }
        while(stat < s && r<n) stat += list[r++];
        //cout << "###" << l << " " << r << " " << stat << " " << ans << endl;
        if(stat >= s)if(ans > r-l) ans = r-l;
    }
    if(ans == 1<<30) cout << "0" << endl;
    else cout << ans << endl;
}