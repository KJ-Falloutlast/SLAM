#include <iostream>
using namespace std;
#include <string>
class Animal{
    public:
        //出虚函数
        virtual void speak() = 0;
        

};
class Cat: public Animal{
    public:
        Cat(string name){
            m_Name = new string(name);
            //把string传进来，并让指针m_Name维护堆区的数据
        }
    //如果不对子类虚函数重写，那么子类也变为抽象类
        virtual void speak(){
            cout << *m_Name << " cat is speaking" << endl;
        }
        
        string *m_Name;

};
void test01(){
    Animal *animal = new Cat("tom");
    animal->speak();
    delete animal;//创建在堆区的数据要释放

}
int main(){
    test01();
}