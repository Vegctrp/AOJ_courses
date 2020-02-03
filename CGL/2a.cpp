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

    point2d operator+(point2d v){
        point2d a(x+v.x, y+v.y); return a;
    }
    point2d operator-(point2d v){
        point2d a(x-v.x, y-v.y); return a;
    }
    double operator*(point2d v){ //内積
        return x*v.x + y*v.y;
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
    double norm() { return x*x+y*y; }
    double length() { return std::sqrt(x*x+y*y); }
    double isZero(){ point2d zero; return (*this).simeq(zero); }
    double dot(point2d v){ return x*v.x + y*v.y; }
    double cross(point2d v){ return x*v.y - y*v.x; }
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
    bool parallel(point2d v, bool near=false){
        double cross = (*this).cross(v);
        if(near)return cross<EPS && cross>-EPS;
        else return cross==0.0;
    }
    bool orthogonal(point2d v, bool near=false){
        double dot = (*this).dot(v);
        if(near)return dot<EPS && dot>-EPS;
        else return dot==0.0;
    }

    friend std::ostream& operator<<(std::ostream &stream, const point2d v){
        stream << std::fixed << std::setprecision(13) << std::showpoint << v.x << " " << v.y;
        return stream;
    }
};

int main(){
    int q;
    cin >> q;
    REP(i,q){
        double x11,x12,x21,x22,y11,y12,y21,y22;
        cin >> x11 >> y11 >> x12 >> y12 >> x21 >> y21 >> x22 >> y22;
        point2d p0(x11,y11), p1(x12,y12), p2(x21,y21), p3(x22,y22);
        point2d v1=p1-p0;
        point2d v2=p3-p2;
        if(v1.parallel(v2, true))cout << "2" << endl;
        else if(v1.orthogonal(v2, true))cout << "1" << endl;
        else cout << "0" << endl;
    }
    return 0;
}