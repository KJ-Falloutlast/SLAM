#include <iostream>
using namespace std;
int& func01(){
    static int a = 1;
    int &ref = a;
    return ref;
}
void test01(){
    int &ref = func01();
    cout << ref << endl;
    cout << ref << endl;//溢出
}
int main(){
    test01();
}
