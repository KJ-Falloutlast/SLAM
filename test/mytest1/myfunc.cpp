#include "myfunc.h"
Circle::Circle(){

}
Circle::Circle(double r){
    m_R = r;
}
void Circle::showArea(){
    double area = 3.14*m_R*m_R;
    cout << "area = " << area << endl;
}
//此文件中只给实现，不给输出