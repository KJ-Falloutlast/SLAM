#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Geometry>
using namespace std;
using namespace Eigen;
int main(){
    //下面3个变量作为演示的中间变量
    //旋转向量
    AngleAxisd V(M_PI/4, Vector3d(0, 0, 1));
    //旋转矩阵
    Matrix3d R = V.matrix();
    //四元数
    Quaterniond q(V);
    
    //对旋转向量（轴角）赋值的方法
    //1.使用旋转的角度和旋转轴向量(此向量为单位向量)初始化
    AngleAxisd V1(M_PI/4, Vector3d(0, 0, 1));
    cout << "Rotation_vector1 = " << endl << V1.matrix() << endl;

    //2.使用旋转矩阵转旋转向量的方式
    //2-1.使用旋转向量的fromRotationMatrix()来对旋转向量赋值(次方法为旋转矩阵独有，四元数没有)
    AngleAxisd V2;
    V2.fromRotationMatrix(R);
    cout << "Rotation_vector2 = " << endl << V2.matrix() << endl;
    
    //2-2.直接使用旋转矩阵来对旋转向量赋值
    AngleAxisd V3;
    V3 = R;
    cout << "Rotation_vector3 = " << endl << V3.matrix() << endl;

    //2-3.使用旋转矩阵来对旋转向量初始化
    AngleAxisd V4(R);
    cout << "Rotation_vector4 = " << endl << V4.matrix() << endl;
    
    //3. 使用四元数对旋转向量赋值
    //3-1.直接使用四元数对旋转向量赋值
    AngleAxisd V5;
    V5 = q;
    cout << "Rotation_vector5 = " << endl << V5.matrix() << endl;
    //3-2.使用四元数来对旋转向量初始化
    AngleAxisd V6(q);
    cout << "Rotation_vector6 = " << endl << V6.matrix() << endl;

//------------------------------------------------
    //对四元数赋值的三大方法(前3个是虚部，最后是实部)
    //1. 使用旋转角度和旋转轴向量(此向量是单位向量)来初始化四元数
    Quaterniond q1(cos(M_PI/4)/2, 
                0 * sin(M_PI/4)/2,
                0 * sin(M_PI/4)/2,
                1 * sin(M_PI/4)/2);
    //1-1.第一种输出四元数的方式
    cout << "Quaternion1 = " << endl << q1.coeffs() << endl;
    //1-2.第二种输出四元数的方式
    cout << q1.x() << endl << endl;
    cout << q1.y() << endl << endl;
    cout << q1.z() << endl << endl;
    cout << q1.w() << endl << endl;
    //2.使用旋转矩阵转四元数的方式
    //2-1.直接使用旋转矩阵来对旋转向量赋值
    Quaterniond q2;
    q2 = R;
    cout << "Quaternion2 = " << endl << q2.coeffs() << endl;
    //2-2.使用选装矩阵来对四元数进行初始化
    Quaterniond q3(R);
    cout << "Quaternion3 = " << endl << q3.coeffs() << endl;
    
    //3.使用旋转向量对四元数赋值
    //3-1.直接用旋转向量对四元数赋值
    Quaterniond q4;
    q4 = V;
    cout << "Quaternion4 = " << endl << q4.coeffs() << endl;
    //3-2.使用旋转向量来对四元数初始化
    Quaterniond q5(V);

    cout << "Quaternion5 = " << endl << q5.coeffs() << endl;
//--------------------------------------------
    //对旋转矩阵赋值的三大方法
    //1. 用旋转矩阵的函数来出初始化旋转矩阵
    Matrix3d R1 = Matrix3d::Identity();
    cout << "Rotation_matrix1 = " << endl << R1 << endl;

    //2.使用旋转向量转旋转矩阵来对旋转矩阵赋值
    //2-1.使用旋转向量的成员函数matrix()来对旋转矩阵赋值
    Matrix3d R2;
    R2 = V.matrix();
    cout << "Rotation_matrix2 = " << endl << R2 << endl;
    //2-2.使用旋转向量的成员函数roRotationMatrix()来对旋转矩阵赋值
    Matrix3d R3;
    R3 = V.toRotationMatrix();
    cout << "Rotation_matrix3 = " << endl << R3 << endl;
    
    //3. 使用四元数旋转矩阵来对旋转矩阵赋值
    //3-1.使用四元数的成员函数matrix()来对旋转矩阵赋值
    Matrix3d R4;
    R4 = q.matrix();
    cout << "Rotation_matrix4 = " << endl << R4 << endl;
    //3-2.使用四元数的成员函数toRotationMatrix()来对旋转矩阵赋值
    Matrix3d R5;-
    R5 = q.toRotationMatrix();
    cout << "Rotation_matrix5 = " << endl << R5 << endl;

    

}
