#include<stdio.h>
#include<vector>
#include<iostream>
#include<deque>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class slide_minimum{
    public:
    std::vector<ll> list;
    std::vector<ll> ans;
    ll n;   // listの長さ
    ll wl;  // 枠の大きさ
    std::deque<ll> deq;

    slide_minimum(ll n, ll l, std::vector<ll> list) : n(n), wl(l){
        for(ll i=0; i<n; i++) this->list.push_back(list[i]);
    }
    std::vector<ll> get(){
        for(ll i=0; i<n; i++){
            while(!deq.empty() && list[deq.back()] >= list[i]) deq.pop_back();
            deq.push_back(i);

            if(i+1 >= wl){
                ans.push_back(list[deq.front()]);
                if(deq.front()==i+1-wl)deq.pop_front();
            }
        }
        return this->ans;
    }
};

int main(){
    ll n,l,a;
    vector<ll> list;
    //vector<ll> ans;
    cin >> n >> l;
    REP(i,n){
        cin >> a;
        list.push_back(a);
    }

    slide_minimum sm(n, l, list);
    vector<ll> ans = sm.get();

    /*
    std::deque<ll> deq;

    for(ll i=0; i<n; i++){
        while(!deq.empty() && list[deq.back()] >= list[i]) deq.pop_back();
        deq.push_back(i);

        if(i+1 >= l){
            ans.push_back(list[deq.front()]);
            if(deq.front()==i+1-l)deq.pop_front();
        }
    }
    */
    
    cout << ans[0];
    for(ll i=1; i<ans.size(); i++)cout << " " << ans[i];
    cout << endl;
}