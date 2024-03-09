#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

class Triangle
{
public:
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
    double getArea();
    double getPerimeter();
    
private:
    double _x1;
    double _y1;
    double _x2;
    double _y2;
    double _x3;
    double _y3;
    // 以下为三条边的长度：
    // l1 对应 (x1,y1) -- (x2, y2)之间的边长
    // l2 对应 (x2,y2) -- (x3, y3)之间的边长
    // l3 对应 (x3,y3) -- (x1, y1)之间的边长
    double _l1;
    double _l2;
    double _l3;
};
// 在下面的空格实现Triangle类的成员函数
Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3){
    _x1 = x1;
    _x2 = x2;
    _x3 = x3;
    _y1 = y1;
    _y2 = y2;
    _y3 = y3;
    _l1 = sqrt(pow(_x1 - _x2, 2) + pow(_y1 - _y2, 2));
    _l2 = sqrt(pow(_x3 - _x2, 2) + pow(_y3 - _y2, 2));
    _l3 = sqrt(pow(_x1 - _x3, 2) + pow(_y1 - _y3, 2));
}

double Triangle::getArea()
{
    return fabs(_x1 * (_y2 - _y3) + _x2 * (_y3 - _y1) + _x3 * (_y1 - _y2)) / 2;
}

double Triangle::getPerimeter()
{
    return _l1 + _l2 + _l3;
}

int main()
{
    double x1, x2, x3, y1, y2, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    Triangle t(x1, y1, x2, y2, x3, y3);

    // 在下面的空格按题目要求输出结果
    cout << fixed << setprecision(2) << t.getPerimeter() << endl;
    cout << fixed << setprecision(2) << t.getArea() << endl;

    return 0;
}
