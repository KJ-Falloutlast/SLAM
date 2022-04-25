project(sayhello)
cmake_minimum_required(VERSION 3.10)
# set(CMAKE_BUILD_TYPE "RELEASE")
#提供头文件的路径
include_directories(./include)
# #设置生成的可执行文件的输出路径
# set(EXECUTABLE_OUTPUT_PATH ./build)
#设置生成的动态库文件的输出路径
# set(LIBRARY_OUTPUT_PATH ./lib)
aux_source_directory(./  DIR_SRCS)#只适用于单个目录，多个文件

add_library(hello SHARED ${DIR_SRCS})
#生成可执行文件
add_executable(sayHello ${DIR_SRCS})
#将可执行文件链接到动态库上
target_link_libraries(sayHello hello)#把可执行文件hello链接到动态库sayHello上

#[[
1.注意事项：PROJECT_SOURCE_DIR是指源文件的路径，也就是的当前目录的路径
2.将sayHello可执行文件链接到动态库上
3.aux_source_directory(./  DIR_SRCS)只适用于添加单个目录，多个文件
4.在build中执行完cmake ..后，set(LIBRARY_OUTPUT_PATH ./lib),set(LIBRARY_OUTPUT_PATH ./lib)
分别将可执行文件hello 和 动态库libhello.so放在 build 和 lib文件中
]]

