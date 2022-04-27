#include "stdafx.h"
#include <iostream>
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
    Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > map1(p1, iRow1, iCol1);
    Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > map2(p2, iRow2, iCol2);
    Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > map3(p3, iCol1, iCol2);
 
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