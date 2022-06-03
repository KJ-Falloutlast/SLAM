# 1.opencv基础
## 1-1.加载修改和保存图像
1. imread
   1. 功能：加载图像文件，使得图像文件成为一个mat对象，其中第一个参数为图像文件名称
   2. 第二参数表示加载的图像是什么文件类型，常见的有3个值
      1. imraed_unchanged(<0)表示加载原图，不做任何改变
      2. imread_grayscale(0)表示把原图作为灰度图像加载进来
      3. imread_color(>0)表示把原图作为rgb图像加载进来
   3. 注意：opencv支持jpg,png,tiff等常见文件
2. cv::namedWindos:功能是创建一个opencv窗口，由opencv自动创建和销毁
3. cv::cvtColor

4. cmake
```cmake
cmake_minimum_required( VERSION 2.8 )
project( imageBasics )

# 添加c++ 11标准支持
set( CMAKE_CXX_FLAGS "-std=c++11" )

# 寻找OpenCV库
find_package( OpenCV REQUIRED )
# 添加头文件
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( demo01 demo01.cpp )
# 链接OpenCV库
target_link_libraries( demo01 ${OpenCV_LIBS} )
```
5. 案例
```cpp
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <opencv2/highgui/highgui_c.h>//主要解决CV_WINDOW_AUTOSIZE问题
using namespace cv;

int main(int argc, char** argv) {
	//1.创建图像
    Mat src;
    //2.读取图像
	src = imread("/home/kim-james/ROS_Space/opencv_ws/opencv_tutorial_data/images/22.jpg");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}
    //3.制定窗口参数,CV_WINDOW_NORMAL是只图像大小可以改变
	namedWindow("input image", CV_WINDOW_NORMAL);
    //4.显示图片
	imshow("input image", src);
    //转换后的图片
    Mat output_image;
    namedWindow("output windows", CV_WINDOW_NORMAL);
    cvtColor(src, output_image, CV_BGR2GRAY);
    //将BGR图像转换为灰度图像
    imshow("output windows", output_image);
    //5.保存图片
    imwrite("./", output_image);
    //6.设置等待时间
    waitKey(0);//0就是不自动退出，为k则等待k秒
}
```
## 1-2.转换图像
1. cvtColor
   1. COLOR_BGR2GRAY = 6彩色到灰度
   2. COLOR_GRAY2BGR = 8灰度到彩色
   3. COLOR_BGR2HSV = 40BGR到HSV
   4. COLOR_HSV2BGR = 54HSV到BGR
2. imwrite
   1. 参数1是保存路径
   2. 参数2是图像内存对象

