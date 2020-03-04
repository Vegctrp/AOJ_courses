#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll x;
    cin >> x;
    cout << x/3600 << ":" << (x%3600)/60 << ":" << x%60 << endl;
    return 0;
}