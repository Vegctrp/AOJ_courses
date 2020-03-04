#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

int main(){
    ll n,a;
    ll max=-1000000000;
    ll min=1000000000;
    ll sum=0;
    cin>>n;
    REP(i,n){
        cin>>a;
        sum+=a;
        if(max<a)max=a;
        if(min>a)min=a;
    }
    cout<< min << " " << max<<" " << sum<<endl;
    return 0;
}