#include "../include/mymath.h"
Circle::Circle(int r){
    this->r = r;
}
int Circle::showArea(){
    return 3.14*r*r;
}
