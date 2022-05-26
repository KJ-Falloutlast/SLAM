#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
int main(){
	list<int> l1;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
//使用auto自动推导
	for (auto i = l1.begin(); i!= l1.end(); i++){
		cout << i.operator->() << endl;
		cout << *i << endl;
	}
}