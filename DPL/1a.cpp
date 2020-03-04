#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    int n,m,cc;
    vector<int> c; c.clear();
    cin>>n>>m;
    REP(i,m){
        cin>>cc;
        c.push_back(cc);
    }
    int mat[25][50005]={};
    REP(i,25)REP(j,50005)mat[i][j]=1<<30;
    mat[0][0]=0;
    REP(i,m){
        REP(j,n+1){
            if(j<c[i])mat[i+1][j]=mat[i][j];
            else mat[i+1][j] = min(mat[i][j], mat[i+1][j-c[i]]+1);
        }
    }
    cout<<mat[m][n]<<endl;
    return 0;
}