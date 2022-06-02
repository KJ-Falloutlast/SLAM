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