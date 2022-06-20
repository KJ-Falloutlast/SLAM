#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int fac(int n){
	if (n == 0 || n == 1){
		return 1;
	}
	else{
		return n * fac(n-1);
	}
}

int fab01(int n){
	if (n == 0 || n == 1){
		return 1;
	}
	else{
		return fab01(n-1) + fab01(n-2);
	}
}

int fab02(int n){
	int *a = new int[10];
    int temp;
    a[0] = 1;
    a[1] = 1;
    for (int i = 2; i <= n; i++){
        a[i] = a[i-1] + a[i-2];
    }
    temp = a[n];
    delete[] a;
    return temp;
}
int main(){
    cout << fab01(10) << endl;
    cout << fab02(10) << endl;
}