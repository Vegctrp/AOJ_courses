#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll p[4][3][10]={};
    ll n,b,f,r,v;
    cin>>n;
    REP(i,n){
        cin>>b>>f>>r>>v;
        p[b-1][f-1][r-1]+=v;
    }
    REP(i,4){
        if(i!=0){
            REP(j,20)cout<<"#";
            cout<<endl;
        }
        REP(j,3){
            REP(k,10){
                cout<<" "<<p[i][j][k];
            }
            cout<<endl;
        }
    }
    return 0;
}