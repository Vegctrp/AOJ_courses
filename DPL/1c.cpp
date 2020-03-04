#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    int n,wei;
    int maxv=-1;
    int v[105]={};
    int w[105]={};
    cin>>n>>wei;
    REP(i,n)cin>>v[i]>>w[i];

    int mat[105][10005];
    REP(i,105)REP(j,10005)mat[i][j]=-(1<<30);
    mat[0][0]=0;
    REP(i,n)REP(j,wei+1){
        if(j<w[i])mat[i+1][j]=mat[i][j];
        else mat[i+1][j] = max(mat[i][j], mat[i+1][j-w[i]]+v[i]);
        if(maxv<mat[i+1][j])maxv=mat[i+1][j];
    }
    cout<<maxv<<endl;
    return 0;
}