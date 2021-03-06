"适合作的开源项目"

1.https://github.com/amhndu/SimpleNES
2.https://github.com/Light-City/CPlusPlusThings
3.https://github.com/TheAlgorithms/C-Plus-Plus
4.https://github.com/changkun/modern-cpp-tutorial
5.https://github.com/wuye9036/CppTemplateTutorial
6.https://github.com/Alinshans/MyTinySTL
7.https://github.com/taylorconor/tinytetris
8.https://github.com/microsoft/calculator


-------------------
2.vscode下c++配置//参考：https://segmentfault.com/a/1190000020155987

 1.在终端中运行：
    1.随便找一个文件夹,我们先写一个Main.cpp
    复制代码

     #include<iostream>
     
     int main(void){
         std::cout<<"Hello Linux!"<<std::endl;
         return 1;
     }

    复制代码

    2.在当前文件夹下打开终端,输入> g++ -g -c Main.cpp 后,当前文件空间下会出现 Main.o

    3.在终端中继续输入 g++ -o Main.out Main.o 后,文件空间下将会出现 Main.out(可执行文件)

    4.在终端中输入 ./Main.out 即可执行

    5.上面的命令也可以简化为: g++ -o Main.out Main.cpp ---->然后直接执行./Main.out
    {
    -o：指定生成可执行文件的名称。使用方法为：g++ -o afile file.cpp file.h ... （可执行文件不可与待编译或链接文件同名，否则会生成相应可执行文件且覆盖原编译或链接文件），如果不使用-o选项，则会生成默认可执行文件a.out
    -c：只编译不链接，只生成目标文件。
    -g：添加gdb调试选项
    }

    2.在vscode中的配置

    1.launch.json文件：
    {
        "version": "0.2.0",
        "configurations": [
            {
                "name": "(gdb) Launch",
                "type": "cppdbg",
                "request": "launch",
                "program": "${workspaceFolder}/${fileBasenameNoExtension}.out",
                "args": [],
                "stopAtEntry": false,
                "cwd": "${workspaceFolder}",
                "environment": [],
                "externalConsole": true,
                "MIMode": "gdb",
                "preLaunchTask":"build",
                "setupCommands": [
                    {
                        "description": "Enable pretty-printing for gdb",
                        "text": "-enable-pretty-printing",
                        "ignoreFailures": true
                    }
                ]
            }
        ]
    }

    2.tasks.json文件：

    {
        "tasks": [
            {
                "label": "build",
                "type": "shell",
                "command": "g++",
                "args": ["-g", "${file}", "-std=c++11", "-o", "${fileBasenameNoExtension}.out"]
            }
         ]
    }

    3.f5编译------>4.在终端运行：g++ -o xxx.out xxx.cpp---->./xxx.out  or 在IDE中用ctrl+alt+n来运行自动生成xxxx.out

-----------------------------

'1.c++初始'

//程序开始执行的地方
#include <iostream>
using namespace std;//告诉便编译器使用std命名空间
int main() { //
     cout << "Hello, world!!!!" << endl;
     return 0;
}
1.变量
1-1.变量格式:

.数据类型 变量名 = 变量初始值
int a = 10;
.例子:
//程序开始执行的地方
#include <iostream>
using namespace std;//告诉便编译器使用std命名空间
int main() { //
    int a = 10;
    cout << "a = " << a << endl;

    system("pause")
    return 0;
}

2.常量
c++两种常量模式:1.#define 常量名 常量值;2.const 数据类型 常量名 = 常量值

3.关键字:命名变量不能用关键字

4.标识符命名规则:
4-1.标识符不能是关键字
4-2.标识符只能由字母,数字,下划线组成
4-3.标识符的第一个字符只能为字母或下划线
4-3.标识符的字母区分大小写


4.数据类型:

用编程语言进行编程时，需要用到各种变量来存储各种信息。变量保留的是它所存储的值的内存位置。这意味着，当您创建一个变量时，就会在内存中保留一些空间。

您可能需要存储各种数据类型（比如字符型、宽字符型、整型、浮点型、双浮点型、布尔型等）的信息，操作系统会根据变量的数据类型，来分配内存和决定在保留内存中存储什么。
基本的内置类型

C++ 为程序员提供了种类丰富的内置数据类型和用户自定义的数据类型。下表列出了七种基本的 C++ 数据类型：
类型  关键字
布尔型 bool
字符型 char
整型  int
浮点型 float
双浮点型    double
无类型 void
宽字符型  wchar_t

其实 wchar_t 是这样来的：

typedef short int wchar_t;

所以 wchar_t 实际上的空间是和 short int 一样。

一些基本类型可以使用一个或多个类型修饰符进行修饰：

    signed
    unsigned
    short
    long

下表显示了各种变量类型在内存中存储值时需要占用的内存，以及该类型的变量所能存储的最大值和最小值。

注意：不同系统会有所差异，一字节为 8 位。

注意：默认情况下，int、short、long都是带符号的，即 signed。

注意：long int 8 个字节，int 都是 4 个字节，早期的 C 编译器定义了 long int 占用 4 个字节，int 占用 2 个字节，新版的 C/C++ 标准兼容了早期的这一设定。

类型  位   范围
char    1 个字节   -128 到 127 或者 0 到 255
unsigned char   1 个字节   0 到 255
signed char 1 个字节   -128 到 127
int 4 个字节   -2147483648 到 2147483647
unsigned int    4 个字节   0 到 4294967295
signed int  4 个字节   -2147483648 到 2147483647
short int   2 个字节   -32768 到 32767
unsigned short int  2 个字节   0 到 65,535
signed short int    2 个字节   -32768 到 32767
long int    8 个字节   -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807
signed long int 8 个字节   -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807
unsigned long int   8 个字节   0 到 18,446,744,073,709,551,615
float   4 个字节   精度型占4个字节（32位）内存空间，+/- 3.4e +/- 38 (~7 个数字)
double  8 个字节   双精度型占8 个字节（64位）内存空间，+/- 1.7e +/- 308 (~15 个数字)
long double 16 个字节  长双精度型 16 个字节（128位）内存空间，可提供18-19位有效数字。
wchar_t 2 或 4 个字节   1 个宽字符

    注意，各种类型的存储大小与系统位数有关，但目前通用的以64位系统为主。

    以下列出了32位系统与64位系统的存储大小的差别（windows 相同）：

从上表可得知，变量的大小会根据编译器和所使用的电脑而有所不同。

下面实例会输出您电脑上各种数据类型的大小。
实例
#include<iostream>  
#include <limits>
 
using namespace std;  
  
int main()  
{  
    cout << "type: \t\t" << "************size**************"<< endl;  
    cout << "bool: \t\t" << "所占字节数：" << sizeof(bool);  
    cout << "\t最大值：" << (numeric_limits<bool>::max)();  
    cout << "\t\t最小值：" << (numeric_limits<bool>::min)() << endl;  
    cout << "char: \t\t" << "所占字节数：" << sizeof(char);  
    cout << "\t最大值：" << (numeric_limits<char>::max)();  
    cout << "\t\t最小值：" << (numeric_limits<char>::min)() << endl;  
    cout << "signed char: \t" << "所占字节数：" << sizeof(signed char);  
    cout << "\t最大值：" << (numeric_limits<signed char>::max)();  
    cout << "\t\t最小值：" << (numeric_limits<signed char>::min)() << endl;  
    cout << "unsigned char: \t" << "所占字节数：" << sizeof(unsigned char);  
    cout << "\t最大值：" << (numeric_limits<unsigned char>::max)();  
    cout << "\t\t最小值：" << (numeric_limits<unsigned char>::min)() << endl;  
    cout << "wchar_t: \t" << "所占字节数：" << sizeof(wchar_t);  
    cout << "\t最大值：" << (numeric_limits<wchar_t>::max)();  
    cout << "\t\t最小值：" << (numeric_limits<wchar_t>::min)() << endl;  
    cout << "short: \t\t" << "所占字节数：" << sizeof(short);  
    cout << "\t最大值：" << (numeric_limits<short>::max)();  
    cout << "\t\t最小值：" << (numeric_limits<short>::min)() << endl;  
    cout << "int: \t\t" << "所占字节数：" << sizeof(int);  
    cout << "\t最大值：" << (numeric_limits<int>::max)();  
    cout << "\t最小值：" << (numeric_limits<int>::min)() << endl;  
    cout << "unsigned: \t" << "所占字节数：" << sizeof(unsigned);  
    cout << "\t最大值：" << (numeric_limits<unsigned>::max)();  
    cout << "\t最小值：" << (numeric_limits<unsigned>::min)() << endl;  
    cout << "long: \t\t" << "所占字节数：" << sizeof(long);  
    cout << "\t最大值：" << (numeric_limits<long>::max)();  
    cout << "\t最小值：" << (numeric_limits<long>::min)() << endl;  
    cout << "unsigned long: \t" << "所占字节数：" << sizeof(unsigned long);  
    cout << "\t最大值：" << (numeric_limits<unsigned long>::max)();  
    cout << "\t最小值：" << (numeric_limits<unsigned long>::min)() << endl;  
    cout << "double: \t" << "所占字节数：" << sizeof(double);  
    cout << "\t最大值：" << (numeric_limits<double>::max)();  
    cout << "\t最小值：" << (numeric_limits<double>::min)() << endl;  
    cout << "long double: \t" << "所占字节数：" << sizeof(long double);  
    cout << "\t最大值：" << (numeric_limits<long double>::max)();  
    cout << "\t最小值：" << (numeric_limits<long double>::min)() << endl;  
    cout << "float: \t\t" << "所占字节数：" << sizeof(float);  
    cout << "\t最大值：" << (numeric_limits<float>::max)();  
    cout << "\t最小值：" << (numeric_limits<float>::min)() << endl;  
    cout << "size_t: \t" << "所占字节数：" << sizeof(size_t);  
    cout << "\t最大值：" << (numeric_limits<size_t>::max)();  
    cout << "\t最小值：" << (numeric_limits<size_t>::min)() << endl;  
    cout << "string: \t" << "所占字节数：" << sizeof(string) << endl;  
    // << "\t最大值：" << (numeric_limits<string>::max)() << "\t最小值：" << (numeric_limits<string>::min)() << endl;  
    cout << "type: \t\t" << "************size**************"<< endl;  
    return 0;  
}

本实例使用了 endl，这将在每一行后插入一个换行符，<< 运算符用于向屏幕传多个值，sizeof() 函数用来获取各种数据类型的大小。

当上面的代码被编译和执行时，它会产生以下的结果，结果会根据所使用的计算机而有所不同：

type:         ************size**************
bool:         所占字节数：1    最大值：1        最小值：0
char:         所占字节数：1    最大值：        最小值：?
signed char:     所占字节数：1    最大值：        最小值：?
unsigned char:     所占字节数：1    最大值：?        最小值：
wchar_t:     所占字节数：4    最大值：2147483647        最小值：-2147483648
short:         所占字节数：2    最大值：32767        最小值：-32768
int:         所占字节数：4    最大值：2147483647    最小值：-2147483648
unsigned:     所占字节数：4    最大值：4294967295    最小值：0
long:         所占字节数：8    最大值：9223372036854775807    最小值：-9223372036854775808
unsigned long:     所占字节数：8    最大值：18446744073709551615    最小值：0
double:     所占字节数：8    最大值：1.79769e+308    最小值：2.22507e-308
long double:     所占字节数：16    最大值：1.18973e+4932    最小值：3.3621e-4932
float:         所占字节数：4    最大值：3.40282e+38    最小值：1.17549e-38
size_t:     所占字节数：8    最大值：18446744073709551615    最小值：0
string:     所占字节数：24
type:         ************size**************

4-1.整型
数据类型        占用空间          取值范围
short(短整型)    2字节           -2^15-2^15-1
int(整型)    2字节              -2^31-2^31-1
long(长整型)    linux为4字节     -2^31-2^31-1
long long(长长整型)    8字节       -2^63-2^63-1

4-2.sizeof关键字
.作用:统计数据类型的所占内存大小
.例:
#include <iostream>
using namespace std;
int main(){
    short a1 = 10;
    cout << "short所占的内存空间为" << sizeof(short) << endl;
    cout << "a1所占的内存空间为" << sizeof(a1) << endl;
    return 0;
}

4-3.浮点型:
.分类:单精度float;双精度:double
.区别:{
    数据类型        占用空间        有效数字范围
    float            4               7位
    double            8               15-16位

}

4-4.字符型:
.作用:字符型变量用于显示单个字符
.语法: char ch = 'a';------->注意:1.在显示字符型变量时,用单引号,不要用双引号;
 2.单引号内只能有一个字符,不可是字符串
.空间:c++中字符型变量只占1个字节
.例子:
#include <iostream>
#define day 100
using namespace std;//告诉便编译器使用std命名空间
int main() { //
     char ch = 'a';
     cout << " a = " << ch << endl;
     cout << (int)ch << endl;//(int)ch表示ch='a'的ascii编码
     system("pause");
     return 0;
}

4-5.转义字符
.作用:表示一些不能显示出来的ascii字符
.列表{
    转义字符 意义 ASCII码值(十进制) 
    \a 响铃(BEL) 007 //alarm
    \b 退格(BS) 008 //backspace
    \f 换页(FF) 012 
    \n 换行(LF) 010 
    \r 回车(CR) 013 
    \t 水平制表(HT) 009 //可以整齐地输出数据
    \v 垂直制表(VT) 011 
    \\ 反斜杠 092 
    \? 问号字符 063 
    \' 单引号字符 039 
    \" 双引号字符 034 
    \0 空字符(NULL) 000 
    \ddd 任意字符 三位八进制 
    \xhh 任意字符 二位十六进制

    注意：

    1，\v垂直制表和\f换页符对屏幕没有任何影响，但会影响打印机执行响应操作。

    2，\n其实应该叫回车换行。换行只是换一行，不改变光标的横坐标；回车只是回到行首，不改变光标的纵坐标。

    3，\t 光标向前移动四格或八格，可以在编译器里设置

    4，\' 在字符里（即单引号里）使用。在字符串里(即双引号里)不需要，只要用 ' 即可。

    5，\? 其实不必要。只要用 ? 就可以了（在windows VC6 和tc2 中验证）。

    6， 转义字符中只能使用小写字母，每个转义字符只能看作一个字符。
}
.例子:
..1.
IN:
#include <iostream>
#define day 100
using namespace std;//告诉便编译器使用std命名空间
int main() { //
     cout << "hello world\n" << endl;
     cout << "aaa\thello world" << endl;
     cout << "aaa\vhello world" << endl;
     cout << "aaa\fhello world" << endl;
     cout << "aaa\\hello world" << endl;
     system("pause");
     return 0;
}
OUT:
hello world

aaa hello world
aaa
   hello world
aaa
   hello world
aaa\hello world
sh: 1: pause: not found

..2.
IN:
#include <iostream>
#define day 100
using namespace std;//告诉便编译器使用std命名空间
int main() { //
     cout << "hello world\n" << endl;
     cout << "aaa\thello world" << endl;
     cout << "aaaa\thello world" << endl;
     cout << "aaaaa\thello world" << endl;
     cout << "aaaaaa\thello world" << endl;
     system("pause");
     return 0;
}
OUT:
hello world

aaa hello world
aaaa    hello world
aaaaa   hello world
aaaaaa  hello world
sh: 1: pause: not found

4-6.字符串型
.语法:string 变量名 = "字符串值"
.注意:1.有头文件:#include <string> 2.等号后面要接双引号,字符型用单引号,字符串型用双引号
.例:
#include <iostream>
#include <string>
using namespace std;//告诉便编译器使用std命名空间
int main() { //
     string a = "a";
     char b = 'a';
     cout << a << endl;
     cout << b << endl;
     system("pause");
     return 0;
}

4-7.布尔型:
.作用:表示真和假的值
.大小:bool型占1个字节

4-8.数据的输入：
作用：从键盘获取数据
语法：cin >> 变量
注意:解决无法输入的问题：设置---> 搜索 runInTerminal，将 Run In Terminal 勾选中--->重启
例子：
#include <iostream>
using namespace std;
int main()
{
     int a = 1;
     int b = 2;
     cout << "请输入一个值";
     cin >> a; 
     if (a > b)
     {
          cout << "False" ;
     }
     else if (a == b)    
     {
          cout << "False";
     }
     else
     {
          cout << "True";
     }
     return 0;
}


5.运算符
运算符是一种告诉编译器执行特定的数学或逻辑操作的符号。C++ 内置了丰富的运算符，并提供了以下类型的运算符：

    算术运算符：+，-,*,/,%，++,--
    关系运算符:>,>=,<,<=,==,!=
    逻辑运算符:&&,||,!
    位运算符:&,|,^,~
    赋值运算符:=,+=,-=,*=,/=,%=,>>=,<<=,&=,|=,^=
    杂项运算符:

本章将逐一介绍算术运算符、关系运算符、逻辑运算符、位运算符、赋值运算符和其他运算符。
5-1.算术运算符

下表显示了 C++ 支持的算术运算符。
假设变量 A 的值为 10，变量 B 的值为 20，则：
运算符 描述  实例
+   把两个操作数相加    A + B 将得到 30
-   从第一个操作数中减去第二个操作数    A - B 将得到 -10
*   把两个操作数相乘    A * B 将得到 200
/   分子除以分母  B / A 将得到 2
%   取模运算符，整除后的余数    B % A 将得到 0
++  自增运算符，整数值增加 1   A++ 将得到 11
--  自减运算符，整数值减少 1   A-- 将得到 9


5-2.关系运算符

.下表显示了 C++ 支持的关系运算符。

假设变量 A 的值为 10，变量 B 的值为 20，则：
运算符 描述  实例
==  检查两个操作数的值是否相等，如果相等则条件为真。    (A == B) 不为真。
!=  检查两个操作数的值是否相等，如果不相等则条件为真。   (A != B) 为真。
>   检查左操作数的值是否大于右操作数的值，如果是则条件为真。    (A > B) 不为真。
<   检查左操作数的值是否小于右操作数的值，如果是则条件为真。    (A < B) 为真。
>=  检查左操作数的值是否大于或等于右操作数的值，如果是则条件为真。 (A >= B) 不为真。
<=  检查左操作数的值是否小于或等于右操作数的值，如果是则条件为真。 (A <= B) 为真。

.实例
#include <iostream>
using namespace std;
 
int main()
{
   int a = 21;
   int b = 10;
   int c ;
 
   if( a == b )
   {
      cout << "Line 1 - a 等于 b" << endl ;
   }
   else
   {
      cout << "Line 1 - a 不等于 b" << endl ;
   }
   return 0;
}

当上面的代码被编译和执行时，它会产生以下结果：

Line 1 - a 不等于 b
Line 2 - a 不小于 b

5-3.逻辑运算符
//注意：非0为真，0为假
.下表显示了 C++ 支持的关系逻辑运算符。

假设变量 A 的值为 1，变量 B 的值为 0，则：
运算符 描述  实例
&&  称为逻辑与运算符。如果两个操作数都 true，则条件为 true。   (A && B) 为 false。
||  称为逻辑或运算符。如果两个操作数中有任意一个 true，则条件为 true。  (A || B) 为 true。
!   称为逻辑非运算符。用来逆转操作数的逻辑状态，如果条件为 true 则逻辑非运算符将使其为 false。 !(A && B) 为 true。

//注意要与位运算符&,|,^,!区分，逻辑运算符无异或

.实例
#include <iostream>
using namespace std;
 
int main()
{
   int a = 5;
   int b = 20;
   int c ;
 
   if ( a && b )
   {
      cout << "Line 1 - 条件为真"<< endl ;
   }
   if ( a || b )
   {
      cout << "Line 2 - 条件为真"<< endl ;
   }
   /* 改变 a 和 b 的值 */
   a = 0;
   b = 10;
   if ( a && b )
   {
      cout << "Line 3 - 条件为真"<< endl ;
   }
   else
   {
      cout << "Line 4 - 条件不为真"<< endl ;
   }
   if ( !(a && b) )
   {
      cout << "Line 5 - 条件为真"<< endl ;
   }
   return 0;
}

当上面的代码被编译和执行时，它会产生以下结果：

Line 1 - 条件为真
Line 2 - 条件为真
Line 4 - 条件不为真
Line 5 - 条件为真

5-4.位运算符

位运算符作用于位，并逐位执行操作。&、 | 和 ^ 的真值表如下所示：
p   q   p & q   p | q   p ^ q//&全真则真，一假则假；|一真则真，全假则假；^异真同假
0   0   0   0   0
0   1   0   1   1
1   1   1   1   0
1   0   0   1   1

假设如果 A = 60，且 B = 13，现在以二进制格式表示，它们如下所示：

A = 0011 1100

B = 0000 1101

-----------------

A&B = 0000 1100

A|B = 0011 1101

A^B = 0011 0001

~A  = 1100 0011

下表显示了 C++ 支持的位运算符。假设变量 A 的值为 60，变量 B 的值为 13，则：
----------------------------------------------------------------------------------------------------------
运算符 描述  实例
(1).&   按位与操作，按二进制位进行"与"运算。运算规则：

0&0=0;   
0&1=0;    
1&0=0;     
1&1=1;
(A & B) 将得到 12，即为 0000 1100   

(2).|  按位或运算符，按二进制位进行"或"运算。运算规则：

0|0=0;   
0|1=1;   
1|0=1;    
1|1=1;

(A | B) 将得到 61，即为 0011 1101
   

(3).^ 异或运算符，按二进制位进行"异或"运算。运算规则：
如果a、b两个值不相同，则异或结果为1。如果a、b两个值相同，异或结果为0
0^0=0;   
0^1=1;   
1^0=1;  
1^1=0;

(A ^ B) 将得到 49，即为 0011 0001
   

(4).~(取反运算符，按二进制位进行"取反"运算。运算规则：

~1=-2;   
~0=-1;

(~A ) 将得到 -61，即为 1100 0011，一个有符号二进制数的补码形式。
(5).
A = 0011 1100，B = 0000 1101
<<  二进制左移运算符。将一个运算对象的各二进制位全部左移若干位（左边丢弃，右边补0）。  A << 2 将得到 240，即为 1111 0000
>>  二进制右移运算符。将一个数的各二进制位全部右移若干位，正数左补0，负数左补1，右边丢弃(右边丢弃,左边补0)。    A >> 2 将得到 15，即为 0000 1111
-----------------------------------------------------------------------------------------------------------------------
实例

请看下面的实例，了解 C++ 中可用的位运算符。

#include <iostream>
using namespace std;
 
int main()
{
   unsigned int a = 60;      // 60 = 0011 1100  
   unsigned int b = 13;      // 13 = 0000 1101
   int c = 0;           
 
   c = a & b;             // 12 = 0000 1100
   cout << "Line 1 - c 的值是 " << c << endl ;
 
   c = a | b;             // 61 = 0011 1101
   cout << "Line 2 - c 的值是 " << c << endl ;
 
   c = a ^ b;             // 49 = 0011 0001
   cout << "Line 3 - c 的值是 " << c << endl ;
 
   c = ~a;                // -61 = 1100 0011
   cout << "Line 4 - c 的值是 " << c << endl ;
 
   c = a << 2;            // 240 = 1111 0000
   cout << "Line 5 - c 的值是 " << c << endl ;
 
   c = a >> 2;            // 15 = 0000 1111
   cout << "Line 6 - c 的值是 " << c << endl ;
 
   return 0;
}

当上面的代码被编译和执行时，它会产生以下结果：

Line 1 - c 的值是 12
Line 2 - c 的值是 61
Line 3 - c 的值是 49
Line 4 - c 的值是 -61
Line 5 - c 的值是 240
Line 6 - c 的值是 15

5-5.赋值运算符

下表列出了 C++ 支持的赋值运算符：
运算符 描述  实例
=   简单的赋值运算符，把右边操作数的值赋给左边操作数    C = A + B 将把 A + B 的值赋给 C
+=  加且赋值运算符，把右边操作数加上左边操作数的结果赋值给左边操作数    C += A 相当于 C = C + A
-=  减且赋值运算符，把左边操作数减去右边操作数的结果赋值给左边操作数    C -= A 相当于 C = C - A
*=  乘且赋值运算符，把右边操作数乘以左边操作数的结果赋值给左边操作数    C *= A 相当于 C = C * A
/=  除且赋值运算符，把左边操作数除以右边操作数的结果赋值给左边操作数    C /= A 相当于 C = C / A
%=  求模且赋值运算符，求两个操作数的模赋值给左边操作数   C %= A 相当于 C = C % A
<<= 左移且赋值运算符    C <<= 2 等同于 C = C << 2
>>= 右移且赋值运算符    C >>= 2 等同于 C = C >> 2
&=  按位与且赋值运算符   C &= 2 等同于 C = C & 2
^=  按位异或且赋值运算符  C ^= 2 等同于 C = C ^ 2
|=  按位或且赋值运算符   C |= 2 等同于 C = C | 2
实例

请看下面的实例，了解 C++ 中可用的赋值运算符。

复制并黏贴下面的 C++ 程序到 test.cpp 文件中，编译并运行程序。
实例
#include <iostream>
using namespace std;
 
int main()
{
   int a = 21;
   int c ;
 
   c =  a;
   cout << "Line 1 - =  运算符实例，c 的值 = : " <<c<< endl ;
 
   c +=  a;
   cout << "Line 2 - += 运算符实例，c 的值 = : " <<c<< endl ;
 
   c -=  a;
   cout << "Line 3 - -= 运算符实例，c 的值 = : " <<c<< endl ;
 
   c *=  a;
   cout << "Line 4 - *= 运算符实例，c 的值 = : " <<c<< endl ;
 
   c /=  a;
   cout << "Line 5 - /= 运算符实例，c 的值 = : " <<c<< endl ;
 
   c  = 200;
   c %=  a;
   cout << "Line 6 - %= 运算符实例，c 的值 = : " <<c<< endl ;
 
   c <<=  2;
   cout << "Line 7 - <<= 运算符实例，c 的值 = : " <<c<< endl ;
 
   c >>=  2;
   cout << "Line 8 - >>= 运算符实例，c 的值 = : " <<c<< endl ;
 
   c &=  2;
   cout << "Line 9 - &= 运算符实例，c 的值 = : " <<c<< endl ;
 
   c ^=  2;
   cout << "Line 10 - ^= 运算符实例，c 的值 = : " <<c<< endl ;
 
   c |=  2;
   cout << "Line 11 - |= 运算符实例，c 的值 = : " <<c<< endl ;
 
   return 0;
}

当上面的代码被编译和执行时，它会产生以下结果：

Line 1 - =  运算符实例，c 的值 = 21
Line 2 - += 运算符实例，c 的值 = 42
Line 3 - -= 运算符实例，c 的值 = 21
Line 4 - *= 运算符实例，c 的值 = 441
Line 5 - /= 运算符实例，c 的值 = 21
Line 6 - %= 运算符实例，c 的值 = 11
Line 7 - <<= 运算符实例，c 的值 = 44
Line 8 - >>= 运算符实例，c 的值 = 11
Line 9 - &= 运算符实例，c 的值 = 2
Line 10 - ^= 运算符实例，c 的值 = 0
Line 11 - |= 运算符实例，c 的值 = 2

注:unsigned and signed
    1、unsigned的作用就是将数字类型无符号化， 例如 int 型的范围：-2^31 ~ 2^31 - 1，而unsigned int的范围：0 ~ 2^32。看起来unsigned 是个不错的类型，尤其是用在自增或者没有负数的情况。但是在实际使用中会出现一些意外的情况。

    2、signed在默认情况下声明的整型变量都是有符号的类型（char有点特别），如果需声明无符号类型的话就需要在类型前加上unsigned。无符号版本和有符号版本的区别就是无符号类型能保存2倍于有符号类型的正整数数据。 

5-6.杂项运算符

下表列出了 C++ 支持的其他一些重要的运算符。
运算符 描述
sizeof  sizeof 运算符返回变量的大小。例如，sizeof(a) 将返回 4，其中 a 是整数。
Condition ? X : Y   条件运算符。如果 Condition 为真 ? 则值为 X : 否则值为 Y。
,   逗号运算符会顺序执行一系列运算。整个逗号表达式的值是以逗号分隔的列表中的最后一个表达式的值。
.（点）和 ->（箭头）    成员运算符用于引用类、结构和共用体的成员。
Cast    强制转换运算符把一种数据类型转换为另一种数据类型。例如，int(2.2000) 将返回 2。
&   指针运算符 & 返回变量的地址。例如 &a; 将给出变量的实际地址。
*   指针运算符 * 指向一个变量。例如，*var; 将指向变量 var。

5-7.C++ 中的运算符优先级

运算符的优先级确定表达式中项的组合。这会影响到一个表达式如何计算。某些运算符比其他运算符有更高的优先级，例如，乘除运算符具有比加减运算符更高的优先级。

例如 x = 7 + 3 * 2，在这里，x 被赋值为 13，而不是 20，因为运算符 * 具有比 + 更高的优先级，所以首先计算乘法 3*2，然后再加上 7。

下表将按运算符优先级从高到低列出各个运算符，具有较高优先级的运算符出现在表格的上面，具有较低优先级的运算符出现在表格的下面。在表达式中，较高优先级的运算符会优先被计算。

类别      运算符                            结合性 
后缀  () [] -> . ++ - -       从左到右 
一元      + - ! ~ ++ - - (type)* & sizeof     从右到左 
乘除      * / %   从左到右 
加减  + -     从左到右 
移位      << >>   从左到右 
关系  < <= > >=   从左到右 
相等      == !=   从左到右 
位与 AND  &   从左到右 
位异或 XOR     ^   从左到右 
位或 OR   |   从左到右 
逻辑与 AND     &&      从左到右 
逻辑或 OR      ||      从左到右 
条件  ?:      从右到左 
赋值      = += -= *= /= %=>>= <<= &= ^= |=    从右到左 
逗号      ,   从左到右 


6.修饰符

C++ 允许在 char、int 和 double 数据类型前放置修饰符。修饰符用于改变基本类型的含义，所以它更能满足各种情境的需求。

下面列出了数据类型修饰符：

    signed
    unsigned
    long
    short

修饰符 signed、unsigned、long 和 short 可应用于整型，signed 和 unsigned 可应用于字符型，long 可应用于双精度型。

修饰符 signed 和 unsigned 也可以作为 long 或 short 修饰符的前缀。例如：unsigned long int。

C++ 允许使用速记符号来声明无符号短整数或无符号长整数。您可以不写 int，只写单词 unsigned、short 或 long，int 是隐含的。例如，下面的两个语句都声明了无符号整型变量。

unsigned x;
unsigned int y;

为了理解 C++ 解释有符号整数和无符号整数修饰符之间的差别，我们来运行一下下面这个短程序：
实例
#include <iostream>
using namespace std;
 
/* 
 * 这个程序演示了有符号整数和无符号整数之间的差别
*/
int main()
{
   short int i;           // 有符号短整数
   short unsigned int j;  // 无符号短整数
 
   j = 50000;
 
   i = j;
   cout << i << " " << j;
 
   return 0;
}

当上面的程序运行时，会输出下列结果：

-15536 50000

上述结果中，无符号短整数 50,000 的位模式被解释为有符号短整数 -15,536。
C++ 中的类型限定符

类型限定符提供了变量的额外信息。
限定符 含义
const   const 类型的对象在程序执行期间不能被修改改变。
volatile    修饰符 volatile 告诉编译器不需要优化volatile声明的变量，让程序可以直接从内存中读取变量。对于一般的变量编译器会对变量进行优化，将内存中的变量值放在寄存器中以加快读写效率。
restrict    由 restrict 修饰的指针是唯一一种访问它所指向的对象的方式。只有 C99 增加了新的类型限定符 restrict。


6.程序流程结构
'6-1.选择语句'
    6-1.选择语句
    /1.语法：
    if(boolean_expression)
    {
       // 如果布尔表达式为真将执行的语句
    }

    如果布尔表达式为 true，则 if 语句内的代码块将被执行。如果布尔表达式为 false，则 if 语句结束后的第一组代码（闭括号后）将被执行。

    C 语言把任何非零和非空的值假定为 true，把零或 null 假定为 false。
    /2.实例

    #include <iostream>
    using namespace std;
     
    int main ()
    {
       // 局部变量声明
       int a = 10;
     
       // 使用 if 语句检查布尔条件
       if( a < 20 )
       {
           // 如果条件为真，则输出下面的语句
           cout << "a 小于 20" << endl;
       }
       cout << "a 的值是 " << a << endl;
     
       return 0;
    }
    它会产生下列结果：

    a 小于 20
    a 的值是 10

    6-2.if-else语句
    /1.语法
    if(boolean_expression)
    {
       // 如果布尔表达式为真将执行的语句
    }
    else
    {
       // 如果布尔表达式为假将执行的语句
    }

    如果布尔表达式为 true，则执行 if 块内的代码。如果布尔表达式为 false，则执行 else 块内的代码。

    /2.实例

    #include <iostream>
    using namespace std;
     
    int main ()
    {
       // 局部变量声明
       int a = 100;
     
       // 检查布尔条件
       if( a < 20 )
       {
           // 如果条件为真，则输出下面的语句
           cout << "a 小于 20" << endl;
       }
       else
       {
           // 如果条件为假，则输出下面的语句
           cout << "a 大于 20" << endl;
       }
       cout << "a 的值是 " << a << endl;
     
       return 0;
    }

    /3.if...else if...else 语句

    一个 if 语句后可跟一个可选的 else if...else 语句，这可用于测试多种条件。

    /3-1.注意：当使用 if...else if...else 语句时，以下几点需要注意：

        一个 if 后可跟零个或一个 else，else 必须在所有 else if 之后。
        一个 if 后可跟零个或多个 else if，else if 必须在 else 之前。
        一旦某个 else if 匹配成功，其他的 else if 或 else 将不会被测试。

    /3-2.语法

    C++ 中的 if...else if...else 语句的语法：

    if(boolean_expression 1)
    {
       // 当布尔表达式 1 为真时执行
    }
    else if( boolean_expression 2)
    {
       // 当布尔表达式 2 为真时执行
    }
    else if( boolean_expression 3)
    {
       // 当布尔表达式 3 为真时执行
    }
    else 
    {
       // 当上面条件都不为真时执行
    }

    实例

    #include <iostream>
    using namespace std;
     
    int main ()
    {
       // 局部变量声明
       int a = 100;
     
       // 检查布尔条件
       if( a == 10 )
       {
           // 如果 if 条件为真，则输出下面的语句
           cout << "a 的值是 10" << endl;
       }
       else if( a == 20 )
       {
           // 如果 else if 条件为真，则输出下面的语句
           cout << "a 的值是 20" << endl;
       }
       else if( a == 30 )
       {
           // 如果 else if 条件为真，则输出下面的语句
           cout << "a 的值是 30" << endl;
       }
       else
       {
           // 如果上面条件都不为真，则输出下面的语句
           cout << "没有匹配的值" << endl;
       }
       cout << "a 的准确值是 " << a << endl;
     
       return 0;
    }

    当上面的代码被编译和执行时，它会产生下列结果：

    没有匹配的值
    a 的准确值是 100

    注意：1.if ()后不要加分号；2.括号格式：if (a = b){}

    6-3.嵌套if
    .语法
    if( boolean_expression 1)
    {
       // 当布尔表达式 1 为真时执行
       if(boolean_expression 2)
       {
          // 当布尔表达式 2 为真时执行
       }
    }
    您可以嵌套 else if...else，方式与嵌套 if 语句相似。
    .实例
    #include <iostream>
    using namespace std;
    int main()
    {
        int a, b, c;//可以用逗号表示连续输入
        cout << "请输入a =";
        cin >> a;
        cout << "请输入b =";
        cin >> b;
        cout << "请输入c =";
        cin >> c;
        if (a > b){
            cout << "a>b" << endl; 
            if (a > c){
                cout << "a>c" << endl;
            }
            else{
                cout << "a<c" << endl;
            }
        }
        else {
            cout << "a<b" << endl;
        return 0;    
        }
    }

    .问题：
    error: expected ‘}’ before ‘else’
    字面上的意思就是“ else”前面缺少了一个“}”

    6-4.switch语句
    /1.功能：
    一个 switch 语句允许测试一个变量等于多个值时的情况。每个值称为一个 case，且被测试的变量会对每个 switch case 进行检查。
    /2.语法
    switch(expression){
        case constant-expression  :
           statement(s);
           break; // 可选的
        case constant-expression  :
           statement(s);
           break; // 可选的
      
        // 您可以有任意数量的 case 语句
        default : // 可选的
           statement(s);
    }
    /3.规则：

        .switch 语句中的 expression 必须是一个整型或枚举类型，或者是一个 class 类型，其中 class 有一个单一的转换函数将其转换为整型或枚举类型。
        .在一个 switch 中可以有任意数量的 case 语句。每个 case 后跟一个要比较的值和一个冒号。
        .case 的 constant-expression 必须与 switch 中的变量具有相同的数据类型，且必须是一个常量或字面量。
        .当被测试的变量等于 case 中的常量时，case 后跟的语句将被执行，直到遇到 break 语句为止。
        .当遇到 break 语句时，switch 终止，控制流将跳转到 switch 语句后的下一行。
        .不是每一个 case 都需要包含 break。如果 case 语句不包含 break，控制流将会 继续 后续的 case，直到遇到 break 为止。
        .一个 switch 语句可以有一个可选的 default case，出现在 switch 的结尾。
        default case 可用于在上面所有 case 都不为真时执行一个任务。default case 中的 break 语句不是必需的。
    总结:
    1.switch的参数必须时枚举型;2.case的参数要与swich一致,case可以有多个;
    3.break执行时会跳出switch语句,若case中无break,则继续执行下面的case语句,直到遇到break时跳出switch
    4.default可有可无,当所有case不满足时会执行default

    /4.实例
    #include <iostream>
    #include <string>
    using namespace std;//必须要用namespace才能成功
    void printcolor(string color, string str){
        int clr;
        string head;
        string tail;
        string display;
        if (color == "green") clr =1;
        if (color == "red") clr = 2;
        switch(clr){
            case 1:{
                head = "a"; 
                tail = "b";
                display = head + str + tail;  
                break;
            }
            case 2:{
                head = "c"; 
                tail = "d";
                display = head + str + tail;  
                break;
            }
            default:{
                display = str;
                break;
            }
        }   
        cout << display << endl;//只有当有endl的时候,每次调用函数才会换行
    }

    int main(){
        printcolor("green", "helloworld");
        printcolor("red", "helloworld");
        
        return 0;
    }

    6-5.嵌套switch
    您可以把一个 switch 作为一个外部 switch 的语句序列的一部分，即可以在一个 switch 语句内使用另一个 switch 语句。
    即使内部和外部 switch 的 case 常量包含共同的值，也没有矛盾。

    /1.语法
    switch(ch1) {
       case 'A': 
          cout << "这个 A 是外部 switch 的一部分";
          switch(ch2) {
             case 'A':
                cout << "这个 A 是内部 switch 的一部分";
                break;
             case 'B': // 内部 B case 代码
          }
          break;
       case 'B': // 外部 B case 代码
    }

    /2.实例
    #include <iostream>
    using namespace std;
    int main ()
    {
       // 局部变量声明
       int a = 100;
       int b = 200;
       switch(a) {
          case 100:{
             cout << "这是外部 switch 的一部分" << endl;
             switch(b) {
                case 200:
                   cout << "这是内部 switch 的一部分" << endl;
             }
       }
       cout << "a 的准确值是 " << a << endl;
       cout << "b 的准确值是 " << b << endl;
       return 0;
    }

    结果:
    这是外部 switch 的一部分
    这是内部 switch 的一部分
    a 的准确值是 100
    b 的准确值是 200

    6-6.三目运算符
    /1.作用:通过三目运算符实现简单判断
    /2.语法:表达式1 ? 表达式2 : 表达式3 | c = a > b ? a : b;
    /3.解释:若表达式1的值为真,执行表达式2,并返回表达式2的结果
    若表达式1的值为假,执行表达式3,并返回表达式3的结果
    /4.例子
    /4-1.
        #include <iostream>
        using namespace std;
        int main(){
            int a = 1, b = 2, c =3;
            c = a > b ? a : b;
            cout << "c = " << c << endl;
            (a > b ? a : b) = 100
            cout << "a = " << a << endl;
        }

    /4-2.
        int a = 1, b = 2, z, c = 3;
         
        z = a > b ? a : (b > c ? b : c);
         
        cout << "z:" << z << endl;

        这样输出的结果是：z:3

'6-2.循环语句'
6-2.while循环

    6-2-1.语法：
    while(condition)
    {
       statement(s);
    }

    在这里，statement(s) 可以是一个单独的语句，也可以是几个语句组成的代码块。
    condition 可以是任意的表达式，当为任意非零值时都为真。当条件为真时执行循环。
    当条件为假时，程序流将继续执行紧接着循环的下一条语句。

    6-2-2.示例:
    /1.例子1
    #include <iostream>
    using namespace std;
    int main ()
    {
       // 局部变量声明
       int a = 10;

       // while 循环执行
       while( a < 20 )
       {
           cout << "a 的值：" << a << endl;
           a++;
       }
     
       return 0;
    }

    当 while() 中的条件值为 0 时，循环就结束了。

    开始 y = 10，每循环一次 y 的值就减 1（y-- 会导致 y 减 1），当 y 值一直减到 0 时，
    退出 while 循环，但是还要继续做 y --操作，所以 y 最后的值就是 -1。

    /2.例子2(死循环)
    #include <iostream>
    using namespace std;
    int main ()
    {
       // 局部变量声明
       int a = 10;
       // while 无限循环执行
       while( 1 )
       {
           cout << "a 的值：" << a << endl;
           a++;
       }
       return 0;
    }

6-3.for循环

    6-3-1.语法
    for ( init; condition; increment )//起始表达式；条件表达式；末尾循环体
    {
       statement(s);
    }

    6-3-2.控制流:
        init 会首先被执行，且只会执行一次。这一步允许您声明并初始化任何循环控制变量。
        您也可以不在这里写任何语句，只要有一个分号出现即可。
        接下来，会判断 condition。如果为真，则执行循环主体。如果为假，则不执行循环主体，且控制流会跳转到紧接着 for 循环的下一条语句。
        在执行完 for 循环主体后，控制流会跳回上面的 increment 语句。该语句允许您更新循环控制变量。该语句可以留空，只要在条件后有一个分号出现即可。
        条件再次被判断。如果为真，则执行循环，这个过程会不断重复（循环主体，然后增加步值，再然后重新判断条件）。在条件变为假时，for 循环终止。

    总结：1.先执行起始表达式，2.再判断条件表达式，若为True，则执行for循环内的语句，然后再执行末尾循环体的语句，直到不满足条件后跳出循环体；
    若为flase，则执行for循环之下的语句
    6-3-3.例子:
    /1.例1
    #include <iostream>
    using namespace std;
     
    int main ()
    {
       // for 循环执行
       for( int a = 10; a < 20; a = a + 1 )//起始表达式；条件表达式；末尾循环体

       {
           cout << "a 的值：" << a << endl;//循环语句
       }
     
       return 0;
    }

    6-3-4.注意事项:for 语句中的三个表达式可部分或全部省略，但两个分号不能省略。

    /1.格式:for (表达式1;表达式2;表达式3) {
        // 循环体语句
    }

    常见的是：将表达式1放在了 for 语句之前，或表达式3放在了循环体中，在 for 语句中就可相应地省略表达式1或表达式3。
    如：
    for(i=1,s=0; i<=100; i++) {
        sum += i;
    }

    可写成如下形式：

    i=1; 
    sum=0;
    for ( ;i<=100; ) {
        sum+=i;  
        i++;
    }      
    // 等效于while循环

    表达式2也可省略，写成：

    for (; ;) {…}

    此时，系统约定表达式2的值为 1，即恒为真，则等同于：

    for (; 1;) {…}

6-4.dowhile循环

    /1.功能:不像 for 和 while 循环，它们是在循环头部测试循环条件。
    do...while 循环是在循环的尾部检查它的条件。
    do...while 循环与 while 循环类似，但是 do...while 循环会确保至少执行一次循环。

    /3.注意：
    条件表达式出现在循环的尾部，所以循环中的 statement(s) 会在条件被测试之前至少执行一次。
    如果条件为真，控制流会跳转回上面的 do，然后重新执行循环中的 statement(s)。
    这个过程会不断重复，直到给定条件变为假为止。

    总结：先执行do语句，然后执行while语句，当条件不满足时，结束循环，执行下一个语句
    /4.例：
    #include <iostream>
    using namespace std;
    int main ()
    {
       // 局部变量声明
       int a = 10;
       // do 循环执行
       do
       {
           cout << "a 的值：" << a << endl;
           a = a + 1;
       }while( a < 20 );
     
       return 0;
    }

6-5.循环嵌套
/1.C++ 中 嵌套 for 循环 语句的语法：
for ( init; condition; increment )
{
   for ( init; condition; increment )
   {
      statement(s);
   }
   statement(s); // 可以放置更多的语句
}

/2.C++ 中 嵌套 while 循环 语句的语法：
while(condition)
{
   while(condition)
   {
      statement(s);
   }
   statement(s); // 可以放置更多的语句
}

/3.C++ 中 嵌套 do...while 循环 语句的语法：
do
{
   statement(s); // 可以放置更多的语句
   do
   {
      statement(s);
   }while( condition );
 
}while( condition );

关于嵌套循环有一点值得注意，您可以在任何类型的循环内嵌套其他任何类型的循环。
比如，一个 for 循环可以嵌套在一个 while 循环内，反之亦然。
/4.例子：
下面的程序使用了一个嵌套的 for 循环来查找 2 到 100 中的质数：
planA    //质数又称为素数，是一个大于1的自然数，除了1和它自身外，不能被其他自然数整除的数叫做质数；否则称为合数。
    #include<iostream>
    using namespace std;
    int main()
    {
        int i,j,count=0;    
        for (i=0;i<100;i++) {
            for(j=2;j<=i;j++) //从2遍历到i-1，寻找是否有i的因子
            {
                if((i%j) == 0)
                {
                    break;
                }
            }
            if(j==i)
            {  //判断是否从第二个for中正常循环出来的i                                          
                cout << i << endl;     
                count++;
            }
        }
        cout << "总数为count=" << count << endl;
        return 0;
    }
planB:
    #include <iostream>
    using namespace std;
    void Primer_Search(int n);
    int main(){
        int n;
        cout << "请输入一个数字范围n=";
        cin >> n;
        Primer_Search(n);
    }

    void Primer_Search(int n){
        int count = 0, i, j;
        for (i = 0; i <= n; i++){
            for (j = 2; j <= i; j++){
                if (i % j == 0){
                    break;
                }
                }
            if (i == j)//当且仅当只能被自己整除的时候才能输入质数，例如6%2=0，但是此时i=6,j=2,i!=j,所以此时不能当质数输出
            {
                cout << "质数i=" << i << endl;
                count++;
            }   
        }
    }

"6-3.跳转语句"
6-3.break
/1.用法
    1.当 break 语句出现在一个循环内时，循环会立即终止，且程序流将继续执行紧接着循环的下一条语句。
    2.它可用于终止 switch 语句中的一个 case。
    3.如果您使用的是嵌套循环（即一个循环内嵌套另一个循环），break 语句会停止执行最内层的循环，然后开始执行该块之后的下一行代码。

/2.实例
#include <iostream>
using namespace std;
int main ()
{
   // 局部变量声明
   int a = 10;

   // do 循环执行
   do
   {
       cout << "a 的值：" << a << endl;
       a = a + 1;
       if( a > 15)
       {
          // 终止循环
          break;
       }
   }while( a < 20 );
 
   return 0;
}
6-4.coutinue
/1.特点:
    .C++ 中的 continue 语句有点像 break 语句。但它不是强迫终止，continue 会跳过当前循环中的代码，强迫开始下一次循环。
    .对于 for 循环，continue 语句会导致执行条件测试和循环增量部分。
    对于 while 和 do...while 循环，continue 语句会导致程序控制回到条件测试上。
/2.例子
    /2-1.#include <iostream>
    using namespace std;
    int main ()
    {
       // 局部变量声明
       int a = 10;

       // do 循环执行
       do
       {
           if( a == 15)
           {
              // 跳过迭代
              a = a + 1;
              continue;
           }
           cout << "a 的值：" << a << endl;
           a = a + 1;
       }while( a < 20 );
     
       return 0;
    }

    当上面的代码被编译和执行时，它会产生下列结果：

    a 的值： 10
    a 的值： 11
    a 的值： 12
    a 的值： 13
    a 的值： 14
    a 的值： 16
    a 的值： 17
    a 的值： 18
    a 的值： 19

    /2-2.例2
    只输出奇数不输出偶数
    #include <iostream>
    using namespace std;
    #include <string>
    int main(){
    int i, j;
    cout << "请输入一个数字范围" << endl;
    cin >> j;
    for (i = 0; i <= j; i++){
        if (i % 2 == 0){
            continue;
        }
        cout << i << endl;
    }

    }

6-5.go-to 
/1.作用：goto 语句允许把控制无条件转移到同一函数内的被标记的语句。

/2.注意：在任何编程语言中，都不建议使用 goto 语句。因为它使得程序的控制流难以跟踪，使程序难以理解和难以修改。
        任何使用 goto 语句的程序可以改写成不需要使用 goto 语句的写法。
/3.语法
goto label;
..
.
label: statement;

在这里，label 是识别被标记语句的标识符，可以是任何除 C++ 关键字以外的纯文本。标记语句可以是任何语句，放置在标识符和冒号（:）后边。
/4.例子
/4-1.例1.
#include <iostream>
using namespace std;
int main(){
    cout << "1" << endl;
    goto flag;
    cout << "2" << endl;
    cout << "3" << endl;
    cout << "4" << endl;
    cout << "5" << endl;
    flag:
    cout << "6" << endl;
}
输出结果：
1
6


7.数组
    7-1.一维数组
    7-1-1.一维数组的定义方式
        /定义数组：/1.数据类型 数组名 [数组长度];
                /2.数据类型 数组名[数组长度] = {value1, value2,...};
                /3.数据类型 数组名称[] = {value1, value2};
        /:访问数组：arr[9]
        /:赋值：arr[3]=100
    /例子1.
    #include <iostream>
    using namespace std;
    int main()
    {
        //方式1
        int arr1[5];
        arr1[0] = 10;
        arr1[1] = 10;
        arr1[2] = 10;
        cout << arr1[0] << endl;//访问数据元素
        //方式2嵌套输出数组
        int arr2[5] = {1, 2, 3, 4, 5};
        for (int i =0; i < 5; i++){
            cout << arr2[i] << endl;// cout = c + out
        }
        ///////方式3,定义数组的时候必须有初始长度
        int arr3[] = {1, 2, 3, 4};
        for (int i =0; i < 4; i++){
            cout << arr3[i] << endl;// cout = c + out
        }
    }
    /例2.
    #include <iostream>
    using namespace std;
     
    #include <iomanip>
    using std::setw;
     
    int main ()
    {
       int n[ 10 ]; // n 是一个包含 10 个整数的数组
     
       // 初始化数组元素          
       for ( int i = 0; i < 10; i++ )
       {
          n[ i ] = i + 100; // 设置元素 i 为 i + 100
       }
       cout << "Element" << setw( 13 ) << "Value" << endl;
     
       // 输出数组中每个元素的值                     
       for ( int j = 0; j < 10; j++ )
       {
          cout << setw( 7 )<< j << setw( 13 ) << n[ j ] << endl;
       }
     
       return 0;
    7-1-2.访问一维数组的方法
    #include <iostream>
    using namespace std;
    int main()
    {
        //1.通过数组名统计整个数组占用内存大小
        int arr4[4] = {1, 2, 3, 4};
        cout << "整个数组占用内存空间为:" << sizeof(arr4) << endl;
        cout << "每个元素占用内存空间为:" << sizeof(arr4[0]) << endl;
        cout << "数组中元素个数为:" << sizeof(arr4) / sizeof(arr4[0]) << endl;
        // 2.可以通过数组名查看数组首地址
        cout << "数组首地址为:" << (int)arr4 << endl;//int是指将地址切换为10进制
        cout << "数组第一个元素地址为:" << (int)&arr4[0] << endl;
        cout << "数组第二个元素地址为:" << (int)&arr4[1] << endl;
        // cout << "数组中第一个元素地址为:" << (int)&arr4[0] << endl;
        //&相当于是个取符号
        return 0;
    }
    /1.案例：
    #include <iostream>
    using namespace std;
    int main()
    {
        int i, max=0, arr[5]={1, 2, 3, 4, 5};
        for (i = 0; i < 5; i++){
            if (arr[i] > max){
                max = arr[i];
            }
        }
        cout << "max = " << max << endl;
    }
    /2.案例2：冒泡排序
    //程序包含两种冒泡排序算法
    //从小到大的冒泡排序BubbleSort
    //从大到小的冒泡排序InverseBubbleSort
    #include <iostream>
    using namespace std;
    void BubbleSort(int arr[], int n);
    void InverseBubbleSort(int arr[], int n);
    void printArray(int arr[], int n);
    const int n = 8;
    int main(int argc, char **argv) //argc[]
    {
        int a[n] = {6,5,3,1,8,7,2,4};
        BubbleSort(a,n);
        cout << "从小到大的冒泡排序:\n";
        printArray(a,n);
        int b[n] = {6,5,3,1,8,7,2,4};
        InverseBubbleSort(b,n);
        cout << "从大到小的冒泡排序:\n";
        printArray(b,n);
        return 0;
    }
    void BubbleSort(int arr[], int n)
    {
        for(int i = 0; i < n - 1; i++)
        {
            for(int j = 0; j < n - i - 1; j++)
            {
                if(arr[j] > arr[j+1])
                    swap(arr[j],arr[j+1]);//swap包含在命名空间std中，swap(a,b)表示对a,b进行交换
            }
        }
    }
    void InverseBubbleSort(int arr[], int n)//要声明函数里面的数据类型
    {
        for(int i = 0; i < n - 1; i++)//有n个数，则要走n-1个循环，第i次循环要进行最多n-i-1次排序
            //因为第一次循环已经把最大的数放在最后了，所以第二次循环就只进行n-1次排序
        {
            for(int j = n - 1; j > 0; j--)
            {
                if(arr[j] > arr[j - 1])
                {
                    swap(arr[j],arr[j-1]);
                }
            }
        }
    }
    void printArray(int arr[], int n)
    {
        for(int i = 0; i < n; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    ------------------------
    注：int main(int argc, char **argv)的详解：
    1.argv:命令行的参数总个数，argv[]是argv个参数，第0个参数是程序的全名，以后的参数命令行后面跟的是用户输入额参数
    所以,argc是参数个数，argv[]是argv个参数，argv[i] = 'output'
    2.char *argv[]是一个字符串组，其大小为int argc,主要用于命令行参数argv[]参数，数组里的每一个元素代表一个参数；
    比如输入：test a b c ,argc = r,argv[0] = "test",argv[1] = "a",...,argv[3] = "c",argc记录了用户在运行程序时输入的参数个数，
    arg指向的数组中至少有一个字符指针，即arg[0],他通常指向程序中的可执行文件的文件名
    3.总结：
    int argv:表示在命令行输入参数命令的时候，一共有多少参数，
    比如说，可执行文件为a.cpp,则当:a.cpp a b c 时候，argc = 3,
    char *argv[]:表示用来取得你所输入的参数，当可执行文件为：a.cpp时候：
    当,aa.cpp a b，argc = 3,argv[0]="aa",argv[1]="a",argv[2]="b"
    最后总结:argc是参数的个数，argv[]是参数，argv[0]是文件名，argv[1]是第一个参数...   
    4.
    4-1关于函数调用的问题：若是先写int main(){}后写void func(){},则需要在最首端申明void func()；，在int main()中调用
    若是先写void func(),则无需申明，只需在int main()中调用就行
    4-2原则：void里面要指明数据类型；而且int main()中的变量在函数中不能复用，需要额外定义
---------------------------------------------------
    7-2.2维数组
    /1.形式：type name[size1][size2]...[sizeN];
    /2.语法：int threedim[3][3][3];---->声明一个3x3x3的Matrix
    /3.二维数组：
        .初始化二维数组：int a[3][4]={{0, 1, 2, 3},//第一行
                                {4, 5, 6,7},//第二行
                                {8, 9, 10, 11}};//第三行
        .初始化方法2：int a[3][4]={0,......,11};
        .访问2维数组：int val = a[2][3];//访问第3行第4列的元素
        .修改2维数组:val[0][0] = 123
        .例子：
            #include <iostream>
            using namespace std;
            int main(){
                int a[5][2] = {{0, 0},{1,2}, {2,4}, {3, 6}, {4, 8}}
                for (int i = 0; i < 5; i++){//输出2维数组中的每个值
                    for (int j = 0; j < 2; j++){
                        cout << "a[" << i << "][" << j << "]";
                        cout << a[i][j] << endl;
                    }
                }
                return 0;
            }
            .例2：
            #include <iostream>
            using namespace std;
            int main(){
                int n;
                cout << "请输入行数n1="
                cin >> n1;
                cout << "请输入列数n2="
                cin >> n2;
                int a[n1][n2];
                for (int i = 0; i < n1; i++){
                    for (int j = 0; j < n2; j++){
                        cout >> "a[i][j]=" >> a[i][j];
                        printf("a[%d][%d]=",a[i][j])
                    }
                }
                return 0;
            }
        .2维数组空间：
        内存空间：sizeof(arr)
        第一行占用的内存：sizeof(arr[0])  行数：sizeof(arr)/sizeof(arr[0])//总内存数/第一行的内存
        第一行第一列元素占用的内存：sizeof(arr[0][0])   列数：sizeof(arr[0])/sizeof(arr[0][0])//第一行的内存数/第一个元素内存数
        2维数组的首地址：(int)arr
        2维数组的第1行的首地址：(int)arr[0]
        2维数组的第2行的首地址：(int)arr[1]
        2维数组的第1个元素的首地址：(int)&arr[0][0]

8.函数
    函数编写的步骤：申明--->定义--->在main()中调用
    8-1.定义：
    返回值类型 函数名 (参数列表){//参数列表：数据类型 变量
        函数体语句
        return 表达式
    }
        .定义格式:
        return_type function_name( parameter list )
        {
           body of the function
        }

        return_type:为函数的返回的数据类型，有些函数执行所需的操作而不返回值，这种情况下，
            return_type是void(所以当定义为int,double, char等这些类型的函数时，必须有返回值，而void不能有返回值,所以,为非void型函数时,必须有返回值,为void型函数时,不能有返回值)
        function_name:函数名称
        parameter list:参数列表包括参数的类型，顺序和数量，它可以没有
        body of the function：定义函数任务的语句

        .声明：
        return_type function_name( parameter list );
            int max(int num1, int num2);
            int max(int, int);//函数若有参数，则必须知名类型，但是名字可以不指定

        .调用：max(1, 2);//调用无需指明类型
        .例子：
            #include <iostream>
            using namespace std;
            #include <string>
            int add(int num1, int num2)
            {//num1和num2为形参
                int sum = num1 +num2;
                return sum;
            }
            int max(int a, int b){
                int c;
                c = a > b ? a : b;
                return c;
            }

            void Select(int a){
                cout << "a*2 = " << a*2 << endl;
            }

            int main(){
                int max1, sum, c;//a,b 为形参数
                sum = add(1, 3);
                max1 = max(1, 3); 
                Select(100);//因为void不能有返回值,所以只能用直接调用而不能赋值给别的变量
                cout << "sum = " << sum << endl;
                cout << "max = " << max1 << endl;
                return 0;
            }


    8-2.调用：
        1.功能：使用定义好的函数
        2.语法：函数名(参数)
        3.例子：
            #include <iostream>
            using namespace std;
            #include <string>
            int add(int num1, int num2){//num1和num2为形参
                int sum = num1 +num2;
                return sum;
            }
            int main(){
                int a=10, b=10;//a,b 为形参数
                int sum1 = add(a, b);//add(a,b)=sum
                cout << "sum = " << sum1 << endl;//这个sum和上面的sum不是一个sum ,他是具有
            }
        4.调用的方法
            1.值传递：//值传递不会影响实参
            // 函数定义
            void swap(int x, int y)//如果函数不需要返回值，声明的时候可以写void
            {
               int temp;
             
               temp = x; /* 保存 x 的值 */
               x = y;    /* 把 y 赋值给 x */
               y = temp; /* 把 x 赋值给 y */
              
            }

            #include <iostream>
            using namespace std;
             
            // 函数声明
            void swap(int x, int y);
             
            int main ()
            {
               // 局部变量声明
               int a = 100;
               int b = 200;
               swap(a, b);
             
               cout << "交换后，a 的值：" << a << endl;
               cout << "交换后，b 的值：" << b << endl;
               return 0;
            }
            2.引用传递://引用传递可以改变实参的值
                #include <iostream>
                using namespace std;
                void swap02(int &x, int &y)//
                {
                   int temp;
                   temp = x;    /* 保存地址 x 的值 */
                   x = y;        /* 把 y 赋值给 x */
                   y = temp;    /* 把 x 赋值给 y */
                }

                int main ()
                {
                   int a = 100, b = 200;  
                   swap02(a, b); 
                   cout << "交换后a= " << a << endl;
                   cout << "交换后b= " << b << endl;
                   return 0;
                }
            3.地址传递：//地址传递可以改变实参的值
                void swap03(int *p1, int *p2){//用指针接受地址
                    int temp = *p1;
                    *p1 = *p2;
                    *p2 = temp;//解引用，实现值的替换
                }
                int main(){
                    int a = 10, b = 20;
                    swap03(&a, &b);//传入a, b变量的地址
                }
            4.总结：
                #include <iostream>
                using namespace std;
                void swap01(int a, int b){
                    int temp = a;
                    a = b;
                    b = temp;
                }

                void swap02(int *p1, int *p2){//用指针接受地址,p1=&a,p2= &b
                    int temp = *p1;//p1指针的值赋给temp
                    *p1 = *p2;//p2指针的值和p1指针的值的交换
                    *p2 = temp;//temp的值，也就是*p1,即是p1的值传递给*p2,也就是p2的值
                }

                void swap03(int &a, int &b){
                    int temp = a;
                    a = b;
                    b = temp;
                }

                int main(){
                    int a = 10, b = 20;
                    swap01(a, b);//值传递不能修改实参的值
                    cout << "a = " << a << endl;
                    cout << "b = " << b << endl;
                    swap02(&a, &b);//传入a, b变量的地址，*p来显示指针值；地址传递可以修改实参的值
                    cout << "a = " << a << endl;
                    cout << "b = " << b << endl;
                    swap03(a, b);//地址传递不可以修改实参的值
                    cout << "a = " << a << endl;
                    cout << "b = " << b << endl;
                }   


        5.函数的常见样式：1.无参无返；有参无返；无参有反；有参有返回
            1.无参无返
            void test01(){
                //void a = 10;无类型不可以创建变量，因为无法分配内存
                cout << " " << endl;
                // test01()；函数调用
            }
            2.有参无返：
            void test02(int a){
                cout << "dsdf" << a << endl;
            }
            3.无参有返：
            int test02(){
                cout << "dfs" << endl;
                return 100
            }
            4.有参有返:
            int test04(int a){
                cout << "dsfsdf" << a endl;
                return a;
            }
        ////////////////函数调用要在之后，先main后定义，要申明函数；先定义后main，不要申明函数
            int main(){
                test01();
                test02(100);//调用函数的时候就不需要定义变量类型,例如test01(int 100)是错误的
                int num1 = test03(); cout << "num1 = " << num1 << endl;//num1 = 100
                int num2 = test04(100);//
                cout << "num2=" << num2;
            }

        6.函数的申明：函数申明能有多次，但是定义只能有1次
        例子：
        int max(int a, int b);
        int max(int a, int b);
        int max(int a, int b){
            return a > b ? a : b;
        }
        int main(){
            max(1,2)
        }
        7.函数的分文件编写
            ..作用：让代码更加简洁
            ..步骤：1.创建后缀名为.h的头文件 2.创建后缀名为.cpp的源文件
            3.在头文件中写函数声明 4.在源文件中写函数定义 5.调用函数
            ..例：
                //swap.h文件
                #include <iostream>
                using namespace std;
                void swap(a, b);
                //swap.cpp文件;
                #include <iostream>
                using namespace std;
                void swap(int a, int b){
                    int temp = a;
                    a = b;
                    b = temp;
                    cout << "a = " << a << endl;
                    cout << "b = " << b << endl;
                }
                //调用文件
                #include <iostream>
                using namespace std;
                #include "swap.h"
                int main(){
                    swap(1, 3);
                    return 0;
                }
        8.函数参数调用方法：
            1.传值调用：
            2.指针调用：
                .把参数的地址复制给形式参数，在函数内，该地址用于访问调用中要用到的实际参数
                这意味着修改形式参数会影响实际参数，按指针传递，参数指针就像其他值一样传递给函数
                .例子：
                // 函数定义
                void swap(int *x, int *y)
                {
                   int temp;
                   temp = *x;    /* 保存地址 x 的值 */
                   *x = *y;        /* 把 y 赋值给 x */
                   *y = temp;    /* 把 x 赋值给 y */
                }
                include <iostream>
                using namespace std;

                // 函数声明
                void swap(int *x, int *y);

                int main ()
                {
                   // 局部变量声明
                   int a = 100;
                   int b = 200;
                   cout << "交换前，a 的值：" << a << endl;
                   cout << "交换前，b 的值：" << b << endl;

                   /* 调用函数来交换值
                    * &a 表示指向 a 的指针，即变量 a 的地址 
                    * &b 表示指向 b 的指针，即变量 b 的地址 
                    */
                   swap(&a, &b);
                   cout << "交换后，a 的值：" << a << endl;
                   cout << "交换后，b 的值：" << b << endl;
                   return 0;
                }


    8-3.lambda表达式
        .形式：[capture](parameters)->return-type{body}
        .例子：[](int x, int y){return x < y;}
        如果没有返回值可以表示为:[capture](parameters){body},例如：[]{++global_x;}
        /* c++的变量传递俄传引用的区别，可以通过前面的[]来指定：
        []      // 沒有定义任何变量。使用未定义变量会引发错误。
        [x, &y] // x以传值方式传入（默认），y以引用方式传入。
        [&]     // 任何被使用到的外部变量都隐式地以引用方式加以引用。
        [=]     // 任何被使用到的外部变量都隐式地以传值方式加以引用。
        [&, x]  // x显式地以传值方式加以引用。其余变量以引用方式加以引用。
        [=, &z] // z显式地以引用方式加以引用。其余变量以传值方式加以引用。 */


9.指针//pointer:ptr
    9-1.指针的作用：可以通过指针间接访内存，其值为另一个变量的地址，即是内存的直接地址
    9-2.指针变量的定义和使用
        语法：数据类型 *变量名;type * var name;
            int    *ip;    /* 一个整型的指针 */
            double *dp;    /* 一个 double 型的指针 */
            float  *fp;    /* 一个浮点型的指针 */
            char   *ch;    /* 一个字符型的指针 */
        例子：
            #include <iostream>
            using namespace std;
            int main(){
                //1.定义指针
                int * p;
                int a = 10;
                p = &a;//让指针记录a的地址.所以指针p就是地址
                cout << "a的地址为" << &a << endl;
                cout << "指针p=" << p << endl;
                //2.使用指针
                //可以通过解引用的方式找到指针指向的内存
                //指针前加*表示解引用，找到指针指向的内存中的数据,修改*p,则会修改a的值
                *p = 234.2;//*p只能为整型
                cout << "a = " << a << endl;
                cout << "*p = " << *p << endl;
                //p = &a,*p = a,指针为变量地址，指针的解引用为变量的内容
            }
    9-3.指针所占的空间：
        #include <iostream>
        using namespace std;
        int main(){
            int a = 10;
            int * p = &a;
            cout << "sizeof(p)=" << sizeof(int *) << endl;
            cout << "sizeof(p)=" << sizeof(char *) << endl;
            cout << "sizeof(p)=" << sizeof(double *) << endl;
            cout << "sizeof(p)=" << sizeof(bool *) << endl;
            cout << "sizeof(p)=" << sizeof(long *) << endl;
            cout << "sizeof(p)=" << sizeof(string *) << endl;
            return 0;
        }
    9-4.指针的类型：
        1.空指针:
            .定义：指针变量指向内存中编号为0的空间
            .注意：空指针指向的内存是不可以访问的
            .例子：
            #include <iostream>
            using namespace std;
            int main(){
                int a = 10;
                int * p = NULL;//空指针用于给指针变量初始化
                *p = 100;//空指针不可访问，因为0-255的内村空间为系统空间，不能直接访问和修改
                cout << *p << endl;//
                return 0;
            }
        2.野指针：
            .定义：指针变量指向非法的内存空间
            .例子：
                int main(){
                    int * p = (int *)0x1100;
                    cout << *p << endl;
                    return 0;
                }
             //由于空指针和野指针不是我们申请的空间，所以不要访问，而且也不能访问
        3.const修饰指针
            .三种情况：
                1.const修饰指针---常量指针
                    常量指针的指向可以修改，但是指向的值不可以修改：
                    const int * p = &a;
                2.const修饰常量---指针常量
                    指针常量的指向不能改，但是值可以改
                    int * const p = &a; 
                3.const既修饰指针又修饰常量
                    const int * const p = &a;
                .总结：
                const int * p:常量指针，不能改值;int * const p:指针常量，不能改址

                4.例子：
                    #include <iostream>
                    using namespace std;
                    int main(){
                        int a = 10, b = 10;
                        /*常量指针*/
                        const int * p1 = &a;
                        int *p2 = &a;
                        cout << *p1 << endl;
                        *p1 = b;//常量指针的值不能修改
                        p1 = &b;
                        cout << *p1 << endl;
                        *p2 = b;//变量指针的值可以修改
                        cout << *p2 << endl;
                        /*指针常量*/
                        int * const p = &a;
                        *p = 20;//指针的值可以改变
                        p = &b;//指针的指向不能变化
                        /*const即修饰指针，又修饰常量*/
                        const int * const p = &a;
                        *p = 20;//错误，此时p的指向和值都不能改变
                        p = &b;//
                        return 0;
                        /*注意:看一个指针是否可变，就是要看const修饰谁，若是const int * p,那么值不能变
                        若是int * const p,那么指向就不能变化 */
                    }

        4.指针的算术运算：
            .我们喜欢在程序中用指针代替数组，因为变量针可以递增，但是数组不能递增,因为数组是一个常量指针
            .例子1：
            #include <iostream>
            using namespace std;
            const int MAX = 3;
            int main(){
                int var[MAX] = {1, 2, 3};
                int *ptr;
                ptr = var;
                for (int i = 0; i < MAX; i++)
                {
                    cout << "Address of var[" << i << "] = ";
                    cout << ptr << endl;
                    cout << "Value of var[" << i << "] = ";
                    cout << *ptr << endl;
                    ptr--;//移动到下一位置
                }
                return 0;
            }
            例子2.
                #include <iostream>
                using namespace std;
                const int MAX = 8;
                int main(){
                    int i, arr[MAX] = {0, 1, 2, 3, 4, 5, 6, 7};
                    int *prt;
                    prt = arr;//prt为arr的初始地址
                    for (i = 0; i < MAX; i++){
                        cout << "the address of arr[" << i << "] is " << prt << endl;
                        cout << "the value of arr[" << i << "] is " << *prt << endl;
                        prt++;
                    }   
                    return 0;
                }

            /*
            int height[10];//int型的数组
            cout << &height << endl;//&height相当于整个height数组取地址
            cout << &height[0] << endl;//&height[0]相当于对height[0]取地址
            height = &height[0]
            */
                .注意事项：
                short int height[10]; //int型的数组（short int 每个数据2字节）
            cout <<  "height       "<< height << endl 
                 <<  "height+1     "<< height + 1 << endl
                 <<  "&height[0]   " <<  &height[0] << endl
                 <<  "&height+1    "<< &height + 1<< endl
                 <<  "height+9     "<< height+9 << endl
                 << "height+10    " << height + 10 << endl

                height       0136F900
                height+1     0136F902
                &height[0]   0136F900
                &height+1    0136F914
                height+9     0136F912
                height+10    0136F914

                .结论:
                    1.height  = &height[0] = &height
                    2.height + 1 = height + 2 = height + 1个short int 元素
                    3.height + 9 = height[]的最后一个元素的地址，height + 10 = 该数组结束后的第一个地址
                    4.&height + 1 = height + 10
                    5.*height = height[0] = i //把i值复制给height中的第一个元素
                    6.*(height + 1)//取height内存后面第一个元素，若height中每个元素为4个字节，则height+1就指向&height[0]+4这个地址
        5.指针和数组：
            .一个指向数组开头的指针可以通过指针的算术运算或数组索引来访问数组
            .例1：
                #include <iostream>
                using namespace std;
                int main ()
                {
                   int arr[] = {1, 2, 3};
                   int * ptr = arr;//ptr = arr，可以理解为指针就是数组，所以arr[i]= ptr[i]
                   for (int i = 0; i < 3; i++){
                      cout << *ptr << endl;
                      cout << ptr[i] << endl;//*ptr = ptr[i]
                      cout << ptr << endl;
                      ptr++;      
                   }
                }
            .例2：
                #include <iostream>
                using namespace std;
                void bubbleSort(int * arr, int len)
                {
                    for (int i = 0; i < len -1; i++)
                    {
                        for (int j = 0; j < len -i -1; j++)
                        {
                            if (arr[j] > arr[j+1]){
                                int temp = arr[i];
                                arr[j] = arr[j+1];
                                arr[j+1] = temp;
                            }
                        }
                    }
                }
                void printArray(int * arr, int len){
                    for (int i = 0; i < len; i++){
                        cout << arr[i] << endl;
                    }
                }
                int main(){
                    int arr[6] = {1, 2, 3, 4, 5, 6};
                    bubbleSort(arr, 6);//arr为数组的首地址，len为数组的长度，将arr的首地址传入
                    printArray(arr, 6);
                    return 0;
                }
        6.指针数组：
            .申明：int *prt[MAX];把指针prt申明为一个数组,有MAX个整数指针构成，所以prt中的每个元素
            都是一个指向int值的指针,prt[MAX]就是一个有MAX元素的指针数组
            .例子：
                #include <iostream>
                using namespace std;
                const int MAX = 3;
                int main ()
                {
                   int  var[MAX] = {10, 100, 200};
                   int *ptr[MAX];
                   for (int i = 0; i < MAX; i++)
                   {
                      cout << "Value of var[" << i << "] = ";
                      ptr[i] = &var[i]; 
                      cout << *ptr[i] << endl;
                   }
                   return 0;
                }

    9-5.指向指针的指针：
        1.定义：指针的指针就是将指针的地址存放在另一个指针里面
        2.图像：
              ptr       ptr      variable
            address---->address--->value 
        3.申明：int **var;
        4.例子：
                #include <iostream>
                using namespace std;
                int main ()
                {
                    int  var;
                    int  *ptr;
                    int  **pptr;
                 
                    var = 3000;
                 
                    // 获取 var 的地址
                    ptr = &var;
                 
                    // 使用运算符 & 获取 ptr 的地址
                    pptr = &ptr;
                 
                    // 使用 pptr 获取值
                    cout << "var 值为 :" << var << endl;
                    cout << "*ptr 值为:" << *ptr << endl;
                    cout << "**pptr 值为:" << **pptr << endl;
                    cout << "var 地址为：" << &var endl;
                    cout << "ptr = &var 地址为：" << ptr endl;
                    cout << "ptr 地址为：" << &ptr endl;
                    cout << "pptr = ptr = &var 值为var的地址为：" << *pptr endl;
                    cout << "pptr 地址为：" << &pptr << endl;
                    return 0;
                }
                    var 值为 :3000
                    *ptr 值为:3000
                    **pptr 值为:3000
                    var 地址为 :0x7ffeec7a65e8
                    ptr=&var 值为var的地址:0x7ffeec7a65e8
                    ptr地址为:0x7ffeec7a65e0
                    *pptr=ptr=&var  值为var的地址:0x7ffeec7a65e8
                    pptr 地址为:0x7ffeec7a65d8
           ------------------------------------------------------
                #include <iostream>
                using namespace std;
                int main()
                {
                    int  var;
                    int* ptr;
                    int** pptr;
                    int*** ppptr;
                    var = 3000;
                    // 获取 var 的地址
                    ptr = &var;
                    // 使用运算符 & 获取 ptr 的地址
                    pptr = &ptr;

                    ppptr = &pptr;
                    // 使用 pptr 获取值
                    cout << "var 值为 :" << var << endl;
                    cout << "ptr 值为:" << ptr << endl;
                    cout << "pptr 值为:" << pptr << endl;
                    cout << "pptr 值为:" << ppptr << endl;

                    return 0;
                }
                    输出结果为：
                    var 值为 :3000
                    ptr 值为:0x7ffe5deb4e14
                    pptr 值为:0x7ffe5deb4e08
                    pptr 值为:0x7ffe5deb4e00
            .结论：
            1.若是pptr = &ptr ; ptr = &var---->var = *ptr(一级指针的值) = **pptr(二级指针的值)  
            2.p,*p,&p的关系：*是寻址符号，&是地址符号，p为变量值，所以*p为p值(地址)的解引用，&p为p的地址,p为值,
                有多少个*,就解引用多少次,解引用就是对地址进行寻址**
            3.int var, *ptr, **pptr(实际上定义的虽然是**pptr,但是指针变量是*ptr,同理可得ptr)--->  
            4.int **pptr------>*pptr为指针变量地址，**pptr为指针变量值
                 当满足&var = ptr, &ptr = pptr时候：
                    1.var = *ptr = **pptr(取值）,//重点****
                    2.&var = ptr = *pptr(取址)//把*prt想成对prt的值进行解析，即进行指向
                           示意图
                    var       ptr       pptr 
                d1 3000<---d2 d1 <---d3 d2
            5.分开来看:
            ptr = &var
            *ptr = *(&var) = var //ptr指针的值就是var的地址,*ptr是直接对var地址取值
            pptr = &pt r
            *pptr = *(&ptr) = ptr = &var
            **pptr = *(*pptr) = *(&var) = var    
            注意:每次在p前加入一个*,相当于对p进行  
            6.对于**pptr,当未定义的时候，只能取得,pptr,&pptr,不能取得,*pptr,**pptr
            若var = 30,*pptr = &var,(pptr = &var是错误的),此时*(*pptr) = *(&var) = 30
            所以对于**pptr，*pptr = &var,即是保证2次寻址，pptr = &var就是1次寻址了，因为此时
            *pptr = *(&var) = 30,**pptr就失去了意义    
            7.指针和数组：int arr[]= {.......},int * ptr = arr<------> ptr = arr <---> ptr[i] = arr[i]                                                                       一次取值,

    9-6.指针函数：
        1.指针函数：
            .int *func (int a ,int b)
                *的优先级低于(),所以func先与()相结合，所以func是一个函数，即int *(func) (int a, int b)
                这个函数的返回值的类型是int *:指向int类型的指针
            .int (*func) (int a, int b):
                (*func)表示func是一个指针，然后后面跟着的()说明这个指针指向一个函数，所以为函数指针



10.变量作用域
    10-1.定义:
        局部变量:在函数或一个代码块内部声明的变量，称为局部变量,
            局部变量只能被函数内部或代码块的语句所用,在函数内部,局部变量的值会覆盖全局变量的值
        形式参数:在函数参数的定义中声明的变量，称为形式参数。
        全局变量:在所有函数外部声明的变量，称为全局变量
            全局变量能在程序的所有位置使用
    10-2.例子
        #include <iostream>
        using namespace std;
        // 全局变量声明
        int g = 20;
         
        int main ()//int main()是主函数,
        {
          // 局部变量声明
          int g = 10;
         
          cout << g;
         
          return 0;
        }
        //输出的为10

10.结构体：
    10-1.结构体的概念：
        1.语法：
            struct type_name {
            member_type1 member_name1;
            member_type2 member_name2;
            member_type3 member_name3;
            .
            .
            } object_names;
        2.例如：
            struct Books
            {
               char  title[50];
               char  author[50];
               char  subject[100];
               int   book_id;
            } book;
        3.方式：
            struct 结构体名称 变量名
            struct 结构体名称 变量名 = {成员1值，成员2值}
            定义结构体时顺便创建变量
        4.例子：
            #include <iostream>
            using namespace std;
            #include <string>
            struct Student{//struct关键字在创建变量时候可以不写，但是在定义的时候要写
                string name;
                int age;
                int score;
            };s3
            int main(){
                //定义方式1
                struct Student s1;//此处的俄struct可以省略
                s1.name = "张三";
                s1.age = 19;
                s1.score = 100;
                cout << "姓名:" << s1.name << "年龄:" << s1.age << "分数:" << s1.score << endl;
                //定义方式2
                struct Student s2 = {"李四", 18, 90};
                cout << "姓名:" << s2.name << "年龄:" << s2.age << "分数:" << s2.score << endl;
                //定义方式3,此时不推荐使用
                s3.name = "张三";//上面已经写了就无需定义
                s3.age = 19;
                s3.score = 100;
            }   
    10-2.结构体数组：
        .语法：struct 结构体名 数组名[元素个数] = {{}, {},...}
        .例子：
            struct student{
                string name;
                int age;
                int score;
            }

            int main(){
                struct student arr[3]={
                    {"a", 18, 20},{"b", 18, 21}, {"c", 12, 32}}

                arr[0].name = "c";
                arr[0].age = 12;
                arr[0].score = 23;
            }
            //输出结构体：
            for (int i = 0; i < 3; i++){
                cout << "姓名:" << arr[i].name 
                     << "年龄:" << arr[i].age << "分数:" 
                    << arr[i].score << endl;
            }

    10-3.结构体指针：
        1.作用：利用->可以通过结构体指针来访问结构体属性
        2.例子：
            #include <iostream>
            using namespace std;
            #include <string>
            struct student{
                string name;
                int age;
                int score;
            };

            int main(){
                //1.创建结构体值：
                student s={
                    "a", 18, 20};
                //2.通过指针指向结构体变量
                student * p = &s;
                //3.通过指针访问结构体变量中的数据：
                cout << "姓名： " << p -> name 
                 << "年龄： " << p -> age
                  << "分数：" << p -> score << endl;

            }

    10-4.结构体嵌套：
            #include <iostream>
            using namespace std;
            #include <string>
            struct student{
                string name;
                int age;
                int score;
            };

            struct teacher{
                string name;
                int age;
                struct student stu;//辅导的学生,需要在上面提前定义
            };

            int main(){
                teacher t;
                t.name = "a";
                t.age = 18;
                t.stu.name = "b";
                t.stu.age = 12;
                t.stu.score = 12;
                cout << "老师姓名:" << t.name 
                    << "老师年龄:" << t.age 
                    << "学生姓名:" << t.stu.name 
                    << "学生年龄:" << t.stu.age 
                    << "学生分数:" << t.stu.score << endl;
            }

    10-5.结构体做函数参数：//结构体既可以作值传递，也可以地址传递，还可以作引用传递
        #include <iostream>
        using namespace std;
        #include <string>
        struct student{
            string name;
            int age;
            int score;
        };
        //值传递
        void printStudent1(struct student s){
            cout << "姓名：" << s.name << "年龄" << s.age << endl;
        }
        //地址传递
        void printStudent2(struct student * p){//p = &s
            cout << "姓名：" << p -> name << "年龄" << p -> age
            << "分数" << p -> score << endl;//p->name:直接指向name地址的值
        }
        //引用传递
        void printStudent3(struct student & s){
            cout << "姓名：" << s.name << "年龄" << s.age << endl;
        }
        int main(){
            student s;
            s.name = "a";
            s.age = 20;
            s.score = 23;
            printStudent1(s);
            printStudent2(&s);
            printStudent3(s);
        }

    10-6.const使用场景：
        #include <iostream>
        using namespace std;
        #include <string>
        struct student{
            string name;
            int age;
            int score;
        };
        //将函数的形参改成指针，可以减少内存空间，而且不会复制一个新的副本出来
        void printStudent1(const student *s){//加入const后，一旦修改就会报错，可以防止失误操作
            s->age = 150; //此操作会将原来的age修改为150
            cout << "姓名：" << s->name << "年龄：" << s->age << "分数："
            << s->score << endl;
        }
        int main(){
            student s = {"张三", 12, 53};
            printStudent1(&s); 
            cout << "main中张三年龄为:" << s.age << endl;
        }

    10-7.指针函数和函数指针：
        1.指针函数:
            .定义：指针函数的本质是一个函数，但是它的返回值是一个指针，即是一个地址
            .形式：int *p(int , int);//先()后*为函数指针
            .例子：
            #include <iostream>
            using namespace std;
            int * Pf(int n){//Pf代表指针函数
                int sum = 0;
                for (int i = 0; i < n; i++){
                    sum+=i;
                }
                int *p = &sum;
                return p;
            }

            int main(){
                cout << "请输入一个数:" << endl;
                int n;
                cin >> n;
                int * c = Pf(n);
                cout << "sum = " << *c << endl;
                
            }

        2.函数指针：
            .定义：返回指针的函数，它是一个指针，该指针的地址指向了一个函数，所以它是指向函数的指针；
            .作用：用作调用函数和作函数的参数
            .例子
                例1.//用作调用函数
                int (*p) (int a, int b);//函数指针指能申明，不能定义
                //typedef int(*PF)(int ,int);
                int max(int a, int b){
                    return a > b ? a : b;
                }
                int min(int a, int b) {  
                    return a < b ? a : b;  
                }
                int main(){
                    f = max;
                    f(1, 2);//(*f)(1, 2)和f(1, 2)等效
                    int c = (*f)(1, 2);
                    f = min;
                    c = (*f)(1, 2);
                }

                例2：//用作函数的参数
                #include <iostream>
                using namespace std;
                typedef int(*PF)(int, int);
                //int(*func)(int a, int b);
                int bar(int a, int b)
                {
                    return a + b;
                }
                 
                int foo(int a, int b)
                {
                    return a;
                }
                void func(int a, int b, PF ptr)
                {
                    cout << ptr(a, b) << endl;
                    return;
                }
                int main()
                {
                    PF ptr;
                    ptr = bar;
                    func(12, 34, ptr);
                    system("pause");
                    ptr = foo;
                    func(12, 34, ptr);
                    system("pause");
                    return 0;
                }



11.类
    11-1.类的定义：
        1.语法：
        class classname{
            Access specifiers://访问修饰符：private/public/protected
                Date members/variables;//变量，类里面即可以定义变量，也可以定义方法，还可以声明方法
                Member functions(){}//方法
        };//以分号结束一个类
        2.例子
        class Box{
            public:
                double length; 
                double breadth; 
                double height; 
        };
        3.申明类：Box Box1;   Box Box2;//分别申明Box1和Box2，类型为Box
        4.访问数据成员：利用.来访问公共数据成员
        5.例：
        #include <iostream>
        using namespace std;
        //定义一个类
        class Box
        {
           public:
              double length;   // 长度
              double breadth;  // 宽度
              double height;   // 高度
              // 成员函数声明
              double get(void);
              void set( double len, double bre, double hei );
        };
        // 成员函数定义
        double Box::get(void)//::用来指代是在Box类中的函数get(void)
        {
            return length * breadth * height;//类中定义的变量就无需定义
        }
         
        void Box::set( double len, double bre, double hei)
        {
            length = len;
            breadth = bre;
            height = hei;//void无return 
        }
        int main( )
        {
           Box Box1;        // 声明 Box1，类型为 Box
           Box Box2;        // 声明 Box2，类型为 Box
           Box Box3;        // 声明 Box3，类型为 Box
           double volume = 0.0;     // 用于存储体积
         
           // box 1 详述
           Box1.height = 5.0; 
           Box1.length = 6.0; 
           Box1.breadth = 7.0;
         
           // box 2 详述
           Box2.height = 10.0;
           Box2.length = 12.0;
           Box2.breadth = 13.0;
         
           // box 1 的体积
           volume = Box1.height * Box1.length * Box1.breadth;
           cout << "Box1 的体积：" << volume <<endl;
         
           // box 2 的体积
           volume = Box2.height * Box2.length * Box2.breadth;
           cout << "Box2 的体积：" << volume <<endl;
         
         
           // box 3 详述
           Box3.set(16.0, 8.0, 12.0); 
           volume = Box3.get(); 
           cout << "Box3 的体积：" << volume <<endl;
           return 0;
        }
    10-2.类的成员函数:
      
        定义方法:
        方法1://在类内部定义
            class Box
            {
               public:
                  double length;      // 长度
                  double breadth;     // 宽度
                  double height;      // 高度
               
                  double getVolume(void)/getVolume(void)=getVolume()
                  {
                     return length * breadth * height;
                  }
            };
        方法2://在类外部定义
            double Box::getVolume(void)
            {
                return length * breadth * height;
            }
        注意:
            Box myBox;          // 创建一个类对象
            myBox.getVolume();  // 调用该对象的成员函数
    10-3.类的访问修饰符
        public、private、protected 称为访问修饰符,成员和类的默认修饰符是private
        1.public(共有成员):公有成员是外部可以访问的,我们可以不使用任何成员函数来设置和获取公有变量的值:
            #include <iostream>
            using namespace std;
            class Line
            {
               public:
                  double length;
                  void setLength( double len );
                  double getLength( void );
            };
            // 成员函数定义
            double Line::getLength(void)
            {
                return length ;
            }
             
            void Line::setLength( double len )
            {
                length = len;
            }
            // 程序的主函数
            int main( )
            {
               Line line;
               // 设置长度
               line.setLength(6.0); 
               cout << "Length of line : " << line.getLength() <<endl;
             
               // 不使用成员函数设置长度
               line.length = 10.0; // OK: 因为 length 是公有的
               cout << "Length of line : " << line.length <<endl;
               return 0;
            }
        2.private(私有成员)
        私有成员变量在函数或在类的外部是不可访问的,甚至是不可查看的,只有类和友元函数可以访问私有成员
        如果您没有使用任何访问修饰符，类的成员将被假定为私有成员：
            #include <iostream>
            using namespace std;
            class Box
            {
               double width;//此时width默认为私有成员
               public:
                  double length;
                  void setWidth( double wid );
                  double getWidth( void );
             
               private:
                  double width;
            };
            // 成员函数定义
            double Box::getWidth(void)
            {
                return width ;
            }
             
            void Box::setWidth( double wid )
            {
                width = wid;
            }
            // 程序的主函数
            int main( )
            {
               Box box;
               // 不使用成员函数设置长度
               box.length = 10.0; // OK: 因为 length 是公有的
               cout << "Length of box : " << box.length <<endl;
               // 不使用成员函数设置宽度
               // box.width = 10.0; // Error: 因为 width 是私有的
               box.setWidth(10.0);  // 使用成员函数设置宽度
               cout << "Width of box : " << box.getWidth() <<endl;
               return 0;
            }

        3.protected(受保护对象)
            .受保护成员变量与私有成员十分相似,但是protected成员在派生类中是可以访问的
            下面的例子中,我们从父类Box中派生了一个子类smallBox,这里的width成员可被派生类smallBox
            的任何成员函数访问
            例子:
            #include <iostream>
            using namespace std;
            class Box
            {
               protected:
                  double width;
            };
             
            class SmallBox:Box // SmallBox 是派生类,是Box的派生
            {
               public:
                  void setSmallWidth( double wid );
                  double getSmallWidth( void );
            };
            // 子类的成员函数
            double SmallBox::getSmallWidth(void)
            {
                return width ;
            }
             
            void SmallBox::setSmallWidth( double wid )
            {
                width = wid;
            }
            // 程序的主函数
            int main( )
            {
               SmallBox box;//叫做box的SmallBox类
             
               // 使用成员函数设置宽度
               box.setSmallWidth(5.0);
               cout << "Width of box : "<< box.getSmallWidth() << endl;
             
               return 0;
            }

    10-4.继承中的特点:
        1.public 继承：基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：public, protected, private
        2.protected 继承：基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：protected, protected, private
        3.private 继承：基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：private, private, private
            但无论哪种继承方式，上面两点都没有改变：
        1.private 成员只能被本类成员（类内）和友元访问，不能被派生类访问；
        2.protected 成员可以被派生类访问。
        -------------------------
        1.public继承:
            #include<iostream>
            #include<assert.h>
            using namespace std;
            class A{
                public:
                  int a;
                  A(){
                    a1 = 1;
                    a2 = 2;
                    a3 = 3;
                    a = 4;
                  }
                  void fun(){
                    cout << a << endl;    //正确
                    cout << a1 << endl;   //正确
                    cout << a2 << endl;   //正确
                    cout << a3 << endl;   //正确
              }
                public:
                  int a1;
                protected:
                  int a2;
                private:
                  int a3;
            };
            class B : public A{
                public:
                    int a;
                    B(int i){
                        A();
                        a = i;
                  }
                    void fun(){
                        cout << a << endl;       //正确，public成员
                        cout << a1 << endl;       //正确，基类的public成员，在派生类中仍是public成员。
                        cout << a2 << endl;       //正确，基类的protected成员，在派生类中仍是protected可以被派生类访问。
                        cout << a3 << endl;       //错误，基类的private成员不能被派生类访问。
                    }
            };
            int main(){
                B b(10);
                cout << b.a << endl;
                cout << b.a1 << endl;   //正确
                cout << b.a2 << endl;   //错误，类外不能访问protected成员
                cout << b.a3 << endl;   //错误，类外不能访问private成员
                system("pause");
                return 0;
            }
        2.protected继承:
            #include<iostream>
            #include<assert.h>
            using namespace std;
            class A{
                public:
                  int a;
                  A(){
                    a1 = 1;
                    a2 = 2;
                    a3 = 3;
                    a = 4;
                  }
                  void fun(){

                    cout << a << endl;    //正确
                    cout << a1 << endl;   //正确
                    cout << a2 << endl;   //正确
                    cout << a3 << endl;   //正确
                  }
                public:
                  int a1;
                protected:
                  int a2;
                private:
                  int a3;
            };
            class B : protected A{
                public:
                  int a;
                  B(int i){
                    A();
                    a = i;
                  }
                  void fun(){
                    cout << a << endl;       //正确，public成员。
                    cout << a1 << endl;       //正确，基类的public成员，在派生类中变成了protected，可以被派生类访问。
                    cout << a2 << endl;       //正确，基类的protected成员，在派生类中还是protected，可以被派生类访问。
                    cout << a3 << endl;       //错误，基类的private成员不能被派生类访问。
                  }
            };
            int main(){
              B b(10);
              cout << b.a << endl;       //正确。public成员
              cout << b.a1 << endl;      //错误，protected成员不能在类外访问。
              cout << b.a2 << endl;      //错误，protected成员不能在类外访问。
              cout << b.a3 << endl;      //错误，private成员不能在类外访问。
              system("pause");
              return 0;
            }
        3.private继承:
            #include<iostream>
            #include<assert.h>
            using namespace std;
            class A{
                public:
                  int a;
                  A(){
                    a1 = 1;
                    a2 = 2;
                    a3 = 3;
                    a = 4;
                  }
                  void fun(){
                    cout << a << endl;    //正确
                    cout << a1 << endl;   //正确
                    cout << a2 << endl;   //正确
                    cout << a3 << endl;   //正确
                  }
                public:
                  int a1;
                protected:
                  int a2;
                private:
                  int a3;
            };
            class B : private A{
                public:
                  int a;
                  B(int i){
                    A();
                    a = i;
                  }
                  void fun(){
                    cout << a << endl;       //正确，public成员。
                    cout << a1 << endl;       //正确，基类public成员,在派生类中变成了private,可以被派生类访问。
                    cout << a2 << endl;       //正确，基类的protected成员，在派生类中变成了private,可以被派生类访问。
                    cout << a3 << endl;       //错误，基类的private成员不能被派生类访问。
                  }
            };
            int main(){
              B b(10);
              cout << b.a << endl;       //正确。public成员
              cout << b.a1 << endl;      //错误，private成员不能在类外访问。
              cout << b.a2 << endl;      //错误, private成员不能在类外访问。
              cout << b.a3 << endl;      //错误，private成员不能在类外访问。
              system("pause");
              return 0;
            }

11.模板
    11-1.定义：
        template <typename type> ret-type func-name(parameter list)
        {
           // 函数的主体
        }
    11-2.分类：
        1.函数模板：
            .作用：建立一个通用函数，其函数的返回值类型和形参类型可以不具体指定，用一个虚拟的类型来代表
            .语法：template<typename T>//T为通用的数据类型，可以用class来代替，通常为大写字母
                  函数申明或者定义
                解释：template:申明创建模板；typename:表示其后面的符号是一种数据类型，可以用class代替
            .方法：1.显示指定类型 2.自动类型推导
            .例子：
            #include <iostream>
            using namespace std;
            //函数模板：
            template<typename T>//申明一个模板，T是一个通用类型

            void mySwap(T &a, T &b){//T可以是int, char,..类型
                T temp = a;
                a = b;
                b = temp;
            }


            void test01(){
                int a = 10;
                int b = 20;
                // swapInt(a, b);
                //方法1：自动类型推导入
                mySwap(a, b);
                //方法2显示指定类型：
                mySwap<int>(a, b);//告诉T = int
                cout << "a = " << a << endl;
                cout << "b = " << b << endl;

            }
            .注意事项：
                1.自动类型推导，必须推导出一致的数据类型T，才可以使用
                2.模板必须要确定出T的类型，才可以使用(调用函数时必须要指定类型)
                3.模板申明必须要须跟在函数的前面
                4.例子:
                #include <iostream>
                using namespace std;
                //函数模板：
                template<typename T>//申明一个模板，T是一个通用类型，写函数模板用typename,写类模板用class
                void mySwap(T &a, T &b){//T可以是int, char,..类型
                    T temp = a;
                    a = b;
                    b = temp;
                }

                void test01(){
                    int a = 10;
                    int b = 20;
                    char c = 'c';
                    //1.错误,a和c的数据类型不一样，否则模板使用会失效
                    mySwap(a, c);//
                    mySwap<int>(a, b);
                    mySwap(a, b);//此处因为已经给出了a,b 的类型了，所以无须再加<int>
                    cout << "a = " << a << endl;
                    cout << "b = " << b << endl;

                }
                //2.函数模板必须要指定T的数据类型才可以使用模板
                template<class T>
                void func(){
                    cout << "func调用"<< endl;
                }
                void test02(){
                    func<int>();//此处要是不指定int类型的话，编译器会无法时识别
                    // func();为错误的，因为没有指定模板类型
                }
                int main(){
                    test02();
                }
            .实例：
            #include <iostream>
            using namespace std;
            //交换模板
            template<class T>
            void mySwap(T &a, T &b){
                T temp = a;
                a = b;
                b = temp;
            }
            //排序模板
            template<class T>//模板申明必须要须跟在函数的前面
            void mySort(T arr[], int len){
                for (int i = 0; i < len; i++){
                    int max = i;
                    for (int j = i + 1; j < len; j++){
                        if (arr[max] < arr[j]){
                            max = j;//更新最大值下标
                        }
                    }
                if (max != i){
                    mySwap(arr[max], arr[i]);
                    //
                }
                }
            }
            //打印模板
            template<class T>
            void printArray(T arr[], int len){
                for (int i = 0; i < len; i++){
                    cout << arr[i] << "  ";
                }
                cout << endl;
            }

            void test01(){
                char charArr[] = "asdfsf";
                int num = sizeof(charArr)/sizeof(char);
                mySort(charArr,num);
                printArray(charArr, num);
            }

            void test02(){
                int intArr[] = {1, 2, 3, 4};
                int num = sizeof(intArr)/sizeof(int);
                mySort(intArr,num);
                printArray(intArr, num);
            }

            int main(){
                test01();
                test02();
            }

        2.类模板：
        #include <iostream>
        using namespace std;
        template <typename T>//T为通用的数据类型，可以用class来代替，通常为大写字母
        class Op{
        public:
            T peocess(T v)
            {
                return v * v;
            }
        };
        int main()
        {
            Op<int> opInt;
            Op<double> opDouble;
            cout << "5 * 5 = " << opInt.peocess(5) <<endl;
            cout << "0.5 * 0.5 = " << opDouble.peocess(0.5) <<endl;
        }

    3.inline函数的用法：
        3-1.原因：为了解决一些频繁调用的小函数消耗大量的堆栈空间的问题，所以引入inline修饰符号，表示内联函数
            栈空间是指放置程序的局部数据的内存空间
        3-2.例子：
            #include <stdio.h>
            inline const char *num_check(int v){
                return (v % 2 > 0) ? "奇数" : "偶数";
            }
            int main(void){
                int i;
                for (i = 0; i < 100; i++){
                    printf("%02d %s\n",i, num_check(i));
                    return 0;
                }
            }

                    










