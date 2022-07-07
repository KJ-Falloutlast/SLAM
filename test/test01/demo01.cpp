#include <iostream>
#include <vector>
#include <cmath>
#define MaxSize 10
#define Typename int
using namespace std;
typedef struct SqDequeue{
	Typename data[MaxSize];
	int front, rear;
}SqDequeue;
void InitSqDequeue(SqDequeue &Q){
	Q.data  = 0;
	Q.front = Q.rear = 0;
}