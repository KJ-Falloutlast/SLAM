#include <iostream>
#include <string>
using namespace std;

template<class T>
void myPrint(T a, T b){
	cout << "函数模板调用" << endl;
}

template<class T>
void myPrint(T a, T b, T c){//T可以接收任何对象
	cout << "函数模板重载" << endl;
}

void myPrint(int a, int b){
	cout << "普通函数调用" << endl;
}

void test(){
	int abc[8];
	int bcd[8];
	myPrint(abc, bcd);
}
int main(){
	test();
}