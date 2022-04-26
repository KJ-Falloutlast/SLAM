#include <iostream>
using namespace std;
class Data
{
public:
    int num;//普通成员变量
    static int data;//静态成员变量(类内声明)
};
//定义的时候 不需要加static
int Data::data=100;//类外定义+初始化

void test01()
{
    //data是静态成员变量 是属于类 可以通过类名称::直接访问
    cout<<Data::data<<endl;//100
    //赋值
    Data::data = 200;
    cout<<Data::data<<endl;//200

    //data静态变量 是所有对象 共享的 可以通过对象名访问
    Data ob1;
    ob1.data = 300;
    cout<<Data::data<<endl;//300

    Data ob2;
    cout<<ob2.data<<endl;//300

    //普通成员变量 属于对象的 只能通过对象名访问
    ob1.num = 100;
    cout<<"ob2.num = "<<ob2.num<<endl;//随机值
    //cout<<Data::num<<endl;//普通成员变量不能通过类名称访问
}
int main(){
    test01();
}
