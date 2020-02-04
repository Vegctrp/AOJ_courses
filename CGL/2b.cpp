#include<stdio.h>
#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class point2d{
    public:
    double x,y;
    constexpr static double EPS = 0.0000000001;

    point2d() : x(0),y(0){}
    point2d(double a, double b) :x(a), y(b){}

    double add(double a, double b){
        if(std::abs(a+b) < EPS * (std::abs(a)+std::abs(b))) return 0;
        return a+b;
    }
    point2d operator+(point2d v){
        point2d a(add(x, v.x), add(y, v.y)); return a;
    }
    point2d operator-(point2d v){
        point2d a(add(x, -v.x), add(y, -v.y)); return a;
    }
    double operator*(point2d v){ //内積
        return add(x*v.x, y*v.y);
    }
    point2d operator*(double v){
        x *= v; y *= v; return (*this);
    }
    point2d operator/(double v){
        if(v==0) cout << "zero division!!!" << endl;
        x /= v; y /=v; return (*this);
    }
    void operator=(point2d v){
        x = v.x; y = v.y;
    }
    bool operator==(point2d v){
        return (x==v.x)&&(y==v.y);
    }

    double simeq(point2d v){
        return ((x-v.x)<EPS && (v.x-x)<EPS && (y-v.y)<EPS && (v.y-y)<EPS);
    }
    double norm() { return add(x*x, y*y); }  //距離^2
    double length() { return std::sqrt(add(x*x, y*y)); }  //距離
    double isZero(){ point2d zero; return (*this).simeq(zero); }
    double dot(point2d v){ return add(x*v.x, y*v.y); }   // 内積
    double cross(point2d v){ return add(x*v.y, -y*v.x); } // 外積
    double cosine(point2d v){
        if((*this).isZero() || v.isZero()) cout << "cannot calc cosine by zero!!!" << endl;
        double cos = (*this).dot(v) / (*this).length() / v.length();
        return cos;
    }
    double sine(point2d v){
        if((*this).isZero() || v.isZero()) cout << "cannot calc sine by zero!!!" << endl;
        double sin = (*this).cross(v) / (*this).length() / v.length();
        return sin;
    }
    bool parallel(point2d v, bool near=true){  // 平行
        double cross = (*this).cross(v);
        if(near)return cross<EPS && cross>-EPS;
        else return cross==0.0;
    }
    bool orthogonal(point2d v, bool near=true){ // 直交
        double dot = (*this).dot(v);
        if(near)return dot<EPS && dot>-EPS;
        else return dot==0.0;
    }
    int clockwise(point2d v){
        double dot = (*this).dot(v);
        double cross = (*this).cross(v);
        if(cross>0.0) return -1; // 反時計回り
        else if(cross<0.0) return 1; //時計回り
        else if(dot>0.0 && (*this).norm() < v.norm()) return 2; // 直線上、向き同じ
        else if(dot<0.0) return -2; // 直線上、逆向き
        else return 0; // 線分上
    }

    friend std::ostream& operator<<(std::ostream &stream, const point2d v){
        stream << std::fixed << std::setprecision(13) << std::showpoint << v.x << " " << v.y;
        return stream;
    }
};

int main(){
}