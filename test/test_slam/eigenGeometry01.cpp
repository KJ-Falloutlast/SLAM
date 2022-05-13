#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>
using namespace std;
int main()
{
    /****************** 旋转类型 ******************/
    // 1. 旋转向量 (3 x 1)
    Eigen::AngleAxisd rotation_vector(M_PI/4, Eigen::Vector3d(0,0,1)); // 表示沿 z 轴旋转 90 度
    std::cout << rotation_vector.matrix() << std::endl;

    // 2. 旋转矩阵 (3 x 3) <-- 旋转向量 (3 x 1)
    Eigen::Matrix3d rotation_matrix = rotation_vector.toRotationMatrix();
    std::cout << rotation_matrix << std::endl;

    // 3. 欧拉角 (3 x 1) <-- 旋转矩阵 (3 x 3)
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0); // 这里数字表示优先级，轴旋转顺序为zyx
    std::cout << euler_angles.transpose() << std::endl;

    // 4. 四元数 (4 x 1) <-- 旋转向量 (3 x 1) or 旋转矩阵 (3 x 3)
    Eigen::Quaterniond q = Eigen::Quaterniond(rotation_vector);
    //Eigen::Quaterniond q = Eigen::Quaterniond(rotation_matrix);

    // 5. 欧式变换矩阵 (4 x 4) <-- 旋转向量 (3 x 1) and 平移向量 (3 x 1)
    Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
    T.rotate(rotation_vector);
    T.pretranslate(Eigen::Vector3d(1, 3, 4));
    std::cout << T.matrix() << std::endl;

    // 以上几种旋转的类型(除了欧拉角)都可以直接和目标相乘，从而旋转目标
    Eigen::Vector3d v(1, 0, 0);
    Eigen::Vector3d v_rotated; 
    v_rotated = rotation_vector * v;
    v_rotated = rotation_matrix * v;
    v_rotated = q * v;
    v_rotated = T * v;
    std::cout << v_rotated << std::endl;
}
