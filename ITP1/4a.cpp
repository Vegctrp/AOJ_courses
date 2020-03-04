#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll a,b;
    cin >> a>>b;
    cout << a/b << " " << a%b << " " <<setprecision(13)<<std::fixed<< (double)a/b << endl;
    return 0;
}