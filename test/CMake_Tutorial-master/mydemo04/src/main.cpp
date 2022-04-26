#include "../include/mymath.h"
#include <iostream>
using namespace std;
int main(){
    Circle c(100);
    int res = c.showArea();
    cout << "the area is " << res << endl;
}