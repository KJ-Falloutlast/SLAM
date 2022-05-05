#include <iostream>
using namespace std;

int DevFun(int a, int b)
{
	if ( 0 == b)  //除数为 0 ， 打印异常提示，并返回 0
	{
		throw b; //抛出异常
	}
	return a / b;
}

int main()
{
	try
	{
		cout << DevFun(6, 2) << endl;
		cout << DevFun(6, 0) << endl;  //除数为 0
	}
	catch (int)  //捕获到异常（捕获到int类型），打印输出, catch (...) 表示任意类型
	{
		cout << "除数不能为 0 !"<< endl;
	}

    return 0;
}
