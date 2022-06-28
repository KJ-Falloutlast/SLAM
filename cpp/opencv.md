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
   1. 把图像从一个彩色空间转换到另一个色彩空间，有3个参数
   2. 第一个参数表示源图像，第2个参数表示色彩空间转换后的图像，第2个参数表示源和目标色彩空间,如COLOR_BGR2HLS,COLOR_BGR2GRAY的等
   3. 例如:**cvtColor(image, gray_image, COLOR_BGR2GRAY);**
   4. COLOR_BGR2GRAY = 6彩色到灰度
   5. COLOR_GRAY2BGR = 8灰度到彩色
   6. COLOR_BGR2HSV = 40BGR到HSV
   7. COLOR_HSV2BGR = 54HSV到BGR
4. cv::imwrite
   1. 保存图像文件到指定目录路径
   2. 只有8位，16位的PNG，jpg,Tiff文格式而且是单通道或者3通道的BGR图像才能通过这种方式保存
   3. 保存png格式的时候可以保存透明通道的图片
   4. 可以指定压缩参数
5. 案例
```cpp
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <opencv2/highgui/highgui_c.h>//主要解决CV_WINDOW_AUTOSIZE问题
using namespace cv;
using namespace std;
int main(){
    //1.加载图像
    Mat src = imread("/home/kim-james/ROS_Space/opencv_ws/opencv_tutorial_data/images/63_12_map.png");
    if (src.empty()){
        cout << "could not load image"<< endl;
    }
    namedWindow("opencv setup demo", CV_WINDOW_AUTOSIZE);//不要加CV
    imshow("opencv setup demo", src);
    //2.修改图像
    Mat outputImage;
    cvtColor(src, outputImage, CV_BGR2HLS);//把src通过CV_BGR2HLS转换成outputImage 
    namedWindow("output windows", CV_WINDOW_AUTOSIZE);
    imshow("output windows", src);
    
    //3.保存图像
    imwrite("/home/kim-james/ROS_Space/opencv_ws/ch2/picture/demo01.png", outputImage);
    //imwrite后要接xxxx.png
    waitKey(0);//无限等待
    return 0;
}
```
## 1-2.图像的掩膜操作
![图像的掩膜操作](../pictures/图像的掩膜操作.png图像的)
1. 获取图像像素指针
   1. CV_Assert(myImage.depth() == CV_8U);
   2. Mat.ptr<uchar>(int i = 0)获取像素矩阵的指针，索引i表示第几行，从0开始计数
   3. 获得当前行的指针:const uchar* current = myImage.ptr<uchar>(row);
   4. 获取当前像素点P(row, col)的像素值p(row, col) = current[col],所以为const uchar* current = myImage.ptr<uchar>(row)[col];
2. 像素范围处理satuate_cast<uchar>
   1. saturate_cast<uchar>(-100):返回0
   2. saturate_cast<uchar>(288):返回255
   3. saturate_cast<uchar>(100):返回100
   4. 这个函数的功能是确保RGB值在范围0-225之间
3. 矩阵的掩膜操作
   1. $ I(i,j)=5∗I(i,j)−[I(i−1,j)+I(i+1,j)+I(i,j−1)+I(i,j+1)]$
4. 函数调用filter2D功能
   1. 定义掩膜: Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
   2. filter2D(src, dst, src.depth(), kernel);其中src和dst是Mat,src.depth表示位图深度，有32， 24， 8
```cpp
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <opencv2/highgui/highgui.hpp>//主要解决CV_WINDOW_AUTOSIZE问题
using namespace cv;
using namespace std;

void sharpen(Mat &image)
{
	int rows = image.rows;
	int cols = image.cols;
	int channels = image.channels();//获取原图像通道数
	Mat dst;
	dst.create(image.size(),image.type());//创建一个和原图像大小和类型相同的输出对象
    //方法1.
	for (int i = 1; i < rows-1; i++)//由于像素的操作需要涉及到上下左右四个像素，所以边缘像素无法操作，所以就减去第一行和最后一行
	{
		const uchar* previous = image.ptr<const uchar>(i - 1);//上一行
		const uchar* current = image.ptr<const uchar>(i);//当前行
		const uchar* next = image.ptr<const uchar>(i + 1);//下一行
		uchar* output = dst.ptr<uchar>(i);//输出行
		for (int j = channels; j < (cols-1)*channels; j++)
		{
		    //锐化算子
			output[j] = saturate_cast<uchar>(5 * current[j] - current[j - channels] - current[j + channels] - previous[j] - next[j]); 
		}//指针可指向行，也可指向单个元素、
	}
    //方法2.
    // Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	// filter2D(image, dst, image.depth(), kernel);
    namedWindow("output picture", WINDOW_FREERATIO);
	imshow("output picture", dst);
}
int main()
{
	Mat image;
	Mat dst1;
	image = imread("/home/kim-james/ROS_Space/opencv_ws/source/images/lena.png");
	namedWindow("input picture", WINDOW_FREERATIO);
	imshow("input picture", image);
	
	sharpen(image);
	waitKey(0);
	return 0;

}

```
## 1-3.Mat








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
// pixel：像素
void QuickDemo::pixel_visit_demo(Mat &image){
    int w = image.cols;
    int h = image.rows;
    int dims = image.channels();//dims是维度也是通道数
    //1.通过数组
    // for (int row = 0; row < h; row++){
    //     for (int col = 0; col < w; col++){
    //         if (dims == 1){//灰度图像channels = 1
    //             int pv = image.at<uchar>(row, col);
    //             image.at<uchar>(row, col) = 255- pv;
    //             /*
    //             1.at<uchar>:将uchar类型的转换为int类型               
    //             2.usigned char:为有符号8位数，-128-127
    //               char:无符号8位数，0-255
    //             */
    //         }
    //         if (dims == 3){//彩色图像channels = 2
    //             Vec3b bgr = image.at<Vec3b>(row, col);//一次性获取了3个值
    //             //Vec3b是一个数组
    //             image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
    //             image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
    //             image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
    //         }
    //     }
    // }


    //2.通过指针访问
    for (int row = 0; row < h; row++){
        uchar *current_row = image.ptr<uchar>(row);//当前行的指针 
        for (int col = 0; col < w; col++){
            if (dims == 1){//灰度图像channels = 1
                int pv = *current_row;
                *current_row++ = 255 - pv;
            }
            if (dims == 3){//彩色图像channels = 3
                *current_row++ = 255 - *current_row;
                *current_row++ = 255 - *current_row;
                *current_row++ = 255 - *current_row;
            }//指针可以实现快速遍历
        }
    }
    imshow("像素读写演示", image);

}
```
### 4.图像的加减乘除
```cpp
void QuickDemo::operators_demo(Mat &image){
    Mat dst1, dst2, dst3, dst4;
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(5, 5, 5);

	//等同于下面的加法算法
	/*
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			Vec3b p1 = image.at<Vec3b>(row, col);
			Vec3b p2 = m.at<Vec3b>(row, col);
			dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0] + p2[0]);
			//通过saturate_cast<uchar>进行类型转换
            dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1] + p2[1]);
			dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2] + p2[2]);
		}
	}
	*/
	add(image, m, dst1);// image + m = dst1
	subtract(image, m, dst2);// image - m
	multiply(image, m, dst3);// image * m
	divide(image, m, dst4);// image / m
	imshow("加法操作", dst1);
	imshow("减法操作", dst2);
	imshow("乘法操作", dst3);
	imshow("除法操作", dst4);
}
```
### 5.图像的亮度和对比度调整

```cpp
static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, m, 0, b, dst);
	imshow("亮度对比操作", dst);
}

static void on_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst);
	imshow("", dst);
}

void QuickDemo::tracking_bar_demo(Mat &image) {
	namedWindow("亮度与对比度操作", WINDOW_AUTOSIZE);
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;
	createTrackbar("Value Bar:", "亮度与对比度调整", &lightness, max_value, on_lightness, (void*) (&image));
    //将image的引用&image转换成void类型的指针
	createTrackbar("Contrast Bar:", "亮度与对比度调整", &contrast_value, 200, on_contrast, (void*)(&image));
	on_lightness(50, &image);
    /*
    1.createTrackbar的参数:
        1.滑动空间名称
        2.滑动空间用于依附的图像窗口的名称
        3.初始化阈值
        4.滑动控件的刻度范围
        5.回调函数
    void (CV_CDECL *TrackbarCallback)(int pos, void* userdata);
    2. 形式
    */
}
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
