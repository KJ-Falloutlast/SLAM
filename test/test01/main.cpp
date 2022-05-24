#include <stdio.h>
typedef int INT;//将INT指代为int类型
typedef int* PINT;
typedef char CHAR;
int main()
{
	INT a = 10;
	CHAR d;
	PINT b, c;//b,c都为指向整型的指针
	b = &a;//b指向a
	c = b;//c 也指向a
	printf("addr of a = %p\n", c);//打印a的地址
	return 0;
}