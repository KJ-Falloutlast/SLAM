#include <iostream>
#include <string>
using namespace std;
class MyTest1{
	public:
		void showMsg(){
			cout << "test1" << endl;
		}
};
class MyTest2{
	public:
		void showMsg(){
			cout << "test2" << endl;
		}
};

template<class T>
class MyClass{
	public:
		T m;
		void func1(){
			m.showMsg();
		}
		void func2(){
			m.showMsg();
		}		
};

void test(){
	MyClass<MyTest1> mc;
	mc.func1();
}

int main(){
	test();
}