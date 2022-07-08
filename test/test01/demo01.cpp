#include <iostream>
#include <vector>
#include <cmath>
#define MaxSize 10
#define Typename int
using namespace std;
typedef struct SqQueue{
	Typename data[MaxSize];
	int front, rear;
}SqQueue;
void InitSqQueue(SqQueue &Q){
	Q.data = {0};
	Q.front = Q.rear = 0;
}
bool IsEmpty(SqQueue Q){
	if (Q.front = Q.rear)
		return true;
	else
		return false;
}
bool Ins