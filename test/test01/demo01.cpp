#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>
#include <algorithm>
using namespace std;
//1.移除数组
int removeNumber(vector<int>& v, int val){
	int left = 0;
	for (int right = 0; right < v.size(); right++){
		if (v[right] != val){
			v[left] = v[right];
			left++;
		}
	}
	return left;
}
//2.去重
int removeDuplicates(vector<int>& v, int val){
	int slow = 1;
	for (int fast = 1; fast < v.size(); fast++){
		if (v[fast] != v[fast - 1]){
			v[slow] = v[fast];
			slow++;
		}
	}
	return slow;
}
//
vector<int> addToArray(vector<int>& v, int val){
	vector<int> res;
	int sum = 0;
	for (int i = v.size() - 1; i >= 0; i--){
		sum += v[i] + val % 10;
		val /= 10;
		if (sum >= 10){
			val++;
			sum -= 10;
		}
		res.push_back(sum);
	}
	reverse(res.begin(), res.end());
	return res;
}

int main(){
	vector<int> v = {1, 2, 3};
	vector<int> v1 = addToArray(v, 345);
	for (int a : v1){
		cout << a << endl;
	}
}
