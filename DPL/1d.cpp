#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

template<class T=ll> ll LIS(std::vector<T> v, T inf=1LL<<62, bool is_strong=true){ // LongestIncreasingSubsequence 最長増加部分列 O(nlogn)
    std::vector<T> dp(v.size(), inf);  // 1indexed, dp[i]:長さiの増加部分列の最後尾の要素の最小値
    for(ll i=0; i<v.size(); i++){
        if(is_strong) *std::lower_bound(dp.begin(), dp.end(), v[i]) = v[i];
        else *std::upper_bound(dp.begin(), dp.end(), v[i]) = v[i];
    }
    return std::lower_bound(dp.begin(),dp.end(), inf) - dp.begin();
}

int main(){
    ll n,a;
    vector<ll> v; v.clear();
    cin>>n;
    REP(i,n){
        cin>>a;
        v.push_back(a);
    }
    cout << LIS(v) << endl;
    return 0;
}