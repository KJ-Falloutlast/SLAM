#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <boost/format.hpp>
#include <algorithm>
using namespace std;
void test01(){
	ofstream ofs("a.csv", ios::out);
	ifstream ifs("a.csv", ios::in);
	for (int i = 0; i < 10; i++){
		ofs << i << " ";
	}
	char buf[10] = {0};
	while (ifs >> buf){
		cout << buf << endl; 
	}

}
int main(){
	test01();
}
