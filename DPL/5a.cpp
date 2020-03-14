#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

struct Mint{
    int v;
    const long long MOD = 1000000007;
    Mint():v(0){}
    Mint(signed v):v(v){}
    Mint(long long t){v=t%MOD; if(v<0)v+=MOD;}

    Mint pow(long long k){
        Mint res(1), tmp(v);
        while(k){
            if(k&1)res*=tmp;
            tmp*=tmp;
            k>>=1;
        }
        return res;
    }
    Mint inv(){return pow(MOD-2);}

    Mint& operator+=(Mint a){v+=a.v; if(v>=MOD)v-=MOD; return *this;}
    Mint& operator-=(Mint a){v+=MOD-a.v; if(v>=MOD)v-=MOD; return *this;}
    Mint& operator*=(Mint a){v=1LL*v*a.v%MOD; return *this;}
    Mint& operator/=(Mint a){return (*this)*=a.inv();}
  
    Mint operator+(Mint a) const{return Mint(v)+=a;};
    Mint operator-(Mint a) const{return Mint(v)-=a;};
    Mint operator*(Mint a) const{return Mint(v)*=a;};
    Mint operator/(Mint a) const{return Mint(v)/=a;};

    Mint operator-(){return v ? MOD-v : v;}
    bool operator==(Mint a)const{return v==a.v;}
    bool operator!=(Mint a)const{return v!=a.v;}

    friend ostream& operator<<(ostream& os, const Mint& mint){
        os << mint.v;
        return os;
    }
};


int main(){
    ll n,k;
    cin>>n>>k;
    cout<<Mint(k).pow(n)<<endl;
    return 0;
}