# 1.第一讲
1. 安装
![链接](https://ros-planning.github.io/moveit_tutorials/doc/getting_started/getting_started.html)
## 1-1.urdf建模原理
1. link
   1. 描述机器人某个刚体部分的外观和物理属性
   2. 描述连杆尺寸(size), 颜色(color), 形状(shape),惯性矩阵(inertial matrix),碰撞参数(collison properties)
   3. 每个link都会成为一个坐标系
2. joint
   1. 表述2个link间的关系，分为6中类型
      1. continuous:旋转关节，可以围绕单轴无限旋转
      2. revolute:旋转关节，类似于continuous,但是有旋转的角度极限
      3. prismatic:滑动关节，沿某一轴线移动的关节，带有位置极限
      4. planar:平面关节，允许在平面正交方向上平移或者旋转
      5. floating:浮动关节，允许进行平移，旋转运动
      6. fixed:固定关节
3. 常量定义<xacro:property name = "" value = ""/>
4. 常量使用
5. 宏定义和宏调用<xacro:macro name = "" params = ""> </xacro:macro>
6. 文件包含:<xacro:include filename = ""/>
7. 打开assitant后，需要将配置文件保存在src目录下

## 1-2.相关问题
1. launch
```xml
<launch>
    <arg name="ur3" />
    <!-- 加载机器人模型参数 -->
    <param name="robot_description" command="$(find xacro)/xacro --inorder $(find ur3)/urdf/ur3.urdf" />

    <!-- 设置GUI参数，显示关节控制插件 -->
    <param name="use_gui" value="true"/>

    <!-- 运行joint_state_publisher节点，发布机器人的关节状态  -->
    <node name="joint_state_publisher" pkg="joint_state_publisher" type="joint_state_publisher" />
    <node name="joint_state_publisher_gui" pkg="joint_state_publisher_gui" type="joint_state_publisher_gui" />
    
    <!-- 运行robot_state_publisher节点，发布tf  -->
    <node name="robot_state_publisher" pkg="robot_state_publisher" type="robot_state_publisher" />
   <!-- type = "robot_state_publisher" -->
    <!-- 运行rviz可视化界面 -->
    <node name="rviz" pkg="rviz" type="rviz" args="-d $(find ur3)/urdf.rviz" required="true" />
</launch>
```
**注意在启动rviz后要更换坐标系**

# 2.第2讲
## 2-1.moveitSetupAssitant
1. start:导入urdf文件
2. 碰撞矩阵:generate
3. virtual_joints:虚拟关节,类似于base_link和world坐标系的关系，若是机器人是固定的，则不需要设置虚拟关节
4. define planning groups：
   1. 添加一个规划组
   2. 选择求解器：正解或者逆解
      1. 默认kdl
      2. 求解时间选择默认
      3. 求解次数：3次
   3. ompl:RPT(**运动规划算法**)
   4. 添加manipulator-Chain:
      1. Base Link:base_link(**最内侧的link**)
      2. Tip Link:tool0(**最外侧的link**)
   5. robot Poses
      1. add pose:命名为home,所有关节的角度都设置为0
   6. End Effectors:终端夹爪
   7. Passive Joints:主要用于将不重要关节剔除运动规划考虑,**若所有关节都需要运动的情况下，就不要设置**
   8. Controllers:控制器,**不建议使用**
   9. Simulation: 能产生一个仿真文件
   10. 3D Preception:主要用于视觉(**8-10都还不成熟，谨慎使用**)

# 2.第3讲
## 2-1.moveit编程接口
1. 连接控制需要的规划组
2. 设置目标位姿势(关节空间或者笛卡尔空间)
3. 设置运动约束(可选)
4. 使用moveit规划一个可达目标的轨迹
5. 修改轨迹
6. 执行规划出的轨迹
