#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    int n,wei;
    int v[105]={};
    int w[105]={};
    cin>>n>>wei;
    REP(i,n)cin>>v[i]>>w[i];
    
    int mat[105][10005]={};
    REP(i,105)REP(j,10005)mat[i][j]=1LL<<30;
    mat[0][0]=0;
    REP(i,n){
        REP(j,10005){
            if(mat[i][j]!=1LL<<30){
                mat[i+1][j]=min(mat[i+1][j], mat[i][j]);
                if(j+v[i]<10005){
                    if(mat[i][j]+w[i]<=wei)mat[i+1][j+v[i]] = min(mat[i+1][j+v[i]], mat[i][j]+w[i]);
                }
            }
        }
    }
    ll maxval=-1;
    REP(i,n+1)REP(j,10005)if(mat[i][j]!=1LL<<30 && maxval<j)maxval=j;
    cout<<maxval<<endl;
    /*REP(i,n+1){
        REP(j,30) cout<<mat[i][j]<<" ";
        cout<<endl;
    }*/
}