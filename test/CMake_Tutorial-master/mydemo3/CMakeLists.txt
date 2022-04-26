project(sayhello)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE "RELEASE")
#提供头文件的路径
include_directories(./include)
#设置生成的可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ./build)
# 设置生成的动态库文件的输出路径
set(LIBRARY_OUTPUT_PATH ./lib)

add_library(hello SHARED src/hello.cpp)#libhello.so

#生成可执行文件
add_executable(sayHello src/useHello.cpp)#sayHello
#将可执行文件链接到动态库上
target_link_libraries(sayHello hello)

#[[
1.注意事项：PROJECT_SOURCE_DIR是指源文件的路径，也就是的当前目录的路径
2.
]]
