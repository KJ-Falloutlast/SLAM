#include <iostream>
using namespace std;
#include <string>
class Building;
class Person{
    public:
        Person();//直接利用构造函数进行对指针的初始化
        void visit();
        Building *building;
};

class Building{
    friend class Person;//此处类做友元和类成员函数做友元都能得到相同的结果
    public:
        Building();
        string sittingRoom;
    private:
        string bedRoom;
};

Person::Person(){
    building = new Building;
}
void Person::visit(){
    cout << "we are visiting  " << building->sittingRoom << "  "<< building->bedRoom << endl;
}

Building::Building(){
    sittingRoom = "room1";
    bedRoom = "room2";
}

void test(){
    Building building;
    Person p;
    p.visit();
}
int main(){
    test();
}