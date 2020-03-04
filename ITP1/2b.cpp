#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll x,y,z;
    cin >> x >> y >> z;
    if(x<y&&y<z) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}