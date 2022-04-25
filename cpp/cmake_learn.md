# 1.杂项
步骤
1.mkdir hello---->
2.touch main.cpp
    #include<stdio.h>
    int main(void)
    {
        printf("Hello,World\n");
        return 0;
    }
3. CMakeLists.txt

#cmake最低版本需求，不加入此行会受到警告信息
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(HELLO) #项目名称
#把当前目录(.)下所有源代码文件和头文件加入变量SRC_LIST
AUX_SOURCE_DIRECTORY(. SRC_LIST)
#生成应用程序 hello
ADD_EXECUTABLE(hello ${SRC_LIST})//该应用程序是hello目录下的hello.cpp文件

4.编译项目：
    1.在hello下创建build，现在整体项目的结构为
    hello/
    |– CMakeLists.txt
    |– build /
    |– main.c
    2.cd hello/build/
    3.cmake ..
    4.make
    5. ./hello
    注意.若是在main.c中需要用其他include<xxxx>,那么要将xxx添加到cmakelist中：
    include_directories( "/usr/include/eigen3" )
    ----------
    CMakeLists的文件为：
    
    #cmake最低版本需求，不加入此行会受到警告信息
    CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
    PROJECT(SLAM) #项目名称
    #把当前目录(.)下所有源代码文件和头文件加入变量SRC_LIST
    AUX_SOURCE_DIRECTORY(. SRC_LIST)
    #生成应用程序 hello
    ADD_EXECUTABLE(ch1_Eigen ${SRC_LIST})
    include_directories( "/usr/include/eigen3" )

    6. g++运行c++脚本的方法

# 2.基本性质和参数

## 1. 基本语法格式：
1. 指令(参数1 参数2)

   1. 参数使用括弧括起
   2. 参数之间使用空格或分号分开
   3. 指令是大小写无关的
   4.例如：add_executable(hello main.cpp hello.cpp)
     ADD_EXECUTABLE(hello main.cpp hello.cpp)
   5. 变量是大小写相关的，使用${}方式取值。但在if语句中是直接使用变量名，set(HELLO hello.cpp)，设置一个变量HELLO，值是hello.cpp，add_executable(hello main.cpp ${HELLO})

## 2.重要指令&常用变量

### 1. 重要指令
1. cmake_minimum_required：指定CMake的最小版本要求
   1. 语法：cmake_minimum_required(VERSION 版本号 [FATAL_ERROR])，// CMake最小版本要求为2.8.3

   2. cmake_minimum_required(VERSION 2.8.3)
3. project：定义工程名称，并可指定工程支持的语言
   1. 语法：project(工程名称 [CXX] [C] [java])
   2. 指定工程名为HELLOWORLD,project(HELLOWORLD)

4. set：显式的定义变量
   1. 语法：set(变量名 [变量值] [CACHE TYPE DOCSTRING [FORCE]])
   2. 定义SRC变量，其值为main.cpp hello.cpp
set(SRC hello.cpp hello.cpp)

4. include_directories：向工程添加多个特定的头文件搜索路径，相当于指定g++编译器的-I参数
   1. 语法：include_directories([AFTER|BEFORE][SYSTEM] dir1 dir2 ...)
   2. 将/usr/include/myincludefolder 和 ./include 添加到头文件搜索路径
   3. include_directories(/usr/include/myincludefolder ./include)

5. link_directories：向工程添加多个特定的库文件搜索路径，相当于指定g++编译器的-L参数
   1. 语法：link_directories(dir1 dir2 ...)
   2. 将/usr/lib/mylibfolder 和 ./lib 添加到库文件搜索路径：link_directories(/usr/lib/mylibfolder ./lib)

6. add_library：生成库文件
   1. 语法：add_library(库名 [SHARED|STATIC|MODULE] [EXCLUDE_FROM_ALL] source1 source2 .. sourceN)
   2. 通过变量 SRC 生成 libhello.so 共享库：SHARED代表动态库，STATIC代表静态库,add_library(hello SHARED ${SRC})

7. add_compile_options：添加编译参数
   1. 语法：add_compile_options(编译参数) 
   2. 添加编译参数 -wall -std=c++11
add_compile_options(-wall -std=c++11 -o2)

8. add_executable：生成可执行文件
   1. 语法：add_executable(exe文件名 source1 source2 .. sourceN)
   2. 编译main.cpp生成可执行文件main:add_executable(main main.cpp)

9. target_link_libraries：为target添加需要链接的共享库，相当于指定g++编译器-l参数
   1.  语法：target_link_libraries(target library1<debug|optimized> library2...)
   2.  将hello动态库文件链接到可执行文件main:target_link_libraries(main hello)

10. add_subdirectory：向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置
    1. 语法：add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
    2. 添加src子目录，src中需要有一个CMakeLists.txt
add_subdirectory(src)

11. aux_source_directory：发现一个目录下所有的源代码文件并将列表存储在一个变量中，这个指令临时被用来自动构建源文件列表
    1.  语法：aux_source_directory(文件夹路径 变量名)
    2.  定义SRC变量，其值为当前目录下所有的源代码文件
**aux_source_directory(. SRC)**,编译SRC变量所代表的源代码文件，生成main可执行文件,**add_executable(main ${SRC})**

### 2.常用变量
1. PROJECT_SOURCE_DIR 工程的根目录
2. 
3. PROJECT_BINARY_DIR 运行cmake命令的目录,通常是${PROJECT_SOURCE_DIR}/build
4. 
5. CMAKE_INCLUDE_PATH 环境变量,非cmake变量
6. 
7. CMAKE_LIBRARY_PATH 环境变量
8. 
9. CMAKE_CURRENT_SOURCE_DIR 当前处理的CMakeLists.txt所在的路径
10. 
11. CMAKE_CURRENT_BINARY_DIR target编译目录,使用ADD_SURDIRECTORY(src bin)可以更改此变量的值
12. 
13. SET(EXECUTABLE_OUTPUT_PATH <新路径>)并不会对此变量有影响,只是改变了最终目标文件的存储路径
14. 
15. CMAKE_CURRENT_LIST_FILE 输出调用这个变量的CMakeLists.txt的完整路径
16. 
17. CMAKE_CURRENT_LIST_LINE 输出这个变量所在的行
18. 
19. CMAKE_MODULE_PATH 定义自己的cmake模块所在的路径
20. 
21. SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake),然后可以用INCLUDE命令来调用自己的模块
22. 
23. EXECUTABLE_OUTPUT_PATH 重新定义目标二进制可执行文件的存放位置
24. 
25. LIBRARY_OUTPUT_PATH 重新定义目标链接库文件的存放位置
26. 
27. PROJECT_NAME 返回通过PROJECT指令定义的项目名称
28. 
29. CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS 用来控制IF ELSE语句的书写方式

### 3.有关源文件和头文件的问题

1. 头文件.h：
    写类的声明（包括类里面的成员和方法的声明）、函数原型、#define常数等，但一般来说不写出具体的实现。
    在写头文件时需要注意，在开头和结尾处必须按照如下样式加上预编译语句（如下）：
   #ifndef CIRCLE_H)
   #define CIRCLE_H
   //你的代码写在这里
   #endif
    
   1. 目的：这样做是为了防止重复编译，不这样做就有可能出错。至于CIRCLE_H这个名字实际上是无所谓的，你叫什么都行，只要符合规范都行。原则上来说，非常建议把它写成这种形式，因为比较容易和头文件的名字对应。
2. 例子
   1. 第一步
```cpp
#ifndef CIRCLE_H//名称是：NAME_H
#define CIRCLE_H

class Circle
{
private:
    double r;//半径
public:
    Circle();//构造函数,有有参就必须自己构造无参
    Circle(double R);//构造函数
    double Area();//求面积函数
};

#endif
```
在头文件里，并不写出函数的具体实现。

   2. 第2步，要给出Circle类的具体实现，因此，在源文件夹里新建一个Circle.cpp的文件，它的内容如下：
```cpp
#include "Circle.h"//#include <xxx> and "xxx"分别是系统的头文件和自定义的头文件，此cpp中，只给实现，不给具体main函数的输出

Circle::Circle()
{
    this->r=5.0;
}

Circle::Circle(double R)
{
    this->r=R;
}

double Circle:: Area()
{
    return 3.14*r*r;
}
```
    需要注意的是：开头处包含了Circle.h，事实上，只要此cpp文件用到的文件，都要包含进来！这个文件的名字其实不一定要叫Circle.cpp，但非常建议cpp文件与头文件相对应。

   3.第三步，我们建一个main.cpp来测试我们写的Circle类，它的内容如下：
```cpp
#include <iostream>
#include "Circle.h"
using namespace std;

int main()
{
    Circle c(3);
    cout<<"Area="<<c.Area()<<endl;
    return 1;
}
```
    注意到开头时有#include "Circle.h"的声明，证明我们使用到了我们刚才写的Circle类。
   说明我们写的Circle类确实可以用了。

3. ***注意事项***：
   1. .h中只写定义，#ifndef.....#endif,其余头文件。已经包含在.h中的头文件在其他文件中就不需要include
   2. .cpp和main.cpp中联系是：2个都要include头文件；区别是.cpp中无main函数，main.cpp中有main函数

4. 源文件和头文件要如何放置：
   1. 头文件(.h)：
      1. 非模板类型
         1. 全局变量声明
         2. 全局函数声明
         3. inline的全局函数的定义
         4. 类的定义
         5. 类的成员函数声明
      2. 模板类型：
         1. 模板类的定义
         2. 模板类成员的定义
         3. 带inline的全局模板函数的声明
   2. 源文件(.cpp)
      1. 全局变量的定义(及初始化)
      2. 全局函数的定义
      3. 类函数成员的定义
      4. 类带static限定符的数据成员的初始化

头文件
头文件的所有内容，都必须包含在

#ifndef {Filename} 
#define {Filename} 

//{Content of head file} 

#endif
这样才能保证头文件被多个其他文件引用(include)时，内部的数据不会被多次定义而造成错误

inline限定符
在头文件中，可以对函数用inline限定符来告知编译器，这段函数非常的简单，可以直接嵌入到调用定义之处。

当然inline的函数并不一定会被编译器作为inline来实现，如果函数过于复杂，编译器也会拒绝inline。

因此简单说来，代码最好短到只有3-5行的才作为inline。有循环，分支，递归的函数都不要用做inline。

对于在类定义内定义实现的函数，编译器自动当做有inline请求（也是不一定inline的）。因此在下边，我把带有inline限定符的函数成员和写在类定义体内的函数成员统称为“要inline的函数成员”

非模板类型
全局类型
就像前面笼统的话讲的：申明写在.h文件。

对于函数来讲，没有实现体的函数，就相当于是申明；而对于数据类型（包括基本类型和自定义类型）来说，其申明就需要用extern来修饰。

然后在.cpp文件里定义、实现或初始化这些全局函数和全局变量。

不过导师一直反复强调：不许使用全局函数和全局变量。用了之后造成的后果，目前就是交上去的作业项目会扣分。当然不能用自有不能用的理由以及解决方案，不过不在目前的讨论范围内。



自定义类型
对于自定义类型，包括类（class）和结构体（struct），它们的定义都是放在.h文件中。其成员的申明和定义就比较复杂了，不过看上边的表格，还是比较清晰的。

函数成员
函数成员无论是否带有static限定符，其申明都放在.h文件的类定义内部。

对于要inline的函数成员其定义放在.h文件；其他函数的实现都放在.cpp文件中。

数据成员
数据成员的申明与定义都是放在.h文件的类定义内部。对于数据类型，关键问题是其初始化要放在什么地方进行。

对于只含有static限定符的数据成员，它的初始化要放在.cpp文件中。因为它是所有类对象共有的，因此必须对它做合适的初始化。

对于只含有const限定符的数据成员，它的初始化只能在构造函数的初始化列表中完成。因为它是一经初始化就不能重新赋值，因此它也必须进行合适的初始化。

对于既含有static限定符，又含有const限定符的数据成员，它的初始化和定义同时进行。它也是必须进行合适的初始化

对于既没有static限定符，又没有const限定符的数据成员，它的值只针对本对象可以随意修改，因此我们并不在意它的初始化什么时候进行。
### 4.用法总结：
#### 1. 单个源文件
   1. ./test
      1. main.cpp
      2. CMakeLists.txt:
```cmake
cmake_minimum_required(VERSION 3.10)
project(test)
add_executable_directory(demo main.cpp)
```
   2. 执行顺序：在当前目录下cmake .----->make

#### 2. 多个源文件
   1. 多个文件，一个目录：
   2. ./test
      1. CMakeList.txt
      2. main.cpp
      3. functions.cpp
      4. functions.h
**functions.h**
```cpp
#ifndef FUNCTIONS_H
#define  FUNCTIONS_H
#include <iostream>
using namespace std;

class Circle{
    private:
        double  r;
    public:
        Circle(double r);
        void showArea();
};

#endif
```
**fuctions.cpp**
```cpp
#include "functions.h"
Circle::Circle(double r){
    this->r  = r;
}

void Circle::showArea(){
    int area = 3.14*r*r;
    cout << "the area is " << area << endl; 
}
```
**main.cpp**
```cpp
#include "math/functions.h"
int main(){
    Circle c(100);
    c.showArea();
}
```
   3. 执行顺序：cmake .------>make 
#### 3.多个文件，多个目录(多个cmake文件)
1. ./test
   1. build
   2. src
      1. main.cpp
      2. CMakeList.txt
   3. include 
      1. mymath.h
      2. mymath.cpp
      3. CMakeLists.txt
   4. CMakeLists.txt
 

#### 4.多目录多文件标准工程
1. 目录树
   1. build
   2. 
