#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll a;
    std:vector<int> l;
    l.clear();
    REP(i,3){
        cin >> a;
        l.push_back(a);
    }
    sort(l.begin(), l.end());
    cout << l[0] << " " << l[1] << " " << l[2] << endl;
    return 0;
}