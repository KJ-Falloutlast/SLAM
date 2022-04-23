#include "functions.h"
Circle::Circle(double r){
    this->r  = r;
}

void Circle::showArea(){
    int area = 3.14*r*r;
    cout << "the area is " << area << endl; 
}
