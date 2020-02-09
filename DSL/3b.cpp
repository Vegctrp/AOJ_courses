#include<stdio.h>
#include<vector>
#include<iostream>
#include<functional>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll n,k,x;
    vector<ll> list;
    cin >> n >> k;
    REP(i,n){
        cin >> x;
        list.push_back(x-1);
    }
    ll l=0, r=0;
    ll ans = 1<<30;
    std::vector<ll> stat; stat.assign(k, 0);
    ll sum=0;
    for(l=0; l<n; l++){
        if(l!=0)if(list[l-1]<k){
            if(stat[list[l-1]]==1) sum--;
            stat[list[l-1]]--;
        }
        if(r<l){ r=l; stat.clear(); sum=0; }
        while(sum < k && r<n){
            if(list[r]<k){
                if(stat[list[r]]==0) sum++;
                stat[list[r]]++;
            }
            r++;
        }
        /*
        cout << "###" << l << " " << r;
        REP(i,k) cout << ":" << stat[k];
        cout << " " << ans << endl;*/
        if(sum >= k)if(ans > r-l) ans = r-l;
    }
    if(ans == 1<<30) cout << "0" << endl;
    else cout << ans << endl;
}