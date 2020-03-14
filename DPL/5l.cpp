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
    Mint bell_number(int n, int k){ // 区別できるn個のボールを区別できないk個以下の箱に分割する方法の数
        if(n==0)return Mint(1);
        k = std::min(k,n);
        init(n);
        Mint ret;
        std::vector<Mint> pref(k+1);
        pref[0] = Mint(1);
        for(int i=1; i<=k; i++){
            if(i&1) pref[i] = pref[i-1] - finv[i];
            else pref[i] = pref[i-1] + finv[i];
        }
        for(int i=1; i<=k; i++){
            ret += Mint(i).pow(n) * finv[i] * pref[k-i];
        }
        return ret;
    }
    std::vector<std::vector<Mint>> D(int n, int m){ // 区別できないn個のボールを区別できないk個以下の箱に分割する方法の数
        if(n<0 || m<0){
            std::vector<std::vector<Mint>> dp(1, std::vector<Mint>(1, Mint(0)));
            return dp;
        }
        std::vector<std::vector<Mint>> dp(n+1, std::vector<Mint>(m+1, Mint(0)));
        dp[0][0] = Mint(1);
        for(int i=0; i<=n; i++){
            for(int j=1; j<=m; j++){
                if(i>=j)dp[i][j] = dp[i][j-1] + dp[i-j][j];
                else dp[i][j] = dp[i][j-1];
            }
        }
        return dp;
    }
};

int main(){
    int n,k;
    cin>>n>>k;
    cmbs cmb;
    if(n-k<0)cout<<"0"<<endl;
    else cout<<cmb.D(n-k,k)[n-k][k]<<endl;
    return 0;
}