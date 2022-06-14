# 1.第一讲
### 1-1.基本命令
#### 1.运行c++文件
1. 过程
   1. 各个文件包的功能
      1. include: 放头文件 xxx.h
      2. src:放源文件 xxx.cpp
      3. lib:放库文件 xxx.a/xxx.so
   2. 目录结构
      1. demo
         1. CMakeList.txt
         2. src
            1. demo.cpp
            2. CMakeLists.txt
         3. include
            1. CMakeLists.txt
            2. mymath.cpp
            3. mymath.h
         4. build
2. 各文件信息
   1. ./CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.10)
project(mydemo2)
add_subdirectory(./include)
add_subdirectory(./src)
```
   2. /include/CMakeLists.txt
```cmake
aux_source_directory(. DIR_LIB_SRCS)
add_library(Mylib STATIC ${DIR_LIB_SRCS})
```
   3. /src/CMakeLists.txt
```cmake
include_directories(../include)
aux_source_directory(./ DIR_SRCS)
add_executable(mydemo2 ${DIR_SRCS})
target_link_libraries(mydemo2 Mylib)
#让include中的库文件Mylib和mydemo2链接起来
```
   4. /include/mymath.h and /include/mymath.cpp
mymath.h
```cpp
#ifndef MYMATH_H
#define MYMATH_H
#include <iostream>
using namespace std;

double power(double a, double b);

#endif
```
mymath.cpp
```cpp
#include "mymath.h"
double power(double a, double b){ 
    int res = a;
    for (int i = 0; i < b; i++){
        res = res*a;
    }
    return res;
}
```
   5. main.cpp
```cpp
#include "../include/mymath.h"
int main(int argc, char** argv){
    if (argc < 3){
        cout << "您的输入有错误:" << endl;
        return 0;
    }
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    double res = power(a, b);
    cout << "您的输出结果是:" << res << endl;
}
```
# 2.第二讲
## 1. eigen的使用
1. >头文件路径：/usr/include/eigen3/Eigen/Core 
2. 基本使用：
   
```cpp
#include <iostream>
#include <Eigen/Dense>
using namespace std;
template <typename T>
static void matrix_mul_matrix(T* p1, int iRow1, int iCol1, T* p2, int iRow2, int iCol2, T* p3)
{
    if (iRow1 != iRow2) return;
 
    //列优先
    //Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> > map1(p1, iRow1, iCol1);
    //Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> > map2(p2, iRow2, iCol2);
    //Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> > map3(p3, iCol1, iCol2);
 
    //行优先
    Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> map1(p1, iRow1, iCol1);
    Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> map2(p2, iRow2, iCol2);
    Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> map3(p3, iCol1, iCol2);
 
    map3 = map1 * map2;
}
 
int main(int argc, char* argv[])
{
    //1. 矩阵的定义
    Eigen::MatrixXd m(2, 2);
    Eigen::Vector3d vec3d;
    Eigen::Vector4d vec4d(1.0, 2.0, 3.0, 4.0);
 
    //2. 动态矩阵、静态矩阵
    Eigen::MatrixXd matrixXd;
    Eigen::Matrix3d matrix3d;
 
    //3. 矩阵元素的访问
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = m(0, 0) + 3; 
    m(1, 1) = m(0, 0) * m(0, 1);
    cout << m << endl << endl;
 
    //4. 设置矩阵的元素
    m << -1.5, 2.4,
        6.7, 2.0;
    cout << m << endl << endl;
    int row = 4;
    int col = 5;
    Eigen::MatrixXf matrixXf(row, col);
    matrixXf << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20;
    cout << matrixXf << endl << endl;
    matrixXf << Eigen::MatrixXf::Identity(row, col);
    cout << matrixXf << endl << endl;
 
    //5. 重置矩阵大小
    Eigen::MatrixXd matrixXd1(3, 3);
    m = matrixXd1;
    cout << m.rows() << "  " << m.cols() << endl << endl;
 
    //6. 矩阵运算
    m << 1, 2, 7,
        3, 4, 8,
        5, 6, 9;
    cout << m << endl;
    matrixXd1 = Eigen::Matrix3d::Random();
    m += matrixXd1;
    cout << m << endl << endl;
    m *= 2;
    cout << m << endl << endl;
    cout << -m << endl << endl;
    cout << m << endl << endl;
 
    //7. 求矩阵的转置、共轭矩阵、伴随矩阵
    cout << m.transpose() << endl << endl;
    cout << m.conjugate() << endl << endl;
    cout << m.adjoint() << endl << endl;
    cout << m << endl << endl;
    m.transposeInPlace();
    cout << m << endl << endl;
 
    //8. 矩阵相乘、矩阵向量相乘
    cout << m*m << endl << endl;
    vec3d = Eigen::Vector3d(1, 2, 3);
    cout << m * vec3d << endl << endl;
    cout << vec3d.transpose()*m << endl << endl;
 
    //9. 矩阵的块操作
    cout << m << endl << endl;
    cout << m.block(1, 1, 2, 2) << endl << endl;
    cout << m.block<1, 2>(0, 0) << endl << endl;
    cout << m.col(1) << endl << endl;
    cout << m.row(0) << endl << endl;
 
    //10. 向量的块操作
    Eigen::ArrayXf arrayXf(10);
    arrayXf << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
    cout << vec3d << endl << endl;
    cout << arrayXf << endl << endl;
    cout << arrayXf.head(5) << endl << endl;
    cout << arrayXf.tail(4) * 2 << endl << endl;
 
    //11. 求解矩阵的特征值和特征向量
    Eigen::Matrix2f matrix2f;
    matrix2f << 1, 2, 3, 4;
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix2f> eigenSolver(matrix2f);
    if (eigenSolver.info() == Eigen::Success) {
        cout << eigenSolver.eigenvalues() << endl << endl;
        cout << eigenSolver.eigenvectors() << endl << endl;
    }
 
    //12. 类Map及动态矩阵的使用
    int array1[4] = { 1, 2, 3, 4 };
    int array2[4] = { 5, 6, 7, 8 };
    int array3[4] = { 0, 0, 0, 0};
    matrix_mul_matrix(array1, 2, 2, array2, 2, 2, array3);
    for (int i = 0; i < 4; i++)
        cout << array3[i] << endl;
 
	return 0;
}
```
3. 注意：

1. 矩阵的定义：Eigen中关于矩阵类的模板函数中，共有六个模板参数，常用的只有前三个。其前三个参数分别表示矩阵元素的类型、行数和列数。
   1. 矩阵定义时可以使用Dynamic来表示矩阵的行列数为未知。
   2. Eigen中无论是矩阵还是数组、向量，无论是静态矩阵还是动态矩阵都提供默认构造函数，也就是定义这些数据结构时都可以不用提供任何参数，其大小均由运行时来确定。矩阵的构造函数中只提供行列数、元素类型的构造参数，而不提供元素值的构造，对于比较小的、固定长度的向量提供初始化元素的定义。

2. 矩阵类型：Eigen中的矩阵类型一般都是用类似MatrixXXX来表示，可以根据该名字来判断其数据类型，比如”d”表示double类型，”f”表示float类型，”i”表示整数，”c”表示复数；Matrix2f，表示的是一个2*2维的，其每个元素都是float类型。
3. 数据存储：Matrix创建的矩阵默认是按列存储，Eigen在处理按列存储的矩阵时会更加高效。如果想修改可以在创建矩阵的时候加入参数，如:
   Matrix<int,3, 4, ColMajor> Acolmajor;
   Matrix<int,3, 4, RowMajor> Arowmajor;
4. 动态矩阵和静态矩阵：动态矩阵是指其大小在运行时确定，静态矩阵是指其大小在编译时确定。
   1. MatrixXd：表示任意大小的元素类型为double的矩阵变量，其大小只有在运行时被赋值之后才能知道。
   2. Matrix3d：表示元素类型为double大小为3*3的矩阵变量，其大小在编译时就知道。

5. 在Eigen中行优先的矩阵会在其名字中包含有row，否则就是列优先。Eigen中的向量只是一个特殊的矩阵，其维度为1而已。

6. 矩阵元素的访问：在矩阵的访问中，行索引总是作为第一个参数，Eigen中矩阵、数组、向量的下标都是从0开始。矩阵元素的访问可以通过”()”操作符完成。例如m(2, 3)既是获取矩阵m的第2行第3列元素。针对向量还提供”[]”操作符，注意矩阵则不可如此使用。

7. 设置矩阵的元素：在Eigen中重载了”<<”操作符，通过该操作符即可以一个一个元素的进行赋值，也可以一块一块的赋值。另外也可以使用下标进行赋值。

8. 重置矩阵大小：当前矩阵的行数、列数、大小可以通过rows()、cols()和size()来获取，对于动态矩阵可以通过resize()函数来动态修改矩阵的大小。注意：
   1. 固定大小的矩阵是不能使用resize()来修改矩阵的大小；
   2. resize()函数会析构掉原来的数据，因此调用resize()函数之后将不能保证元素的值不改变；
   3. 使用”=”操作符操作动态矩阵时，如果左右两边的矩阵大小不等，则左边的动态矩阵的大小会被修改为右边的大小。

9. 如何选择动态矩阵和静态矩阵：对于小矩阵(一般大小小于16)使用固定大小的静态矩阵，它可以带来比较高的效率；对于大矩阵(一般大小大于32)建议使用动态矩阵。注意：如果特别大的矩阵使用了固定大小的静态矩阵则可能会造成栈溢出的问题。

10. 矩阵和向量的算术运算：在Eigen中算术运算重载了C++的+、-、*
    1.  矩阵的运算：提供+、-、一元操作符”-”、+=、-=；二元操作符+/-，表示两矩阵相加(矩阵中对应元素相加/减，返回一个临时矩阵)；一元操作符-表示对矩阵取负(矩阵中对应元素取负，返回一个临时矩阵)；组合操作法+=或者-=表示(对应每个元素都做相应操作)；矩阵还提供与标量(单一数字)的乘除操作，表示每个元素都与该标量进行乘除操作；
    2.  求矩阵的转置、共轭矩阵、伴随矩阵：可以通过成员函数transpose()、conjugate()、adjoint()来完成。注意：这些函数返回操作后的结果，而不会对原矩阵的元素进行直接操作，如果要让原矩阵进行转换，则需要使用响应的InPlace函数，如transpoceInPlace()等；
    3.  矩阵相乘、矩阵向量相乘：使用操作符*，共有*和*=两种操作符；
    4.  矩阵的块操作：有两种使用方法：
        1.  matrix.block(i,j, p, q) : 表示返回从矩阵(i, j)开始，每行取p个元素，每列取q个元素所组成的临时新矩阵对象，原矩阵的元素不变；
        2.  matrix.block<p,q>(i, j) :<p, q>可理解为一个p行q列的子矩阵，该定义表示从原矩阵中第(i, j)开始，获取一个p行q列的子矩阵，返回该子矩阵组成的临时矩阵对象，原矩阵的元素不变；
        3.  向量的块操作：
```cpp
获取向量的前n个元素：vector.head(n);

获取向量尾部的n个元素：vector.tail(n);

获取从向量的第i个元素开始的n个元素：vector.segment(i,n);

Map类：在已经存在的矩阵或向量中，不必拷贝对象，而是直接在该对象的内存上进行运算操作。
```


## 2.eigen的使用总结：
```cpp
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
using namespace std;
int main(){
    //**1.创建和初始化矩阵**//
    //1-1. 普通矩阵生成
    Eigen::Matrix4d m1;//在定义时不能后接endl
    m1 << 1, 0, 0, 0,
          0, 2, 0, 0,
          0, 0, 3, 0,
          0, 0, 0, 4;
    cout << m1 << endl;
    //1-2. 向量生成
    Eigen::Vector3d vec1(1, 2, 3), vec2(2, 3, 4);
    cout << vec1 << endl << vec2 << endl;
    //1-3.Array生成
    Eigen::ArrayXd array1(3), array2(3);
    array1 << 1, 2, 3;
    array2 << 1, 2, 3;
    cout << array1 << endl << array2 << endl;
    //1-2. 特殊矩阵生成
    Eigen::MatrixXd m3(3, 3);//若为动态矩阵，则需括号，若为静态矩阵，则无须括号
    Eigen::MatrixXd m4(3, 3);
    Eigen::MatrixXd m5(3, 3);
    Eigen::MatrixXd m6(3, 3);
    m3 = Eigen::Matrix3d::Random();//随机矩阵
    m4 = Eigen::Matrix3d::Zero();
    m5 = Eigen::Matrix3d::Identity();//单位矩阵
    m6 = Eigen::Matrix3d::Ones();//全1矩阵
    cout << m3 << endl << endl;
    cout << m4 << endl << endl;
    cout << m5 << endl << endl;
    cout << m6 << endl << endl;
    //**2. 矩阵运算**//
    //2-1. 基本运算
    cout << " vec1.vec2 =\n " << vec1.dot(vec2) << endl; //点积 
    cout << "vec1 x vec2 =\n " << vec1.cross(vec2) << endl;    //叉积
    cout << "m1.sum() =\n " << m1.sum() <<  endl << endl;            // 各元素和
    cout << "m1.trace() =\n " << m1.trace() <<  endl << endl;          // 迹
    cout <<"m1.determinant() =\n " <<  m1.determinant() <<  endl << endl;    // 行列式
    cout << "m1.transpose() =\n " << m1.transpose() <<  endl << endl;      // 转置
    cout <<"m1.inverse() =\n " <<  m1.inverse() <<  endl << endl;        // 逆
    cout << "m1.adjoint() =\n " << m1.adjoint() <<  endl << endl;        // 伴随
    cout <<"m1.conjugate() =\n " <<  m1.conjugate() <<  endl << endl;      // 共轭
    //2-2. 块的操作
    //2-2-1. vector块操作
    cout << vec1.tail(2) << endl << endl;
    cout << vec1.head(2) << endl << endl;
    cout << vec1.segment(1, 2) << endl;//segment的索引是从0开始往后面推，所以(1, 2) = (2, 3)
    //2-2-2. matrix块操作
    cout << m1.block(1, 1, 2, 2) << endl;
    cout << m1.block<2, 2>(1, 1) << endl;
    //2-3. 类型的转换
    cout << m1.cast<int>() << endl << endl;    
    cout << m1.cast<float>() << endl << endl;    
    cout << m1.cast<double>() << endl << endl;    
    //**3. 矩阵的特征值 // 
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix4d> eigenSolver(m1.transpose()*m1);//实对称矩阵可以相似对角化
    if(eigenSolver.info() == Eigen::Success){
        cout << "eigenvalues = \n" << eigenSolver.eigenvalues() << endl;
        cout << "eigenvectors = \n" << eigenSolver.eigenvectors() << endl << endl;
    }
    //**4. 解方程** //
    Eigen::Matrix3d m2;
    Eigen::Vector3d vec3d(1, 2, 3);
    m2 << 1, 0, 0;
          0, 2, 0,
          0, 0, 3;
    m2.inverse();
    cout << "the result = " << m2*vec3d << endl;
    
}

```
## 3.实践
1. 四元数
```cpp
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
 
using namespace std;
using namespace Eigen;
 
int main(int argc, char** argv) {
  Quaterniond q1(0.35, 0.2, 0.3, 0.1), q2(-0.5, 0.4, -0.1, 0.2);
  q1.normalize();
  q2.normalize();
  Vector3d t1(0.3, 0.1, 0.1), t2(-0.1, 0.5, 0.3);
  Vector3d p1(0.5, 0, 0.2);
 
  Isometry3d T1w(q1), T2w(q2);
  T1w.pretranslate(t1);
  T2w.pretranslate(t2);
 
  Vector3d p2 = T2w * T1w.inverse() * p1;
  cout << endl << p2.transpose() << endl;
  return 0;
}
```
2. useEigen
3. useGeometry
   1. 例1
```cpp
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Geometry>
using namespace std;
using namespace Eigen;
void test(){
    //三个对象作为媒介
    AngleAxisd V(M_PI/4, Vector3d(0, 0, 1));
    Matrix3d R(V);
    Quaterniond q(V);
    //1.对旋转向量进行构造
    //1-1.方法1: V = R
    AngleAxisd V1(M_PI/4, Vector3d(0, 0, 1));
    V1 = R;
    cout << "v1.matrix() = \n" << V1.matrix() << endl;
    //1-2.方法2：V(R)
    AngleAxisd V2(R); 
    cout << "v2.matrix() = \n" << V2.matrix() << endl;
    
    //2.对四元数构造
    //2-1.方法1：直接法
    Quaterniond q1(cos(M_PI/8), 0 * sin(M_PI/8), 0 * sin(M_PI/8), 1 * sin(M_PI/8));
    cout << "q1.coeffs() = \n" << q1.coeffs() << endl;
    //2-2.方法2：利用旋转向量
    Quaterniond q2(V);
    cout << "q2.matrix() = \n" << q2.matrix() << endl;
    cout << "q2.coeffs() = \n" << q2.coeffs() << endl;
    cout << "q2.x() = " << q2.x() << endl;
    cout << "q2.y() = " << q2.y() << endl;
    cout << "q2.z() = " << q2.z() << endl;
    cout << "q2.w() = " << q2.w() << endl;
    //2-3.方法3:利用旋转矩阵
    Quaterniond q3(R);
    //2-3-1.planA
    cout << "q3.matrix1 = \n" <<  q3.matrix() << endl;
    //2-3-2.planB
    cout << "q3.matrix2 = \n" <<  q3.toRotationMatrix() << endl;
    
    //3.对旋转矩阵构造
    //3-1.利用旋转向量
    cout << "V.matrix = \n" << V.matrix() << endl;
    //3-2.利用四元数
    Matrix3d R1(q);
    cout << "R1(q) = \n" << R1 << endl;

    //4.对欧拉角进行构造
    cout << "R.eulerAngles(2,1,0) = \n" << R.eulerAngles(2,1,0) << endl;
    
    //5.对欧式矩阵构造
    Isometry3d T(R);
    Vector3d V3(1, 2, 3);
    T.pretranslate(V3);
    
    cout << "T.matrix = \n" <<  T.matrix() << endl;

    //6.对向量旋转
    Vector3d p(0, 0, 1);
    Vector3d vector_rotated;
    //6-1.利用旋转矩阵
    vector_rotated = R * p;
    //6-2.利用旋转向量
    vector_rotated = V * p;
    //6-3.利用四元数
    vector_rotated = q * p;
    //6-4.利用欧式矩阵
    vector_rotated = T * p;
    cout << "vector_rotated = \n" << vector_rotated << endl;
     
}

int main(){
    test();
}
```

![各类角度转换](../pictures/各类角度转换.png)


2. visualizeGeometry
```cpp

#include <iostream>
#include <iomanip>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>
using namespace Eigen;

#include <pangolin/pangolin.h>

struct RotationMatrix
{
    Matrix3d matrix = Matrix3d::Identity();
};

ostream& operator << ( ostream& out, const RotationMatrix& r ) 
{
    out.setf(ios::fixed);
    Matrix3d matrix = r.matrix;
    out<<'=';
    out<<"["<<setprecision(2)<<matrix(0,0)<<","<<matrix(0,1)<<","<<matrix(0,2)<<"],"
    << "["<<matrix(1,0)<<","<<matrix(1,1)<<","<<matrix(1,2)<<"],"
    << "["<<matrix(2,0)<<","<<matrix(2,1)<<","<<matrix(2,2)<<"]";
    return out;
}

istream& operator >> (istream& in, RotationMatrix& r )
{
    return in;
}

struct TranslationVector
{
    Vector3d trans = Vector3d(0,0,0);
};

ostream& operator << (ostream& out, const TranslationVector& t)
{
    out<<"=["<<t.trans(0)<<','<<t.trans(1)<<','<<t.trans(2)<<"]";
    return out;
}

istream& operator >> ( istream& in, TranslationVector& t)
{
    return in;
}

struct QuaternionDraw
{
    Quaterniond q;
};

ostream& operator << (ostream& out, const QuaternionDraw quat )
{
    auto c = quat.q.coeffs();
    out<<"=["<<c[0]<<","<<c[1]<<","<<c[2]<<","<<c[3]<<"]";
    return out;
}

istream& operator >> (istream& in, const QuaternionDraw quat)
{
    return in;
}

int main ( int argc, char** argv )
{
    pangolin::CreateWindowAndBind ( "visualize geometry", 1000, 600 );
    glEnable ( GL_DEPTH_TEST );
    pangolin::OpenGlRenderState s_cam (
        pangolin::ProjectionMatrix ( 1000, 600, 420, 420, 500, 300, 0.1, 1000 ),
        pangolin::ModelViewLookAt ( 3,3,3,0,0,0,pangolin::AxisY )
    );
    
    const int UI_WIDTH = 500;
    
    pangolin::View& d_cam = pangolin::CreateDisplay().SetBounds(0.0, 1.0, pangolin::Attach::Pix(UI_WIDTH), 1.0, -1000.0f/600.0f).SetHandler(new pangolin::Handler3D(s_cam));
    
    // ui
    pangolin::Var<RotationMatrix> rotation_matrix("ui.R", RotationMatrix());
    pangolin::Var<TranslationVector> translation_vector("ui.t", TranslationVector());
    pangolin::Var<TranslationVector> euler_angles("ui.rpy", TranslationVector());
    pangolin::Var<QuaternionDraw> quaternion("ui.q", QuaternionDraw());
    pangolin::CreatePanel("ui")
        .SetBounds(0.0, 1.0, 0.0, pangolin::Attach::Pix(UI_WIDTH));
    
    while ( !pangolin::ShouldQuit() )
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        d_cam.Activate( s_cam );
        
        pangolin::OpenGlMatrix matrix = s_cam.GetModelViewMatrix();
        Matrix<double,4,4> m = matrix;
        // m = m.inverse();
        RotationMatrix R; 
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                R.matrix(i,j) = m(j,i);
        rotation_matrix = R;
        
        TranslationVector t;
        t.trans = Vector3d(m(0,3), m(1,3), m(2,3));
        t.trans = -R.matrix*t.trans;
        translation_vector = t;
        
        TranslationVector euler;
        euler.trans = R.matrix.transpose().eulerAngles(2,1,0);
        euler_angles = euler;
        
        QuaternionDraw quat;
        quat.q = Quaterniond(R.matrix);
        quaternion = quat;
        
        glColor3f(1.0,1.0,1.0);
        
        pangolin::glDrawColouredCube();
        // draw the original axis 
        glLineWidth(3);
        glColor3f ( 0.8f,0.f,0.f );
        glBegin ( GL_LINES );
        glVertex3f( 0,0,0 );
        glVertex3f( 10,0,0 );
        glColor3f( 0.f,0.8f,0.f);
        glVertex3f( 0,0,0 );
        glVertex3f( 0,10,0 );
        glColor3f( 0.2f,0.2f,1.f);
        glVertex3f( 0,0,0 );
        glVertex3f( 0,0,10 );
        glEnd();
        
        pangolin::FinishFrame();
    }
}
```
## 3.课后习题：
1. 验证旋转矩阵是正交矩阵
2. 罗德里格斯公式推导
3. 四元数旋转某个点后仍然是虚四元数
4. 旋转矩阵，轴角，欧拉角， 四元数的关系
5. 假设我有一个大的 Eigen 矩阵，我想把它的左上角 3 × 3 的块取出来，然后赋值为I3×3 。请编程实现此事
```cpp
#include <iostream>
#include "/usr/include/eigen3/Eigen/Dense"
using namespace std;
using namespace Eigen;
 
int main()
{
    Matrix4d matrix_44 = Matrix4d::Constant(0.5);
    cout << "Here is a matrix:\n" << matrix_44 << endl;
    Matrix3d matrix_33 = Matrix3d::Constant(0.1);
    matrix_44.block(0,0,3,3) = matrix_33;
    cout << "左上角３×３的块取出来赋值为Matrix3_3\n" << matrix_44 << endl;
    return 0;
}
```
```cmake
cmake_minimum_required(VERSION 2.8)
project(visualizegeometry)
set(CMAKE_CXX_FLAGS "-std=c++14")#此处要改成14，不要写11

# 添加Eigen头文件
include_directories( "/usr/include/eigen3" )

# 添加Pangolin依赖
find_package( Pangolin )
include_directories( ${Pangolin_INCLUDE_DIRS} )

set(CMAKE_BUILD_TYPE "Debug")
add_executable(visualizegeometry main.cpp)
target_link_libraries( visualizegeometry ${Pangolin_LIBRARIES} )

install(TARGETS visualizegeometry RUNTIME DESTINATION bin)
```
6. 设有小萝卜一号和小萝卜二号位于世界坐标系中。小萝卜一号的位姿为：q 1 =
[0.35, 0.2, 0.3, 0.1], t 2 = [0.3, 0.1, 0.1] T （q 的第一项为实部。请你把 q 归一化后再
进行计算）
。这里的 q 和 t 表达的是 T cw ，也就是世界到相机的变换关系。小萝卜二号的位姿为 q 2 = [−0.5, 0.4, −0.1, 0.2], t = [−0.1, 0.5, 0.3] T 。现在，小萝卜一号看到
某个点在自身的坐标系下，坐标为 p = [0.5, 0, 0.2] T ，求该向量在小萝卜二号坐标系
下的坐标。请编程实现此事。
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <Eigen/Core>
#include <Eigen/Geometry>
 
using namespace std;
using namespace Eigen;
 
int main(int argc, char** argv) {
  Quaterniond q1(0.35, 0.2, 0.3, 0.1), q2(-0.5, 0.4, -0.1, 0.2);
  q1.normalize();
  q2.normalize();
  Vector3d t1(0.3, 0.1, 0.1), t2(-0.1, 0.5, 0.3);
  Vector3d p1(0.5, 0, 0.2);
 
  Isometry3d T1w(q1), T2w(q2);
  T1w.pretranslate(t1);
  T2w.pretranslate(t2);
 
  Vector3d p2 = T2w * T1w.inverse() * p1;
  cout << endl << p2.transpose() << endl;
  return 0;
}
```
# 3.第三讲
## 3-1.Sophus的安装
[Sophus1](https://blog.csdn.net/LW20211020/article/details/124204127)
[Sophus2](https://blog.csdn.net/mine_1/article/details/117703483)
[解决无法编译成功的问题](https://blog.csdn.net/King91701/article/details/120184602?spm=1001.2101.3001.6650.12&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-12-120184602-blog-117703483.pc_relevant_aa&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-12-120184602-blog-117703483.pc_relevant_aa&utm_relevant_index=12)
1. sophus的使用
```cpp
#include <iostream>
#include <cmath>
using namespace std; 

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "sophus/so3.h"
#include "sophus/se3.h"

int main( int argc, char** argv )
{
    // 沿Z轴转90度的旋转矩阵
    Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI/2, Eigen::Vector3d(0,0,1)).toRotationMatrix();
    
    Sophus::SO3 SO3_R(R);               // Sophus::SO(3)可以直接从旋转矩阵构造
    Sophus::SO3 SO3_v( 0, 0, M_PI/2 );  // 亦可从旋转向量构造
    Eigen::Quaterniond q(R);            // 或者四元数
    Sophus::SO3 SO3_q( q );
    // 上述表达方式都是等价的
    // 输出SO(3)时，以so(3)形式输出
    cout<<"SO(3) from matrix: "<<SO3_R<<endl;
    cout<<"SO(3) from vector: "<<SO3_v<<endl;
    cout<<"SO(3) from quaternion :"<<SO3_q<<endl;
    
    // 使用对数映射获得它的李代数
    Eigen::Vector3d so3 = SO3_R.log();
    cout<<"so3 = "<<so3.transpose()<<endl;
    // hat 为向量到反对称矩阵
    cout<<"so3 hat=\n"<<Sophus::SO3::hat(so3)<<endl;
    // 相对的，vee为反对称到向量
    cout<<"so3 hat vee= "<<Sophus::SO3::vee( Sophus::SO3::hat(so3) ).transpose()<<endl; // transpose纯粹是为了输出美观一些
    
    // 增量扰动模型的更新
    Eigen::Vector3d update_so3(1e-4, 0, 0); //假设更新量为这么多
    Sophus::SO3 SO3_updated = Sophus::SO3::exp(update_so3)*SO3_R;
    cout<<"SO3 updated = "<<SO3_updated<<endl;
    
    /********************萌萌的分割线*****************************/
    cout<<"************我是分割线*************"<<endl;
    // 对SE(3)操作大同小异
    Eigen::Vector3d t(1,0,0);           // 沿X轴平移1
    Sophus::SE3 SE3_Rt(R, t);           // 从R,t构造SE(3)
    Sophus::SE3 SE3_qt(q,t);            // 从q,t构造SE(3)
    cout<<"SE3 from R,t= "<<endl<<SE3_Rt<<endl;
    cout<<"SE3 from q,t= "<<endl<<SE3_qt<<endl;
    // 李代数se(3) 是一个六维向量，方便起见先typedef一下
    typedef Eigen::Matrix<double,6,1> Vector6d;
    Vector6d se3 = SE3_Rt.log();
    cout<<"se3 = "<<se3.transpose()<<endl;
    // 观察输出，会发现在Sophus中，se(3)的平移在前，旋转在后.
    // 同样的，有hat和vee两个算符
    cout<<"se3 hat = "<<endl<<Sophus::SE3::hat(se3)<<endl;
    cout<<"se3 hat vee = "<<Sophus::SE3::vee( Sophus::SE3::hat(se3) ).transpose()<<endl;
    
    // 最后，演示一下更新
    Vector6d update_se3; //更新量
    update_se3.setZero();
    Sophus::SE3 SE3_updated = Sophus::SE3::exp(update_se3)*SE3_Rt;
    cout<<"SE3 updated = "<<endl<<SE3_updated.matrix()<<endl;
    
    return 0;
}
```
```cmake
cmake_minimum_required( VERSION 2.8 )
project( useSophus )

# 为使用 sophus，您需要使用find_package命令找到它
find_package( Sophus REQUIRED )
message(STATUS ${Sophus_LIBRARISE})
include_directories( ${Sophus_INCLUDE_DIRS} )
include_directories( "/usr/include/eigen3" )
add_executable( useSophus useSophus.cpp )
set(Sophus_LIBRARIES libSophus.so)
#安装Sophus会有libSophus.so文件，cmake没有连接到Sophus_LIBRARIES上
target_link_libraries( useSophus ${Sophus_LIBRARIES} )
```
## 3-2.项目1
```cpp
//以下所有的Eigen::aligned_allocator<Sophus::SE3>都可以去掉
#include <sophus/se3.h>//针对于se3
#include <string>
#include <iostream>
#include <fstream>
#include <Eigen/Core>
//下面3个文件主要是面对usleep(5000)报错的 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// need pangolin for plotting trajectory
#include <pangolin/pangolin.h>

using namespace std;

// path to trajectory file
string trajectory_file = "/home/kim-james/ROS_Space/SLAM_ws/slam_test/ch3/trajectory/trajectory.txt";

// function for plotting trajectory, don't edit this code
// start point is red and end point is blue
void DrawTrajectory(vector<Sophus::SE3>);

int main(int argc, char **argv) {

    vector<Sophus::SE3> poses;
    //只有加入了Eigen::aligned_allocator<Sophus::SE3>才可以允许vector加入SE3，但是可以去掉
    // 定义一个文件读取器
    fstream file(trajectory_file); 
    double time, tx, ty, tz, qx, qy, qz, qw; 
    //按照time, translation, quaternion顺序读取
    //若是eof()返回0，说明数据没读完,所以!0 = 1
    while (!file.eof()){
        file >> time >> 
        tx >> ty >> tz >> 
        qx >> qy >> qz >> qw; 
        //处理读取的数据
        //处理平移
        Eigen::Vector3d t(tx, ty, tz);
        //处理四元数(注意顺序)
        Eigen::Quaterniond q(qw, qx, qy, qy);
        //注意归一化
        q.normalize();
        //将四元数转换为旋转矩阵
        Eigen::Matrix3d R(q);
        //存入到Sophus对应的SE3 -> T,转化为变换矩阵
        Sophus::SE3 SE3_from_Eigen(R, t);
        poses.push_back(SE3_from_Eigen); 
    }
    cout << "the number of points = " << poses.size() << endl;
    DrawTrajectory(poses);
    return 0;
}

/*******************************************************************************************/
void DrawTrajectory(vector<Sophus::SE3> poses) {
    if (poses.empty()) {
        cerr << "Trajectory is empty!" << endl;
        return;
    }

    // create pangolin window and plot the trajectory
    pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );

    pangolin::View &d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -1024.0f / 768.0f)
            .SetHandler(new pangolin::Handler3D(s_cam));


    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glLineWidth(2);
        for (size_t i = 0; i < poses.size() - 1; i++) {
            glColor3f(1 - (float) i / poses.size(), 0.0f, (float) i / poses.size());
            glBegin(GL_LINES);
            auto p1 = poses[i], p2 = poses[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();
        }
        pangolin::FinishFrame();
        usleep(5000);   // sleep 5 ms
    }

}
```
```cmake
cmake_minimum_required(VERSION 3.0)
project(trajectory)
# 在cmake脚本中，设置编译选项可以通过add_compile_options命令，也可以通过set命令修改CMAKE_CXX_FLAGS或CMAKE_C_FLAGS。
# add_compile_options(-std=c++11) # 这句话的意思是在make时让编译器（g++）自动添加C++11的性质 -> 设置编译选项

option(USE_UBUNTU_20 "Set to ON if you are using Ubuntu 20.04" ON)
find_package(Pangolin REQUIRED)
if(USE_UBUNTU_20)
    message("You are using Ubuntu 20.04, fmt::fmt will be linked")
    find_package(fmt REQUIRED)
    set(FMT_LIBRARIES fmt::fmt)
endif()
include_directories(${Pangolin_INCLUDE_DIRS})
add_executable(draw_trajectory draw_trajectory.cpp)
target_link_libraries(draw_trajectory ${FMT_LIBRARIES})
target_link_libraries(draw_trajectory ${Pangolin_LIBRARIES})

set(CMAKE_BUILD_TYPE "Release")
set(Sophus_LIBRARIES  "/usr/local/lib/libSophus.so")
find_package(Sophus REQUIRED)
include_directories( ${Sophus_INCLUDE_DIRS} )
target_link_libraries(draw_trajectory ${Sophus_LIBRARIES})


使用方法：
add_executable(pub pub.cpp)
set(roscpp_LIBRARIES "/../../xxxx.so")
find_package(roscpp REQUIRED)#find_package和include_directories紧密联系
include_directories(${roscpp_INCLUDE_DIRS})
target_link_libraries(pub ${roscpp_LIBRARIES})#将变量用$括起来
```
1. cmake的使用
```cmake
1. 使用方法：
add_executable(pub pub.cpp)
set(roscpp_LIBRARIES "/../../xxxx.so")
find_package(roscpp REQUIRED)#find_package和include_directories紧密联系
include_directories(${roscpp_INCLUDE_DIRS})
target_link_libraries(pub ${roscpp_LIBRARIES})#将变量用$括起来

2. message是指输出变量值：
IN ===> message("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
OUT ===> CMAKE_SOURCE_DIR = /xxxx/xxx

```
## 3-3.项目2
![群](./../pictures/群.jpg)
![转换关系](./../pictures/sophus.png)
*注意在使用这个文件时，SE3 = SE3d, SO3 = SO3d, h = hpp*
```cmake
cmake_minimum_required( VERSION 2.8 )
project( useSophus )

# 为使用 sophus，您需要使用find_package命令找到它
find_package( Sophus REQUIRED )
include_directories( ${Sophus_INCLUDE_DIRS} )#添加Sophus库
include_directories( "/usr/include/eigen3" )#添加Eigen库
add_executable( useSophus useSophus.cpp )#添加可执行文件
set(Sophus_LIBRARIES libSophus.so)#设置变量
#定义了一个变量Sophus，他的值为libSophus.so
target_link_libraries( useSophus ${Sophus_LIBRARIES} )
```
```cpp
#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "sophus/so3.h"
#include "sophus/se3.h"
using namespace std; 
int main(){
    /* SO3的使用*/
    //1.构造SO3
    Eigen::AngleAxisd V(M_PI/2, Eigen::Vector3d(0, 0, 1));
    Eigen::Quaterniond q(V);
    Eigen::Matrix3d R(V);
    //通过旋转向量，旋转矩阵和四元数
    Sophus::SO3 SO3_V(0, 0, M_PI/2);
    Sophus::SO3 SO3_R(R);
    Sophus::SO3 SO3_q(q);
    cout << "so3 from V = \n" << SO3_V << endl;
    cout << "SO3 from V = \n" << SO3_V.matrix() << endl;
    cout << "so3 from R = \n" << SO3_R << endl;
    cout << "so3 from q = \n" << SO3_q << endl;

    //2.对数映射和 hat,vee的转换
    Eigen::Vector3d so3 = SO3_R.log();
    cout << "so3 hat = \n" << Sophus::SO3::hat(so3) << endl;
    cout << "so3 hat vee = \n" << Sophus::SO3::vee(Sophus::SO3::hat(so3)) << endl;
    
    //3.扰动模型
    Eigen::Vector3d updated_V(1, 0, 0);
    Sophus::SO3 SO3_updated = Sophus::SO3::exp(updated_V) * SO3_R;
    cout << " SO3_updated = \n" << SO3_updated << endl;       
    cout << " SO3_updated.matrix = \n" << SO3_updated.matrix() << endl;       
    /*SE3的使用*/
    //1.构造SE3
    Eigen::Vector3d t(1, 0, 0);
    Sophus::SE3 SE3_R(R, t);
    Sophus::SE3 SE3_q(q, t);
    cout << "se3 from R,t = \n" << SE3_R << endl;
    cout << "SE3 from R,t = \n" << SE3_R.matrix() << endl;
    cout << "se3 from R,t = \n" << SE3_q << endl;
    cout << "SE3 from R,t = \n" << SE3_q.matrix() << endl;
    //2.对数映射和hat vee
    
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    Vector6d se3 = SE3_R.log();//对数映射
    cout << "se3  = \n " <<  se3 << endl;
    cout << "se3 hat =  \n" <<  Sophus::SE3::hat(se3) << endl;
    cout << "se3 hat vee =  \n" <<  Sophus::SE3::vee(Sophus::SE3::hat(se3)) << endl;

    //3.扰动
    Vector6d v1;
    v1 << 1, 0, 0, 0, 0, 0;
    Sophus::SE3  SE3_updated = Sophus::SE3::exp(v1) * SE3_R;
    cout << "SE3_updated  = \n" << SE3_updated << endl;
    cout << "SE3_updated.matrix = \n" << SE3_updated.matrix() << endl;

}
```
```cpp
hus_test/build   master ✚  ./demo01
so3 from V = 
     0      0 1.5708

SO3 from V = 
          0          -1           0
          1           0           0
          0           0           1
so3 from R = 
     0      0 1.5708

so3 from q = 
     0      0 1.5708

so3 hat = 
      0 -1.5708       0
 1.5708       0      -0
     -0       0       0
so3 hat vee = 
     0
     0
1.5708
 SO3_updated = 
 0.779333 -0.779333   1.42656

 SO3_updated.matrix = 
    0           -1            0
    0.540302     0            0
    0.841471     0     0.540302
se3 from R,t = 
      0      0 1.5708
1 0 0

SE3 from R,t = 
          0          -1           0           1
          1           0           0           0
          0           0           1           0
          0           0           0           1
se3 from R,t = 
     0      0 1.5708
1 0 0

SE3 from R,t = 
          0          -1           0           1
          1           0           0           0
          0           0           1           0
          0           0           0           1
se3  = 
  0.785398
-0.785398
        0
        0
        0
   1.5708
se3 hat =  
        0   -1.5708         0  0.785398
   1.5708         0        -0 -0.785398
       -0         0         0         0
        0         0         0         0
se3 hat vee =  
 0.785398
-0.785398
        0
        0
        0
   1.5708
SE3_updated  = 
     0      0 1.5708
2 0 0

SE3_updated.matrix = 
          0          -1           0           2
          1           0           0           0
          0           0           1           0
          0           0           0           1
```
*方法2*
```cpp
#include <iostream>
#include "sophus/se3.h"
#include "sophus/so3.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
using namespace std;
void printSO3(){
    //1.SO3的构造
    Eigen::AngleAxisd V(M_PI/2, Eigen::Vector3d(0, 0, 1));
    Eigen::Quaterniond q(V);    
    Eigen::Matrix3d R(V);
    Sophus::SO3 SO3_R(R);
    Sophus::SO3 SO3_q(q);
    cout << "SO3_R = \n" << SO3_R << endl;
    cout << "SO3_R.matrix = \n" << SO3_R.matrix() << endl;
    cout << "SO3_R = \n" << SO3_R << endl;
    cout << "SO3_R.matrix = \n" << SO3_R.matrix() << endl;
    //2.so3 and hat&vee
    Eigen::Vector3d so3 = SO3_R.log();
    cout << "so3 = \n" << SO3_R.log() << endl;
    cout << "so3 hat = \n" << Sophus::SO3::hat(so3) << endl;
    cout << "so3 hat vee = \n" << Sophus::SO3::vee(Sophus::SO3::hat(so3)) << endl;
    //3.扰动
    Eigen::Vector3d V1(0, 0, 1.57);
    cout << "SO3 = \n" << Sophus::SO3::exp(V1) << endl;//旋转向量
    cout << "SO3.matrix() = \n" << Sophus::SO3::exp(V1).matrix() << endl;//旋转矩阵
    Sophus::SO3 SO3_updated = Sophus::SO3::exp(V1) * SO3_R;
    cout << "SO3_updated = \n" << SO3_updated << endl;//扰动后的向量
    cout << "SO3_updated.matrix = \n" << SO3_updated.matrix() << endl;//扰动后的矩阵

}
void printSE3(){
    //1.SE3的构造
    Eigen::AngleAxisd V(M_PI/2, Eigen::Vector3d(0, 0, 1));
    Eigen::Quaterniond q(V);
    Eigen::Vector3d t(0, 0, 1);    
    Eigen::Matrix3d R(V);
    Sophus::SE3 SE3_R(R, t);
    Sophus::SE3 SE3_q(q, t);
    cout << "SE3_R = \n" << SE3_R << endl;
    cout << "SE3_R.matrix = \n" << SE3_R.matrix() << endl;
    cout << "SE3_q = \n" << SE3_q << endl;
    cout << "SE3_q.matrix = \n" << SE3_q.matrix() << endl;
    //2.so3 and hat&vee
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    Vector6d se3 = SE3_R.log();
    cout << "se3 = \n" << SE3_R.log() << endl;
    cout << "se3 hat = \n" << Sophus::SE3::hat(se3) << endl;
    cout << "se3 hat vee = \n" << Sophus::SE3::vee(Sophus::SE3::hat(se3)) << endl;
    //3.扰动
    Vector6d V1;
    V1.setZero();
    V1(0, 0) = 1;
    cout << "SE3 = \n" << Sophus::SE3::exp(V1) << endl;//变换向量
    cout << "SE3.matrix() = \n" << Sophus::SE3::exp(V1).matrix() << endl;//变换矩阵
    Sophus::SE3 SE3_updated = Sophus::SE3::exp(V1) * SE3_R;
    cout << "SE3_updated = \n" << SE3_updated << endl;//扰动后的向量
    cout << "SE3_updated.matrix = \n" << SE3_updated.matrix() << endl;//扰动后的矩阵

}
int main(){
    cout << "***********SO3************" << endl;
    printSO3();
    cout << "***********SE3************" << endl;
    printSE3();
}
```
## 3-3.pangolin的使用
模板
```cpp
#include <iostream>
#include <pangolin/pangolin.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <vector>
#include <string>
#include "sophus/se3.h"
using namespace std;

int main()
{
    pangolin::CreateWindowAndBind("Main",640,480);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(640,480,420,420,320,320,0.2,100),
        pangolin::ModelViewLookAt(2,0,2, 0,0,0, pangolin::AxisY)
    );

    pangolin::Handler3D handler(s_cam); //交互相机视图句柄
    pangolin::View& d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f/480.0f)
            .SetHandler(&handler);
    while( !pangolin::ShouldQuit() )
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);
 /*-------- .绘图  --------*/
    /*---------------*/

        pangolin::FinishFrame();
    }
    
    return 0;
}
```
1. 使用方法1
[链接](https://blog.csdn.net/u011341856/article/details/107199600?spm=1001.2101.3001.6650.8&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-8-107199600-blog-65441315.pc_relevant_paycolumn_v3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-8-107199600-blog-65441315.pc_relevant_paycolumn_v3&utm_relevant_index=11)
```cpp
//以下所有的Eigen::aligned_allocator<Sophus::SE3>都可以去掉
#include <sophus/se3.h>//针对于se3
#include <string>
#include <iostream>
#include <fstream>
#include <Eigen/Core>
//下面3个文件主要是面对usleep(5000)报错的 
#include <unistd.h>
#include <stdio.h>

// need pangolin for plotting trajectory
#include <pangolin/pangolin.h>

using namespace std;

// path to trajectory file
string trajectory_file = "/home/kim-james/ROS_Space/SLAM_ws/slam_test/ch3/trajectory/trajectory.txt";

// function for plotting trajectory, don't edit this code
// start point is red and end point is blue
void DrawTrajectory(vector<Sophus::SE3>);
int main(int argc, char **argv) {

    vector<Sophus::SE3> poses;//poses为旋转矩阵的容器
    //只有加入了Eigen::aligned_allocator<Sophus::SE3>才可以允许vector加入SE3，但是可以去掉
    // 定义一个文件读取器
    fstream file(trajectory_file); 
    double time, tx, ty, tz, qx, qy, qz, qw; 
    //按照time, translation, quaternion顺序读取
    //若是eof()返回0，说明数据没读完,所以!0 = 1,eof() = end of file
    while (!file.eof()){
        file >> time >> 
        tx >> ty >> tz >> 
        qx >> qy >> qz >> qw; 
        //处理读取的数据
        //处理平移
        Eigen::Vector3d t(tx, ty, tz);
        //处理四元数(注意顺序)
        Eigen::Quaterniond q(qw, qx, qy, qz);
        //注意归一化
        q.normalize();
        //将四元数转换为旋转矩阵
        Eigen::Matrix3d R(q);
        //存入到Sophus对应的SE3 -> T,转化为变换矩阵
        Sophus::SE3 SE3_from_Eigen(R, t);
        poses.push_back(SE3_from_Eigen); //传入的是SE3的vector
    }
    cout << "the number of points = " << poses.size() << endl;//points = 120
    DrawTrajectory(poses);//先声明后使用
    return 0;
}

/*******************************************************************************************/
void DrawTrajectory(vector<Sophus::SE3> poses) {
    
    if (poses.empty()) {
        cerr << "Trajectory is empty!" << endl;
        return;
    }

    // create pangolin window and plot the trajectory
    pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );

    pangolin::View &d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -1024.0f / 768.0f)
            .SetHandler(new pangolin::Handler3D(s_cam));

    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glLineWidth(2);
        //size_t: size of type 
        for (int i = 0; i < poses.size() - 1; i++) {
            glColor3f(1 - (float)i / poses.size(), 0.0f, (float) i / poses.size());//颜色变化的算法
            /*
            1.(float)i：将i转成float类型
            2.poses.size()为vector的大小
            2.auto = vector<Sophus::SE3>
            */
            glBegin(GL_LINES);//画线开始
            auto p1 = poses[i], p2 = poses[i + 1];
            //vertex为顶点
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);//p1点的(x, y, z)坐标
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);//p2点的(x, y, z)坐标
            glEnd();//画线结束，将p1和p2连成一条线
        }
        pangolin::FinishFrame();//绘图
    }
}
```
2. 基本用法
```cpp
#include <pangolin/pangolin.h>
#include <iostream>
int main()
{
    // 1.创建名称为“Main”的GUI窗口，尺寸为640×640
    pangolin::CreateWindowAndBind("Main",640,480);
    // 2.启动深度测试，开启这个功能后，窗口只会绘制面朝相机的那一面像素，要使用3D可视化就要开启这个功能
    glEnable(GL_DEPTH_TEST);
    //3.打开颜色混合，把某一像素位置原来的颜色和将要画上去的颜色通过某种方式混合，实现特殊的效果
    glEnable(GL_BLEND);
    //4.紧跟glEnable(GL_BLEND)表示颜色的混合方式
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /*5.创建一个观察相机视图，用真实的相机来模拟真实的世界
    5-1.ProjectMatrix(int h, int w, int fu, int fv, int cu, int cv, int znear, int zfar)
    依次是观察相机的图像高度，宽度，4个内参，以及最近和最远视距
    5-2.ModelViewLookAt(double x, double y, double z,double lx, double ly, double lz, AxisDirection Up)
    x,y,z为相机所在的位置;lx,ly,lz为相机所看视点的位置;AxixDirection UP为相机轴的方向
    以自己脑袋为例，前3个参数为脑袋的位置，4-6参数为眼睛所看的方向, 最后参数为头顶的朝向
    */
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(640,480,420,420,320,320,0.2,100),
        pangolin::ModelViewLookAt(2,0,2, 0,0,0, pangolin::AxisY)
    );

    //6.创建相机视图句柄，需要用它来显示前面设置的相机拍摄的内容
    pangolin::Handler3D handler(s_cam); //交互相机视图句柄
    //7.进行显示设置，SetBounds前4个参数为视图在视窗中的范围(下，上，左，右)，最后一个参数为长宽比
    //(0, 1, 0, 1)：第一个0表示显示的拍摄窗口的下边在整个GUI的最下面，第二个参数1表示上边在GUI的最上面，中间就用0.5
    pangolin::View& d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f/480.0f)
            .SetHandler(&handler);
    //8.检测是否关闭OpenGL窗口
    while( !pangolin::ShouldQuit() )
    {
        //9.清空颜色和深度缓存
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //10.激活并设置状态矩阵
        d_cam.Activate(s_cam);
 /*--------  11.绘图  --------*/
        //11-1.在原点创建一个立方体对象
        pangolin::glDrawColouredCube();
        
        //11-2.绘制点
        //点的大小
        glPointSize(30.0);//
        //开始画点
        glBegin(GL_POINTS);//后面s不能掉
        //设置点1的颜色:rgb, float类型
        glColor3f(0, 1, 0);
        //设置点1的坐标， 3维float类型
        glVertex3f(0 , 0, 0);
        //设置点2的颜色,坐标
        glColor3f(1, 0, 0);
        glVertex3f(0 , 1, 0);
        //结束画点
        glEnd();
        //11-3.绘制线段
        //11-3-1.设置大小
        glLineWidth(4);
        //11-3-2.开始画线条
        glBegin(GL_LINES);
        //设置颜色
        glColor3f(0, 1, 0);
        //设置起点
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);
        //结束画线
        glEnd();
        
        //11-3.绘制折线
        glLineWidth(2);
        //  开始
        glBegin ( GL_LINE_STRIP );
        //  设置颜色
        glColor3f(0, 1, 0);
        //  设置折点坐标
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);
        glVertex3f(1, 1, 0);
        //  结束
        glEnd();

        //11-4.绘制封闭的不规则图形
        //  设置大小
        glLineWidth(2);
        //  开始
        glBegin ( GL_LINE_LOOP );
        //  设置颜色
        glColor3f(0, 1, 0);
        //  设置折点坐标
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);
        glVertex3f(1, 1, 0);
        //  结束
        glEnd();
        //11.运行帧循环以推进窗口事件
        pangolin::FinishFrame();
    }
    
    return 0;
}
```
3. 画函数图像
```cpp
#include <iostream>
#include <pangolin/pangolin.h>

int main()
{
  // Create OpenGL window in single line
  pangolin::CreateWindowAndBind("Main",640,480);

  // Data logger object
  pangolin::DataLog log;

  // Optionally add named labels
  std::vector<std::string> labels;
  labels.push_back(std::string("sin(t)"));
  labels.push_back(std::string("cos(t)"));
  labels.push_back(std::string("sin(t)+cos(t)"));
  log.SetLabels(labels);

  const float tinc = 0.01f;

  // OpenGL 'view' of data. We might have many views of the same data.
  pangolin::Plotter plotter(&log,0.0f,4.0f*(float)M_PI/tinc,-4.0f,4.0f,(float)M_PI/(4.0f*tinc),0.5f);
  plotter.SetBounds(0.0, 1.0, 0.0, 1.0);
  plotter.Track("$i");//坐标轴自动滚动

  // Add some sample annotations to the plot（为区域着色）
  plotter.AddMarker(pangolin::Marker::Vertical,   50*M_PI, pangolin::Marker::LessThan, pangolin::Colour::Blue().WithAlpha(0.2f) );
  plotter.AddMarker(pangolin::Marker::Horizontal,   3, pangolin::Marker::GreaterThan, pangolin::Colour::Red().WithAlpha(0.2f) );
  plotter.AddMarker(pangolin::Marker::Horizontal,    3, pangolin::Marker::Equal, pangolin::Colour::Green().WithAlpha(0.2f) );

  pangolin::DisplayBase().AddDisplay(plotter);

  float t = 0;

  // Default hooks for exiting (Esc) and fullscreen (tab).
  while( !pangolin::ShouldQuit() )
  {
    //清空颜色和缓存
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    log.Log(sin(t),cos(t),sin(t)+cos(t));
    t += tinc;

    // Render graph, Swap frames and Process Events
    pangolin::FinishFrame();
  }

  return 0;
}
```
4. GUI
```cpp
#include <pangolin/pangolin.h>

void function(){
    std::cout << "Hello pangolin" << std::endl;
}

int main() {
    pangolin::CreateWindowAndBind("Main",640,480);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(640,480,420,420,320,320,0.2,100),
            pangolin::ModelViewLookAt(2,0,2, 0,0,0, pangolin::AxisY)
    );

    pangolin::Handler3D handler(s_cam);
    pangolin::View& d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f/480.0f)
            .SetHandler(&handler);

    pangolin::CreatePanel("ui").SetBounds(0.0, 1.0, 0.0, pangolin::Attach::Pix(180));//创建

    pangolin::Var<bool> a_button("ui.A_Button", false, false);//设置一个按钮，默认值为false，最后一个false表示按钮形式
    pangolin::Var<double> a_double("ui.A_Double", 3, 0, 5);//设置一个double的、可拖动变换值的玩意(不知道咋形容)！
    pangolin::Var<int> a_int("ui.A_Int", 2, 0, 5);//设置一个int的、可拖动变换值的玩意
    pangolin::Var<std::function<void(void)>> reset("ui.Reset", function);//设置一个按钮，用于调用function函数

    while( !pangolin::ShouldQuit() )
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);

        if (pangolin::Pushed(a_button)){//如果a_button按钮被点，就运行if里面的语句
            std::cout << "You tough a_buttom" << std::endl;
            a_double = 0;
            a_int = 0;
        }

        glColor3f(1.0, 1.0, 1.0);
        pangolin::glDrawColouredCube();

        pangolin::FinishFrame();
    }

    return 0;
}
```
## 3-4.计算轨迹误差

**2阶范数就是向量的模**
```cpp
#include <sophus/se3.h>//针对于se3
#include <string>
#include <iostream>
#include <fstream>
#include <Eigen/Core>
#include <unistd.h>
#include <stdio.h>
#include <pangolin/pangolin.h>
using namespace std;

// path to trajectory file
string trajectory_est= "/home/kim-james/ROS_Space/SLAM_ws/slam_test/ch3/trajectory/estimated.txt";
string trajectory_ground= "/home/kim-james/ROS_Space/SLAM_ws/slam_test/ch3/trajectory/groundtruth.txt";

// start point is red and end point is blue
void DrawTrajectory(vector<Sophus::SE3> poses_est, vector<Sophus::SE3> poses_gd);
int main(int argc, char **argv) {
    //1.组织数据
    vector<Sophus::SE3> poses_est;//poses为旋转矩阵的容器
    vector<Sophus::SE3> poses_gd;//poses为旋转矩阵的容器

    fstream file_est(trajectory_est); 
    fstream file_ground(trajectory_ground); 
    double time, tx, ty, tz, qx, qy, qz, qw; 
    //按照time, translation, quaternion顺序读取
    //若是eof()返回0，说明数据没读完,所以!0 = 1,eof() = end of file
    while (!file_est.eof()){
        file_est >> time >> 
        tx >> ty >> tz >> 
        qx >> qy >> qz >> qw; 
        //处理读取的数据
        //处理平移
        Eigen::Vector3d t(tx, ty, tz);
        //处理四元数(注意顺序)
        Eigen::Quaterniond q(qw, qx, qy, qz);
        //注意归一化
        q.normalize();
        //将四元数转换为旋转矩阵
        Eigen::Matrix3d R(q);
        //存入到Sophus对应的SE3 -> T,转化为变换矩阵
        Sophus::SE3 SE3_from_Eigen(R, t);
        poses_est.push_back(SE3_from_Eigen); //传入的是SE3的vector
    }
    
    while (!file_ground.eof()){
        file_ground >> time >> 
        tx >> ty >> tz >> 
        qx >> qy >> qz >> qw; 
        //处理读取的数据
        //处理平移
        Eigen::Vector3d t(tx, ty, tz);
        //处理四元数(注意顺序)
        Eigen::Quaterniond q(qw, qx, qy, qz);
        //注意归一化
        q.normalize();
        //将四元数转换为旋转矩阵
        Eigen::Matrix3d R(q);
        //存入到Sophus对应的SE3 -> T,转化为变换矩阵
        Sophus::SE3 SE3_from_Eigen(R, t);
        poses_gd.push_back(SE3_from_Eigen); //传入的是SE3的vector
    }
    cout << "the number of ground_points = " << poses_gd.size() << endl;//points = 120
    cout << "the number of est_points = " << poses_gd.size() << endl;//points = 120
    
    //2.开始测试RMSE
    double RMSE = 0;
    double e = 0;
    //定义好轨迹点的存放容器
    Sophus::SE3 p_est;
    Sophus::SE3 p_gd;
    for (int i = 0; i < poses_est.size(); i++){
        p_est = poses_est[i];
        p_gd = poses_gd[i];
        //e = ||log(Tg.inserve * Te)||2
        e = (p_gd.inverse() * p_est).log().norm();
        RMSE = RMSE + e * e / poses_est.size();
    }
    RMSE = sqrt(RMSE);
    cout << "The RMSE of trajectory = " << RMSE << endl;
    
    //3.画图
    DrawTrajectory(poses_est, poses_gd);//先声明后使用

    return 0;
}

/*******************************************************************************************/
void DrawTrajectory(vector<Sophus::SE3> poses_est, vector<Sophus::SE3> poses_gd) {
    

    // create pangolin window and plot the trajectory
    pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );
    
    pangolin::Handler3D handler(s_cam); 
    
    pangolin::View& d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f/480.0f)
            .SetHandler(&handler);

    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glLineWidth(2);
        //pose_est
        for (int i = 0; i < poses_est.size() - 1; i++) {
            // glColor3f(1 - (float)i / poses_est.size(), 0.0f, (float) i / poses_est.size());//颜色变化的算法,起点为红色，终点为蓝色
            glColor3f(1.0f, 0.0f, 0.0f);//估计轨迹为红色
            glBegin(GL_LINES);//画线开始
            auto p1 = poses_est[i], p2 = poses_est[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);//p1点的(x, y, z)坐标
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);//p2点的(x, y, z)坐标
            glEnd();//画线结束，将p1和p2连成一条线

        }
        //pose_ground
        for (int i = 0; i < poses_gd.size() - 1; i++) {

            glColor3f(0.0f, 0.0f, 1.0f);//实际轨迹为蓝色
            glBegin(GL_LINES);//画线开始
            auto p1 = poses_gd[i], p2 = poses_gd[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);//p1点的(x, y, z)坐标
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);//p2点的(x, y, z)坐标
            glEnd();//画线结束，将p1和p2连成一条线

        }
        pangolin::FinishFrame();//绘图
    }

}
```
# 3.第4讲
## 3-1.点云
1. [安装链接](https://blog.csdn.net/abcbeifeng/article/details/123935675)
2. c_cpp_properties.json
```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "/opt/ros/noetic/include",
                "/usr/include",
                "${workspaceFolder}/**",
                "/usr/local/share/**",
                "${workspaceFolder}/devel/include",
                "/usr/local/include/opencv4/**",
                "/usr/local/lib/**",
                "/usr/local/include/sophus",
                "/usr/include/eigen3",
                "/usr/include/pcl-1.10",
                "/usr/local/include",
                "/usr/include/vtk-7.1"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "clang-x64"
        }
    ],
    "version": 4
  }
/*注意尤其是
 "/usr/include/pcl-1.10",
 "/usr/local/include",
 "/usr/include/vtk-7.1"
这3条不能少
*/
```
3. 案例
   1. [运行失败解决](https://www.it610.com/article/1280327715483828224.htm)
```cpp
#include <iostream>
#include <fstream>
using namespace std;
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <Eigen/Geometry> 
#include <boost/format.hpp>  // for formating strings
#include <pcl/point_types.h> 
#include <pcl/io/pcd_io.h> 
#include <pcl-1.10/pcl/visualization/pcl_visualizer.h>
int main( int argc, char** argv )
{
    vector<cv::Mat> colorImgs, depthImgs;    // 彩色图和深度图
    vector<Eigen::Isometry3d, Eigen::aligned_allocator<Eigen::Isometry3d>> poses;         // 相机位姿
    
    ifstream fin("../pose.txt");//在pose.txt的上一级目录
    if (!fin)
    {
        cerr<<"请在有pose.txt的目录下运行此程序"<<endl;
        return 1;
    }
    
    for ( int i=0; i<5; i++ )
    {
        //注意此处也是"../%s/%d.%s"
        boost::format fmt( "../%s/%d.%s" );  //图像文件格式
        // ./%s/%d.%s = ./color/1.png | 
        colorImgs.push_back( cv::imread( (fmt%"color"%(i+1)%"png").str() ));
        depthImgs.push_back( cv::imread( (fmt%"depth"%(i+1)%"pgm").str(), -1 )); // 使用-1读取原始图像
        
        double data[7] = {0};
        for ( auto& d:data )
            fin>>d;
        Eigen::Quaterniond q( data[6], data[3], data[4], data[5] );
        Eigen::Isometry3d T(q);
        T.pretranslate( Eigen::Vector3d( data[0], data[1], data[2] ));
        poses.push_back( T );
    }
    
    // 计算点云并拼接
    // 相机内参 
    double cx = 325.5;
    double cy = 253.5;
    double fx = 518.0;
    double fy = 519.0;
    double depthScale = 1000.0;
    
    cout<<"正在将图像转换为点云..."<<endl;
    
    // 定义点云使用的格式：这里用的是XYZRGB
    typedef pcl::PointXYZRGB PointT; 
    typedef pcl::PointCloud<PointT> PointCloud;
    
    // 新建一个点云
    PointCloud::Ptr pointCloud( new PointCloud ); 
    for ( int i=0; i<5; i++ )
    {
        cout<<"转换图像中: "<<i+1<<endl; 
        cv::Mat color = colorImgs[i]; 
        cv::Mat depth = depthImgs[i];
        Eigen::Isometry3d T = poses[i];
        for ( int v=0; v<color.rows; v++ )
            for ( int u=0; u<color.cols; u++ )
            {
                unsigned int d = depth.ptr<unsigned short> ( v )[u]; // 深度值
                if ( d==0 ) continue; // 为0表示没有测量到
                Eigen::Vector3d point; 
                point[2] = double(d)/depthScale; 
                point[0] = (u-cx)*point[2]/fx;
                point[1] = (v-cy)*point[2]/fy; 
                Eigen::Vector3d pointWorld = T*point;
                
                PointT p ;
                p.x = pointWorld[0];
                p.y = pointWorld[1];
                p.z = pointWorld[2];
                p.b = color.data[ v*color.step+u*color.channels() ];
                p.g = color.data[ v*color.step+u*color.channels()+1 ];
                p.r = color.data[ v*color.step+u*color.channels()+2 ];
                pointCloud->points.push_back( p );
            }
    }
    
    pointCloud->is_dense = false;
    cout<<"点云共有"<<pointCloud->size()<<"个点."<<endl;
    pcl::io::savePCDFileBinary("map.pcd", *pointCloud );
    return 0;
}
/*
-0.228993 0.00645704 0.0287837 -0.0004327 -0.113131 -0.0326832 0.993042
-0.50237 -0.0661803 0.322012 -0.00152174 -0.32441 -0.0783827 0.942662
-0.970912 -0.185889 0.872353 -0.00662576 -0.278681 -0.0736078 0.957536
-1.41952 -0.279885 1.43657 -0.00926933 -0.222761 -0.0567118 0.973178
-1.55819 -0.301094 1.6215 -0.02707 -0.250946 -0.0412848 0.966741
前面3个参数是xyz的平移，后面4个是q = (w, x, y, z),每个相机的外参
*/
```
## 3-2.点云基础使用
1. cmake
```cmake
cmake_minimum_required( VERSION 2.8 )
project( joinMap )

set( CMAKE_BUILD_TYPE Release )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

# opencv 
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# eigen 
include_directories( "/usr/include/eigen3/" )

# pcl 
find_package( PCL REQUIRED COMPONENT common io )
find_package( PCL 1.8 REQUIRED)#解决版本问题
include_directories( ${PCL_INCLUDE_DIRS} )
add_definitions( ${PCL_DEFINITIONS} )

# add_executable( joinMap joinMap.cpp )
# target_link_libraries( joinMap ${OpenCV_LIBS} ${PCL_LIBRARIES} )

# add_executable( jointMap01 jointMap01.cpp )
# target_link_libraries( jointMap01 ${OpenCV_LIBS} ${PCL_LIBRARIES}  )
add_executable( pcl_use01 pcl_use01.cpp )
target_link_libraries( pcl_use01 ${OpenCV_LIBS} ${PCL_LIBRARIES}   )
```
2. 基本操作
```cpp
#include <pcl/io/io.h>//必须包含的头文件
#include <pcl/point_types.h>//必须包含的头文件
#include <pcl/io/pcd_io.h>//读取点云
#include <pcl/visualization/cloud_viewer.h>//显示点云文件
#include <boost/thread/thread.hpp>//for formating strings
#include <iostream>
#include <string>
using namespace std;
//1.定义点云
void test01(){
    //1.定义点云对象
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudPtr(new pcl::PointCloud<pcl::PointXYZ>);//生成一个点云指针
    // pcl::PointCloud<pcl::PointXYZ>& cloud = *cloudPtr;//两者等价，表示cloud是*cloud_ptr的解引用的引用
    pcl::PointCloud<pcl::PointXYZ> cloud;//两者等价，表示cloud是*cloud_ptr的解引用的引用,
    //2.初始化点云数据pcd文件头

    cloud.width = 30720;//指定了点云集在宽度方向有多少点
    /*
    1.(u, v)  = (f*x/z, f*y/z)
    2.height:指定了点云集在高的方向上有多少点,这个高有2个意思
    1.制定了点云中1行有多少点，如果是有组织的点云集合的话
    2.如果是无组织的点云集合，这个数据被设置为1
    */
    cloud.height = 1;
    cloud.is_dense = false;
    cloud.points.resize(cloud.width * cloud.height);//点云的数量
    pcl::PointXYZRGB color_point;
    for (size_t i = 0; i < cloud.points.size(); i++){
        //size_t是一种记录大小的数据类型
        cloud.points[i].x = color_point.x;
        cloud.points[i].y = color_point.y;
        cloud.points[i].z = color_point.z;
    }
    //2.保存点云对象
    pcl::io::savePCDFileBinary("map01.pcd", cloud);//第一个是文件路径，第二个是点云
    if (pcl::io::savePCDFile<pcl::PointXYZ>("map01.pcd", cloud) == -1){
        cerr << "can't save the cloud file" << endl;

    }
    //3.读取点云对象
    string pcd_path = "/home/kim-james/ROS_Space/SLAM_ws/slam_test/ch4/joinMap/build/map01.pcd";
    if (pcl::io::loadPCDFile<pcl::PointXYZ>(pcd_path, cloud) == -1){
        cerr << "can't load point cloud file" << endl;
    
    }
    cout << "loaded: " << cloud.width * cloud.height << " points" << endl;
    cout << "loaded: " << cloud.size() << " points" << endl;
    cout << "field = " << pcl::getFieldsList(cloud) << endl;
    
    //4.显示点云
    //可视化结果,显示的对象必须是点云指针
	pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
	viewer.showCloud(cloudPtr);
	while (!viewer.wasStopped())
	{
 
	}
}
int main(){
    test01();
}


/*
指定了点云集在高的方向上有多少点,这个高有2个意思
1.制定了点云中1列有多少点，如果是有组织的点云集合的话
2.如果是无组织的点云集合，这个数据被设置为1
3.eg:
    cloud.width = 640; // Image-like organized structure, with 480 rows and 640 columns, 
    cloud.height = 480; // thus 640*480=307200 points total in the dataset
    cloud.width = 307200;
    cloud.height = 1; // unorganized point cloud dataset with 307200 points
4.pcl::points<pcl::PointCloud::points>
eg:
    pcl::PointCloud<pcl::PointXYZ> cloud;
    vector<pcl::PointXYZ> data = cloud.points;
    以上类型是等同的
5.pcl::PointCloud::is_dense>:指定points中数据是否都是有限的
6.等价关系
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudPtr
    pcl::PointCloud<pcl::PointXYZ> cloud
    cloudPtr = &cloud
7.访问和size:
    cloud.points[i].x
    cloudPtr->points[i].x
*/
```

