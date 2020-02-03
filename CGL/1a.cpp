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
    double norm(){
        return std::sqrt(x*x+y*y);
    }

    
    friend std::ostream& operator<<(std::ostream &stream, const point2d v){
        stream << std::setprecision(15) << v.x << " " << v.y;
        return stream;
    }
};

int main(){
    double x1, y1, x2, y2;
    int q;
    cin >> x1 >> y1 >> x2 >> y2 >> q;
    point2d p1(x1,y1), p2(x2,y2);
    double x,y;
    REP(i,q){
        cin >> x >> y;
        point2d p(x,y);
        cout << ((p2-p1) * ((p-p1)*(p2-p1)) / ((p2-p1).norm() * (p2-p1).norm()) + p1) << endl;
    }
}