#include <iostream>
#include <string>
using namespace std;
template<class T1, class T2>
void test(T1 a, T2 b){
	cout << "主模板函数调用" << endl;
}

template<class T2>
void test(int a, T2 b){
	cout << "主模板函数重载" << endl;
}
template<>
void test(int a, int b){
	cout << "全特化模板函数" << endl;
}
// void test(int a, int b){
// 	cout << "普通函数调用" << endl;
// }

void test01(){
	test(1, 1);
	test(1, "sssss");
	test('a', 'sss');
}

int main(){
	test01();
}