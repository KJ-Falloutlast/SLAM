cmake_minimum_required( VERSION 2.8 )
project( geometry )

# 添加Eigen头文件
include_directories( "/usr/include/eigen3" )

add_executable( eigenGeometry eigenGeometry.cpp )
add_executable( eigenGeometry01 eigenGeometry01.cpp )
add_executable( eigenGeometry02 eigenGeometry02.cpp )
