# 1.通信机制
## 1-1.话题通信
1. 话题通信基本操作
    * 发布数据
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
    * 接收数据
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
    * 调整cmake文件
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

2. 话题通信自定义msg调用
    * 2-1.流程：
      * 1. 修改xml文件和cmake文件：
        * 在cmake中:
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
        ```
        * 在xml中：message_generation+message_runtime<--->build_depend+build_export_depend+exec_depend
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
      * 2. 发布方的实现
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
      * 3.订阅方的实现
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
    * 2-2.总结：
      * 在pub_sub目录下创建msg/Person.msg
      * 配置xml和cmake文件
        * 1.cmake:message_runtime message_generation std_msg , Person.msg;add_excutable,add_dependencies
        * 2.xml:见上面
        * 3.catkin_make
        * 4.将devep/include/**的头文件路径加到cpp_jason文件中
        * 5.编写pub_msg.cpp+sub_msg.cpp
        * 6.修改cmakelist文件：Person.msg;add_excutable
        * 6.catkin_make
        * 7.rosrun执行