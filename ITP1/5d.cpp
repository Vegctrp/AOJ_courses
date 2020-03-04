#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

void call(ll n);
void check();
void include();
void eend();
ll i,x,n;

void call(ll n){
    i=1;
    check();
}

void check(){
    x=i;
    if(x%3==0){
        cout<<" "<<i;
        eend();
        return;
    }
    include();
}

void include(){
    if(x%10==3){
        cout<<" "<<i;
        eend();
        return;
    }
    x/=10;
    if(x){
        include();
        return;
    }
    eend();
}

void eend(){
    if(++i<=n){
        check();
        return;
    }
    cout<<endl;
}

int main(){
    cin>>n;
    call(n);
    return 0;
}