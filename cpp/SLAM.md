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
1. 常用命令
```cpp
[Eigen](https://blog.csdn.net/m0_46577050/article/details/121657750)


### 1.矩阵的定义：
```cpp
#include <Eigen/Dense>

Matrix<double, 3, 3> A;               // Fixed rows and cols. Same as Matrix3d.
Matrix<double, 3, Dynamic> B;         // Fixed rows, dynamic cols.
Matrix<double, Dynamic, Dynamic> C;   // Full dynamic. Same as MatrixXd.
Matrix<double, 3, 3, RowMajor> E;     // Row major; default is column-major.
Matrix3f P, Q, R;                     // 3x3 float matrix.
Vector3f x, y, z;                     // 3x1 float matrix.
RowVector3f a, b, c;                  // 1x3 float matrix.
VectorXd v;                           // Dynamic column vector of doubles
// Eigen          // Matlab           // comments
x.size()          // length(x)        // vector size
C.rows()          // size(C,1)        // number of rows
C.cols()          // size(C,2)        // number of columns
x(i)              // x(i+1)           // Matlab is 1-based
C(i,j)            // C(i+1,j+1)       //
```
### 2.基础使用
```cpp
// Basic usage
// Eigen        // Matlab           // comments
x.size()        // length(x)        // vector size
C.rows()        // size(C,1)        // number of rows
C.cols()        // size(C,2)        // number of columns
x(i)            // x(i+1)           // Matlab is 1-based
C(i, j)         // C(i+1,j+1)       //

A.resize(4, 4);   // Runtime error if assertions are on.
B.resize(4, 9);   // Runtime error if assertions are on.
A.resize(3, 3);   // Ok; size didn't change.
B.resize(3, 9);   // Ok; only dynamic cols changed.
                  
A << 1, 2, 3,     // Initialize A. The elements can also be
     4, 5, 6,     // matrices, which are stacked along cols
     7, 8, 9;     // and then the rows are stacked.
B << A, A, A;     // B is three horizontally stacked A's.
A.fill(10);       // Fill A with all 10's.
```

###  3.Eigen特殊矩阵生成
```cpp
// Eigen                            // Matlab
MatrixXd::Identity(rows,cols)       // eye(rows,cols)
C.setIdentity(rows,cols)            // C = eye(rows,cols)
MatrixXd::Zero(rows,cols)           // zeros(rows,cols)
C.setZero(rows,cols)                // C = zeros(rows,cols)
MatrixXd::Ones(rows,cols)           // ones(rows,cols)
C.setOnes(rows,cols)                // C = ones(rows,cols)
MatrixXd::Random(rows,cols)         // rand(rows,cols)*2-1        // MatrixXd::Random returns uniform random numbers in (-1, 1).
C.setRandom(rows,cols)              // C = rand(rows,cols)*2-1
VectorXd::LinSpaced(size,low,high)  // linspace(low,high,size)'
v.setLinSpaced(size,low,high)       // v = linspace(low,high,size)'
```

### 4.矩阵分块
```cpp
// Matrix slicing and blocks. All expressions listed here are read/write.
// Templated size versions are faster. Note that Matlab is 1-based (a size N
// vector is x(1)...x(N)).
// Eigen                           // Matlab
x.head(n)                          // x(1:n)
x.head<n>()                        // x(1:n)
x.tail(n)                          // x(end - n + 1: end)
x.tail<n>()                        // x(end - n + 1: end)
x.segment(i, n)                    // x(i+1 : i+n)
x.segment<n>(i)                    // x(i+1 : i+n)
P.block(i, j, rows, cols)          // P(i+1 : i+rows, j+1 : j+cols)
P.block<rows, cols>(i, j)          // P(i+1 : i+rows, j+1 : j+cols)
P.row(i)                           // P(i+1, :)
P.col(j)                           // P(:, j+1)
P.leftCols<cols>()                 // P(:, 1:cols)
P.leftCols(cols)                   // P(:, 1:cols)
P.middleCols<cols>(j)              // P(:, j+1:j+cols)
P.middleCols(j, cols)              // P(:, j+1:j+cols)
P.rightCols<cols>()                // P(:, end-cols+1:end)
P.rightCols(cols)                  // P(:, end-cols+1:end)
P.topRows<rows>()                  // P(1:rows, :)
P.topRows(rows)                    // P(1:rows, :)
P.middleRows<rows>(i)              // P(i+1:i+rows, :)
P.middleRows(i, rows)              // P(i+1:i+rows, :)
P.bottomRows<rows>()               // P(end-rows+1:end, :)
P.bottomRows(rows)                 // P(end-rows+1:end, :)
P.topLeftCorner(rows, cols)        // P(1:rows, 1:cols)
P.topRightCorner(rows, cols)       // P(1:rows, end-cols+1:end)
P.bottomLeftCorner(rows, cols)     // P(end-rows+1:end, 1:cols)
P.bottomRightCorner(rows, cols)    // P(end-rows+1:end, end-cols+1:end)
P.topLeftCorner<rows,cols>()       // P(1:rows, 1:cols)
P.topRightCorner<rows,cols>()      // P(1:rows, end-cols+1:end)
P.bottomLeftCorner<rows,cols>()    // P(end-rows+1:end, 1:cols)
P.bottomRightCorner<rows,cols>()   // P(end-rows+1:end, end-cols+1:end)

```
### 5.Eigen矩阵元素交换
```cpp
// Of particular note is Eigen's swap function which is highly optimized.
// Eigen                           // Matlab
R.row(i) = P.col(j);               // R(i, :) = P(:, i)
R.col(j1).swap(mat1.col(j2));      // R(:, [j1 j2]) = R(:, [j2, j1])
```

### 6.矩阵转置
```cpp
// Views, transpose, etc; all read-write except for .adjoint().
// Eigen                           // Matlab
R.adjoint()                        // R'
R.transpose()                      // R.' or conj(R')
R.diagonal()                       // diag(R)
x.asDiagonal()                     // diag(x)
R.transpose().colwise().reverse(); // rot90(R)
R.conjugate()                      // conj(R)
```
### 7.矩阵乘积
```cpp
// All the same as Matlab, but matlab doesn't have *= style operators.
// Matrix-vector.  Matrix-matrix.   Matrix-scalar.
y  = M*x;          R  = P*Q;        R  = P*s;
a  = b*M;          R  = P - Q;      R  = s*P;
a *= M;            R  = P + Q;      R  = P/s;
                   R *= Q;          R  = s*P;
                   R += Q;          R *= s;
                   R -= Q;          R /= s;
```
### 8.矩阵单个元素操作

```cpp
// Vectorized operations on each element independently
// Eigen                  // Matlab
R = P.cwiseProduct(Q);    // R = P .* Q
R = P.array() * s.array();// R = P .* s
R = P.cwiseQuotient(Q);   // R = P ./ Q
R = P.array() / Q.array();// R = P ./ Q
R = P.array() + s.array();// R = P + s
R = P.array() - s.array();// R = P - s
R.array() += s;           // R = R + s
R.array() -= s;           // R = R - s
R.array() < Q.array();    // R < Q
R.array() <= Q.array();   // R <= Q
R.cwiseInverse();         // 1 ./ P
R.array().inverse();      // 1 ./ P
R.array().sin()           // sin(P)
R.array().cos()           // cos(P)
R.array().pow(s)          // P .^ s
R.array().square()        // P .^ 2
R.array().cube()          // P .^ 3
R.cwiseSqrt()             // sqrt(P)
R.array().sqrt()          // sqrt(P)
R.array().exp()           // exp(P)
R.array().log()           // log(P)
R.cwiseMax(P)             // max(R, P)
R.array().max(P.array())  // max(R, P)
R.cwiseMin(P)             // min(R, P)
R.array().min(P.array())  // min(R, P)
R.cwiseAbs()              // abs(P)
R.array().abs()           // abs(P)
R.cwiseAbs2()             // abs(P.^2)
R.array().abs2()          // abs(P.^2)
(R.array() < s).select(P,Q);  // (R < s ? P : Q)
```

### 9.矩阵化简
```cpp
// Reductions.
int r, c;
// Eigen                  // Matlab
R.minCoeff()              // min(R(:))
R.maxCoeff()              // max(R(:))
s = R.minCoeff(&r, &c)    // [s, i] = min(R(:)); [r, c] = ind2sub(size(R), i);
s = R.maxCoeff(&r, &c)    // [s, i] = max(R(:)); [r, c] = ind2sub(size(R), i);
R.sum()                   // sum(R(:))
R.colwise().sum()         // sum(R)
R.rowwise().sum()         // sum(R, 2) or sum(R')'
R.prod()                  // prod(R(:))
R.colwise().prod()        // prod(R)
R.rowwise().prod()        // prod(R, 2) or prod(R')'
R.trace()                 // trace(R)
R.all()                   // all(R(:))
R.colwise().all()         // all(R)
R.rowwise().all()         // all(R, 2)
R.any()                   // any(R(:))
R.colwise().any()         // any(R)
R.rowwise().any()         // any(R, 2)
```
### 10.矩阵点乘
```cpp
// Dot products, norms, etc.
// Eigen                  // Matlab
x.norm()                  // norm(x).    Note that norm(R) doesn't work in Eigen.
x.squaredNorm()           // dot(x, x)   Note the equivalence is not true for complex
x.dot(y)                  // dot(x, y)
x.cross(y)                // cross(x, y) Requires #include <Eigen/Geometry>
```
### 11.矩阵类型转换
```cpp
 Type conversion
// Eigen                           // Matlab
A.cast<double>();                  // double(A)
A.cast<float>();                   // single(A)
A.cast<int>();                     // int32(A)
A.real();                          // real(A)
A.imag();                          // imag(A)
// if the original type equals destination type, no work is done
```
### 12.求解线性方程组
```cpp
// Solve Ax = b. Result stored in x. Matlab: x = A \ b.
x = A.ldlt().solve(b));  // A sym. p.s.d.    #include <Eigen/Cholesky>
x = A.llt() .solve(b));  // A sym. p.d.      #include <Eigen/Cholesky>
x = A.lu()  .solve(b));  // Stable and fast. #include <Eigen/LU>
x = A.qr()  .solve(b));  // No pivoting.     #include <Eigen/QR>
x = A.svd() .solve(b));  // Stable, slowest. #include <Eigen/SVD>
// .ldlt() -> .matrixL() and .matrixD()
// .llt()  -> .matrixL()
// .lu()   -> .matrixL() and .matrixU()
// .qr()   -> .matrixQ() and .matrixR()
// .svd()  -> .matrixU(), .singularValues(), and .matrixV()
```
### 13.矩阵特征值
```cpp
// Eigenvalue problems
// Eigen                          // Matlab
A.eigenvalues();                  // eig(A);
EigenSolver<Matrix3d> eig(A);     // [vec val] = eig(A)
eig.eigenvalues();                // diag(val)
eig.eigenvectors();               // vec
// For self-adjoint matrices use SelfAdjointEigenSolver<>
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
