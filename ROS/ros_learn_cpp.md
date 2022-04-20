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
         1. 例如demo01/src/test01 ,demo02/src/test01,这样是不允许的，必须要将2个test01变成不同的值，否则会编译失败


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