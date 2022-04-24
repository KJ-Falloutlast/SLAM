#设置cmake名称
cmake_minimum_required(VERSION 3.0)
#起一个名字
project(cmake_parctice)
#设置编译模式:CMAKE_BUILD_RPATH ="Release"
set(CMAKE_BUILD_RPATH "Release")
#编译主文件
add_executable(sayhello useHello.cpp)
#添加头文件
include_directories(${PROJECT_SOURCE_DIR}/include)#将源文件路径包含进来
#编译动态链接库
add_library(hello SHARED ${PROJECT_SOURCE_DIR}/src/hello.cpp)
#与源文件建立联系
target_link_libraries(sayhello hello)
