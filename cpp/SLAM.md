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
#include <cmath>
using namespace std;

#include <Eigen/Core>
// Eigen 几何模块
#include <Eigen/Geometry>

/****************************
* 本程序演示了 Eigen 几何模块的使用方法
****************************/

int main ( int argc, char** argv )
{
    // Eigen/Geometry 模块提供了各种旋转和平移的表示
    // 3D 旋转矩阵直接使用 Matrix3d 或 Matrix3f
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    // 旋转向量使用 AngleAxis, 它底层不直接是Matrix，但运算可以当作矩阵（因为重载了运算符）
    Eigen::AngleAxisd rotation_vector ( M_PI/4, Eigen::Vector3d ( 0,0,1 ) );     //沿 Z 轴旋转 45 度
    cout .precision(3);
    cout<<"rotation matrix =\n"<<rotation_vector.matrix() <<endl;                //用matrix()转换成矩阵
    // 也可以直接赋值
    rotation_matrix = rotation_vector.toRotationMatrix();
    // 用 AngleAxis 可以进行坐标变换
    Eigen::Vector3d v ( 1,0,0 );
    Eigen::Vector3d v_rotated = rotation_vector * v;
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;
    // 或者用旋转矩阵
    v_rotated = rotation_matrix * v;
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;

    // 欧拉角: 可以将旋转矩阵直接转换成欧拉角
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles ( 2,1,0 ); // ZYX顺序，即roll pitch yaw顺序
    cout<<"yaw pitch roll = "<<euler_angles.transpose()<<endl;

    // 欧氏变换矩阵使用 Eigen::Isometry
    Eigen::Isometry3d T=Eigen::Isometry3d::Identity();                // 虽然称为3d，实质上是4＊4的矩阵
    T.rotate ( rotation_vector );                                     // 按照rotation_vector进行旋转
    T.pretranslate ( Eigen::Vector3d ( 1,3,4 ) );                     // 把平移向量设成(1,3,4)
    cout << "Transform matrix = \n" << T.matrix() <<endl;

    // 用变换矩阵进行坐标变换
    Eigen::Vector3d v_transformed = T*v;                              // 相当于R*v+t
    cout<<"v tranformed = "<<v_transformed.transpose()<<endl;

    // 对于仿射和射影变换，使用 Eigen::Affine3d 和 Eigen::Projective3d 即可，略

    // 四元数
    // 可以直接把AngleAxis赋值给四元数，反之亦然
    Eigen::Quaterniond q = Eigen::Quaterniond ( rotation_vector );
    cout<<"quaternion = \n"<<q.coeffs() <<endl;   // 请注意coeffs的顺序是(x,y,z,w),w为实部，前三者为虚部
    // 也可以把旋转矩阵赋给它
    q = Eigen::Quaterniond ( rotation_matrix );
    cout<<"quaternion = \n"<<q.coeffs() <<endl;
    // 使用四元数旋转一个向量，使用重载的乘法即可
    v_rotated = q*v; // 注意数学上是qvq^{-1}
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;

    return 0;
}
```
  2. 例2
```cpp
\一、旋转向量

1.0 初始化旋转向量：旋转角为alpha，旋转轴为(x,y,z)

Eigen::AngleAxisd rotation_vector(alpha,Vector3d(x,y,z))

1.1 旋转向量转旋转矩阵

Eigen::Matrix3d rotation_matrix;
rotation_matrix=rotation_vector.matrix();

Eigen::Matrix3d rotation_matrix;
rotation_matrix=rotation_vector.toRotationMatrix();

1.2 旋转向量转欧拉角(Z-Y-X，即RPY)

Eigen::Vector3d eulerAngle=rotation_vector.matrix().eulerAngles(2,1,0);

1.3 旋转向量转四元数

Eigen::Quaterniond quaternion(rotation_vector);
Eigen::Quaterniond quaternion;
quaternion=rotation_vector;


二、旋转矩阵

2.0 初始化旋转矩阵

Eigen::Matrix3d rotation_matrix;rotation_matrix<<x_00,x_01,x_02,x_10,x_11,x_12,x_20,x_21,x_22;

2.1 旋转矩阵转旋转向量

Eigen::AngleAxisd rotation_vector(rotation_matrix);


Eigen::AngleAxisd rotation_vector;rotation_vector=rotation_matrix;

Eigen::AngleAxisd rotation_vector;rotation_vector.fromRotationMatrix(rotation_matrix);

2.2 旋转矩阵转欧拉角(Z-Y-X，即RPY)

Eigen::Vector3d eulerAngle=rotation_matrix.eulerAngles(2,1,0);

2.3 旋转矩阵转四元数

Eigen::Quaterniond quaternion(rotation_matrix);

Eigen::Quaterniond quaternion;quaternion=rotation_matrix;


三、欧拉角

3.0 初始化欧拉角(Z-Y-X，即RPY)

Eigen::Vector3d eulerAngle(yaw,pitch,roll);

3.1 欧拉角转旋转向量

Eigen::AngleAxisd rollAngle(AngleAxisd(eulerAngle(2),Vector3d::UnitX()));//2是Z的欧拉角，UnitX()是旋转向量在X轴的分量
Eigen::AngleAxisd pitchAngle(AngleAxisd(eulerAngle(1),Vector3d::UnitY()));//Y
Eigen::AngleAxisd yawAngle(AngleAxisd(eulerAngle(0),Vector3d::UnitZ())); //X
Eigen::AngleAxisd rotation_vector;rotation_vector=yawAngle*pitchAngle*rollAngle;//实际上是RPY

3.2 欧拉角转旋转矩阵

Eigen::AngleAxisd rollAngle(AngleAxisd(eulerAngle(2),Vector3d::UnitX()));
Eigen::AngleAxisd pitchAngle(AngleAxisd(eulerAngle(1),Vector3d::UnitY()));
Eigen::AngleAxisd yawAngle(AngleAxisd(eulerAngle(0),Vector3d::UnitZ())); 
Eigen::Matrix3d rotation_matrix;
rotation_matrix=yawAngle*pitchAngle*rollAngle;

3.3 欧拉角转四元数

Eigen::AngleAxisd rollAngle(AngleAxisd(eulerAngle(2),Vector3d::UnitX()));
Eigen::AngleAxisd pitchAngle(AngleAxisd(eulerAngle(1),Vector3d::UnitY()));
Eigen::AngleAxisd yawAngle(AngleAxisd(eulerAngle(0),Vector3d::UnitZ())); 
Eigen::Quaterniond quaternion;
quaternion=yawAngle*pitchAngle*rollAngle;


四、四元数

4.0 初始化四元数

Eigen::Quaterniond quaternion(w,x,y,z);

4.1 四元数转旋转向量

Eigen::AngleAxisd rotation_vector(quaternion);

Eigen::AngleAxisd rotation_vector;rotation_vector=quaternion;

4.2 四元数转旋转矩阵

Eigen::Matrix3d rotation_matrix;
rotation_matrix=quaternion.matrix();

Eigen::Matrix3d rotation_matrix;
rotation_matrix=quaternion.toRotationMatrix();

4.4 四元数转欧拉角(Z-Y-X，即RPY)

Eigen::Vector3d eulerAngle=quaternion.matrix().eulerAngles(2,1,0);

```
1. visualizeGeometry
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