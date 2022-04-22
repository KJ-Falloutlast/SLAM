#include <iostream>
using namespace std;
class Complex {
private:
    double i;
    double j;
public:
    Complex(int = 0, int = 0);
    void display();
    Complex operator++ ();//前缀自增
    Complex operator++ (int);//后缀自增，参数需要加int
};

Complex::Complex(int a, int b) {
    i = a;
    j = b;
}

void Complex::display() {
    cout << i << '+' << j << 'i' << endl;
}


Complex Complex::operator ++() {//这个2个complex的含义不同，第一个是重载函数的类型，即为类本身，第二个是调到作用域
    ++i;
    ++j;
    return *this;
}

Complex Complex::operator ++(int) {
    Complex temp =*this;
    ++*this;
    return temp;
}

int main()
{
    Complex comnum1(2,2), comnum2,comnum3;
    cout << "自增计算前:" << endl;
    cout << "comnum1:";
    comnum1.display();
    cout << "comnum2:";
    comnum2.display();
    cout << "comnum3:";
    comnum3.display();
    cout << endl;

    cout << "前缀自增计算后：" << endl;
    comnum2 = ++comnum1;
    cout << "comnum1:";
    comnum1.display();
    cout << "comnum2:";
    comnum2.display();
    cout << endl;

    cout << "后缀自增计算后:" << endl;
    comnum3 = comnum1++;
    cout << "comnum1:";
    comnum1.display();
    cout << "comnum3:";
    comnum3.display();

    return 0;
}