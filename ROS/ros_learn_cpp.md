# 1.通信机制
## 1.话题通信
### 1-1. 话题通信基本操作
1. 发布数据
```cpp
 #include "ros/ros.h"
 #include "std_msgs/String.h"//普通文本类型的消息
 #include <sstream>
 int main(int argc, char *argv[]){
     setlocale(LC_ALL, "");
     ros::init(argc, argv, "talker");
     ros::NodeHandle nh;
     ros::Publisher pub = nh.advertise<std_msgs::String>("chatter",10);
     std_msgs::String msg;
     std::string msg_front = "hello";   
     int count = 0;
     ros::Rate r(1);
     while (ros::ok()){
         std::stringstream ss;//使用stringstream拼接字符串和编号
         ss << msg_front << count;
         msg.data = ss.str();
         //发布消息
         pub.publish(msg);
         ROS_INFO("发送的消息:%s",msg.data.c_str());
         r.sleep()//休眠时间 = 1/频率
         count++;
         ros::spinOnce();
     }
     return 0;
 }
```      
2. 接收数据
```cpp
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
/*
    訂約方实现：
    1.包含头文件：
        ROS中文本类型-->std_msgs/String.h
    2.初始化节点
    3.创建节点句柄
    4.创建訂閱者对象
    5.處理訂閱數據

*/
void doMsg(const std_msgs::String::ConstPtr &msg){//发布类型为std_msgs下的常量指針的引用
    //通過msg獲取並操作訂库閱到的數據
    ROS_INFO("翠花订阅的数据%s", msg->data.c_str());//因为msg是指针的引用，所以需要用->调用，c_str()指的是c风格的字符串
}

int main(int argc, char *argv[])
{
    //2.初始化ROS节点
    ros::init(argc, argv, "subscriber");
    //3.创建节点句柄
    ros::NodeHandle nh;
    //4.创建订阅者对象
    ros::Subscriber sub = nh.subscribe<std_msgs::String>("fangzi", 10, doMsg);
    //5.处理订阅的消息
    //6.回旋函数
    ros::spin();//循环执行main()
    return 0; 
}
```
---
3. 调整cmake文件
  ```cmake
  add_executable(Hello_pub
    src/Hello_pub.cpp
  )
  add_executable(Hello_sub
    src/Hello_sub.cpp
  )

  target_link_libraries(Hello_pub
    ${catkin_LIBRARIES}
  )
    ${catkin_LIBRARIES}
  )
  ```

4. 话题通信自定义msg调用
流程：
1. 修改xml文件和cmake文件：
   1. 在cmake中:
```cmake 
find_package:message_generation
add_message_file:Person.msg
generate_messages:std_msgs
catkin_package:message_runtime
add_executable(person_talker src/person_talker.cpp)
add_executable(person_listener src/person_listener.cpp)

add_dependencies(person_talker ${PROJECT_NAME}_generate_messages_cpp)
add_dependencies(person_listener ${PROJECT_NAME}_generate_messages_cpp)

target_link_libraries(person_talker
${catkin_LIBRARIES}
)
target_link_libraries(person_listener
${catkin_LIBRARIES}
)

```cmake//**总的来看**
## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(server ${PROJECT_NAME}_gencpp)
add_dependencies(client ${PROJECT_NAME}_gencpp)

## Specify libraries to link a library or executable target against
target_link_libraries(server
  ${catkin_LIBRARIES}
)
target_link_libraries(client
  ${catkin_LIBRARIES}
)
```
   2. xml 在xml中：message_generation+message_runtime<--->build_depend+build_export_depend+exec_depend
   ```xml
     <buildtool_depend>catkin</buildtool_depend>
     <build_depend>roscpp</build_depend>
     <build_depend>rospy</build_depend>
     <build_depend>std_msgs</build_depend>
     <build_depend>message_generation</build_depend>
     <build_depend>message_runtime</build_depend>

     <build_export_depend>roscpp</build_export_depend>
     <build_export_depend>rospy</build_export_depend>
     <build_export_depend>std_msgs</build_export_depend>
     <build_export_depend>message_generation</build_export_depend>
     <build_export_depend>message_runtime</build_export_depend>

     <exec_depend>roscpp</exec_depend>
     <exec_depend>rospy</exec_depend>
     <exec_depend>std_msgs</exec_depend>
     <exec_depend>message_runtime</exec_depend>
     <exec_depend>message_generation</exec_depend>

   ```
2. 发布方的实现
```cpp
#include "ros/ros.h"
#include "pub_sub/Person.h"
int main(int argc, char *argv[]){
    setlocale(LC_ALL,"");
    ros::init(argc, argv, "publisher");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<pub_sub::Person>("house", 20);
    ros::Rate rate(1);
    pub_sub::Person msg;
    int count = 0;
    while (ros::ok()){
        msg.name = "James";
        msg.age = 18;
        msg.height = 1.75;
        pub.publish(msg);
        ROS_INFO("published%d", count);
        rate.sleep();
        count++;
    }
    return 0;
}
```
3. 订阅方的实现
```cpp
 #include "ros/ros.h"
 #include "pub_sub/Person.h"
 void doMsg(const pub_sub::Person::ConstPtr &msg){
     ROS_INFO("发布的消息是：姓名:%s, 身高:%d, 年龄:%d",msg->name.c_str(), msg->age, msg->height);//char类型必须转换成char.c_str()类型才能输出
 }
 int main(int argc, char *argv[]){
     setlocale(LC_ALL,"");//加上这一段可以避免中文乱码
     ros::init(argc, argv, "subscriber");
     ros::NodeHandle nh;
     ros::Subscriber sub = nh.subscribe<pub_sub::Person>("house", 20, doMsg);
     ros::spin();
     return 0;
 }
```
4.总结：
  1. 在pub_sub目录下创建msg/Person.msg
  2. 修改cmake:message_runtime message_generation std_msgadd_dependencies
  3. 修改xml:见上面
  4. catkin_make
  5. 将devep/include/**的头文件路径加到cpp_jason文件中
  6. 编写pub_msg.cpp+sub_msg.cpp
  7. **再次修改cmakelist文件**：Person.msg;add_excutable
  8. catkin_make
  9. rosrun执行


## 2.服务通信
### 2-1. 服务端(**server**)

```cpp
#include "ros/ros.h"
#include "server_client/AddInts.h"
//4.创建服务端
bool doReq(server_client::AddInts::Request &req, server_client::AddInts::Response &resp){//引用传递
    int num1 = req.num1;
    int num2 = req.num2;
    resp.sum = num1 + num2;
    ROS_INFO("您输入的信息是num1+num2=%d",resp.sum);
    return true;
    }
           
int main(int argc, char *argv[]){
    setlocale(LC_ALL,"");
    //1.创建节点
    ros::init(argc, argv, "server");
    //2.创建节点句柄
    ros::NodeHandle nh;
    //3.创建服务端
    ros::ServiceServer server = nh.advertiseService("AddInts", doReq);//此处无模板,此处话题名称相同
    //5.回旋
    ros::spin();
    return 0;
}
```
### 2-2. 客户端
```cpp
#include "ros/ros.h"
#include "server_client/AddInts.h"
int main(int argc, char *argv[]){
    setlocale(LC_ALL, "");
    //优化实现
    if (argc != 3){
        ROS_INFO("提交的参数个数不对！");
        return 1;
    }
    //1.初始化节点
    ros::init(argc, argv, "client");
    //2.创建节点句柄
    ros::NodeHandle nh;
    //3.创建客户端对象
    ros::ServiceClient client = nh.serviceClient<server_client::AddInts>("AddInts");//客户端发布数据，所以需要指定数据类型，服务端接收数据，所以无须指定数据类型
    //client = ServiceClient,serviceClient; server = ServiceServer,advertiseService
    //4.创建请求逻辑
    //4-1.创建请求
    server_client::AddInts req;
    req.request.num1 = atoi(argv[1]);//argv[1]是字符串类型的，要变成整型值，用atoi(argv[1]),
    // atoi = ascii to integer,是将字符串转为整形的函数
    req.request.num2 = atoi(argv[2]);
    //4-2.处理响应
    //调用判断服务器状态的函数
    client.waitForExistence();//如果服务器没启动，就挂起，不启动
    bool resp = client.call(req);//访问服务器把ai对象提交了,客户端接收返回的结果，是否是true
    if (resp){//若是客户端先于服务端启动，resp = flase
        ROS_INFO("响应成功！");
        ROS_INFO("响应结果 = %d", req.response.sum);//结果被封装在ai.response.sum里面
    }
    else{
        ROS_INFO("处理失败...");
    }
    return 0;
}
```
### 2-3.配置cmake和xml,以及srv文件
1. cmake文件
* find_package->message_generation
* add_service_files->AddInts.srv
* generate_messages->std_msgs
* catkin_package->message_runtime
---
* add_executable(client src/client.cpp)
*add_dependencies(server ${PROJECT_NAME}_gencpp)
*target_link_libraries(client
  ${catkin_LIBRARIES}
)
1. xml
```xml
  <buildtool_depend>catkin</buildtool_depend>
  <build_depend>roscpp</build_depend>
  <build_depend>rospy</build_depend>
  <build_depend>std_msgs</build_depend>
  <build_depend>message_generation</build_depend>
  <build_depend>message_runtime</build_depend>

  <build_export_depend>roscpp</build_export_depend>
  <build_export_depend>rospy</build_export_depend>
  <build_export_depend>std_msgs</build_export_depend>
  <build_export_depend>message_generation</build_export_depend>
  <build_export_depend>message_runtime</build_export_depend>

  <exec_depend>roscpp</exec_depend>
  <exec_depend>rospy</exec_depend>
  <exec_depend>std_msgs</exec_depend>
  <exec_depend>message_runtime</exec_depend>
  <exec_depend>message_generation</exec_depend>
```
3. srv文件
```srv
int32 num1//客户端
int32 num2
---
int32 sum//服务端
```
4. 步骤总结：
   1. client
      1. 创建节点
      2. 创建节点句柄
      3. 创建客户端:ros::ServiceClient client = nh.serviceClient<service_client::AddInts>("house")
      4. 组织请求数据
         1. 创建请求数据:service_client::AddInts req
         2. 返回请求:bool resp = client.call(req) 
    2. server
       1. 创建节点
       2. 创建节点句柄
       3. 创建服务端：ros::ServiceServer server = nh.advertise("house",doReq)
       4. 创建回调函数:bool doReq(service_client::AddInts::Request &req,service_client::AddInts::Request &resp){}
       5. 回旋：ros::spin()


## 3.参数服务器
### 1.参数的增
1. 方法
   1. ros::NodeHandle nh -> nh.setParam("keys","values")
   2. ros::param::set("keys","values");
2. 调试：rosparam get /keys = xxxx
3. 案例：
   1. 设置参数
```cpp
#include "ros/ros.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
int main(int argc, char** argv){
    ros::init(argc, argv, "param");
    ros::NodeHandle nh;
    //******增***********//
    //方法1:nh
    nh.setParam("radius", 1);
    //方法2:ros::param
    ros::param::set("length", 2);
    //*******改*******//
    //方法1&&2同上直接覆盖就行
    //********查*******//
    
}
```
   2. 获取
```cpp
#include "ros/ros.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
int main(int argc, char** argv){
    setlocale(LC_ALL,"");
    ros::init(argc, argv, "param");
    ros::NodeHandle nh;
    //nh.param***************************//
    //********查*******//
    //方法1.param,查询到的话就返回正确值，没查询到的话就返回默认值
    int radius = nh.param("radius", 1);//查询键为"radius"的函数值，若是没有的，返回1
    ROS_INFO("radius = %d", radius);
    //方法2：getParam，查询到的话就返回true,将正确值赋给radius1,否则就是false
    int radius1 = 0;
    bool res = nh.getParam("radius", radius1);
    if (res){
        ROS_INFO("getParam获取的半径是:%d", radius1);
    }
    else{
        ROS_INFO("被查询的变量不存在");
    }
    //方法3：getParamCached()用法同getParam()
    bool res1 = nh.getParamCached("radius", radius1);
    if (res1){
        ROS_INFO("getParamCached获取的半径是:%d", radius1);
    }
    else{
        ROS_INFO("被查询的变量不存在");
    }
    //4.getParamNames
    vector<string> names;
    nh.getParamNames(names);//获取每一个键的名称
    names.push_back("a");
    names.push_back("b");
    ///方法1:for--auto
    for (auto &&name : names){
        ROS_INFO("遍历的元素是%s",name.c_str());
    }
    ///方法2：for--iter,容易乱码
    vector<string>::iterator iter = names.begin();
    for (;iter != names.end(); iter++){
        cout << "键:" << *iter << endl;
    }
    //5.hasParam，若是存在的话,返回true,否则flase
    bool flag1 = nh.hasParam("radius");//"radius"的值是int，所以必须返回bool或者int
    bool flag2 = nh.hasParam("radiusxxx");
    ROS_INFO("radius存在吗？%d", flag1);
    ROS_INFO("radius存在吗？%d", flag2);
    //6.searchParam
    string key;//由于"radius"的键是字符串，所以必须将返回值定为string
    nh.searchParam("radius", key);//查询的是radius,用key保存,若存在的话，将radius赋值给key,否则保持默认值
    ROS_INFO("搜索结果:%s", key.c_str());//若输出是string的话，则要将其转化为c_str(),否则会乱码
 
    //ros::param******************************//ros::param和nh.param模式完全一样
    //ros::param::param
    int radius_param = ros::param::param("radius", 11);
    ROS_INFO("radius_param = %d", radius_param);
    vector<string> names_param;
    ros::param::getParamNames(names_param);//得到所有参数的键后将其放入vector容器names_param中,然后就可以直接遍历
    ///方法1：for--auto
    for (auto &&name : names_param){
        ROS_INFO("键:%s", name.c_str());
    }
    ///方法2：for--iter
    vector<string>::iterator iter1 = names_param.begin();
    for (iter1; iter1 != names_param.end(); iter1++){
        cout << "键:" << *iter1 << endl;//这里用ROS_INFO势必会乱码，所以如果用for-iter输出，直接用cout;用for-auto输出，用ROS_INFO和cout都可
    }
    //ros::param::
    return 0;
}
```
   3. 删除
```cpp
#include "ros/ros.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
/*
ros::NodeHandle---->delParam
ros::param----del()
*/

int main(int argc, char** argv){
    setlocale(LC_ALL,"");
    ros::init(argc, argv, "param");
    ros::NodeHandle nh;
    //******NodeHandle*******//
    bool flag1 = nh.deleteParam("radius");//delete返回一个bool类型，若删除成功，则返回true
    if (flag1){
        ROS_INFO("deleteParam删除成功");
    }
    else{
        ROS_INFO("delelteParam删除失败");
    }
    //*******ros::param**********//
    bool flag2 = ros::param::del("radius");
    if (flag2){
        ROS_INFO("rosparam删除成功");
    }
    else{
        ROS_INFO("rosparam删除失败");
    }
    
}
```
   4. 总结
      1. 若是需要修改功能包的名称，修改cmakelist文件的project和xml的<name>param_service</name> 和 <description>The param_service package</description>这三个地方的功能包文件名
      2. 多个功能包下的执行文件不能重名
      3. 例如demo01/src/test01 ,demo02/src/test01,这样是不允许的，必须要将2个test01变成不同的值，否则会编译失败
      4. 功能
         1. nh.setParam(key,value):
         2. res = nh.param(key,flag):若能得到key的value，则res = value,否则res = flag, 
         3. res = nh.getParam(key, flag):若能得到key的值，则res = true,否则为false
         4. res = nh.getParamCached(key, flag):同上
         5. nh.getParamNames(vec):得到所有参数的名字，并赋值给vec
         6. res = nh.hasParam(key,flag)：若有key,则flag = key(value)
         7. res = nh.searchParam(key, flag):若有key的话，则res = true


1. for(auto:)语句
```cpp
#include <iostream>
#include <vector>
using namespace std;
void printVec(vector<int> &vec){
    for (int i = 0; i < vec.size(); i++){
        cout << vec[i] << endl;
    }
}
int main(){
    vector<int> vec = {1, 2, 3, 4};
//*****************第一种，不会改变vec中的值，相当于是值传递
    for (auto i : vec){
        i += 1;
    }
    printVec(vec);
//****************第二种,改变vec中的值，相当于是引用传递
    for (auto &i : vec){
        i += 1;
    }
    printVec(vec);
//****************第三种，会改变vec中的值，相当于是引用传递
    for (auto &&i : vec){
        i += 1;
    }
    printVec(vec);
}
```
* 注意：
  * 1.for(auto &i : vec)相当于python中的for (x in range),&i = x,vec = range,而auto是修饰符号
  * 2.i为值传递，&i ,&&i相当于是引用传递
  * 3.修改完ros.cpp后，再catkin_make后再执行rosrun xxxx ros.cpp，此时修改才能生效
  * 4.vector<int> vec, ros::string<int, int>(xxxx)利用到了模板和变量声明 

## 3.常用命令
    rosnode : 操作节点
    rostopic : 操作话题#话题对应消息
    rosmsg : 操作msg消息
    rosservice : 操作服务#服务对应SRV
    rossrv : 操作srv消息
    rosparam : 操作参数#最后一个param
    1. 2+2+2：node,prama;topic,msg;service,srv
    2. list,info,find,pub,echo,show,get,set为常用命令,可以直接用TAB补全命令
    3. 几个重要常用的：rostopic echo pkg 用来输出位置
    4. rostopic pub;rosservice call;rosparam get/set;

### 3-1.rosnode

rosnode 是用于获取节点信息的命令

1. rosnode ping    测试到节点的连接状态
2. rosnode list    列出活动节点
3. rosnode info    打印节点信息
4. rosnode machine    列出指定设备上节点
5. rosnode kill    杀死某个节点
6. rosnode cleanup    清除不可连接的节点#就是清除已经死亡的但是rosmaster还不知道的节点

    rosnode ping

    测试到节点的连接状态

    rosnode list

    列出活动节点

    rosnode info

    打印节点信息

    rosnode machine

    列出指定设备上的节点

    rosnode kill

    杀死某个节点

    rosnode cleanup

    清除无用节点，启动乌龟节点，然后 ctrl + c 关闭，该节点并没被彻底清除，可以使用 cleanup 清除节点

##可以通过rosrun info -h来查看相关帮助信息,
##也可通过rosnode -h来查看信息

### 3-2.rostopic
1. 命令  详细说明
   1. rostopic list   显示活动的话题目录
   2. rostopic echo [话题名称]   实时显示指定话题的消息内容
   3. rostopic find [类型名称]   示使用指定类型的消息的名称
   4. rostopic type [话题名称]   显示指定话题的消息类型 
   5. rostopic bw [话题名称]      显示指定话题的消息带宽（bandwidth） 
   6. rostopic hz [话题名称] 显示指定话题的消息数据发布周期
   7. rostopic info [话题名称]   显示指定话题的信息 
   8. rostopic pub [话题名称] [消息类型] [参数]    用指定的话题名称发布消息 

2. 详解：
   1. rostopic list：列出活动话题
　　通过将“-v”选项添加到rostopic list命令，可以分开发布话题和订阅话题，并将每个话题的消息类型一起显示。rostopic list -v

   2. rostopic echo [话题名称]：实时显示指定话题的消息内容
以下示例实时显示组成/turtle/pose话题的x、y、theta、linear_velocity和angular_velocity的数据。    

rostopic echo /turtle/pose

   3. rostopic find [类型名称]：显示使用指定类型的消息的话题    
rostopic find turtlesim/Pose

   4. rostopic type [话题名称]：显示指定话题的消息类型
rostopic type /turtle/pose

   5. rostopic bw [话题名称]：显示指定话题的消息数据带宽（bandwidth）
　　在以下示例中，用于/turtle/pose话题的数据带宽平均为每秒.25 KB。
rostopic bw /turtle/pose

   6. rostopic hz [话题名称]：显示指定话题的消息数据发布周期
　　在以下示例中，用户可以检查/turtle/pose数据的发布周期。从结果可以看出，该消息以大约62.5Hz（0.06秒= 6毫秒）的频率被发布。
rostopic hz /turtle/pose

   7. rostopic info [话题名称]：显示指定话题的信息
　　在以下示例中，用户可以看到/turtle/pose话题使用turtlesim/Pose消息类型，发布到/turtlesim节点，并且没有实际订阅的话题。
    
rostopic info /turtle/pose

   8. rostopic pub [话题名称] [消息类型] [参数]：使用指定的话题名称发布消息
以下是使用/turtle/cmd_vel话题名称发布类型为geometry_msgs/Twist的消息的示例。

rostopic pub /turtle/cmd_vel geometry_msgs/Twist -- ‘[2.0, 0.0, 0.0]’ ‘[0.0, 0.0, .8]’
rostopic pub -r 10 
　　每个选项的描述如下。

    -只发布一次消息（实际上只运行一次，但会像以前的结果一样运行3秒）。
    /turtle1/cmd_vel 指定的话题名称
    geometry_msgs/Twist 要发布的消息类型名称
    -- ‘[2.0, 0.0, 0.0]’ ‘[0.0, 0.0, 1.8]’ 在x轴坐标上以每秒2.0 m的速度移动，以z轴为中心，每秒旋转1.8rad


### 3-3.rosservice

rosservice包含用于列出和查询ROSServices的rosservice命令行工具。

调用部分服务时，如果对相关工作空间没有配置 path，需要进入工作空间调用 source ./devel/setup.bash

rosservice args 打印服务参数
rosservice call    使用提供的参数调用服务
rosservice find    按照服务类型查找服务
rosservice info    打印有关服务的信息
rosservice list    列出所有活动的服务
rosservice type    打印服务类型
rosservice uri    打印服务的 ROSRPC uri

1. rosservice list

列出所有活动的 service

2. rosservice args

打印服务参数

rosservice args /spawn
x y theta name

3. rosservice call

调用服务

为小乌龟的案例生成一只新的乌龟

rosservice call /spawn "x: 1.0
y: 2.0
theta: 0.0
name: 'xxx'"
name: "xxx"

//生成一只叫 xxx 的乌龟

4. rosservice find

根据消息类型获取话题

5. rosservice info

获取服务话题详情

6. rosservice type

获取消息类型

7. rosservice uri

获取服务器 uri


### 3-3.rosmsg

rosmsg是用于显示有关 ROS消息类型的 信息的命令行工具。

rosmsg 演示

rosmsg show    显示消息描述
rosmsg info    显示消息信息#show和info是一样的
rosmsg list    列出所有消息
rosmsg md5    显示 md5 加密后的消息
rosmsg package    显示某个功能包下的所有消息
rosmsg packages    列出包含消息的功能包

1. rosmsg list

会列出当前 ROS 中的所有 msg

2. rosmsg packages

列出包含消息的所有包

3. rosmsg package

列出某个包下的所有msg/rosmsg package 包名 
rosmsg package turtlesim

4. rosmsg show

显示消息描述

//rosmsg show 消息名称
rosmsg show turtlesim/Pose#前一个是包名，后一个是Pose.msg
结果:
float32 x
float32 y
float32 theta
float32 linear_velocity
float32 angular_velocity

5. rosmsg info

作用与 rosmsg show 一样

### 3-5.rossrv

rossrv是用于显示有关ROS服务类型的信息的命令行工具，与 rosmsg 使用语法高度雷同。

rossrv show    显示服务消息详情
rossrv info    显示服务消息相关信息
rossrv list    列出所有服务信息
rossrv md5    显示 md5 加密后的服务消息
rossrv package    显示某个包下所有服务消息
rossrv packages    显示包含服务消息的所有包

1. rossrv list

会列出当前 ROS 中的所有 srv 消息

2. rossrv packages

列出包含服务消息的所有包

3. rossrv package

列出某个包下的所有msg

//rossrv package 包名 
rossrv package turtlesim

4. rossrv show

显示消息描述

rossrv show 消息名称
rossrv show turtlesim/Spawn
结果:
float32 x
float32 y
float32 theta
string name
string name

rossrv info

作用与 rossrv show 一致

rossrv md5

对 service 数据使用 md5 校验(加密)

### 3-6.rosparam
1. rosparam list
列出所有参数

2. rosparam list

3. rosparam set
设置参数

rosparam set name huluwa

//再次调用 rosparam list 结果
/name  

4. rosparam get

获取参数

rosparam get name

//结果
huluwa

5. rosparam delete

删除参数

rosparam delete name

6. rosparam load(先准备 yaml 文件)

从外部文件加载参数

rosparam load xxx.yaml

7. rosparam dump

将参数写出到外部文件

rosparam dump yyy.yaml

## 4.通信机制实际操作
### 4-1.话题发布
1. 话题与消息获取
准备: 先启动键盘控制乌龟运动案例。

   1. 话题获取
获取话题:/turtle1/cmd_vel
通过计算图查看话题，启动计算图:

rqt_graph
或者通过 rostopic 列出话题:

rostopic list
   2. 消息获取
获取消息类型:geometry_msgs/Twist

rostopic type /turtle1/cmd_vel
获取消息格式:

rosmsg info geometry_msgs/Twist
响应结果:

geometry_msgs/Vector3 linear
  float64 x
  float64 y
  float64 z

geometry_msgs/Vector3 angular
  float64 x
  float64 y
  float64 z
linear(线速度) 下的xyz分别对应在x、y和z方向上的速度(单位是 m/s)；

angular(角速度)下的xyz分别对应x轴上的翻滚、y轴上俯仰和z轴上偏航的速度(单位是rad/s)。

3. 实现发布节点
创建功能包需要依赖的功能包: roscpp rospy std_msgs geometry_msgs

实现方案A: C++
```cpp
/*
    编写 ROS 节点，控制小乌龟画圆

    准备工作:
        1.获取topic(已知: /turtle1/cmd_vel)
        2.获取消息类型(已知: geometry_msgs/Twist)
        3.运行前，注意先启动 turtlesim_node 节点

    实现流程:
        1.包含头文件
        2.初始化 ROS 节点
        3.创建发布者对象
        4.循环发布运动控制消息
*/

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    // 2.初始化 ROS 节点
    ros::init(argc,argv,"control");
    ros::NodeHandle nh;
    // 3.创建发布者对象
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1000);
    // 4.循环发布运动控制消息
    //4-1.组织消息
    geometry_msgs::Twist msg;
    msg.linear.x = 1.0;
    msg.linear.y = 0.0;
    msg.linear.z = 0.0;

    msg.angular.x = 0.0;
    msg.angular.y = 0.0;
    msg.angular.z = 2.0;

    //4-2.设置发送频率
    ros::Rate r(10);
    //4-3.循环发送
    while (ros::ok())
    {
        pub.publish(msg);

        ros::spinOnce();
    }


    return 0;
}
```

### 4-2.话题订阅
实现分析:

首先，需要启动乌龟显示以及运动控制节点并控制乌龟运动。
要通过ROS命令，来获取乌龟位姿发布的话题以及消息。
编写订阅节点，订阅并打印乌龟的位姿。
实现流程:

通过ros命令获取话题与消息信息。
编码实现位姿获取节点。
启动 roscore、turtlesim_node 、控制节点以及位姿订阅节点，控制乌龟运动并输出乌龟的位姿。
1. 话题与消息获取

获取话题:/turtle1/pose

rostopic list
获取消息类型:turtlesim/Pose

rostopic type  /turtle1/pose
获取消息格式:

rosmsg info turtlesim/Pose
响应结果:

​float32 x
float32 y
float32 theta
float32 linear_velocity
float32 angular_velocity

2.实现订阅节点
创建功能包需要依赖的功能包: roscpp rospy std_msgs turtlesim
```cpp
/*  
    订阅小乌龟的位姿: 时时获取小乌龟在窗体中的坐标并打印
    准备工作:
        1.获取话题名称 /turtle1/pose
        2.获取消息类型 turtlesim/Pose
        3.运行前启动 turtlesim_node 与 turtle_teleop_key 节点

    实现流程:
        1.包含头文件
        2.初始化 ROS 节点
        3.创建 ROS 句柄
        4.创建订阅者对象
        5.回调函数处理订阅的数据
        6.spin
*/

#include "ros/ros.h"
#include "turtlesim/Pose.h"

void doPose(const turtlesim::Pose::ConstPtr& p){
    ROS_INFO("乌龟位姿信息:x=%.2f,y=%.2f,theta=%.2f,lv=%.2f,av=%.2f",
        p->x,p->y,p->theta,p->linear_velocity,p->angular_velocity
    );
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    // 2.初始化 ROS 节点
    ros::init(argc,argv,"sub_pose");
    // 3.创建 ROS 句柄
    ros::NodeHandle nh;
    // 4.创建订阅者对象
    ros::Subscriber sub = nh.subscribe<turtlesim::Pose>("/turtle1/pose",1000,doPose);
    // 5.回调函数处理订阅的数据
    // 6.spin
    ros::spin();
    return 0;
}
```
2.服务客户端实现
创建功能包需要依赖的功能包: roscpp rospy std_msgs turtlesim

实现方案A:C++
```cpp
/*
    生成一只小乌龟
    准备工作:
        1.服务话题 /spawn
        2.服务消息类型 turtlesim/Spawn
        3.运行前先启动 turtlesim_node 节点

    实现流程:
        1.包含头文件
          需要包含 turtlesim 包下资源，注意在 package.xml 配置
        2.初始化 ros 节点
        3.创建 ros 句柄
        4.创建 service 客户端
        5.等待服务启动
        6.发送请求
        7.处理响应

*/

#include "ros/ros.h"
#include "turtlesim/Spawn.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    // 2.初始化 ros 节点
    ros::init(argc,argv,"set_turtle");
    // 3.创建 ros 句柄
    ros::NodeHandle nh;
    // 4.创建 service 客户端
    ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
    // 5.等待服务启动
    // client.waitForExistence();
    ros::service::waitForService("/spawn");
    // 6.发送请求
    turtlesim::Spawn spawn;
    spawn.request.x = 1.0;
    spawn.request.y = 1.0;
    spawn.request.theta = 1.57;
    spawn.request.name = "my_turtle";
    bool flag = client.call(spawn);//在已经生成一个新乌龟的情况下就不能生成旧乌龟
    // 7.处理响应结果
    if (flag)
    {
        ROS_INFO("新的乌龟生成,名字:%s",spawn.response.name.c_str());
    } else {
        ROS_INFO("乌龟生成失败！！！");
    }


    return 0;
}
```

### 4-3.服务调用
实现分析:

首先，需要启动乌龟显示节点。
要通过ROS命令，来获取乌龟生成服务的服务名称以及服务消息类型。
编写服务请求节点，生成新的乌龟。
实现流程:

通过ros命令获取服务与服务消息信息。
编码实现服务请求节点。
启动 roscore、turtlesim_node 、乌龟生成节点，生成新的乌龟。
1. 服务名称与服务消息获取
获取话题:/spawn

rosservice list
获取消息类型:turtlesim/Spawn

rosservice type /spawn
获取消息格式:

rossrv info turtlesim/Spawn
响应结果:

float32 x
float32 y
float32 theta
string name
**-------**
string name

2. 订阅节点(见上面)

### 4-4.参数设置
实现分析:

首先，需要启动乌龟显示节点。
要通过ROS命令，来获取参数服务器中设置背景色的参数。
编写参数设置节点，修改参数服务器中的参数值。
实现流程:

通过ros命令获取参数。
编码实现服参数设置节点。
启动 roscore、turtlesim_node 与参数设置节点，查看运行结果。

1. 参数名获取
获取参数列表:

rosparam list
响应结果:

/turtlesim/background_b
/turtlesim/background_g
/turtlesim/background_r

2. 参数修改
实现方案A:C++
```cpp
/*
    注意命名空间的使用。

*/
#include "ros/ros.h"
int main(int argc, char *argv[])
{
    ros::init(argc,argv,"haha");

    ros::NodeHandle nh("turtlesim");
    //ros::NodeHandle nh;

    // ros::param::set("/turtlesim/background_r",0);
    // ros::param::set("/turtlesim/background_g",0);
    // ros::param::set("/turtlesim/background_b",0);

    nh.setParam("background_r",0);
    nh.setParam("background_g",0);
    nh.setParam("background_b",0);


    return 0;
}
```
### 4-5.总结
在上面的例子中
1. publisher和subcriber在这个案例中分别对应publisher和乌龟的节点
2. 因为没有自定义srv和msg文件，所以在cmake和xml中都无须配置依赖文件，cmake添加add_executabel和target_link_libraries()就行，xml维持不变
