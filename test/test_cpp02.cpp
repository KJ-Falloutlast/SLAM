#include <iostream>
#include <string>
using namespace std;
template<class T1, class T2>
class Person{
	public:
		T1 m_Name;
		T2 m_Age;
	    Person(T1 i, T2 j):m_Name(i), m_Age(j){
		}
		void showPerson(){
			cout << "name = " << this->m_Name << "   age = " << this->m_Age << endl;

		}
};
//1.指定传入类型
void printPerson1(Person<string, int> &p){//p直接传入
	p.showPerson();
}
void test01(){
	Person<string, int> p("tom", 1);
	printPerson1(p);
}
//2.参数模板化
template<class T1, class T2>///p直接传入会出错，必须声明这个T1，T2这2个模板
void printPerson2(Person<T1, T2> &p){
	p.showPerson();
	cout << "T1的类型为：" << typeid(T1).name() << endl;
	cout << "T2的类型为：" << typeid(T2).name() << endl;
}
void test02(){
	Person<string, int> p("jack", 1);
	printPerson2(p);
}
//3.整个类模板化
template<class T>///p直接传入会出错，必须声明这个T
void printPerson3(T &p){
	p.showPerson();
	cout << "T的类型为：" << typeid(T).name() << endl;
}
void test03(){
	Person<string, int> p("Synic", 3);
	printPerson3(p);
}
int main(){
	test01();
	test02();
	test03();
}