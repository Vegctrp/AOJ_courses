#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll a,b;
    cin >> a >> b;
    if(a<b) cout << "a < b" << endl;
    else if(a>b) cout << "a > b" << endl;
    else cout << "a == b" << endl;
    return 0;
}