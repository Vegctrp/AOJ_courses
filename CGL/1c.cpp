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

    double neq(point2d v){
        return ((x-v.x)<EPS && (v.x-x)<EPS && (y-v.y)<EPS && (v.y-y)<EPS);
    }
    double norm() { return x*x+y*y; }
    double length() { return std::sqrt(x*x+y*y); }
    double isZero(){ point2d zero; return (*this).neq(zero); }
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

    friend std::ostream& operator<<(std::ostream &stream, const point2d v){
        stream << std::fixed << std::setprecision(13) << std::showpoint << v.x << " " << v.y;
        return stream;
    }
};

int main(){
    double x1, y1, x2, y2;
    int q;
    cin >> x1 >> y1 >> x2 >> y2 >> q;
    point2d p0(x1,y1), p1(x2,y2);
    double x,y;
    REP(i,q){
        cin >> x >> y;
        point2d p2(x,y);
        point2d v1=p1-p0;
        point2d v2=p2-p0;
        double dot = v1.dot(v2);
        double cross = v1.cross(v2);
        if(cross>0.0) cout << "COUNTER_CLOCKWISE" << endl;
        else if(cross<0.0) cout << "CLOCKWISE" << endl;
        else if(dot>0.0){
            if(v1.norm()>=v2.norm()) cout << "ON_SEGMENT" << endl;
            else cout << "ONLINE_FRONT" << endl;
        }
        else if(dot<0.0)cout << "ONLINE_BACK" << endl;
        else cout << "ON_SEGMENT" << endl;
    }
    return 0;
}