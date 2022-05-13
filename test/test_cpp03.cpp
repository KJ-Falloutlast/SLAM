#include <iostream>
#include <string>
using namespace std;
template<class T1, class T2>
class Person{
	private:
		T1 a;
		T2 b;
	public:
		Person(T1 i, T2 j):a(i), b(j){}
		void showPerson(){
			cout << " name  =  " << a << " age  = " << b << end;
		}
	
};
void test(){
	Person<string, int> p("tim", 12);
	p.showPerson();
	
}
int main(){
	test();
}