#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll a,b;
    REP(i,10000){
        cin >> a>>b;
        if(a==0&&b==0)break;
        if(a>b)swap(a,b);
        cout << a << " " << b <<endl;
    }
    return 0;
}