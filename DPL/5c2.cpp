#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class Mint{
    public:
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

    Mint operator=(Mint a) {v=a.v;return a;}

    friend ostream& operator<<(ostream& os, const Mint& mint){
        os << mint.v;
        return os;
    }
};

class cmbs{
    public:
    vector<Mint> fact, finv, inv;
    cmbs(){
        fact.clear(); finv.clear(); inv.clear();
    }
    void init(int n){
        if(n+1 <= (signed)fact.size())return;
        fact.assign(n+1,1);
        finv.assign(n+1,1);
        inv.assign(n+1,1);

        for(int i=1; i<=n; i++) fact[i] = fact[i-1]*Mint(i);
        finv[n] = Mint(1)/fact[n];
        for(int i=n; i>=1;i--) finv[i-1] = finv[i]*Mint(i);
        for(int i=1; i<=n; i++) inv[i] = finv[i]*fact[i-1];
    }
    Mint comb(long long n, int k){
        if(n<k||k<0)return Mint(0);
        Mint res(1);
        for(int i=0; i<k; i++){
            res *= Mint(n-i);
            res /= Mint(i+1);
        }
        return res;
    }
    Mint C(int n,int k){
        if(n<k||k<0)return Mint(0);
        init(n);
        return fact[n]*finv[n-k]*finv[k];
    }
    Mint P(int n, int k){
        if(n<k || k<0)return Mint(0);
        init(n);
        return fact[n]*finv[n-k];
    }
    Mint H(int n, int k){
        if(n<0||k<0)return Mint(0);
        if(!n&&!k)return Mint(1);
        init(n+k-1);
        return C(n+k-1,k);
    }
    Mint S(int n, int k){
        Mint res;
        init(k);
        for(int i=0; i<=k; i++){
            Mint v = (C(k,i) * Mint(k-i).pow(n));
            if(i%2==0) res+=v;
            else res-=v;
        }
        return res;
    }
};

int main(){
    ll n,k;
    cin>>n>>k;
    if(n<k){
        cout<<"0"<<endl;
        return 0;
    }
    cmbs cmb;
    cout<<cmb.S(n,k)<<endl;
    return 0;
}