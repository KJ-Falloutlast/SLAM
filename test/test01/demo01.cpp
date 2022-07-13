#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>
// #include <stdio.h>
// #include <stdlib.h>
using namespace std;
typedef int SLDataType;
typedef struct SeqList{
	SLDataType* a;
	int size;
	int capacity;
}SL;

void SeqListCheckCapacity(SL* s){
	if (s->size >= s->capacity){
		s->capacity *= 2;
		s->a = (SLDataType*)realloc(s->a, sizeof(SLDataType) * s->capacity);
		if (s->a == NULL){
			cout << "内存分配失败" << endl;
		}
	}
}

void SeqListInit(SL* s){
	SeqListCheckCapacity(s);
	s->size = 0;
	s->capacity = 10;
}

void SeqListPushBack(SL* s, int x){
	assert(s);
	s->a[s->size] = x;
	s->size++;
}

void SeqListPopBack(SL* s){
	assert(s);
	s->size--;
}

void SeqListPushFront(SL* s, int x){
	assert(s);
	int end = s->size - 1;
	while (end >= 0){
		s->a[end + 1] = s->a[end];
		end--;
	}
	s->a[0] = x;
	s->size++;
}

void SeqListPopFront(SL* s){
	assert(s);
	int start = 0;
	while (start < s->size-1){//移动2次就行
		s->a[start] = s->a[start + 1];
		start++;		
	}
	s->size--;
}

void SeqListPrint(SL* s){
	for (int i = 0; i < s->size; i++){
		cout << s->a[i] << endl;
	}
}