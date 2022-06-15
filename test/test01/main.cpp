#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int mySum01(int n){
	int sum = 0;
	for (int i = 1; i <= n; i++){
		sum += pow(-1, n);
	}
	return sum;
}

int mySum02(int n){
	int sum = 0;
	if (n % 2 == 0){
		return 1;
	}
	else{
		return -1;
	}
}

int fac(int n){
	if (n < 1){
		return 0;
	}
	else if(n == 0 || n == 1){
		return 1;
	}
	else{
		return n * fac(n-1);
	}	
}

int fab01(int n){//此处不能用vector，要用数组
	int v[n];
	v[0] = 1;
	v[1] = 1;
	for (int i = 2; i <= n; i++){
		v[i] = v[i-1] + v[i-2];
	}
	return v[n];
}
int fab02(int n){
	if (n == 0 || n == 1){
		return 1;
	}
	else{
		return fab02(n-1) + fab02(n-2);
	}	
}

int main(){
	cout << fab01(5) << endl;//以0作为索引的第一个值
	cout << fab02(5) << endl;
}