#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll w,h,x,y,r;
    cin >> w >> h >> x >> y >> r;
    if(r<=x && x<=w-r && r<=y && y<= h-r)cout<< "Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}