#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

double pi = 3.141592653589793138;
int main(){
    ll a,b; std::string s;
    while(1==1){
        cin >> a >> s >> b;
        if(s=="+")cout<<a+b<<endl;
        else if(s=="-") cout<<a-b<<endl;
        else if(s=="*") cout<<a*b<<endl;
        else if(s=="/") cout<<a/b<<endl;
        else break;
    }
    return 0;
}