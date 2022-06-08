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

# 3.第4讲
1. 正向运动学和逆向运动学的区别
   1. 正向运动学是已知每个关节的转角来求末端执行器的*位姿和位置(T)*
   2. 逆向运动学是已知末端执行器的位置和位姿(T)来求*每个关节的转角*
## 3-1.正向运动学
```cpp
//fk代表正运动学:forward kinematics, IK:Inverse kinematics
#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "moveit_fk_demo");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    moveit::planning_interface::MoveGroupInterface arm("manipulator");

    arm.setGoalJointTolerance(0.001);

    arm.setMaxAccelerationScalingFactor(0.2);
    arm.setMaxVelocityScalingFactor(0.2);

    // 控制机械臂先回到初始化位置
    arm.setNamedTarget("home");
    arm.move();
    sleep(1);

    //设置目标位姿数组
    /*
    1.定义1个数组,来存放6个关节的信息
    2.通过关节空间的6个角度来设置目标姿态
    */
    double targetPose[6] = {0.391410, -0.676384, -0.376217, 0.0, 1.052834, 0.454125};
    std::vector<double> joint_group_positions(6);
    joint_group_positions[0] = targetPose[0];
    joint_group_positions[1] = targetPose[1];
    joint_group_positions[2] = targetPose[2];
    joint_group_positions[3] = targetPose[3];
    joint_group_positions[4] = targetPose[4];
    joint_group_positions[5] = targetPose[5];
    //将关节写入
    arm.setJointValueTarget(joint_group_positions);
    arm.move();//规划+移动
    sleep(1);

    // 控制机械臂先回到初始化位置
    arm.setNamedTarget("home");
    arm.move();
    sleep(1);

    ros::shutdown(); 

    return 0;
}
```
## 3-2.逆向运动学
```cpp
/***********************************************************************
Copyright 2019 Wuhan PS-Micro Technology Co., Itd.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***********************************************************************/

#include <string>
#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "moveit_fk_demo");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    moveit::planning_interface::MoveGroupInterface arm("manipulator");

    //获取终端link的名称
    std::string end_effector_link = arm.getEndEffectorLink();

    //设置目标位置所使用的参考坐标系
    std::string reference_frame = "base_link";
    arm.setPoseReferenceFrame(reference_frame);

    //当运动规划失败后，允许重新规划
    arm.allowReplanning(true);

    //设置位置(单位：米)和姿态（单位：弧度）的允许误差
    arm.setGoalPositionTolerance(0.001);
    arm.setGoalOrientationTolerance(0.01);

    //设置允许的最大速度和加速度
    arm.setMaxAccelerationScalingFactor(0.2);
    arm.setMaxVelocityScalingFactor(0.2);

    // 控制机械臂先回到初始化位置
    arm.setNamedTarget("home");//设置目标位置名称
    arm.move();//移动机械臂
    sleep(1);

    // 设置机器人终端的目标位置
    geometry_msgs::Pose target_pose;
    target_pose.orientation.x = 0.70692;
    target_pose.orientation.y = 0.0;
    target_pose.orientation.z = 0.0;
    target_pose.orientation.w = 0.70729;

    target_pose.position.x = 0.2593;
    target_pose.position.y = 0.0636;
    target_pose.position.z = 0.1787;

    // 设置机器臂当前的状态作为运动初始状态
    arm.setStartStateToCurrentState();//设置机械臂当前状态为初始状态

    arm.setPoseTarget(target_pose);//设置机械臂终端的目标位姿

    // 进行运动规划，计算机器人移动到目标的运动轨迹，此时只是计算出轨迹，并不会控制机械臂运动
    moveit::planning_interface::MoveGroupInterface::Plan plan;
    moveit::planning_interface::MoveItErrorCode success = arm.plan(plan);//返回一个bool值，看运动是否规划成功

    ROS_INFO("Plan (pose goal) %s",success?"":"FAILED");   

    //让机械臂按照规划的轨迹开始运动。
    if(success)
      arm.execute(plan);//如果成功的话，就执行运动规划
    sleep(1);

    // 控制机械臂先回到初始化位置
    arm.setNamedTarget("home");//设置目标位置
    arm.move();//运动机器臂
    sleep(1);

    ros::shutdown(); 

    return 0;
}
```

## 3-3.圆弧轨迹规划
```cpp
#include <math.h>
#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/robot_trajectory/robot_trajectory.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "moveit_cartesian_demo");
    /*
    1.spin()是指同步查询，即程序会卡在spin()的位置，一旦有消息进来，就会调用回调函数，进行循环
    2.AsyncSpinner是指的是异步循环，即在后台开启一个线程，当有数据进来的时候，会执行回调函数和调用消息对象

    */
	ros::AsyncSpinner spinner(1);
    //spinner开始
	spinner.start();
    //
    moveit::planning_interface::MoveGroupInterface arm("manipulator");

    //获取终端link的名称
    std::string end_effector_link = arm.getEndEffectorLink();

    //设置目标位置所使用的参考坐标系
    std::string reference_frame = "base_link";
    arm.setPoseReferenceFrame(reference_frame);

    //当运动规划失败后，允许重新规划 
    arm.allowReplanning(true);

    //设置位置(单位：米)和姿态（单位：弧度）的允许误差
    arm.setGoalPositionTolerance(0.001);
    arm.setGoalOrientationTolerance(0.01);

    //设置允许的最大速度和加速度
    arm.setMaxAccelerationScalingFactor(0.8);
    arm.setMaxVelocityScalingFactor(0.8);

    // 控制机械臂先回到初始化位置
    arm.setNamedTarget("home");//先设置一个目标参考系
    arm.move();//再移动机械臂
    sleep(1);

    // 设置机器人终端的目标位置(也就是圆心的位置)
    //目标位姿的旋转
    geometry_msgs::Pose target_pose;
    target_pose.orientation.x = -0.482974;
    target_pose.orientation.y = 0.517043;
    target_pose.orientation.z = -0.504953;
    target_pose.orientation.w = -0.494393;
    //目标位姿的位置
    target_pose.position.x = 0.331958;
    target_pose.position.y = 0.0;
    target_pose.position.z = 0.307887;

    arm.setPoseTarget(target_pose);//设置一个目标位姿
    arm.move();//移动机械臂

	std::vector<geometry_msgs::Pose> waypoints;//设置一个存放路标点的容器

    //将初始位姿(圆心)加入路点列表
	waypoints.push_back(target_pose);

    double centerA = target_pose.position.y;//圆心的Y
    double centerB = target_pose.position.z;//圆心的Z
    double radius = 0.1;//圆的半径

    for(double th=0.0; th<6.28; th=th+0.01)//th = thetha = 2PI
    {
        //6.28/0.01 = 628个点。每隔0.01rad就确定一个点
        target_pose.position.y = centerA + radius * cos(th);
        target_pose.position.z = centerB + radius * sin(th);
        waypoints.push_back(target_pose);//将600多个点全部放入容器中
    }

	// 笛卡尔空间下的路径规划
	moveit_msgs::RobotTrajectory trajectory;//定义一个trajectory
	const double jump_threshold = 0.0;
    /*
    1.关节连续运动之间的距离<=Jump_threshold * 关节位置的平均距离/绝对距离，
    2.这个参数代表的含义是在笛卡尔空间运动时，避免在经过某个奇异点而发生关节的抖动
    3.这个参数一般设置为0
    4.含义就是轨迹需要调整的点数,0加1步，大于0加5步
	*/
    //一步走多远，根据目标点和当前位置的距离处于eef_step，得到轨迹的点数
    const double eef_step = 0.01;
	double fraction = 0.0;
    int maxtries = 100;   //最大尝试规划次数
    int attempts = 0;     //已经尝试规划次数

    while(fraction < 1.0 && attempts < maxtries)
    {
        fraction = arm.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
        // fraction代表轨迹规划的完成度，如果是1就代表完全规划完
        /*
        1.computeCartesianPath会将waypoints中的第一个作为目标点
        2.由eef_step, jump_threshold这两个参数获得到达第一个目标点之间需要多少个轨迹点，
        再将这些轨迹点通过IK计算成关节值
        3.再由当前位置为初始位置，下一个waypoints中的点作为目标点，重复2，直到计算完所有的目标点
        4.最后所有的关节值会存在一起作为一条轨迹，并赋予速度，加速度，持续时间
        */
        attempts++;
        
        if(attempts % 10 == 0)
            ROS_INFO("Still trying after %d attempts...", attempts);
    }
    
    if(fraction == 1)
    {   
        ROS_INFO("Path computed successfully. Moving the arm.");

	    // 生成机械臂的运动规划数据
	    moveit::planning_interface::MoveGroupInterface::Plan plan;
	    plan.trajectory_ = trajectory;//生成运动学轨迹

	    // 执行运动
	    arm.execute(plan);
        sleep(1);
    }
    else
    {
        ROS_INFO("Path planning failed with only %0.6f success after %d attempts.", fraction, maxtries);
    }

    // 控制机械臂先回到初始化位置
    arm.setNamedTarget("home");
    arm.move();
    sleep(1);
	return 0;
}

```
## 2-4.轨迹重定义
**要学会查询API文档**
```cpp
#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/robot_trajectory/robot_trajectory.h>

void scale_trajectory_speed(moveit::planning_interface::MoveGroupInterface::Plan &plan, double scale)
{
    int n_joints = plan.trajectory_.joint_trajectory.joint_names.size();

    for(int i=0; i<plan.trajectory_.joint_trajectory.points.size(); i++)
    {
        plan.trajectory_.joint_trajectory.points[i].time_from_start *= 1/scale;
        
        for(int j=0; j<n_joints; j++)
        {
            plan.trajectory_.joint_trajectory.points[i].velocities[j] *= scale;
            plan.trajectory_.joint_trajectory.points[i].accelerations[j] *= scale*scale;
        }
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "moveit_revise_trajectory_demo");
    ros::NodeHandle node_handle; //设置节点句柄
    ros::AsyncSpinner spinner(1);//设置异步spinner
    spinner.start();//启动spinner

    moveit::planning_interface::MoveGroupInterface arm("manipulator");//设置机械臂

    arm.setGoalJointTolerance(0.001);//设置

    arm.setMaxAccelerationScalingFactor(1);
    arm.setMaxVelocityScalingFactor(1);

    // 控制机械臂先回到初始化位置
    arm.setNamedTarget("home");
    arm.move();
    sleep(1);


    double targetPose[6] = {0.391410, -0.676384, -0.376217, 0.0, 1.052834, 0.454125};
    std::vector<double> joint_group_positions(6);
    joint_group_positions[0] = targetPose[0];
    joint_group_positions[1] = targetPose[1];
    joint_group_positions[2] = targetPose[2];
    joint_group_positions[3] = targetPose[3];
    joint_group_positions[4] = targetPose[4];
    joint_group_positions[5] = targetPose[5];

    arm.setJointValueTarget(joint_group_positions);
    arm.move();
    sleep(1);

    // 控制机械臂先回到初始化位置
    arm.setNamedTarget("home");
    arm.move();
    sleep(1);


    arm.setJointValueTarget(joint_group_positions);
    moveit::planning_interface::MoveGroupInterface::Plan plan;
    moveit::planning_interface::MoveItErrorCode success = arm.plan(plan);

    ROS_INFO("Plan (pose goal) %s",success?"":"FAILED");   
    
    scale_trajectory_speed(plan, 0.25);

    //让机械臂按照规划的轨迹开始运动。
    if(success)
      arm.execute(plan);
    sleep(1);

    // 控制机械臂先回到初始化位置
    arm.setNamedTarget("home");
    arm.move();
    sleep(1);

    ros::shutdown(); 

    return 0;
}
```

