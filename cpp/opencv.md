# 1.opencv和点云处理基础
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

## 1-3.opencv基础
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
      4. ```mat.at<uchar>(row, col):单通道，返回uchar类型; mat.ar<Vec4b>(row, col):4通道，返回<Vec4b>,返回一个uchar数组，长度为4``
4. 图像遍历的方法
```cpp
#include <../include/quickopencv.h>
#include <opencv2/opencv.hpp>
#include <map>
#include <iostream>
using namespace cv;
using namespace std;
//1.使用数组
void test01(){
    // 9 % 3 = 0, 3 % 9  = 3;取模运算 = a/b后的余数
    Mat grayImage(5, 5, CV_8UC1);       //创建一个大小为600x800的单通道灰度图
    Mat colorImage(3, 3, CV_8UC3);      //创建一个大小为600x800的三通道彩色图

    //1.单通道遍历所有像素并设置像素值
    for(int i = 0; i < grayImage.rows; ++i)         //遍历行
        for(int j = 0; j < grayImage.cols; ++j)     //遍历列
            grayImage.at<uchar>(i, j) = (i + j) % 255;

    //2.3通道遍历所有像素并设置像素值
    for(int i = 0; i < colorImage.rows; ++i)         //遍历行
        for(int j = 0; j < colorImage.cols; ++j)     //遍历列
        {
            Vec3b pixel;            //定义三通道像素值变量
            pixel[0] = i % 255;     //Blue
            pixel[1] = j % 255;     //Green
            pixel[2] = (i + j) % 255;           //Red

            colorImage.at<Vec3b>(i, j) = pixel;
        }

    //显示简历图像的结果
    namedWindow("grayImage", WINDOW_AUTOSIZE);
    imshow("grayImage", grayImage);

    namedWindow("colorImage", WINDOW_AUTOSIZE);
    imshow("colorImage", colorImage);
    cout << "M(grayImage) = \n " <<  grayImage << endl;
    cout << "M(colorImage) = \n " << colorImage << endl;
    waitKey(0);

}
//2.使用迭代器
void test02(){
    Mat grayImage(400, 600, CV_8UC1);       //创建一个大小为600x800的单通道灰度图
    Mat colorImage(400, 600, CV_8UC3);      //创建一个大小为600x800的三通道彩色图

    //1.单通道遍历所有像素并设置像素值
    MatIterator_<uchar> grayit, grayend;
    for(grayit = grayImage.begin<uchar>(), grayend = grayImage.end<uchar>(); grayit != grayend; ++grayit)
        *grayit = rand() % 255;

    //2.3通道遍历所有像素并设置像素值
    MatIterator_<Vec3b> colorit, colorend;
    for(colorit = colorImage.begin<Vec3b>(), colorend = colorImage.end<Vec3b>(); colorit != colorend; ++colorit)
    {
        (*colorit)[0] = rand() % 255;       //Blue
        (*colorit)[1] = rand() % 255;       //Green
        (*colorit)[2] = rand() % 255;       //Red
    }


    //显示简历图像的结果
    namedWindow("grayImage", WINDOW_AUTOSIZE);
    imshow("grayImage", grayImage);

    namedWindow("colorImage", WINDOW_AUTOSIZE);
    imshow("colorImage", colorImage);

    waitKey(0);
}
//通过指针遍历
void test03(){
    Mat grayImage(5, 5, CV_8UC1);       //创建一个大小为600x800的单通道灰度图
    Mat colorImage(3, 3, CV_8UC3);      //创建一个大小为600x800的三通道彩色图

    //1.单通道遍历所有像素并设置像素值
    for(int i = 0; i < grayImage.rows; ++i)
    {
        uchar* p = grayImage.ptr<uchar>(i);     //获取第i行第一个像素的指针
        for(int j = 0; j < grayImage.cols; ++j)
            p[j] = (i + j) % 255;               //对每个i行的所有像素进行赋值操作
    }

    //2.3通道遍历所有像素并设置像素值

    for(int i = 0; i < colorImage.rows; ++i)
    {
        Vec3b* p = colorImage.ptr<Vec3b>(i);
        for(int j = 0; j < colorImage.cols; ++j)
        {
            p[j][0] = i % 255;      //Blue
            p[j][1] = j % 255;      //Gree
            p[j][2] = (i + j) % 255;//Red
        }
    }

    //显示简历图像的结果
    namedWindow("grayImage", WINDOW_AUTOSIZE);
    imshow("grayImage", grayImage);

    namedWindow("colorImage", WINDOW_AUTOSIZE);
    imshow("colorImage", colorImage);
    cout << "M(grayImage) = \n " <<  grayImage << endl;
    cout << "M(colorImage) = \n " << colorImage << endl;
    waitKey(0);//waitKey(0)表示用户无限等待
}
int main()
{
    // test01();
    // test02();
    test03();
}
```
5. Vec3b案例
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

## 1-4.案例
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
### 1.图像的读取和显示
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
```
### 2.图像的创建和赋值
```cpp
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
### 3.图像的读写操作
```cpp

```

## 1-5.补充知识
### 1.scalar
1. 例子1
```cpp
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
using namespace std;
using namespace cv;
void scalar_demo1(){
	Mat M(4,4,CV_32FC2,Scalar(1,3));//一般来说,2通道的mat,Scalar只要写2个数字,3通道及其以上的mat,scalar只要写3个数字
	cout<<M<<endl;
    /*
    1.创建一个2通道，且每个通道的值都为（1,3），深度为32，4行4列的图像矩阵。CV_32F表示每个元素的值的类型为32位浮点数，C2表示通道数为2，
    Scalar（1,3）表示对矩阵每个元素都赋值为（1,3），第一个通道中的值都是1，第二个通道中的值都是3.
    2.成为矩阵的时候先分配后赋值,比如说是,Mat(4, 4, 8UC3, Scalar(255, 255, 0)),则生成的矩阵为
    [255 255 0 255 255 0 255 255 0
     255 255 0 255 255 0 255 255 0
     255 255 0 255 255 0 255 255 0
     255 255 0 255 255 0 255 255 0]
    */
}
void scalar_demo2(){
	Mat M(4,4,CV_32FC3,Scalar(1,2,3));
    //创建一个4x4的3通道的32位浮点数的矩阵,矩阵中的每一个元素赋值为(1,2,3),第一个通道中的值为1,第二个是2, 第三个是3
	cout<<M<<endl;
}
void scalar_demo3(){
	Mat M(4,4,CV_32FC4,Scalar(1,2,3));
	cout<<M<<endl;
}
void scalar_demo4(){
	Mat blue_m(256,256,CV_8UC3,Scalar(255,0,0));//BGR
    //生成1个256x256的3通道的usignedchar的矩阵,每个元素是(255,0,0)
	Mat green_m(256,256,CV_8UC3,Scalar(0,255,0));
	Mat red_m(256,256,CV_8UC3,Scalar(0,0,255));
	imshow("Blue",blue_m);
	waitKey(0);
	imshow("Green",green_m);
	waitKey(0);
	imshow("Red",red_m);
	waitKey(0);
	
}
int main(void)
{
	//resize_img();
	//convert_color_space();
	scalar_demo1();
	cout<<"**********************************"<<endl;
	scalar_demo2();
	cout<<"**********************************"<<endl;
	scalar_demo3();
	scalar_demo4();
	return 0;
}
/*
[1, 3, 1, 3, 1, 3, 1, 3;0   
 1, 3, 1, 3, 1, 3, 1, 3;
 1, 3, 1, 3, 1, 3, 1, 3;
 1, 3, 1, 3, 1, 3, 1, 3]
**********************************
[1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3;
 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3;
 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3;
 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3]
**********************************
[1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0;
 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0;
 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0;
 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0]
*/
```
### 2.















# 2.点云处理
## 2-1.点云的基本概念
1. 概念：同一空间参考系下表达目标空间分布和目标表面特性的海量点集合，是在获取物体表面每个采样点的空间坐标后得到的点的集合，称为点云(Point Cloud)
2. 数据类型
   1. 类型
```cpp
//1.
pcl::PointCloud<pcl::PointXYZ>
//PointXY成员:float x, y, z表达了xyz3d的信息，可以通过points[i].data[0] or points[i].x访问点x的坐标值
pcl::PointCloud<pcl::PointXYZI>
//PointXYZI成员:float x, y, z, intensity;表示XYZ信息加上强度信息的类型
pcl::PointCloud<pcl::PointXYZRGB>
//PointCloudRGB成员:float x, y, z; 表示xyz信息加上rgb信息，rgb存储为一个float
pcl::PointCloud<pcl::PointXYZRGBA>
/*PointXYZRGBA成员: float x, y, z, unit32_t rgba;
表示XYZ信息加上RGBA信息，RGBA用32bit的int型存储的
*/
```
   2. 转换
      1. pcl::PointCloud<pcl::PointXYZ> cloud;(点云对
      2. pcl::PointCloud<pcl::PointXYZ>::ptr cloudPtr;(点云指针)
      3. pcl::PointXYZ overlap(点)
      4. >cloud = * cloudPtr; cloudPtr = cloud.makeshared()
      5. 访问单个点:
         1. cloud.points[i].x;
         2. cloudPtr->points[i].x;
         3. overlap.x;
      6. 获取点数
         1. sizeof(overlap);
         2. cloud.size();
         3. cloudPtr->size();
## 2-2.代码实例
1. 创建点云数据(pcl_create.cpp)
```cpp
#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
 
main (int argc, char **argv)
{
    ros::init (argc, argv, "pcl_create");
 
    ros::NodeHandle nh;
    ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2> ("pcl_output", 1);
    pcl::PointCloud<pcl::PointXYZ> cloud;
    sensor_msgs::PointCloud2 output;
 
    // Fill in the cloud data
    cloud.width  = 100;
    cloud.height = 1;
    cloud.points.resize(cloud.width * cloud.height);
 
    for (size_t i = 0; i < cloud.points.size (); ++i)
    {
        cloud.points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);
        cloud.points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);
        cloud.points[i].z = 1024 * rand () / (RAND_MAX + 1.0f);
    }
 
    //Convert the cloud to ROS message
    pcl::toROSMsg(cloud, output);
    output.header.frame_id = "odom";
 
    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        pcl_pub.publish(output);
        ros::spinOnce();
        loop_rate.sleep();
    }
 
    return 0;
}
```
```cmake
cmake_minimum_required(VERSION 2.8.3)
project(chapter10_tutorials)
find_package(catkin REQUIRED COMPONENTS
  pcl_conversions
  pcl_ros
  roscpp
  sensor_msgs
  rospy
)
 
find_package(PCL REQUIRED)
catkin_package()
 
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)
 
link_directories(${PCL_LIBRARY_DIRS})
 
 
add_executable(pcl_create src/pcl_create.cpp)
target_link_libraries(pcl_create ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(pcl_read src/pcl_read.cpp)
add_executable(pcl_write src/pcl_write.cpp)
 
target_link_libraries(pcl_read ${catkin_LIBRARIES} ${PCL_LIBRARIES})
target_link_libraries(pcl_write ${catkin_LIBRARIES} ${PCL_LIBRARIES})
```
2. 加载点云数据(pcl_read.cpp)
```cpp
#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
 
main(int argc, char **argv)
{
    ros::init (argc, argv, "pcl_read");
 
    ros::NodeHandle nh;
    ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2> ("pcl_output", 1);
 
    sensor_msgs::PointCloud2 output;
    pcl::PointCloud<pcl::PointXYZ> cloud;
 
    pcl::io::loadPCDFile ("test_pcd.pcd", cloud);
 
    pcl::toROSMsg(cloud, output);
    output.header.frame_id = "odom";
 
    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        pcl_pub.publish(output);
        ros::spinOnce();
        loop_rate.sleep();
    }
 
    return 0;
}
```
3. 保存点云数据(pcl_write.cpp)
```cpp
#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
 
void cloudCB(const sensor_msgs::PointCloud2 &input)
{
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::fromROSMsg(input, cloud);
    pcl::io::savePCDFileASCII ("write_pcd_test.pcd", cloud);
}
 
main (int argc, char **argv)
{
    ros::init (argc, argv, "pcl_write");
    ros::NodeHandle nh;
    ros::Subscriber bat_sub = nh.subscribe("pcl_output", 10, cloudCB);
    ros::spin();
 
    return 0;
}
```
4. cloud_viewer可视化pcd中的点云(pcl_view.cpp)
```cpp
#include <iostream>
#include <ros/ros.h>
#include <pcl/visualization/cloud_viewer.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
 
class cloudHandler
{
public:
    cloudHandler()
    : viewer("Cloud Viewer")
    {
     pcl::PointCloud<pcl::PointXYZ> cloud;
     pcl::io::loadPCDFile ("0.pcd", cloud);
     viewer.showCloud(cloud.makeShared());
     viewer_timer = nh.createTimer(ros::Duration(0.1), &cloudHandler::timerCB, this);
    }
 
    void timerCB(const ros::TimerEvent&)
    {
        if (viewer.wasStopped())
        {
            ros::shutdown();
        }
    }
 
protected:
    ros::NodeHandle nh;
    pcl::visualization::CloudViewer viewer;
    ros::Timer viewer_timer;
};
 
main (int argc, char **argv)
{
    ros::init (argc, argv, "pcl_filter");
    cloudHandler handler;
    ros::spin();
    return 0;
}
```
5. 随机生成10000个三维点，然后赋值给点云
```cpp
#include <iostream>
//点云需要的头文件
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>
#include <pcl/visualization/pcl_visualizer.h>
using namespace std;
//随机生成了10000个三维点，然后赋值给一片点云，并且完成显示
void drawPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, string titleName)
{
    pcl::visualization::PCLVisualizer viewer (titleName);
    int v (0);

    viewer.createViewPort (0.0, 0.0, 1.0, 1.0, v);

    viewer.addCoordinateSystem(0.5);

    float bckgr_gray_level = 0.0;  // Black
    float txt_gray_lvl = 1.0 - bckgr_gray_level;

    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_in_color_h (cloud, (int) 255 * txt_gray_lvl, (int) 255 * txt_gray_lvl, (int) 255 * txt_gray_lvl);
    viewer.addPointCloud (cloud, cloud_in_color_h, "cloud_in_v1", v);

    viewer.addText (titleName, 10, 15, 16, txt_gray_lvl, txt_gray_lvl, txt_gray_lvl, "icp_info_1", v);

    viewer.setBackgroundColor (bckgr_gray_level, bckgr_gray_level, bckgr_gray_level, v);

    viewer.setCameraPosition (-3.68332, 2.94092, 5.71266, 0.289847, 0.921947, -0.256907, 0);
    viewer.setSize (1280, 1024);

    while (!viewer.wasStopped())
    {
        viewer.spinOnce();
    }
}

pcl::PointCloud<pcl::PointXYZ>::Ptr readPointCloud_camera(int width, int height, vector<int> x, vector<int> y, vector<int> z)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
      
    cloud->width = width;
    cloud->height = height;
    cloud->points.resize(width*height);

    for (int i = 0 ; i < width*height; i++)
    {
        cloud->points[i].x = x[i];
        cloud->points[i].y = y[i];
        cloud->points[i].z = z[i];
    }
    return cloud;  
}

int main(int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;

    vector<int> x, y, z;
    for (int i = 0 ; i < 10000; i ++)
    {      
        x.push_back(i);
        y.push_back(i + 2);
        z.push_back(i+10);
    }
    cloud = readPointCloud_camera(100, 100, x, y, z);

    drawPointCloud(cloud, "user defined pointcloud");

	return 1;
}
```