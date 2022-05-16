#include "Array.hpp"
void test(){
	MyArray<int> arr1(10);
	MyArray<int> arr2(arr1);
	MyArray<int> arr3 = arr2;


} 
int main(){
	test();
}