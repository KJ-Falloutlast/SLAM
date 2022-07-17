#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>
#include <algorithm>
using namespace std;
typedef int SListDataType;
struct SListNode{
	SListDataType data;
	SListNode* next;
};
void BuySListNode(SListDataType x){
	SListNode* newNode = (SListNode*)malloc(sizeof(SListDataType));
	if (newNode == NULL){
		cout << "内存分配失败" << endl;
	}
	
}