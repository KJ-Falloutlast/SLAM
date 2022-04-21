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

# 1.基本语法特性

1. 基本语法格式：指令(参数1 参数2)
参数使用括弧括起
参数之间使用空格或分号分开
指令是大小写无关的
add_executable(hello main.cpp hello.cpp)
ADD_EXECUTABLE(hello main.cpp hello.cpp)
变量是大小写相关的，使用${}方式取值。但在if语句中是直接使用变量名
set(HELLO hello.cpp)  # 设置一个变量HELLO，值是hello.cpp
add_executable(hello main.cpp ${HELLO})
重要指令&常用变量

1. 重要指令
cmake_minimum_required：指定CMake的最小版本要求
语法：cmake_minimum_required(VERSION 版本号 [FATAL_ERROR])
// CMake最小版本要求为2.8.3
cmake_minimum_required(VERSION 2.8.3)
project：定义工程名称，并可指定工程支持的语言
语法：project(工程名称 [CXX] [C] [java])
// 指定工程名为HELLOWORLD
project(HELLOWORLD)
set：显式的定义变量
语法：set(变量名 [变量值] [CACHE TYPE DOCSTRING [FORCE]])
// 定义SRC变量，其值为main.cpp hello.cpp
set(SRC sayhello.cpp hello.cpp)
include_directories：向工程添加多个特定的头文件搜索路径，相当于指定g++编译器的-I参数
语法：include_directories([AFTER|BEFORE][SYSTEM] dir1 dir2 ...)
// 将/usr/include/myincludefolder 和 ./include 添加到头文件搜索路径
include_directories(/usr/include/myincludefolder ./include)
link_directories：向工程添加多个特定的库文件搜索路径，相当于指定g++编译器的-L参数
语法：link_directories(dir1 dir2 ...)
// 将/usr/lib/mylibfolder 和 ./lib 添加到库文件搜索路径
link_directories(/usr/lib/mylibfolder ./lib)
add_library：生成库文件
语法：add_library(库名 [SHARED|STATIC|MODULE] [EXCLUDE_FROM_ALL] source1 source2 .. sourceN)
// 通过变量 SRC 生成 libhello.so 共享库
// SHARED代表动态库，STATIC代表静态库
add_library(hello SHARED ${SRC})
add_compile_options：添加编译参数
语法：add_compile_options(编译参数)
// 添加编译参数 -wall -std=c++11
add_compile_options(-wall -std=c++11 -o2)
add_executable：生成可执行文件
语法：add_executable(exe文件名 source1 source2 .. sourceN)
// 编译main.cpp生成可执行文件main
add_executable(main main.cpp)
target_link_libraries：为target添加需要链接的共享库，相当于指定g++编译器-l参数
语法：target_link_libraries(target library1<debug|optimized> library2...)
// 将hello动态库文件链接到可执行文件main
target_link_libraries(main hello)
add_subdirectory：向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置
语法：add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
// 添加src子目录，src中需要有一个CMakeLists.txt
add_subdirectory(src)
aux_source_directory：发现一个目录下所有的源代码文件并将列表存储在一个变量中，这个指令临时被用来自动构建源文件列表
语法：aux_source_directory(文件夹路径 变量名)
// 定义SRC变量，其值为当前目录下所有的源代码文件
aux_source_directory(. SRC)
// 编译SRC变量所代表的源代码文件，生成main可执行文件
add_executable(main ${SRC})
2. 常用变量
CMAKE_C_FLAGS：gcc编译选项
CMAKE_CXX_FLAGS：g++编译选项
// 在CMAKE_CXX_FLAGS编译选项后追加-std=c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
CMAKE_BUILD_TYPE：编译类型(Debug, Release)

// 设定编译类型为debug，因为在调试时需要选择debug
set(CMAKE_BUILD_TYPE Debug)
// 设定编译类型为release，因为在发布时需要选择release
set(CMAKE_BUILD_TYPE release)
EXECUTABLE_OUTPUT_PATH：可执行文件输出的存放路径

LIBRARY_OUTPUT_PATH：库文件输出的存放路径

CMake编译工程

CMake目录结构：项目主目录存在一个CMakeLists.txt文件

两种方式设置编译规则：
包含源文件的子文件夹包含CMakeLists.txt文件，主目录的CMakeLists.txt通过add_subdirectory添加子目录即可
包含源文件的子文件夹未包含CMakeLists.txt文件，子目录编译规则体现在主目录的CMakeLists.txt中
1. 编译流程
在linux平台下使用CMake构建C/C++工程的流程如下：
手动编写CMakeLists.txt
执行命令cmake PATH生成Makefile(PATH是顶层CMakeLists.txt所在目录)
执行命令make进行编译
2. 两种构建方式
内部构建(in-source build)：不推荐使用
内部构建会在同级目录下产生一大堆中间文件，这些中间文件和工程源文件放在一起显得杂乱无章
## 内部构建

# 在当前目录下，编译本目录的CMakeLists.txt，生成Makefile和其他文件
$ cmake .
# 执行make命令，生成target
$ make
外部构建(out-of-source build):推荐使用
将编译输出文件和源文件放到不同的目录中
## 外部构建

# 1. 在当前目录下，创建build文件夹
$ mkdir build
# 2. 进入到build文件夹
$ cd build
# 3. 编译上级目录的CMakeLists.txt，生成Makefile和其他文件
$ cmake ..
# 4. 执行make命令，生成target
$ make
