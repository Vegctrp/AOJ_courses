#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll n,m;
    cin>>n>>m;
    ll a[105][105]={};
    ll b[105]={};
    REP(i,n)REP(j,m){
        cin>>a[i][j];
    }
    REP(i,m)cin>>b[i];
    REP(i,n){
        ll sum=0;
        REP(j,m){
            sum+=a[i][j]*b[j];
        }
        cout<<sum<<endl;
    }
    return 0;
}