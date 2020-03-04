#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll h,w;
    while(true){
        cin>>h>>w;
        if(h==0&&w==0)return 0;
        REP(i,h){
            REP(j,w){
                if((i+j)%2==0)cout<<"#";
                else cout<<".";
            }
            cout<<endl;
        }
        cout<<endl;
    }
}