#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll n,x;
    ll a[4][13]={};
    char c[4]={'S','H','C','D'};
    cin>>n;
    char cc;
    REP(i,n){
        cin>>cc>>x;
        REP(j,4){
            if(c[j]==cc)a[j][x-1]=1;
        }
    }
    REP(i,4)REP(j,13){
        if(a[i][j]==0){
            cout<<c[i]<<" "<<j+1<<endl;
        }
    }
    return 0;
}