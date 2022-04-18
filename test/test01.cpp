#include <iostream>
#include <vector>
 
using namespace std;
 
void printVec(vector<int>& vec) {
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << endl;
}
 
int main() {
	vector<int>vec = {4,3,2,1,0 };
	cout<<"***************第一种*************"<<endl;
    //这个时候每个取出来的iter只是原来vec元素的副本，不会改变vec中任何元素
	for (auto iter : vec) {
		iter = iter + 100;
	}
	printVec(vec);
 
	cout<<"***************第二种*************"<<endl;
    //这个时候取出来的是 &iter，代表原来vec中元素的引用，如果对iter进行任何改变都会作用在vec上
	for (auto& iter : vec) {
		iter = iter + 100;
	}
	printVec(vec);

	cout<<"***************第三种*************"<<endl;
    for (auto&& iter : vec){
        iter = iter + 100;
    }
    printVec(vec);
}