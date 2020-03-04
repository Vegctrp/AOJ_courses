#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll a;
    REP(i,10000){
        cin >> a;
        if(a==0)break;
        cout<< "Case " << i+1 << ": " << a<<endl;
    }
    return 0;
}