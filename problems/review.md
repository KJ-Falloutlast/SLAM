"ROS"
1.话题通信
1-1.publisher
#! /usr/bin/env
import rospy
from std_msgs.msg import String
if __name__ == '__main__':

    rospy.init_node('publisher')

    pub = rospy.Publisher('house', String, queue_size=10)

    msg = String()

    count = 0

    rate = rospy.Rate(1)
    
    while not rospy.is_shutdown():
        msg.data = str(count)#msg.data对象必须为一个str对象

        pub.publish(msg)

        rate.sleep()

        rospy.loginfo('发布的数据是%s'%msg.data)

        count += 1
        count %= 154
        #表示每次执行到153再循环一次

.执行顺序：'''1.创建节点--->2.创建发布对象---->3.创建爱发布逻辑：
3-1.创建数据对象；3-2.创建发布频率；3-3.创建循环：3-3-1.发布数据；
3-3-2：睡觉；3-3-3：显示数据'''

1-2.subcriber
#! /usr/bin/env
import rospy
from std_msgs.msg import String

def doMsg(msg):

    rospy.loginfo('您输出的结果是:%s'%msg.data)

if __name__ == '__main__':
    
    rospy.init_node('subscriber')

    sub = rospy.Subscriber('house', String, doMsg, queue_size=10)
    
###相当于把msg=String()传递给doMsg的msg中

    rospy.spin()

.执行顺序：'''1.创建节点--->2.创建订阅对象---->3.创建回调函数---->4.spin()'''

1-2.roslaunch问题

<launch>

    <node pkg='model01' type='model01_pub.py' name='publisher' output='screen'/>
    <node pkg='model01' type='model01_sub.py' name='subscriber' output='screen'/><!--结束标签'/'不能忘记'-->

</launch>

注意事项：###########################
    .<!--结束标签'/'不能忘记'-->
    .chmod +x xxxx
    .正确的格式：
    <launch>
        <node name="demo" pkg="demo_package"
              type="demo_pub" output="screen"/>
        <node name="demo" pkg="demo_package"
              type="demo_sub" output="screen"/>
    </launch>
    .启动：roslaunch PACKAGE_NAME LAUNCH_FILE_NAME
    .roslaunch只能一次性output一个节点

1-3.roalaunch详解
    1.launch标签小结

    1.0 <launch>

    launch标签就像一个有容乃大的括号，规定了一片区域，所有的launch文件都由<launch>开头，由</launch>结尾，所有的描述标签都要写在<launch></launch>之间

    <launch>
    ……
    ……
    ……
    </launch>


    1.1 <node>

    node标签可以说是launch文件里最常见的标签了，每个node标签里包括了ROS图中节点的名称属性name、该节点所在的包名pkg以及节点的类型type（其实就是可执行文件的名称，如果是用Python编写的就填写xxx.py，如果是cpp就写编译生成的可执行文件名），在上面的例子中还出现了output这个东西，这个属性在调试阶段很有用，output=“screen”表示了将终端输出转储在当前的控制台上，而不是在日志文件中。
    属性  属性作用
    name="NODE_NAME"    为节点指派名称，这将会覆盖掉ros::init()定义的node_name
    pkg="PACKAGE_NAME"  节点所在的包名
    type="FILE_NAME"    执行文件的名称如果是用Python编写的就填写xxx.py，如果是cpp就写编译生成的可执行文件名
    output="screen" 终端输出转储在当前的控制台上，而不是在日志文件中
    respawn="true"  当roslaunch启动完所有该启动的节点之后，会监测每一个节点，保证它们正常的运行状态。对于任意节点，当它终止时，roslaunch 会将该节点重启
    required="true" 当被此属性标记的节点终止时，roslaunch会将其他的节点一并终止。注意此属性不可以与respawn="true"一起描述同一个节点
    launch-prefix = "command-prefix"    我的理解是，相当于在执行启动命令时加上一段命令前缀
    ns = "NAME_SPACE"   这个属性可以让你在自定义的命名空间里运行节点
   
    1.2<include>

    该标签可以导入另一个roslaunch XML文件到当前文件。
    属性  属性作用
    file ="$(find pkg-name)/path/filename.xml"  指明我们想要包含进来的文件
    ns="NAME_SPACE" 相对NAME_SPACE命名空间导入文件

    使用起来就像下面这样

    <include file="$(find demo)/launch/demo.launch" ns="demo_namespace"/>

    1.3<remap>

    remap标签顾名思义重映射，ROS支持topic的重映射，remap标签里包含一个original-name和一个new-name，及原名称和新名称。
    比如现在你拿到一个节点，这个节点订阅了"/chatter"topic，然而你自己写的节点只能发布到"/demo/chatter"topic，由于这两个topic的消息类型是一致的，你想让这两个节点进行通讯，那么可以在launch文件中这样写：

    <remap from="chatter" to="demo/chatter"/>

    这样就可以直接把/chattertopic重映射到/demo/chatter，这样子不用修改任何代码，就可以让两个节点进行通讯。
    如果这个 remap标签写在与 node 元素的同一级，而且在launch 元素内的最顶层。 那么这个重映射将会作用于launch文件中所有的节点。
    1.4<param>

    param标签的作用相当于命令行中的rosparam set
    比如现在在参数服务器中添加一个名为demo_param，值为666的参数

    <param name="demo_param" type="int" value="666"/>


    1.5<rosparam>

    rosparam标签允许从YAML文件中一次性导入大量参数。
    使用起来就像这样：

    <rosparam command="load" file="$(find pkg-name)/path/name.yaml"/>


    1.6<arg>

    arg标签用来在launch文件中定义参数，arg和param在ROS里有根本性的区别，就像局部变量和全局变量的区别一样。arg不储存在参数服务器中，不能提供给节点使用，只能在launch文件中使用。param则是储存在参数服务器中，可以被节点使用。

    <arg name="demo"/>


    像上面这样，就简单地声明了一个参数，名叫demo，但是声明不等于定义，我们需要给他赋值，在赋值之后参数才能够发挥作用。

    <arg name="demo" value="666"/>
    <arg name="demo" default="666"/>

 

    以上是两种简单的赋值方法，两者的区别是使用后者赋值的参数可以在命令行中像下面这样被修改，前者则不行。

    roslaunch demo demo.launch demo:=6666


    arg还有更加高级，也更加灵活的用法：
    $(arg arg_name)
    当$(arg arg_name)出现在launch文件任意位置时，将会自动替代为所给参数的值。
    1.7<group>

    group标签可以将若干个节点同时划分进某个工作空间。

    <group ns="demo_1">
        <node name="demo_1" pkg="demo_1" type="demo_pub_1" output="screen"/>
        <node name="demo_1" pkg="demo_1" type="demo_sub_1" output="screen"/>
    </group>
    <group ns="demo_2">
        <node name="demo_2" pkg="demo_2" type="demo_pub_2" output="screen"/>
        <node name="demo_2" pkg="demo_2" type="demo_sub_2" output="screen"/>
    </group>

    group标签还可以做到对node的批量管理。比如我可以同时终止在同一个group中的节点。

    <group if="1-or-0">
    ……
    ……
    ……
    </group>

    <group unless="1-or-0">
    ……
    ……
    ……
    </group>


    第一种情况，当if属性的值为0的时候将会忽略掉<group></group>之间的标签。
    第二种恰好相反，当if属性的值为1的时候将会忽略掉<group></group>之间的标签。
    但是我们通常不会直接用1或0来定义if标签。因为这样不够灵活。
    通常会搭配$(arg arg_name)来使用。
    demo.launch文件

    <launch>
        <include file="include.launch">
            <arg name="demo_arg" value="1"/>
        </include>
    </launch>

    include.launch文件

    <launch>
        <arg name="demo_arg"/>
        <group if="$(demo_arg)">
            <node name="demo" pkg="demo" type="demo_pub" output="screen"/>
            <node name="demo" pkg="demo" type="demo_sub" output="screen"/>
        </group>
    </launch>

2.服务通信

2-1.client:
#! /usr/bin/env python
import rospy
from model01.srv import *

if __name__ == '__main__':

    rospy.init_node('client')
    
    client = rospy.ServiceProxy('AddInts', AddInts)
    
    req = AddIntsRequest()

    req.num1 = int(sys.argv[1])
    req.num2 = int(sys.argv[2])

    resp = client.call(req)
    
    rospy.loginfo('响应的结果:%d',resp.sum1)//resp只能用响应参数类型,所以resp.num1是错误的


2-2.server:
#! /usr/bin/env python
import rospy
from model01.srv import *
def doRequest(req):
    num1 = req.num1
    num2 = req.num2
    sum1 = req.sum1
    rospy.loginfo('num1 + num2 =%f'%sum1)
    resp = addIntsResponse(req)
    return resp
if __name__ == '__main__':

    rospy.init_node('server')
    
    server = rospy.Service('house', addInts, doRequest)

    rospy.spin()


注：
/1.逻辑：
client:创建节点---->创建客户端--->创建请求逻辑：1.创建请求对象req = AddIntsRequest();2.发送请求resp = client.call(req)
server:创建节点---->创建服务端--->创建回调函数doRequest()：1.解析请求数据;2.创建并返回响应对象resp = addIntsResponse(req)并返回resp
----->rospy.spin()
publisher：1.创建节点--->2.创建发布对象---->3.创建发布逻辑：
3-1.创建数据对象；3-2.创建发布频率；3-3.创建循环：3-3-1.发布数据；3-3-2：睡觉；3-3-3：显示数据

subscriber:1.创建节点--->2.
创建订阅对象---->3.创建回调函数---->4.spin()
/2.注意事项：

1.在cmake中：find_package:message_generation---->add_message_file:Person.msg
----->generate_messages:std_msgs---->catkin_package:message_runtime------>catkin_install_python
2.在xml中：message_generation+message_runtime<--->build_depend+build_export_depend+exec_depend
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
  
3.导包：c/s and p/s都要导入:from model.msg/model.srv import *


---------------------------------------------------------------------------------
"cpp"
1.数据类型：
int:int(4) | long(4) |long long(4);float(4),double(8);
char(4)；string(多少字符多少字节）:#include <string>；
bool; 
输入：cin >> a //cout输出往左边；cin输入往右边

k
2.运算符：
算术：+ ,- ,* ,++,--
逻辑：&&,||,~
关系：>,>=,<,<=,==,!=
赋值：=,+=,-=,*=,/=,%=，/=，&=, |=,^=.>>=,<<=
位：&,|,!,^,>>,<<,

3.语句
3-1.条件语句

#include <iostream>
#include <string>
int main(){
    int a = 1;
    int b = 0;
    string c = "abc";
    char d = 'd';
    cout << "请输入一个数"；
    cin >> a;
    if (a>b){

        cout << "True";
    }

    else if (a = b)
    {
        cout << "False"
    }
}   else{

    cout << "True"
    return 0;
}

