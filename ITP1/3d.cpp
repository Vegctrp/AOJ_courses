#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll a,b,c;
    cin >> a>>b>>c;
    int ans=0;
    for(int i=a; i<=b; i++){
        if(c%i==0)ans++;
    }
    cout << ans << endl;
    return 0;
}