#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll n;
    ll a[105]={};
    cin>>n;
    REP(i,n)cin>>a[i];
    REP(i,n){
        if(i!=0)cout<<" ";
        cout<<a[n-i-1];
    }
    cout<<endl;
}