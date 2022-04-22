#ifndef MYFUNC_H
#define MYFUNC_H
#include <iostream>
using namespace std;
class Circle{
    private:
        double m_R;
    public:
        Circle();
        Circle(double r);
        void showArea();
};
#endif