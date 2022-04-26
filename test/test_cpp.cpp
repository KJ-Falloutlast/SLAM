#include <iostream>
using namespace std;
class Animal{
    public:
        void speak(){
            cout << "the animal is speaking " << endl;
        }
};//非静态成员函数不属于类的对象里面的
class Dog: public Animal{
    public:
        void speak(){
            cout << "Dog is speaking" << endl;
        }
};
void doSpeak(Animal &animal){
    animal.speak();
}
void test(){
    Dog dog;
    doSpeak(dog);
}
void test02(){
    cout << "size of Animal = " << sizeof(Animal) << endl;
}
int main(){
    test();
    test02();
}