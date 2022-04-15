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
