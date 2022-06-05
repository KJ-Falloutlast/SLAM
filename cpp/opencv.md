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

# 2.opencv基础
1. Mat基本结构
   1. header:头部|数据部分
   2. 赋值，克隆，拷贝
2. 创建方法
   1. m1.copyTo(m2)
   2. m1 = m2
   3. m1 = Scalar(255 0 0)
3. Vec3b:
   1. 可以看做vector<uchar, 3>,即一个uchar类型，长度为3个vector
   2. color[0] = 255 (0, 1, 2分别代表BGR通道)
   3. 读取像素:
      1. imread读取到的Mat图像，都是用uchar类型存储,对于RGB三通道，每个点都是Vec3b
      2. >Mat mat = imread("test.jpg");
      3. mat.at<Vec3b>(row, col)[0] = 255;修改(row, col)的B通道，[1], [2]同理
      4. ```mat.at<uchar>(row, col):单通道，返回uchar类型; mat.ar<Vec4b>(row, col):4通道，返回<Vec4b>,返回一个uchar数组，长度为4```
4. Vec3b案例
```cpp
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
    Mat m(3, 3, CV_8UC3);
    Vec3b vec;
    for (int row = 0; row < 3; row++){
        for (int col = 0; col < 3; col++){
            vec[0] = row;
            vec[1] = col;
            vec[2] = row + col;
            m.at<Vec3b>(row, col) = vec;
        }
    }
    cout << "M = " << endl << m << endl;
    Vec3b a = m.at<Vec3b>(2, 2);
    int b = m.at<Vec3b>(2, 2)[0];//
    cout << "M(2, 2) = " << a <<  endl;
    cout << "M(2, 2)[0] = " << b << endl;
}
}
```

# 3.案例
1. quickopencv.h
```cpp
#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;
class QuickDemo{
    public:
        void colorSpace_Demo(Mat &image);
        void mat_creation_demo(Mat &image);
};
```
2. quickopencv.cpp
```cpp
#include "../include/quickopencv.h"
void QuickDemo::colorSpace_Demo(Mat &image){
    Mat gray, hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);//转hsv
    cvtColor(image, gray, COLOR_BGR2GRAY);//转灰度
    imshow("HSV", hsv);
    imshow("灰度", gray);
    imwrite("/home/kim-james/ROS_Space/opencv_ws/ch1/picture/hsv.png", hsv);
    //千万不要忘记hsv.png和gray.png
    imwrite("/home/kim-james/ROS_Space/opencv_ws/ch1/picture/gray.png", gray);
    /*
    1.R G B:0-255
    2.H:0-180,S,V:0-255;H,S是改变颜色的通道，V是改变亮度的通道
    */
}
void QuickDemo::mat_creation_demo(Mat &image){
    //第一讲:创建图像基本操作
    // Mat m1, m2;
    // m1 = image.clone();
    // image.copyTo(m2);
    //创建空白图像

    //第二讲:mat操作
    //1.mat的赋值
    //1-1.利用矩阵
    Mat m3 = Mat::zeros(Size(400, 400), CV_8UC3);
    
    //1-2.直接赋值
    // m3 = 123;//表示把第一个通道变为123;

    //1-3.利用scalar(a, b, c); 默认为:BGR
    m3 = Scalar(255, 0, 0);//表示把3个通道都变成127
    /*
    1.产生8X8的0矩阵，8表示8位，
    UC表示usigned char,1表示单通道
    2.如果是3，则是表示3通道的矩阵，所以变成了8X24的矩阵，
    由于有3个通道，所以列数变成了3x8,故列数为(cols * channels)
    3.mat支持对任意操作符的重载，所以可以大胆使用
    4.Size()的大小会改变图像的大小，所以size越大图像就越大
    */

    cout << m3 << endl;
    cout << "width = " << m3.cols 
    << " height = " << m3.rows 
    << " channels = " << m3.channels() << endl;
    
    //2.mat的拷贝操作
    //2-1.m1 = m2
    Mat m4;
    m4 = m3;
    m4 = Scalar(0, 0, 255);//m4不会被scalar改变
    //此时m4会随着m3的变化而变化

    // 2-2.m1 = m2.clone()
    m4 = m3.clone();
    m4 = Scalar(0, 0, 255);//m4会被scalar改变
    
    //2-3.m3.copyTo()
    m3.copyTo(m4);/m4会被scalar改变
    //当调用m3的copyTo()和clone()，不会改变m4的值
    imshow("创建图像m3", m3);
    imshow("创建图像m4", m4);
    //m3和m4都变成了黄色
}
```
3. main.cpp
```cpp
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <opencv2/highgui/highgui_c.h>//主要解决CV_WINDOW_AUTOSIZE问题
#include "../include/quickopencv.h"
using namespace cv;

int main(int argc, char** argv) {
	Mat src = imread("/home/kim-james/ROS_Space/opencv_ws/opencv_tutorial_data/images/63_12_map.png");
    
    if (src.empty()){
        return -1;
    }
    namedWindow("input", WINDOW_FREERATIO);//任意窗口大小
    imshow("input", src);//imshow只支持8位的输入
    QuickDemo qd;
    qd.colorSpace_Demo(src);
    qd.mat_creation_demo(src);
    waitKey(0);
    destroyAllWindows();

}
```