
'1.ros环境搭建'

python:

1.测试ros:roscore---rosrun turtlesim turtlesim_node---rosrun turtlesim turtle_teleop_key
2.创建工作空间并初始化：
makedir -p demo_ws/src
cd demo_ws
catkin_make#进入到工作空间中进行编译(cd demo03_ws-->code .启动vscode)
cd src
catkin_create_pkg helloworld roscpp rospy std_msgs
#helloworld是包名，roscpp rospy std_msgs分别对应使用c++的库，python的库，标准消息库
#c++库运行效率高，开发效率低，python库反之
mkdir scripts /helloworld
cd scripts
gedit helloworld.py
编辑在helloworld下的CamkeList.txt 文件
cd demo_ws
catkin_make
source ./devel/setup.bash
rosrun 包名 自定义文件名.py
'''source ~/工作空间/devel/setup.bash可以直接添加进.bashrc文件
方法一：使用gedit编辑.bashrc文件，最后添加内容)(ctrl+h找到.bashrc,这样对这个文件就可以每次新开一个终端的情况下仍然能够执行rosrun helloworld helloworld.py)
方法二：echo "source ~/工作空间/devel/setup.bash" >> ~.bashrc'''

c++:

mkdir -p cpp_ws/src
cd cpp_ws
catkin_make
cd src
catkin_create_pkg demo01 roscpp std_msgs
cd demo01/src
touch helloworld.cpp
    #include "ros/ros.h"    // 此处一定要用双引号而非单引号,c++的单双引号要搞明白

    int main(int argc, char *argv[])
    {
        ros::init(argc,argv,"helloworld_node");

        ROS_INFO("hello world!");
        return 0;

    }

修改cmake文件：
add_executable(hello src/helloworld.cpp)#被映射名+映射名，可以通过hello映射到helloworld.cpp文件
target_link_libraries(hello#目标链接库,名字改成上面的被映射名
${catkin_LIBRARIES}
)



3.编写脚本#可在/demo01_ws/src/helloworld/下直接用gedit helloworld.py
#!/usr/bin/env python
##指定解释器
#1.导包
import rospy
#2.编写入口
if __name__=='__main__':
    rospy.init_node('hello_p')
    #3.初始化ros节点
    rospy.loginfo('hello world')
    #4.输入日志

4.添加可执行权限：cd ~/demo01_ws/src/hellowold/ --- chmod +x helloworld.py##利用ll来查看是否有可执行权限
总体的文件树：
demo01_ws
|
├── build
│  
├── devel
│   ├── cmake.lock
│   ├── env.sh
│   ├── lib
│   ├── local_setup.bash
│   ├── local_setup.sh
│   ├── local_setup.zsh
│   ├── setup.bash#生效文件
│   ├── setup.sh
│   ├── _setup_util.py
│   └── setup.zsh
└── src
    ├── ~.bashrc
    ├── CMakeLists.txt -> /opt/ros/noetic/share/catkin/cmake/toplevel.cmake
    └── helloworld
        ├── CMakeLists.txt
        ├── include
        │   └── helloworld
        ├── package.xml
        └── src
            └── helloworld.py
5.编辑配置文件：CMakeLists.txt##此步骤的目的是让noetic下可接入python3
mkdir /demo01_ws/src/hellowold/scripts#在helloworld文件里面添加脚本文件夹,这一步不能忘
gedit hellowold.py--->添加可执行权限
然后编辑配置文件：


#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# catkin_install_python(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

|
|
v

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
 catkin_install_python(PROGRAMS
  scripts/helloworld.py
   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )


cd demo01_ws
catkin_make
##此处bug:
'''find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs#s千万不要掉了否则编译失败
)'''
source ./devel/setup.bash#刷新环境变量
rosrun helloworld helloworld.py##第一个helloworld是包名，第二个是脚本

6.集成开发环境：
terminator终端配置https://blog.csdn.net/weixin_42369926/article/details/99712378

    下载terminator

        sudo apt-get update
        sudo apt-get install terminator

    新建terminator配置文件

        mkdir ~/.config/terminator
        vim ~/.config/terminator/config

    配置terminator

        [global_config]
          geometry_hinting = False
          handle_size = 1
          inactive_color_offset = 1.0
          title_font = mry_KacstQurn Bold 11
          title_hide_sizetext = True
        [keybindings]
        [layouts]
          [[default]]
            [[[child1]]]
              parent = window0
              profile = default
              type = Terminal
            [[[window0]]]
              parent = ""
              type = Window
        [plugins]
        [profiles]
          [[default]]
            background_darkness = 0.49
            background_image = '背景图片路径'
            background_type = transparent
            cursor_color = "#3036ec"
            custom_command = tmux
            font = Ubuntu Mono 13
            foreground_color = "#ffffff"
            login_shell = True
            scroll_background = False
            show_titlebar = False
            use_system_font = False

    terminator常用快捷方式
    序号  快捷键 功能
    1   Ctrl+Shift+O    水平分割终端
    2   Ctrl+Shift+E    垂直分割终端
    3   Ctrl+Shift+F    搜索
    4   Ctrl+Shift+C    复制
    5   Ctrl+Shift+V    粘贴
    6   Ctrl+Shift+W    关闭当前终端
    7   Ctrl+Shift+Q    退出当前窗口
    8   Ctrl+Shift+T    打开终端
    9   Ctrl+Shift+X    切换显示当前窗口
    10  F11 全屏状态
    11  Ctrl+Shift+G    clear屏幕
    12  Ctrl+Shift+Right    在垂直分割的终端中将分割条向右移动
    13  Ctrl+Shift+Left 在垂直分割的终端中将分割条向左移动
    14  Ctrl+Shift+S    隐藏/显示滚动条

7.当mv,rm,mkdir,touch,cp,等权限不够时可加sudo
# sudo cp -rf VSCode-linux-x64 /opt
#sudo rm -r VSCode-linux-x64/强制删除
#sudo chmod 777 Python.sublime-package (最高权限)
#rm -r dir
8.如何下载vscode及其配置：
    Ctrl+Shift+P, F1
    打开命令面板

    Ctrl+p    
    快速打开文件

    Ctrl+Shift+N     
    打开新窗口/实例

    Ctrl+Shift+W    
    关闭窗口/实例

基础编辑
    
    Ctrl+X      
    剪切当前行

    Ctrl+C    
    复制当前行

    Alt+ ↑ / ↓    
    向上/向下移动当前行

    Shift+Alt + ↓ / ↑    
    向上/向下复制当前行

    Ctrl+Shift+K   
    删除当前行

    Ctrl+Enter    
    在当前行以下插入

    Ctrl+Shift+Enter    
    在当前行以上插入

    Ctrl+Shift+\      
    跳转到匹配的括号

    Ctrl+] / [    
    缩进/取消缩进

    Home     
    转到行首

    End     
    转到行尾

    Ctrl+Home    
    转到页首

    Ctrl+End     
    转到页尾

    Ctrl+↑ / ↓   
    向上/向下滚动

    Alt+PgUp / PgDown
    向上/向下翻页

    Ctrl+Shift+[ 
    折叠当前代码块

    Ctrl+Shift+]
    展开当前代码块

    Ctrl+K Ctrl+[  
    折叠所有子代码块

    Ctrl+K Ctrl+]
    展开所有子代码块

    Ctrl+K Ctrl+0
    折叠所有代码块

    Ctrl+K Ctrl+J   
    展开所有代码块

    Ctrl+K Ctrl+C  
    添加行注释

    Ctrl+K Ctrl+U
    删除行注释

    Ctrl+/   
    添加/删除行注释

    Shift+Alt+A 
    添加/删除块注释

    Alt+Z  
    自动换行

导航   

    Ctrl+T  
    显示所有符号

    Ctrl+G
    跳转到行

    Ctrl+P    
    跳转到文件

    Ctrl+Shift+O      
    跳转到符号

    Ctrl+Shift+M  
    显示问题面板

    F8 
    跳转到下一个问题或警告

    Shift+F8
    跳转到前一个问题或警告

    Ctrl+Shift+Tab
    显示编辑器文件历史

    Alt+ ← / →
    向后/向前查看文件

    Ctrl+M
    开启/关闭 Tab 移动焦点

搜索和替换
    Ctrl+F 
    查找
    
    Ctrl+H
    替换

    F3 / Shift+F3
    查找下一个/前一个

    Alt+Enter  
    选择所有匹配项

    Ctrl+D   
    选择下一个匹配项

    Ctrl+K Ctrl+D
    跳过当前选择项

    Alt+C / R / W
    切换大小写敏感/正则表达式/全词

多光标与选择
    Alt+Click       
    插入光标

    Ctrl+Alt+ ↑ / ↓
    向上/向下插入光标

    Ctrl+U 
    撤销上一个光标
    
    Shift+Alt+I
    在选中行的行尾插入光标
    
    Ctrl+I
    选择当前行
    
    Ctrl+Shift+L
    选择当前选中项的所有匹配项
    
    Ctrl+F2
    选择当前单词的所有匹配项

    Shift+Alt+→  
    扩展选择

    Shift+Alt+←
    缩小选择

    Shift+Alt + (drag mouse)
    列（框）选择

    Ctrl+Shift+Alt + (arrow key)
    列（框）选择

    Ctrl+Shift+Alt +PgUp/PgDown
向上页/下页列（框）选择
    2、自定义快捷键:(以下代码表示方向键可以自定义)
    // Place your key bindings in this file to overwrite the defaults
    // alt + i, j, k,l
    [{
      "key": "alt+j",
      "command": "cursorLeft"
      },
      {
      "key": "alt+j ",
      "command": "list.collapse",
      "when": "listFocus"
      },
      {
      "key": "alt+k",
      "command": "cursorDown"
      },
      {
      "key": "alt+k",
      "command": "repl.action.historyNext",
      "when": "editorTextFocus && inDebugRepl && onLastDebugReplLine"
      }, {
      "key": "alt+k",
      "command": "settings.action.focusSettingsFile",
      "when": "inSettingsSearch"
      }, {
      "key": "alt+k",
      "command": "showNextParameterHint",
      "when": "editorTextFocus && parameterHintsMultipleSignatures && parameterHintsVisible"
      }, {
      "key": "alt+k",
      "command": "selectNextSuggestion",
      "when": "editorTextFocus && suggestWidgetMultipleSuggestions && suggestWidgetVisible"
      }, {
      "key": "alt+k",
      "command": "keybindings.editor.focusKeybindings",
      "when": "inKeybindings && inKeybindingsSearch"
      }, {
      "key": "alt+k",
      "command": "keybindings.editor.focusKeybindings",
      "when": "inKeybindings && inKeybindingsSearch"
      }, {
      "key": "alt+k",
      "command": "search.focus.nextInputBox",
      "when": "inputBoxFocus && searchViewletVisible"
      }, {
      "key": "alt+k",
      "command": "workbench.action.interactivePlayground.arrowDown",
      "when": "interactivePlaygroundFocus && !editorTextFocus"
      },
      {
      "key": "alt+l",
      "command": "cursorRight"
      },
      {
      "key": "alt+l",
      "command": "repl.action.acceptSuggestion",
      "when": "editorTextFocus && inDebugRepl && suggestWidgetVisible"
      }, {
      "key": "alt+l",
      "command": "list.expand",
      "when": "listFocus"
      },
      {
      "key": "alt+i",
      "command": "cursorUp"
      },
      {
      "key": "alt+i",
      "command": "repl.action.historyPrevious",
      "when": "editorTextFocus && inDebugRepl && onLastDebugReplLine"
      }, {
      "key": "alt+i",
      "command": "showPrevParameterHint",
      "when": "editorTextFocus && parameterHintsMultipleSignatures && parameterHintsVisible"
      }, {
      "key": "alt+i",
      "command": "selectPrevSuggestion",
      "when": "editorTextFocus && suggestWidgetMultipleSuggestions && suggestWidgetVisible"
      },
      {
      "key": "alt+i",
      "command": "list.focusUp",
      "when": "listFocus"
      }, {
      "key": "alt+i",
      "command": "search.action.focusSearchFromResults",
      "when": "firstMatchFocus && searchViewletVisible"
      }, {
      "key": "alt+i",
      "command": "search.action.focusSearchFromResults",
      "when": "firstMatchFocus && searchViewletVisible"
      }, {
      "key": "alt+i",
      "command": "workbench.action.interactivePlayground.arrowUp",
      "when": "interactivePlaygroundFocus && !editorTextFocus"
      }
      ]
      
  

9.用vscode开发ros:
mkdir demo01_ws/src
cd demo01_ws
catkin_make
cd demo01_ws
code .
在/demo01_ws/src下catkin_create_pkg helloworld rospy std_msgs
ctrl+shift+B 调用编译,选择catkin_make:build
修改.vscode/tasks.json：##以后此步骤可以执行，即可以打开task.json，但是不必要修改此文件，直接默认即可

{
// 有关 tasks.json 格式的文档，请参见
// https://go.microsoft.com/fwlink/?LinkId=733558
"version": "2.0.0",
"tasks": [
    {
        "label": "catkin_make:debug", //代表提示的描述性信息
        "type": "shell",  //可以选择shell或者process,如果是shell代码是在shell里面运行一个命令，如果是process代表作为一个进程来运行
        "command": "catkin_make",//这个是我们需要运行的命令
        "args": [],//如果需要在命令后面加一些后缀，可以写在这里，比如-DCATKIN_WHITELIST_PACKAGES=“pac1;pac2”
        "group": {"kind":"build","isDefault":true},
        "presentation": {
            "reveal": "always"//可选always或者silence，代表是否输出信息
        },
        "problemMatcher": "$msCompile"
    }
]
}
在demo01_ws/src/hellowold/scripts下新建helloworld.py并添加可执行权限

写脚本：
#! /usr/bin/env python
"""
    Python 版本的 HelloVScode，执行在控制台输出 HelloVScode
    实现:
    1.导包
    2.初始化 ROS 节点
    3.日志输出 HelloWorld


"""

import rospy # 1.导包

if __name__ == "__main__":

    rospy.init_node("Hello_Vscode_p")  # 2.初始化 ROS 节点
    rospy.loginfo("Hello VScode, 我是 Python ....")  #3.日志输出 HelloWorld

配置 CMakeLists.txt：
catkin_install_python(PROGRAMS scripts/自定义文件名.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

编译: ctrl + shift + B#实际上已经代替了catkin_make 
激活：source ./devel/setup.bash
rosrun helloworld helloworld.py

10.用launch文件来控制输出：

1..需求

    一个程序中可能需要启动多个节点，比如:ROS 内置的小乌龟案例，如果要控制乌龟运动，要启动多个窗口，分别启动 roscore、乌龟界面节点、键盘控制节点。如果每次都调用 rosrun 逐一启动，显然效率低下，如何优化?

官方给出的优化策略是使用 launch 文件，可以一次性启动多个 ROS 节点。
2.实现

    选定功能包右击 ---> 添加 launch 文件夹

    选定 launch 文件夹右击 ---> 添加 launch 文件

    编辑 launch 文件内容

    <launch>
        <node pkg="helloworld" type="demo_hello" name="hello" output="screen" />
        <node pkg="turtlesim" type="turtlesim_node" name="t1"/>
        <node pkg="turtlesim" type="turtle_teleop_key" name="key1" />
        <!-- 结尾/不能忘 -->
        <!-- node为节点代号，pkg代表包名，type为节点，name为节点命名 -->
        <!-- 每次新开一个终端都要执行source ./devel/setup.bash -->

    </launch>

    node ---> 包含的某个节点

    pkg -----> 功能包

    type ----> 被运行的节点文件

    name --> 为节点命名

    output-> 设置日志的输出目标

运行 launch 文件：roslaunch 包名 launch文件名

3.运行小乌龟:rosrun turtlesim turtlesim_node-->rosrun turtlesim turtle_teleop_key


11.ros架构:
demo01_ws
.
├── build
├── devel
│   ├── cmake.lock
│   ├── env.sh
│   ├── lib
│   ├── local_setup.bash
│   ├── local_setup.sh
│   ├── local_setup.zsh
│   ├── setup.bash
│   ├── setup.sh
│   ├── _setup_util.py
│   ├── setup.zsh
│   └── share
│       └── helloworld
│           └── cmake
│               ├── helloworldConfig.cmake
│               └── helloworldConfig-version.cmake
├── src
│   ├── CMakeLists.txt -> /opt/ros/noetic/share/catkin/cmake/toplevel.cmake
│   └── helloworld
│       ├── CMakeLists.txt
│       ├── include##*h
│       │   └── helloworld
│       ├── launch##用于存放*.launch文件
│       │   └── start_turtle.launch
│       ├── package.xml
│       ├── scripts##*.py和*.sh
│       │   └── helloworld.py
│       └── src##用于存放*.cpp文件
│           └── helloworld.py
└──

12.ros的文件系统:
(可以在rosrun的时候点击2次tab键进行提示)
1.增

catkin_create_pkg 自定义包名 依赖包 === 创建新的ROS功能包

sudo apt install xxx === 安装 ROS功能包
2.删

sudo apt purge xxx ==== 删除某个功能包
3.查

rospack list === 列出所有功能包

rospack find 包名 === 查找某个功能包是否存在，如果存在返回安装路径

roscd 包名 === 进入某个功能包#可以直接进入某个功能包

rosls 包名 === 列出某个包下的文件

apt search xxx === 搜索某个功能包
#apt search noetic | grep -i gmapping(|后的东西是筛选出某些需要的包名)

4.改

rosed 包名 文件名 === 修改功能包文件

需要安装 vim

比如:rosed turtlesim Color.msg
5.执行
    5.1roscore

    roscore === 是 ROS 的系统先决条件节点和程序的集合， 必须运行 roscore 才能使 ROS 节点进行通信。

    roscore 将启动:

        ros master

        ros 参数服务器

        rosout 日志节点

    用法:

    roscore

    或(指定端口号)

    roscore -p xxxx

    5.2rosrun

    rosrun 包名 可执行文件名 === 运行指定的ROS节点

    比如:rosrun turtlesim turtlesim_node
    5.3roslaunch

    roslaunch 包名 launch文件名 === 执行某个包下的 launch 文件


13.ros计算图

1.计算图简介

前面介绍的是ROS文件结构，是磁盘上 ROS 程序的存储结构，是静态的，而 ros 程序运行之后，不同的节点之间是错综复杂的，ROS 中提供了一个实用的工具:rqt_graph。

rqt_graph能够创建一个显示当前系统运行情况的动态图形。ROS 分布式系统中不同进程需要进行数据交互，计算图可以以点对点的网络形式表现数据交互过程。rqt_graph是rqt程序包中的一部分。

2.计算图演示

接下来以 ROS 内置的小乌龟案例来演示计算图

首先，按照前面所示，运行案例

然后，启动新终端，键入: rqt_graph 或 rosrun rqt_graph rqt_graph，可以看到类似下图的网络拓扑图，该图可以显示不同节点之间的关系。

方法一：使用roslaunch启用多个节点

!!!要用roslaunch启动launch文件，不能用rosrun

roslaunch helloworld start_turtle
<launch>
    <node pkg="turtlesim" type="turtlesim_node" name="t1"/>
    <node pkg="turtlesim" type="turtle_teleop_key" name="key1" />
    <node pkg="rqt_graph" type="rqt_graph" name="graph" />
    <!-- 结尾/不能忘 -->
    <!-- node为节点代号，pkg代表包名，type为节点，name为节点命名 -->
    <!-- 每次新开一个终端都要执行source ./devel/setup.bash -->

</launch>


方法二：用rosrun rqt_graph rqt_graph

.若是出现如下问题
ERROR: cannot launch node of type [pub_sub/pub]: Cannot locate node of type [pub] in package [pub_sub]. Make sure file exists in package path and permission is set to executable (chmod +x)
ERROR: cannot launch node of type [pub_sub/sub]: Cannot locate node of type [sub] in package [pub_sub]. Make sure file exists in package path and permission is set to executable (chmod +x)

要添加可执行权限

'2.ros通信机制'

机器人是一种高度复杂的系统性实现，在机器人上可能集成各种传感器(雷达、摄像头、GPS...)以及运动控制实现，为了解耦合，在ROS中每一个功能点都是一个单独的进程，每一个进程都是独立运行的。更确切的讲，ROS是进程（也称为Nodes）的分布式框架。 因为这些进程甚至还可分布于不同主机，不同主机协同工作，从而分散计算压力。不过随之也有一个问题: 不同的进程是如何通信的？
也即不同进程间如何实现数据交换的？在此我们就需要介绍一下ROS中的通信机制了。

ROS 中的基本通信机制主要有如下三种实现策略:

    话题通信(发布订阅模式):关注--->订阅

    服务通信(请求响应模式)：server--->client#先通过client发布请求，然后server再响应
                              <---

    参数服务器(参数共享模式)：

本章的主要内容就是是介绍各个通信机制的应用场景、理论模型、代码实现以及相关操作命令。本章预期达成学习目标如下:

    能够熟练介绍ROS中常用的通信机制
    能够理解ROS中每种通信机制的理论模型
    能够以代码的方式实现各种通信机制对应的案例
    能够熟练使用ROS中的一些操作命令
    能够独立完成相关实操案例


1.话题通信

话题通信是ROS中使用频率最高的一种通信模式，话题通信是基于发布订阅模式的，也即:一个节点发布消息，另一个节点订阅该消息。话题通信的应用场景也极其广泛，比如下面一个常见场景:

    机器人在执行导航功能，使用的传感器是激光雷达，机器人会采集激光雷达感知到的信息并计算，然后生成运动控制信息驱动机器人底盘运动。

在上述场景中，就不止一次使用到了话题通信。

    以激光雷达信息的采集处理为例，在 ROS 中有一个节点需要时时的发布当前雷达采集到的数据，导航模块中也有节点会订阅并解析雷达数据。
    再以运动消息的发布为例，导航模块会根据传感器采集的数据时时的计算出运动控制信息并发布给底盘，底盘也可以有一个节点订阅运动信息并最终转换成控制电机的脉冲信号。

以此类推，像雷达、摄像头、GPS.... 等等一些传感器数据的采集，也都是使用了话题通信，换言之，话题通信适用于不断更新的数据传输相关的应用场景。
概念

以发布订阅的方式实现不同节点之间数据交互的通信模式。
作用

用于不断更新的、少逻辑处理的数据传输场景。



话题通信实现模型是比较复杂的，该模型如下图所示,该模型中涉及到三个角色:

    ROS Master (管理者) 
    Talker (发布者)
    Listener (订阅者)  
        

        (0)advertise('bar',foo:1234)             ---------------------
        |--------------- ----------------------->|    ROS Master      |
        |               |                        |        (媒婆)       |
        |               |<-----xml/rpc---         --------------------
        |                        |       |      (2){foo:1234}|   A 
        |                        |       |------------------>|   |(1)subscribe('bar')
        |                        |                           |   |
        |                        |                           |   |
        |                        V                           |   |
------------------   (3)connect('scan',tcp)                  V
|Talker           |<-------------------------  ---------------
|xml/rpc:foo:1234 |--------------------------> |   Listener   |
|tcp data:foo:2345|  (4)tcp server:foo:2345    |      （翠花） |
|(二狗子)          |                            |              |
|                 |                            |              |
|                 |                            |              |
|                 |    (5)connect('foo',2345)  |              |
|                 |<-------------------------  |              |
|                 |--------------------------> |              | 
|                 |  (4)data messages:<-----tcp|              |
|                 |                             ----------------
|                 |  
-------------------
注解:rpc相当于远程控制，相当于手机号;tcp相当于微信
过程：
(0).狗子提交个人信息(房)---手机号
(1).翠花提交个人信息话题(房) 
(2).把狗子的电话发送给翠花 
(3).翠花打电话给狗子
(4).狗子响应(加微信)
(5)翠花通过tcp访问狗子(相当于加微信)
(6)发布消息

ROS Master 负责保管 Talker 和 Listener 注册的信息，并匹配话题相同的 Talker 与 Listener，帮助 Talker 与 Listener 建立连接，连接建立后，Talker 可以发布消息，且发布的消息会被 Listener 订阅。

整个流程由以下步骤实现:
0.Talker注册

Talker启动后，会通过RPC在 ROS Master 中注册自身信息，其中包含所发布消息的话题名称。ROS Master 会将节点的注册信息加入到注册表中。
1.Listener注册

Listener启动后，也会通过RPC在 ROS Master 中注册自身信息，包含需要订阅消息的话题名。ROS Master 会将节点的注册信息加入到注册表中。
2.ROS Master实现信息匹配

ROS Master 会根据注册表中的信息匹配Talker 和 Listener，并通过 RPC 向 Listener 发送 Talker 的 RPC 地址信息。
3.Listener向Talker发送请求

Listener 根据接收到的 RPC 地址，通过 RPC 向 Talker 发送连接请求，传输订阅的话题名称、消息类型以及通信协议(TCP/UDP)。
4.Talker确认请求

Talker 接收到 Listener 的请求后，也是通过 RPC 向 Listener 确认连接信息，并发送自身的 TCP 地址信息。
5.Listener与Talker件里连接

Listener 根据步骤4 返回的消息使用 TCP 与 Talker 建立网络连接。
6.Talker向Listener发送消息

连接建立后，Talker 开始向 Listener 发布消息。

    注意1:上述实现流程中，前五步使用的 RPC协议，最后两步使用的是 TCP 协议

    注意2: Talker 与 Listener 的启动无先后顺序要求

    注意3: Talker 与 Listener 都可以有多个

    注意4: Talker 与 Listener 连接建立后，不再需要 ROS Master。也即，即便关闭ROS Master，Talker 与 Listern 照常通信。

2.话题通信基本操作

需求:

    编写发布订阅实现，要求发布方以10HZ(每秒10次)的频率发布文本消息，订阅方订阅消息并将消息内容打印输出。

分析:

在模型实现中，ROS master 不需要实现，而连接的建立也已经被封装了，需要关注的关键点有三个:

    发布方
    接收方
    数据(此处为普通文本)

流程:

    编写发布方实现；
    编写订阅方实现；
    为python文件添加可执行权限；
    编辑配置文件；
    编译并执行。

2-1.发布方

#! /usr/bin/env python
"""
    需求: 实现基本的话题通信，一方发布数据，一方接收数据，
         实现的关键点:
         1.发送方
         2.接收方
         3.数据(此处为普通文本)

         PS: 二者需要设置相同的话题


    消息发布方:
        循环发布信息:HelloWorld 后缀数字编号

    实现流程:
        1.导包 
        2.初始化 ROS 节点:命名(唯一)
        3.实例化 发布者 对象
        4.组织被发布的数据，并编写逻辑发布数据


"""
#1.导包 
import rospy
from std_msgs.msg import String

if __name__ == "__main__":
    #2.初始化 ROS 节点:命名(唯一)
    rospy.init_node("talker_p")
    #3.实例化 发布者 对象
    pub = rospy.Publisher("chatter",String,queue_size=10)
    #4.组织被发布的数据，并编写逻辑发布数据
    msg = String()  #创建 msg 对象
    msg_front = "hello 你好"
    count = 0  #计数器 
    # 设置循环频率
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():

        #拼接字符串
        msg.data = msg_front + str(count)

        pub.publish(msg)
        rate.sleep()
        rospy.loginfo("写出的数据:%s",msg.data)
        count += 1

2-2.订阅方

#! /usr/bin/env python
"""
    需求: 实现基本的话题通信，一方发布数据，一方接收数据，
         实现的关键点:
         1.发送方
         2.接收方
         3.数据(此处为普通文本)


    消息订阅方:
        订阅话题并打印接收到的消息

    实现流程:
        1.导包 
        2.初始化 ROS 节点:命名(唯一)
        3.实例化 订阅者 对象
        4.处理订阅的消息(回调函数)
        5.设置循环调用回调函数



"""
#1.导包 
import rospy
from std_msgs.msg import String

def doMsg(msg):
    rospy.loginfo("I heard:%s",msg.data)

if __name__ == "__main__":
    #2.初始化 ROS 节点:命名(唯一)
    rospy.init_node("listener_p")
    #3.实例化 订阅者 对象
    sub = rospy.Subscriber("chatter",String,doMsg,queue_size=10)
    #4.处理订阅的消息(回调函数)
    #5.设置循环调用回调函数
    rospy.spin()

3.添加可执行权限

终端下进入 scripts 执行:chmod +x *.py
4.配置 CMakeLists.txt#一般放开注释的find_pkg;catkin_pkg;catkin_install

catkin_install_python(PROGRAMS
  scripts/talker_p.py
  scripts/listener_p.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

5.ctrl+shift+b编译执行

1.启动 roscore;

2.启动发布节点:rosrun helloworld talker_p.py 


3.启动订阅节点:rosrun helloworld listener_p


PS：可以使用 rqt_graph 查看节点关系:
可以使用rostopic echo 


6.总结：
'''talker--publisher'''
import rospy
from std_msgs.msg import String

if __name__ == "__main__":
    #2.初始化 ROS 节点:命名(唯一)
    rospy.init_node("talker")
    #3.实例化 发布者 对象
    pub = rospy.Publisher("house",String,queue_size=10)#此处要注意，发布方和接收方必须要用相同的话题名称'house',否则无法执行成功
    #4.组织被发布的数据，并编写逻辑发布数据
    msg = String()  #创建 msg 对象
    msg_front = "hello 你好"
    count = 0  #计数器 
    # 设置循环频率
    rate = rospy.Rate(1)#每一秒钟循环一次
    rospy.sleep(3)  #防止丢失数据，要在发布之前休息3S
    while not rospy.is_shutdown():

        #拼接字符串
        msg.data = msg_front + str(count)

        pub.publish(msg)#发布msg对象
        rate.sleep()
        rospy.loginfo("订阅的数据:%s",msg.data)#打印数据
        count += 1

'''listener--subscriber'''

#1.导包 
import rospy
from std_msgs.msg import String

def doMsg(msg):#把订阅到的数据传递进来
    rospy.loginfo("发布的数据:%s",msg.data)#打印数据

if __name__ == "__main__":
    #2.初始化 ROS 节点:命名(唯一)
    rospy.init_node("listener")
    #3.实例化 订阅者 对象
    sub = rospy.Subscriber("house",String,doMsg,queue_size=10)
    ##订阅者对象里面要有 话题名称，数据类型，回调函数，队列，且talker和listener的队列数要一致
    #4.处理订阅的消息(回调函数)
    #5.设置循环调用回调函数，如果遗忘它，那么无法接受从talker的数据
    rospy.spin()

-------------------------------------------------------

                     /house
最终的计算图：/talker------------->/subscriber

注意：                 

##采用rostopic echo chatter来看数据的发布情况
##queue_size的含义
    Publisher的消息队列是为了缓存发布节点发布的消息
    一旦队列中消息的数量超过了queue_size
    那么最先进入队列的（最老的）消息被舍弃

    Subscriber的消息队列是为了缓存节点接收到的信息
    一旦回调处理的速度过慢，接收到的消息数量超过了queue_size
    那么最先进入队列的（最老的）消息会被舍弃

    所以，想只处理最新的消息，实际上只需要把两个queue_size都设置成1
    那么系统不会缓存数据，自然处理的就是最新的消息
##发布方和接收方必须要用相同的话题'house',否则无法执行成功
##ros可以实现节点耦合，所以不同的语言写的节点也可以实现交互

'3.话题通信自定义msg'

在 ROS 通信协议中，数据载体是一个较为重要组成部分，ROS 中通过 std_msgs 封装了一些原生的数据类型,比如:String、Int32、Int64、Char、Bool、Empty.... 但是，这些数据一般只包含一个 data 字段，结构的单一意味着功能上的局限性，当传输一些复杂的数据，比如: 激光雷达的信息... std_msgs 由于描述性较差而显得力不从心，这种场景下可以使用自定义的消息类型

msgs只是简单的文本文件，每行具有字段类型和字段名称，可以使用的字段类型有：

    int8, int16, int32, int64 (或者无符号类型: uint*)

    float32, float64

    string

    time, duration(时间，持续时间)

    other msg files(其他消息文件)

    variable-length array[] and fixed-length array[C](变长数组，定长数组)

ROS中还有一种特殊类型：Header，标头包含时间戳和ROS中常用的坐标帧信息。会经常看到msg文件的第一行具有Header标头。

需求:创建自定义消息，该消息包含人的信息:姓名、身高、年龄等。

1.流程:

    按照固定格式创建 msg 文件
    编辑配置文件
    编译生成可以被 Python 或 C++ 调用的中间文件

1-1.定义msg文件

功能包下新建 msg 目录，添加文件 Person.msg

string name
uint16 age
float64 height#小数要用float64/32,

1-2.编辑配置文件

package.xml中添加编译依赖与执行依赖

  <build_depend>message_generation</build_depend>
  <exec_depend>message_runtime</exec_depend>
  <!-- 
  exce_depend 以前对应的是 run_depend 现在非法
  -->
##此处的问题是：
  '''catkin_package() the catkin package 'std_msgs' has been find_package()-ed
  but is not listed as a build dependency in the package.xml'''
##解决方法：换成如下形式
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

CMakeLists.txt编辑 msg 相关配置


#编译式依赖
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)
# 需要加入 message_generation,必须有 std_msgs
'''find_package和catkin_package相对应，若是编译helloworld的功能包，就必须要依赖于find_packaged的功能包
而find_package的功能包必须依赖于catkin_package的功能包'''

## 配置 msg 源文件
add_message_files(##若是自定义msg,则要放开3个注释，否则都不需要放开(catkin_install除外)
  FILES
  Person.msg
)

# 生成消息时依赖于 std_msgs(如果要执行Person.msg就必须要依赖于std_msgs)
generate_messages(
  DEPENDENCIES
  std_msgs
)

#执行时依赖
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES demo02_talker_listener
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime#message_runtime是添加的功能包
#  DEPENDS system_lib
)

add_message_file---generate_messages---catkin_package---find_package
#配置msg源文件---如果要执行Person.msg就必须要依赖于std_msgs---helloworld依赖于find_package---find_package依赖于catkin_package
#所以find_package可以理解为编译式依赖，而catkin_package是运行式依赖

1-3.编译

编译后的中间文件查看:

C++ 需要调用的中间文件(.../工作空间/devel/include/包名/Person.h)

Python 需要调用的中间文件(.../工作空间/devel/lib/python3/dist-packages/包名/msg/Person.py)

后续调用相关 msg 时，是从这些中间文件调用的
my_python_script

4.话题通信自定义msg调用

需求:

    编写发布订阅实现，要求发布方以1HZ(每秒1次)的频率发布自定义消息，订阅方订阅自定义消息并将消息内容打印输出。

分析:

在模型实现中，ROS master 不需要实现，而连接的建立也已经被封装了，需要关注的关键点有三个:

    发布方
    接收方
    数据(此处为自定义消息)

流程:

    1.编写发布方实现；
    2.编写订阅方实现；
    3.为python文件添加可执行权限；
    4.编辑配置文件；
    5.编译并执行。

4-1.vscode配置

为了方便代码提示以及误抛异常，需要先配置 vscode，将前面生成的 python 文件路径配置进 settings.json

{
    "python.autoComplete.extraPaths": [
        "/opt/ros/noetic/lib/python3/dist-packages",
        "/home/kim/demo01/devel/lib/python3/dist-packages/helloworld/msg"
    ],
    "python.analysis.extraPaths": [
        "/opt/ros/noetic/lib/python3/dist-packages"
    ],
    "ros.distro": "noetic"
}

4-2.发布方

#! /usr/bin/env python
"""
    发布方:
        循环发送消息

"""
import rospy
from demo02_talker_listener.msg import Person


if __name__ == "__main__":
    #1.初始化 ROS 节点
    rospy.init_node("talker_person_p")
    #2.创建发布者对象
    pub = rospy.Publisher("chatter_person",Person,queue_size=10)
    #3.组织消息
    p = Person()
    p.name = "葫芦瓦"
    p.age = 18
    p.height = 0.75

    #4.编写消息发布逻辑
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        pub.publish(p)  #发布消息
        rate.sleep()  #休眠
        rospy.loginfo("姓名:%s, 年龄:%d, 身高:%.2f",p.name, p.age, p.height)#输出

4-3.订阅方

#! /usr/bin/env python
"""
    订阅方:
        订阅消息

"""
import rospy
from demo02_talker_listener.msg import Person

def doPerson(p):
    rospy.loginfo("接收到的人的信息:%s, %d, %.2f",p.name, p.age, p.height)

注意：发布方和订阅方都要导入Person

if __name__ == "__main__":
    #1.初始化节点
    rospy.init_node("listener_person_p")
    #2.创建订阅者对象
    sub = rospy.Subscriber("chatter_person",Person,doPerson,queue_size=10)
    rospy.spin() #3.循环

4-4.权限设置

终端下进入 scripts 执行:chmod +x *.py
4-5.配置 CMakeLists.txt

catkin_install_python(PROGRAMS
  scripts/talker_p.py
  scripts/listener_p.py
  scripts/person_talker.py
  scripts/person_listener.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

4-6.执行

    1.启动 roscore;

    2.启动发布节点;

    3.启动订阅节点。

    运行结果与引言部分的演示案例2类似。

    PS：
    可以使用 rqt_graph 查看节点关系。
    连续按2次f5可以调试程序
    !!!注意：helloworld包下的include,msg,scripts,src是平级别文件不要搞错



!conclude:
1.在cmake中：find_package:message_generation---->add_message_file:Person.msg
----->generate_messages:std_msgs---->catkin_package:message_runtime------>catkin_install_python
2.在xml中：message_generation+message_runtime<--->build_depend+build_export_depend+exec_depend
3.导包：c/s and p/s都要导入:from model.msg/model.srv import *
'3.通信机制'

服务通信较之于话题通信更简单些，理论模型如下图所示，该模型中涉及到三个角色:

    ROS master(管理者)
    Server(服务端)
    Client(客户端)

ROS Master 负责保管 Server 和 Client 注册的信息，并匹配话题相同的 Server 与 Client ，帮助 Server 与 Client 建立连接，连接建立后，Client 发送请求信息，Server 返回响应信息。

整个流程由以下步骤实现:
0.Server注册

Server 启动后，会通过RPC在 ROS Master 中注册自身信息，其中包含提供的服务的名称。ROS Master 会将节点的注册信息加入到注册表中。
1.Client注册

Client 启动后，也会通过RPC在 ROS Master 中注册自身信息，包含需要请求的服务的名称。ROS Master 会将节点的注册信息加入到注册表中。
2.ROS Master实现信息匹配

ROS Master 会根据注册表中的信息匹配Server和 Client，并通过 RPC 向 Client 发送 Server 的 TCP 地址信息。
3.Client发送请求

Client 根据步骤2 响应的信息，使用 TCP 与 Server 建立网络连接，并发送请求数据。
4.Server发送响应

Server 接收、解析请求的数据，并产生响应结果返回给 Client。

    注意:

    1.客户端请求被处理时，需要保证服务器已经启动；

    2.服务端和客户端都可以存在多个。

    3.话题，服务端口，客户端，数据载体#要保证话题是一致的


1.服务通信自定义srv

需求:

    服务通信中，客户端提交两个整数至服务端，服务端求和并响应结果到客户端，请创建服务器与客户端通信的数据载体。

流程:

srv 文件内的可用数据类型与 msg 文件一致，且定义 srv 实现流程与自定义 msg 实现流程类似:

    按照固定格式创建srv文件

    编辑配置文件

    编译生成中间文件

1-1.定义srv文件

服务通信中，数据分成两部分，请求与响应，在 srv 文件中请求和响应使用---分割，具体实现如下:

功能包下新建 srv 目录，添加 xxx.srv 文件，内容:

# 客户端请求时发送的两个数字
int32 num1
int32 num2
---
# 服务器响应发送的数据
int32 sum

1-2.编辑配置文件

package.xml中添加编译依赖与执行依赖

  <build_depend>message_generation</build_depend>
  <exec_depend>message_runtime</exec_depend>
  <!-- 
  exce_depend 以前对应的是 run_depend 现在非法
  -->

CMakeLists.txt编辑 srv 相关配置

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)
# 需要加入 message_generation,必须有 std_msgs

add_service_files(
  FILES
  AddInts.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)
#find_package是当前创建的包依赖的包，catkin_package是依赖包所依赖的包
注意: 官网没有在 catkin_package 中配置 message_runtime,经测试配置也可以
1-3.编译

编译后的中间文件查看:

C++ 需要调用的中间文件(.../工作空间/devel/include/包名/xxx.h)

Python 需要调用的中间文件(.../工作空间/devel/lib/python3/dist-packages/包名/srv)

后续调用相关 srv 时，是从这些中间件调用的
!!!devel文件下include是专门放c++文件，lib是专门放python文件，但是还需进入到python3/dist-packages/包名/srv/_AddInts.py下查看具体信息

2.服务通信自定义srv调用

需求:

    编写服务通信，客户端提交两个整数至服务端，服务端求和并响应结果到客户端。

分析:

在模型实现中，ROS master 不需要实现，而连接的建立也已经被封装了，需要关注的关键点有三个:

    服务端
    客户端
    数据

流程:

    编写服务端实现；
    编写客户端实现；
    为python文件添加可执行权限；
    编辑配置文件；
    编译并执行。

2-0.vscode配置

需要像之前自定义 msg 实现一样配置settings.json 文件，如果以前已经配置且没有变更工作空间，可以忽略，如果需要配置，配置方式与之前相同:

{
    "python.autoComplete.extraPaths": [
        "/opt/ros/noetic/lib/python3/dist-packages",
    ]
}

2-1.服务端

#! /usr/bin/env python
"""
    需求: 
        编写两个节点实现服务通信，客户端节点需要提交两个整数到服务器
        服务器需要解析客户端提交的数据，相加后，将结果响应回客户端，
        客户端再解析

    服务器端实现:
        1.导包
        2.初始化 ROS 节点
        3.创建服务对象
        4.回调函数处理请求并产生响应
        5.spin()#有回调函数就必需要有rospy.spin()

"""
# 1.导包
import rospy
from model_01 import AddInts,AddIntsRequest,AddIntsResponse
# 回调函数的参数是请求对象，返回值是响应对象
def doReq(req):
    # 1.解析提交的数据
    sum = req.num1 + req.num2
    rospy.loginfo("提交的数据:num1 = %d, num2 = %d, sum = %d",req.num1, req.num2, sum)

    # resp = AddIntsResponse()
    # resp.sum = sum
    # 2.创建响应对象，将结果装进响应对象，并返回响应对象
    resp = AddIntsResponse(sum)
    return resp#response


if __name__ == "__main__":
    # 2.初始化 ROS 节点
    rospy.init_node("addints_server_p")
    # 3.创建服务端
    server = rospy.Service("AddInts",AddInts,doReq)
    rospy.loginfo('服务器已经启动')
    
    '''1.addints代表主题，且service和serviceproxy的主题要一致
    2.proxy表示代理人;3.第二个参数是service_class,即是服务类型；
    4.第三个参数是handler,即是回调函数，回调函数的作用是处理master请求并产生响应
    请求会以参数的方式来传递给函数，响应会以返回值的方式来返回'''
    
    # 4.回调函数处理请求并产生响应

    # 5.spin 函数
    rospy.spin()

总结：
import rospy
from model_02.srv import *

def doReq(req):

    sum = req.num1 + req.num2#1.解析数据

    response = AddIntsRequest(sum)#2.将数据封装进响应对象；函数传入的数据是请求，返回的响应，

    return response
##实际上是1.发出请求，2.返回响应


if __name__ == '__main__':

    rospy.init_node('server')

    server = rospy.Server('house',AddInts,doReq)

    rospy.spin()

2-2.客户端

#! /usr/bin/env python

"""
    需求: 
2-        编写两个节点实现服务通信，客户端节点需要提交两个整数到服务器
        服务器需要解析客户端提交的数据，相加后，将结果响应回客户端，
        客户端再解析

    客户端实现:
        1.导包
        2.初始化 ROS 节点
        3.创建请求对象
        4.发送请求
        5.接收并处理响应

    优化:
        加入数据的动态获取


"""
'简化版'
import rospy
from helloworld.srv import *
import sys


if __name__ == '__main__':
    #1.初始化节点
    rospy.init_node('client')
    #2.创建客户端对象
    client = rospy.ServiceProxy('house',addInts)
    #3.组织请求数据
    response = client.call(12,23)#服务参数的对象
    #4.处理响应
    

    rospy.loginfo('响应的结果:%d',response.sum)

'升级版'
#! /usr/bin/env python
#1.导包
import rospy
from demo03_server_client.srv import *
import sys

if __name__ == "__main__":

    #优化实现
    if len(sys.argv) != 3:
        rospy.logerr("请正确提交参数")
        sys.exit(1)#退出程序


    # 2.初始化 ROS 节点
    rospy.init_node("AddInts_Client_p")
    # 3.创建请求对象
    client = rospy.ServiceProxy("AddInts",AddInts)
    # 请求前，等待服务已经就绪
    # 方式1:
    # rospy.wait_for_service("AddInts")
    # 方式2
    client.wait_for_service()
    # 4.发送请求,接收并处理响应
    # 方式1
    # resp = client(3,4)
    # 方式2
    # resp = client(AddIntsRequest(1,5))
    # 方式3
    req = AddIntsRequest()##1.发送请求
    # req.num1 = 100
    # req.num2 = 200 

    #优化
    req.num1 = int(sys.argv[1])
    req.num2 = int(sys.argv[2]) 

    resp = client.call(req)##2.处理响应,#当于将调用server，并把req传给doReq(req)的req,并返回resp
    rospy.loginfo("响应结果:%d",resp.sum)

--------------------------------------------------------
!!!sys.argv的作用

argv[0]代表模块文件名、argv[1]代表传入的第一个命令行参数，argv[2]为传入的第二个命令行参数值，以此类推

详解：argv是sys模块的一个全局变量，也称sys模块的一个属性！argv本身为一个list类型的对象，该对象持有的第1个元素是命令行中传入的模块名、从第2个元素开始（含），均为命令行中传入的参数！

注意：argv持有的每个元素的类型均为str（字符串）

 
举个例子

python temp.py a b c d#在终端中运行python文件的格式

说明：命令行运行temp.py模块，同时传入4个参数：a、b、c、d 

sys.argv == ["temp.py","a","b","c","d"]  #sys.argv是持有5个元素的list对象

sys.argv[0]  == "temp.py"   #第1个元素为模块名“temp.py”

sys.argv[1] == "a"               #第2个元素为"a"

sys.argv[2] == "b"               #第3个元素为"b"

sys.argv[3] == "c"               #第4个元素为"c"

sys.argv[4] == "d"               #第5个元素为"d"
-------------------------------------------------------------------------------------------------

2-3.设置权限

终端下进入 scripts 执行:chmod +x *.py
2-4.配置 CMakeLists.txt

CMakeLists.txt

catkin_install_python(PROGRAMS
  scripts/AddInts_Server_p.py 
  scripts/AddInts_Client_p.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

2-5.执行

流程:

    需要先启动服务:rosrun 包名 服务

    然后再调用客户端 :rosrun 包名 客户端 参数1 参数2

结果:

会根据提交的数据响应相加后的结果。

---------------------------------------------------------

4.参数服务器

参数服务器实现是最为简单的，该模型如下图所示,该模型中涉及到三个角色:

    ROS Master (管理者)
    Talker (参数设置者)
    Listener (参数调用者)

                rosmaster
   ------------>          <---------------------------------
  | (1)setParam('foo',1)                |                    |
  |                                     |(3){foo:1}          |(2)getParam{'foo'}
  |                                     |                    |
  |                                     V                    |
  |                                     V---------------------
talker                                listener

ROS Master 作为一个公共容器保存参数，Talker 可以向容器中设置参数，Listener 可以获取参数。
整个流程由以下步骤实现:
1.Talker 设置参数

Talker 通过 RPC 向参数服务器发送参数(包括参数名与参数值)，ROS Master 将参数保存到参数列表中。
2.Listener 获取参数

Listener 通过 RPC 向参数服务器发送参数查找请求，请求中包含要查找的参数名。
3.ROS Master 向 Listener 发送参数值

ROS Master 根据步骤2请求提供的参数名查找参数值，并将查询结果通过 RPC 发送给 Listener。

！！！talker发送参数--->listener请求参数--->master给listener发送参数

参数可使用数据类型:

    32-bit integers

    booleans

    strings

    doubles

    iso8601 dates

    lists

    base64-encoded binary data

    字典

    注意:参数服务器不是为高性能而设计的，因此最好用于存储静态的非二进制的简单数据
需求:实现参数服务器参数的增删改查操作。
#int float bool list dict 
4-1.参数服务器新增(修改)参数

#! /usr/bin/env python
"""
    参数服务器操作之新增与修改(二者API一样)_Python实现:
"""

import rospy

if __name__ == "__main__":
    rospy.init_node("set_update_paramter_p")

    # 设置各种类型参数
    rospy.set_param("p_int",10)
    rospy.set_param("p_double",3.14)
    rospy.set_param("p_bool",True)
    rospy.set_param("p_string","hello python")
    rospy.set_param("p_list",["hello","haha","xixi"])
    rospy.set_param("p_dict",{"name":"hulu","age":8})

    # 修改
    rospy.set_param("p_int",100)

4-2.参数服务器获取参数

#! /usr/bin/env python

"""
    参数服务器操作之查询_Python实现:    
        get_param(键,默认值)
            当键存在时，返回对应的值，如果不存在返回默认值
        get_param_cached
        get_param_names
        has_param
        search_param
"""

import rospy

if __name__ == "__main__":
    rospy.init_node("get_param_p")

    #获取参数
    int_value = rospy.get_param("p_int",10000)
    double_value = rospy.get_param("p_double")
    bool_value = rospy.get_param("p_bool")
    string_value = rospy.get_param("p_string")
    p_list = rospy.get_param("p_list")
    p_dict = rospy.get_param("p_dict")

    rospy.loginfo("获取的数据:%d,%.2f,%d,%s",
                int_value,
                double_value,
                bool_value,
                string_value)
    for ele in p_list:
        rospy.loginfo("ele = %s", ele)

    rospy.loginfo("name = %s, age = %d",p_dict["name"],p_dict["age"])

    # get_param_cached
    int_cached = rospy.get_param_cached("p_int")#cache：N.是高速缓存器，V.缓存
    rospy.loginfo("缓存数据:%d",int_cached)

    # get_param_names
    names = rospy.get_param_names()
    for name in names:
        rospy.loginfo("name = %s",name)

    rospy.loginfo("-"*80)

    # has_param
    flag = rospy.has_param("p_int")
    rospy.loginfo("包含p_int吗？%d",flag)#1表示有，0表示无

    # search_param
    key = rospy.search_param("p_int")
    rospy.loginfo("搜索的键 = %s",key)#键为p_int

4-3.参数服务器删除参数

#! /usr/bin/env python
"""
    参数服务器操作之删除_Python实现:
    rospy.delete_param("键")
    键存在时，可以删除成功，键不存在时，会抛出异常
"""
import rospy

if __name__ == "__main__":
    rospy.init_node("delete_param_p")

    try:
        rospy.delete_param("p_int")
    except Exception as e:
        rospy.loginfo("删除失败")
##包含get_param/set_param/get_param_cached/get_param_names/has_param/search_param

.输入：rosparam list 
/p_bool
/p_dict/age
/p_dict/name
/p_double
/p_list
/p_string
/rosdistro
/roslaunch/uris/host_kim_g3_3590__42061
/rosversion
/run_id

..执行顺序：rosrun model_02 param_set.py -----> rosrun model_02 param_get.py--->rosrun model_02 param_del.py

设置数据：rospy.prama_set('int',12)--->
得到数据：int_value=rospy.param_get('int')/
    得到数据名称：names=rospy.param_get_names()/
    得到缓存数据：cached = rospy.param_get_cached('int')/
判断数据：flag = rospy.has_param('int')##1表示有，0表示无/
搜索数据：key = rospy.search_param('int')----->
删除数据：del_int = rospy.delete_param('int')

..执行结果：

...rosrun model_02 param_get.py

[INFO] [1647430235.144727]: 获取的数据:100,3.14,1,hello python
[INFO] [1647430235.147715]: ele = hello
[INFO] [1647430235.150563]: ele = haha
[INFO] [1647430235.153614]: ele = xixi
[INFO] [1647430235.156332]: name = hulu, age = 8
[INFO] [1647430235.160170]: 缓存数据:100
[INFO] [1647430235.164161]: name = /run_id
[INFO] [1647430235.165953]: name = /roslaunch/uris/host_kim_g3_3590__42061
[INFO] [1647430235.167757]: name = /rosversion
[INFO] [1647430235.169456]: name = /rosdistro
[INFO] [1647430235.170811]: name = /p_double
[INFO] [1647430235.171926]: name = /p_bool
[INFO] [1647430235.173018]: name = /p_string
[INFO] [1647430235.174171]: name = /p_list
[INFO] [1647430235.175277]: name = /p_dict/name
[INFO] [1647430235.176169]: name = /p_dict/age
[INFO] [1647430235.177039]: name = /p_int
[INFO] [1647430235.177932]: --------------------------------------------------------------------------------
[INFO] [1647430235.179457]: 包含p_int吗？1
[INFO] [1647430235.180835]: 搜索的键 = /p_int

...rosrun model_02 param_del.py---->删除了 rospy.set_param("p_int",10)中的p_int,所以接下来执行rosrun model_02 param_get.py时侯会失败
set_param() get_param
5.常用命令

机器人系统中启动的节点少则几个，多则十几个、几十个，不同的节点名称各异，通信时使用话题、服务、消息、参数等等都各不相同，一个显而易见的问题是: 当需要自定义节点和其他某个已经存在的节点通信时，如何获取对方的话题、以及消息载体的格式呢？

在 ROS 同提供了一些实用的命令行工具，可以用于获取不同节点的各类信息，常用的命令如下:

    rosnode : 操作节点
    rostopic : 操作话题#话题对应消息
    rosmsg : 操作msg消息
    rosservice : 操作服务#服务对应SRV
    rossrv : 操作srv消息
    rosparam : 操作参数#最后一个param
    .2+2+2：node,prama;topic,msg;service,srv
    .list,info,find,pub,echo,show,get,set为常用命令,可以直接用TAB补全命令
    .几个重要常用的：rostopic echo pkg 用来输出位置
    .rostopic pub;rosservice call;rosparam get/set;

作用

和之前介绍的文件系统操作命令比较，文件操作命令是静态的，操作的是磁盘上的文件，而上述命令是动态的，在ROS程序启动后，可以动态的获取运行中的节点或参数的相关信息。
案例

本节将借助于2.1、2.2和2.3的通信实现介绍相关命令的基本使用，并通过练习ROS内置的小海龟例程来强化命令的应用。

!!!要注意在查看信息之前要source下

5-1.rosnode

rosnode 是用于获取节点信息的命令

rosnode ping    测试到节点的连接状态
rosnode list    列出活动节点
rosnode info    打印节点信息
rosnode machine    列出指定设备上节点
rosnode kill    杀死某个节点
rosnode cleanup    清除不可连接的节点#就是清除已经死亡的但是rosmaster还不知道的节点

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

5-2.rostopic

rostopic包含rostopic命令行工具，用于显示有关ROS 主题的调试信息，包括发布者，订阅者，发布频率和ROS消息。它还包含一个实验性Python库，用于动态获取有关主题的信息并与之交互。

rostopic bw     显示主题使用的带宽
rostopic delay  显示带有 header 的主题延迟
rostopic echo   打印消息到屏幕#打印发布者的消息
rostopic find   根据类型查找主题
rostopic hz     显示主题的发布频率
rostopic info   显示主题相关信息
rostopic list   显示所有活动状态下的主题
rostopic pub    将数据发布到主题#打印订阅者的消息
rostopic type   打印主题类型

rostopic list(-v)

直接调用即可，控制台将打印当前运行状态下的主题名称

rostopic list -v : 获取话题详情(比如列出：发布者和订阅者个数...)

rostopic pub

可以直接调用命令向订阅者发布消息

为roboware 自动生成的 发布/订阅 模型案例中的 订阅者 发布一条字符串

rostopic pub /话题名称 消息类型 消息内容
rostopic pub /chatter std_msgs gagaxixi

为 小乌龟案例的 订阅者 发布一条运动信息

rostopic pub /turtle1/cmd_vel geometry_msgs/Twist
 "linear:
  x: 1.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 2.0"
//只发布一次运动信息

rostopic pub -r 10 /turtle1/cmd_vel geometry_msgs/Twist'''使用此段代码时候，要基于没有-r和10时候的rostopic情况，这样有助于直接修改参数
因为此情况下无补全功能'''
 "linear:
  x: 1.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 2.0"
// 以 10HZ 的频率循环发送运动信息

rostpic echo

获取指定话题当前发布的消息

rostopic info

获取当前话题的小关信息

消息类型

发布者信息

订阅者信息

rostopic type

列出话题的消息类型

rostopic find 

根据消息类型查找话题

rostopic delay

列出消息头信息

rostopic hz

列出消息发布频率

rostopic bw

列出消息发布带


'补充说明'

命令  详细说明
rostopic list   显示活动的话题目录
 rostopic echo [话题名称]   实时显示指定话题的消息内容 
rostopic find [类型名称]    显示使用指定类型的消息的话题 
 rostopic type [话题名称]   显示指定话题的消息类型 
rostopic bw [话题名称]      显示指定话题的消息带宽（bandwidth） 
rostopic hz [话题名称]      显示指定话题的消息数据发布周期 
 rostopic info [话题名称]   显示指定话题的信息 
 rostopic pub [话题名称] [消息类型] [参数]    用指定的话题名称发布消息 

　　在运行ROS话题示例之前，请先关闭所有节点。通过在不同的终端窗口中分别运行以下命令来运行turtlesim_node和turtle_teleop_key。

roscore
rosrun turtlesim turtlesim_node
rosrun turtlesim turtle_teleop_key

rostopic list：列出活动话题

　　rostopic list命令显示当前正在发送和接收的所有话题的列表。

    
rostopic list

　

　　通过将“-v”选项添加到rostopic list命令，可以分开发布话题和订阅话题，并将每个话题的消息类型一起显示。

    
rostopic list -v

rostopic echo [话题名称]：实时显示指定话题的消息内容

　　以下示例实时显示组成/turtle/pose话题的x、y、theta、linear_velocity和angular_velocity的数据。

    
rostopic echo /turtle/pose

rostopic find [类型名称]：显示使用指定类型的消息的话题

    
rostopic find turtlesim/Pose

 rostopic type [话题名称]：显示指定话题的消息类型

    
rostopic type /turtle/pose

rostopic bw [话题名称]：显示指定话题的消息数据带宽（bandwidth）

　　在以下示例中，用于/turtle/pose话题的数据带宽平均为每秒.25 KB。

    
rostopic bw /turtle/pose

rostopic hz [话题名称]：显示指定话题的消息数据发布周期

　　在以下示例中，用户可以检查/turtle/pose数据的发布周期。从结果可以看出，该消息以大约62.5Hz（0.06秒= 6毫秒）的频率被发布。

    
rostopic hz /turtle/pose

 rostopic info [话题名称]：显示指定话题的信息

　　在以下示例中，用户可以看到/turtle/pose话题使用turtlesim/Pose消息类型，发布到/turtlesim节点，并且没有实际订阅的话题。

    
rostopic info /turtle/pose

rostopic pub [话题名称] [消息类型] [参数]：使用指定的话题名称发布消息

　　以下是使用/turtle/cmd_vel话题名称发布类型为geometry_msgs/Twist的消息的示例。

    
rostopic pub /turtle/cmd_vel geometry_msgs/Twist -- ‘[2.0, 0.0, 0.0]’ ‘[0.0, 0.0, .8]’
rostopic pub -r 10 
　　每个选项的描述如下。

    -只发布一次消息（实际上只运行一次，但会像以前的结果一样运行3秒）。
    /turtle1/cmd_vel 指定的话题名称
    geometry_msgs/Twist 要发布的消息类型名称
    -- ‘[2.0, 0.0, 0.0]’ ‘[0.0, 0.0, 1.8]’ 在x轴坐标上以每秒2.0 m的速度移动，以z轴为中心，每秒旋转1.8rad


5-3.rosservice

rosservice包含用于列出和查询ROSServices的rosservice命令行工具。

调用部分服务时，如果对相关工作空间没有配置 path，需要进入工作空间调用 source ./devel/setup.bash

rosservice args 打印服务参数
rosservice call    使用提供的参数调用服务
rosservice find    按照服务类型查找服务
rosservice info    打印有关服务的信息
rosservice list    列出所有活动的服务
rosservice type    打印服务类型

5-rosservice uri    打印服务的 ROSRPC uri

rosservice list

列出所有活动的 service

~ rosservice list
/clear
/kill
/listener/get_loggers
/listener/set_logger_level
/reset
/rosout/get_loggers
/rosout/set_logger_level
/rostopic_4985_1578723066421/get_loggers
/rostopic_4985_1578723066421/set_logger_level
/rostopic_5582_1578724343069/get_loggers
/rostopic_5582_1578724343069/set_logger_level
/spawn
/turtle1/set_pen
/turtle1/teleport_absolute
/turtle1/teleport_relative
/turtlesim/get_loggers
/turtlesim/set_logger_level

rosservice args

打印服务参数

rosservice args /spawn
x y theta name

rosservice call

调用服务

为小乌龟的案例生成一只新的乌龟

rosservice call /spawn "x: 1.0
y: 2.0
theta: 0.0
name: 'xxx'"
name: "xxx"

//生成一只叫 xxx 的乌龟

rosservice find

根据消息类型获取话题

rosservice info

获取服务话题详情

rosservice type

获取消息类型

rosservice uri

获取服务器 uri


5-4.rosmsg

rosmsg是用于显示有关 ROS消息类型的 信息的命令行工具。

rosmsg 演示

rosmsg show    显示消息描述
rosmsg info    显示消息信息#show和info是一样的
rosmsg list    列出所有消息
rosmsg md5    显示 md5 加密后的消息
rosmsg package    显示某个功能包下的所有消息
rosmsg packages    列出包含消息的功能包

rosmsg list

会列出当前 ROS 中的所有 msg

rosmsg packages

列出包含消息的所有包

rosmsg package

列出某个包下的所有msg/rosmsg package 包名 
rosmsg package turtlesim

rosmsg show

显示消息描述

//rosmsg show 消息名称
rosmsg show turtlesim/Pose#前一个是包名，后一个是Pose.msg
结果:
float32 x
float32 y
float32 theta
float32 linear_velocity
float32 angular_velocity

    rosmsg info

    作用与 rosmsg show 一样

    rosmsg md5 (资料:http://wiki.ros.org/ROS/Technical%20Overview#Message_serialization_and_msg_MD5_sums)

    一种校验算法，保证数据传输的一致性


5-5.rossrv

rossrv是用于显示有关ROS服务类型的信息的命令行工具，与 rosmsg 使用语法高度雷同。

rossrv show    显示服务消息详情
rossrv info    显示服务消息相关信息
rossrv list    列出所有服务信息
rossrv md5    显示 md5 加密后的服务消息
rossrv package    显示某个包下所有服务消息
rossrv packages    显示包含服务消息的所有包

ros5-srv list

会列出当前 ROS 中的所有 srv 消息

rossrv packages

列出包含服务消息的所有包

rossrv package

列出某个包下的所有msg

//rossrv package 包名 
rossrv package turtlesim

rossrv show

显示消息描述

//rossrv show 消息名称
rossrv show turtlesim/Spawn
结果:
float32 x
float32 y
float32 theta
string name
---
string name

rossrv info

作用与 rossrv show 一致

rossrv md5

对 service 数据使用 md5 校验(加密)

5-6.rosparam

 

ros5-param list

列出所有参数

rosparam list

//默认结果
/rosdistro
/roslaunch/uris/host_helloros_virtual_machine__42911
/rosversion
/run_id

rosparam set

设置参数

rosparam set name huluwa

//再次调用 rosparam list 结果
/name  

rosparam get

获取参数

rosparam get name

//结果
huluwa

rosparam delete

删除参数

rosparam delete name

//结果
//去除了name

rosparam load(先准备 yaml 文件)

从外部文件加载参数

rosparam load xxx.yaml

rosparam dump

将参数写出到外部文件

rosparam dump yyy.yaml

7.通信机制实操

7-1.实操01_话题发布

需求描述:编码实现乌龟运动控制，让小乌龟做圆周运动。

结果演示:

实现分析:

    乌龟运动控制实现，关键节点有两个，一个是乌龟运动显示节点 turtlesim_node，另一个是控制节点，二者是订阅发布模式实现通信的，乌龟运动显示节点直接调用即可，运动控制节点之前是使用的 turtle_teleop_key通过键盘 控制，现在需要自定义控制节点。
    控制节点自实现时，首先需要了解控制节点与显示节点通信使用的话题与消息，可以使用ros命令结合计算图来获取。
    了解了话题与消息之后，通过 C++ 或 Python 编写运动控制节点，通过指定的话题，按照一定的逻辑发布消息即可。-
.实现流程:

    通过计算图结合ros命令获取话题与消息信息。
    编码实现运动控制节点。
    启动 roscore、turtlesim_node 以及自定义的控制节点，查看运行结果。

1.话题与消息获取

准备: 先启动键盘控制乌龟运动案例。
1.1话题获取

获取话题:/turtle1/cmd_vel

通过计算图查看话题，启动计算图:

rqt_graph

或者通过 rostopic 列出话题:

rostopic list

1.2消息获取

获取消息类型:geometry_msgs/Twist

rostopic type /turtle1/cmd_vel

获取消息格式:

rosmsg info geometry_msgs/Twist#twist是扭转

响应结果:

geometry_msgs/Vector3 linear#线速度
  float64 x
  float64 y
  float64 z
geometry_msgs/Vector3 angular#角速度
  float64 x
  float64 y
  float64 z

linear(线速度) 下的xyz分别对应在x、y和z方向上的速度(单位是 m/s)；

angular(角速度)下的xyz分别对应x轴上的翻滚、y轴上俯仰和z轴上偏航的速度(单位是rad/s)。

注意：
linear.x指向机器人前方，linear.y指向左方，linear.z垂直向上满足右手系，平面移动机器人常常linear.y和linear.z均为0

angular.z代表平面机器人的角速度，因为此时z轴为旋转轴

    Y
    |
    |
    .Z----->X
rosrun turtlesim turtlesim_node--->rosrun turtlesim turtle_teleop_key---->rostopic echo /turtle1/cmd_vel--->控制乌龟输出结果    

rostopic pub -r 10 /turtle1/cmd_vel geometry_msgs/Twist ""linear:(-r 10代表发布；频率为10，10后的参数可以自动补全)
  x: 1.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 1.0""(实际上是一个引号)

 .注意：rostopic pub -h: -r RATE, --rate=RATE  publishing rate (hz).  For -f and stdin input, this
                        defaults to 10.  Otherwise it is not set.


#! /usr/bin/env python
"""
    编写 ROS 节点，控制小乌龟画圆

    准备工作:
        1.获取topic(已知: /turtle1/cmd_vel)
        2.获取消息类型(已知: geometry_msgs/Twist)
        3.运行前，注意先启动 turtlesim_node 节点

    实现流程:
        1.导包
        2.初始化 ROS 节点
        3.创建发布者对象
        4.循环发布运动控制消息

"""

#!usr/bin/env python

import rospy
from geometry_msgs.msg import Twist

if __name__ == '__main__':
    rospy.init_node('control_circle')#1.初始化节点

    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)
    #2.创建发布者对象
    #3.创建发布信息
    '''
    3.1创建信息对象
    3.2创建发布频率
    3.3创建循环-----3.3.1发布信息；3.3.2睡觉'''
    msg = Twist()
    msg.linear.x = 1 
    msg.linear.y = 0
    msg.linear.z = 0
    msg.angular.x = 0
    msg.angular.y = 0
    msg.angular.z = 1

    rate = rospy.Rate(10)
    
    while not rospy.is_shutdown():

        pub.publish(msg)
        rate.sleep()

        

权限设置以及配置文件此处略
3.运行

首先，启动 roscore；

然后启动乌龟显示节点；

最后执行运动控制节点；

最终执行结果与演示结果类似。

4.用twist来控制运动

ROS中用Twist消息控制机器人

INSTALLING THE ROS-BY-EXAMPLE CODE是书中第五章的内容，如果我们按照上一篇教程执行过了，就可以直接进入第五章，安装一个叫rbx1的包。这个包里面包括了本书中用到的所有例子的源码，包括路径规划，视觉，语音识别等功能。这本书基本就围绕这个包来学习ROS的使用方法。


.基本包的功能介绍

ROS Base Controller是ROS中的基本控制节点，其中包含基本PID算法来控制电机运动。它主要任务是监听终端中或其他节点发出的以/cmd_vel为topic的控制指令(Topic是ROS中的一个基本概念，不同的节点之间通过发布和订阅相同Topic的消息来通信)，
然后发布/odom topic的odometry 消息(里程，指直接获得的机器人走过的距离，通常由编码器数据计算得到或结合惯导经EKF得到),
同时发布/odom坐标系和机体坐标系之间的转换(如果odom数据由EKF得到的话，这个工作由 robot_pose_ekf 节点完成).

move_base pacakge 可以让机器人移动至我们指定的目标地点，其中包含避障，路径规划等功能。

gmapping package :SLAM,用激光雷达或Kinect构建实时地图

amcl package : 机器人利用SLAM或odometry数据实时定位


7-2-. 实操02_话题订阅

需求描述: 已知turtlesim中的乌龟显示节点，会发布当前乌龟的位姿(窗体中乌龟的坐标以及朝向)，要求控制乌龟运动，并时时打印当前乌龟的位姿。

结果演示:

实现分析:

    首先，需要启动乌龟显示以及运动控制节点并控制乌龟运动。
    要通过ROS命令，来获取乌龟位姿发布的话题以及消息。
    编写订阅节点，订阅并打印乌龟的位姿。

实现流程:

    通过ros命令获取话题与消息信息。
    编码实现位姿获取节点。
    启动 roscore、turtlesim_node 、控制节点以及位姿订阅节点，控制乌龟运动并输出乌龟的位姿。

7-2-1.话题与消息获取

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

7-2-2.实现订阅节点

创建功能包需要依赖的功能包: roscpp rospy std_msgs turtlesim
!注意创建功能包的时候，要在xml中加入: 
<build_depend>turtlesim</build_depend>
<build_depend>turtlesim</build_depend>
然后在cmake文件中加入turtlesim:
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  turtlesim
)



#! /usr/bin/env python
"""
    订阅小乌龟的位姿: 时时获取小乌龟在窗体中的坐标并打印
    准备工作:
        1.获取话题名称 /turtle1/pose
        2.获取消息类型 turtlesim/Pose
        3.运行前启动 turtlesim_node 与 turtle_teleop_key 节点

    实现流程:
        1.导包
        2.初始化 ROS 节点
        3.创建订阅者对象
        4.回调函数处理订阅的数据
        5.spin

"""

import rospy
from turtlesim.msg import Pose

def doPose(data):
    rospy.loginfo("乌龟坐标:x=%.2f, y=%.2f,theta=%.2f",data.x,data.y,data.theta)

if __name__ == "__main__":

    # 2.初始化 ROS 节点
    rospy.init_node("sub_pose_p")

    # 3.创建订阅者对象
    sub = rospy.Subscriber("/turtle1/pose",Pose,doPose,queue_size=1000)
    #     4.回调函数处理订阅的数据
    #     5.spin
    rospy.spin()

权限设置以及配置文件此处略
7-2-3.运行

首先，启动 roscore；

然后启动乌龟显示节点，执行运动控制节点；

最后启动乌龟位姿订阅节点；

最终执行结果与演示结果类似。

7-3.实操03_服务调用

需求描述:编码实现向 turtlesim 发送请求，在乌龟显示节点的窗体指定位置生成一乌龟，这是一个服务请求操作。

结果演示:

实现分析:

    首先，需要启动乌龟显示节点。
    要通过ROS命令，来获取乌龟生成服务的服务名称以及服务消息类型。
    编写服务请求节点，生成新的乌龟。

实现流程:

    通过ros命令获取服务与服务消息信息。
    编码实现服务请求节点。
    启动 roscore、turtlesim_node 、乌龟生成节点，生成新的乌龟。

7-3-1.服务名称与服务消息获取

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
---
string name

7-3-2.服务客户端实现

创建功能包需要依赖的功能包: roscpp rospy std_msgs turtlesim


#! /usr/bin/env python
"""
    生成一只小乌龟
    准备工作:
        1.服务话题 /spawn
        2.服务消息类型 turtlesim/Spawn
        3.运行前先启动 turtlesim_node 节点

    实现流程:
        1.导包
          需要包含 turtlesim 包下资源，注意在 package.xml 配置
        2.初始化 ros 节点
        3.创建 service 客户端
        4.等待服务启动
        5.发送请求
        6.处理响应

"""

import rospy
from turtlesim.srv import Spawn,SpawnRequest,SpawnResponse

if __name__ == "__main__":
    # 2.初始化 ros 节点
    rospy.init_node("set_turtle_p")
    # 3.创建 service 客户端
    client = rospy.ServiceProxy("/spawn",Spawn)
    # 4.等待服务启动
    client.wait_for_service()
    # 5.发送请求
    req = SpawnRequest()
    req.x = 2.0
    req.y = 2.0
    req.theta = -1.57
    req.name = "my_turtle_p"
    try:
        response = client.call(req)
        # 6.处理响应
        rospy.loginfo("乌龟创建成功!，叫:%s",response.name)
    except expression as identifier:
        rospy.loginfo("服务调用失败")

权限设置以及配置文件此处略
7-3-3.运行

首先，启动 roscore；

然后启动乌龟显示节点；

最后启动乌龟生成请求节点；

最终执行结果与演示结果类似。


7-4. 实操04_参数设置

需求描述: 修改turtlesim乌龟显示节点窗体的背景色，已知背景色是通过参数服务器的方式以 rgb 方式设置的。

结果演示:

实现分析:

    首先，需要启动乌龟显示节点。
    要通过ROS命令，来获取参数服务器中设置背景色的参数。
    编写参数设置节点，修改参数服务器中的参数值。

实现流程:

    通过ros命令获取参数。
    编码实现服参数设置节点。
    启动 roscore、turtlesim_node 与参数设置节点，查看运行结果。

7-4-1.参数名获取

获取参数列表:

rosparam list

响应结果:

/turtlesim/background_b
/turtlesim/background_g
/turtlesim/background_r

7-4-2.参数修改

实现方案A:C++

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

配置文件此处略

实现方案B:Python

#! /usr/bin/env python

import rospy

if __name__ == "__main__":
    rospy.init_node("hehe")
    # rospy.set_param("/turtlesim/background_r",255)
    # rospy.set_param("/turtlesim/background_g",255)
    # rospy.set_param("/turtlesim/background_b",255)
    rospy.set_param("background_r",255)
    rospy.set_param("background_g",255)
    rospy.set_param("background_b",255)  # 调用时，需要传入 __ns:=xxx

权限设置以及配置文件此处略
7-4-3.运行

首先，启动 roscore；

然后启动背景色设置节点；

最后启动乌龟显示节点；

最终执行结果与演示结果类似。

PS: 注意节点启动顺序，如果先启动乌龟显示节点，后启动背景色设置节点，那么颜色设置不会生效。
7-4-4.其他设置方式

方式1:修改小乌龟节点的背景色(命令行实现)

rosparam set /turtlesim/background_b 自定义数值

rosparam set /turtlesim/background_g 自定义数值

rosparam set /turtlesim/background_r 自定义数值

修改相关参数后，重启 turtlesim_node 节点，背景色就会发生改变了

方式2:启动节点时，直接设置参数

rosrun turtlesim turtlesim_node _background_r:=100 _background_g=0 _background_b=0

方式3:通过launch文件传参

<launch>
    <node pkg="turtlesim" type="turtlesim_node" name="set_bg" output="screen">
        <!-- launch 传参策略1 -->
        <!-- <param name="background_b" value="0" type="int" />
        <param name="background_g" value="0" type="int" />
        <param name="background_r" value="0" type="int" /> -->

        <!-- launch 传参策略2 -->
        <rosparam command="load" file="$(find demo03_test_parameter)/cfg/color.yaml" />
    </node>

</

.roslaunch的使用问题：
    ..<!--结束标签'/'不能忘记'-->
    ..chmod +x xxxx

7-4-5.header()

    (1)ROS std_msgs/Header 数据含义
    std_msgs/Header.msg消息里数据主要有一下几部分：

    uint32 seq //存储原始数据类型uint32
    time stamp //存储ROS中的时间戳信息
    string frame_id //用于表示和此数据关联的帧，在坐标系变化中可以理解为数据所在的坐标系名称

    (2)具体解释
    你如果想使用这个消息，那么看到这个页面，根据我们之前讲的内容，你至少可以做下面这几件事
    1:　包含头文件#include "geometry_msgs/PoseStamped.h"，这样我们才可以使用这个类型的消息
    2: 　通过geometry_msgs::PoseStamped msg定义一个叫msg的对象，该对象可以使用上图中的header,pose两个数据成员．即你可以通过msg.header,msg.pose来调用数据类型为std_msgs/Header,geometry_msgs/Pose的两个数据成员．

    但是那个header和pose具体是什么东西我们不清楚．但之前说了，任何复杂数据类型都是由简单的组成的，页面下的浅蓝色字体是链接可以点进去，咱们先点击std_msgs/Header看看他是个什么东西．你会看到下图内容．
    headerDef.png


7-5.通信机制比较

三种通信机制中，参数服务器是一种数据共享机制，可以在不同的节点之间共享数据，话题通信与服务通信是在不同的节点之间传递数据的，三者是ROS中最基础也是应用最为广泛的通信机制。
这其中，话题通信和服务通信有一定的相似性也有本质上的差异，在此将二者做一下简单比较:
二者的实现流程是比较相似的，都是涉及到四个要素:

    要素1: 消息的发布方/客户端(Publisher/Client)
    要素2: 消息的订阅方/服务端(Subscriber/Server)
    要素3: 话题名称(Topic/Service)
    要素4: 数据载体(msg/srv)

可以概括为: 两个节点通过话题关联到一起，并使用某种类型的数据载体实现数据传输。

二者的实现也是有本质差异的，具体比较如下:
    Topic(话题)   Service(服务)
通信模式    发布/订阅   请求/响应
同步性     异步  同步#同步表示publisher发布一个消息,subscriber就接受，然后再发布再接受；异步表示执行顺序不是严格照常进行
底层协议    ROSTCP/ROSUDP   ROSTCP/ROSUDP
缓冲区     有   无#缓冲区指的是，可以把数据放在缓冲区，然后再处理，所以P/S模式异步的，C/S模式是同步的
时时性     弱   强#因为有缓冲区，所以P/S模式时时性不强
节点关系    多对多     一对多(一个 Server)#P/S模式可以多对多，C/S模式只能一对多
通信数据    msg     srv#msg:字段 名称；srv:request --- response
使用场景    连续高频的数据发布与接收:雷达、里程计     偶尔调用或执行某一项特定功能：拍照、语音识别

不同通信机制有一定的互补性，都有各自适应的应用场景。尤其是话题与服务通信，需要结合具体的应用场景与二者的差异，选择合适的通信机制。

'3.通信机制进阶'

1.常用API# Application Programming Interface，简称：API，又称为应用编程接口
进入此网站查询：http://wiki.ros.org/APIs
1-1.发布对象
.例子：
#! /usr/bin/env python
import rospy
from std_msgs.msg import String

if __name__ == "__main__":
    rospy.init_node('sandai',anonymous=True)#可以同时发布多个节点
    pub = rospy.Publisher("che", String, queue_size=10)
    msg = String()
    rate = rospy.Rate(1)
    count = 0
    while not rospy.is_shutdown():
        count += 1
        msg.data = "hello" + str(count)
        pub.publish(msg)
        rate.sleep()
        rospy.loginfo("您输入的数据是:%s",msg.data )

1-2.获取时间：
#! /usr/bin/env python
import rospy

if __name__ == "__main__":
    rospy.init_node("time")
###############################1.时刻
    # 获取当前时刻
    right_now = rospy.Time.now()
    rospy.loginfo("当前时刻:%.2f",right_now.to_sec())
    rospy.loginfo("当前时刻:%.2f",right_now.to_nsec())# 1ns = 10e-9s
    # 自定义时刻
    some_time1 = rospy.Time(1234.567891011)
    some_time2 = rospy.Time(1234.567891011)
    rospy.loginfo("设置时刻1:%.2f",some_time1.to_sec())
    rospy.loginfo("设置时刻2:%.2f",some_time2.to_sec())
    # 从时间创建对象
    # some_time3 = rospy.Time.from_seconds(543.21)
    some_time3 = rospy.Time.from_sec(543.21) # from_sec 替换了 from_seconds
    rospy.loginfo("设置时刻3:%.2f",some_time3.to_sec())
    
#################################2.持续时间
    # 持续时间相关API
    rospy.loginfo("持续时间测试开始.....")
    du = rospy.Duration(3.3)
    rospy.loginfo("du1 持续时间:%.2f",du.to_sec())
    rospy.sleep(du) #休眠函数
    rospy.loginfo("持续时间测试结束.....")
    #持续时间和时刻运算
    rospy.loginfo("时间运算")
    now = rospy.Time.now()
    du1 = rospy.Duration(10)
    du2 = rospy.Duration(20)
    rospy.loginfo("当前时刻:%.2f",now.to_sec())
    before_now = now - du1
    after_now = now + du1
    dd = du1 + du2
    # now = now + now #非法
    rospy.loginfo("之前时刻:%.2f",before_now.to_sec())
    rospy.loginfo("之后时刻:%.2f",after_now.to_sec())
    rospy.loginfo("持续时间相加:%.2f",dd.to_sec())

#######################################4.设置运行频率
    rate = rospy.Rate(0.5)
    while not rospy.is_shutdown():
        rate.sleep() #休眠
        rospy.loginfo("+++++++++++++++")

#######################################5.创建一个定时器，实现类似于rospy.Rate的功能
#! /usr/bin/env python
import rospy
def doMsg(event):
    now1 = rospy.Time.now()
    now2 = rospy.Time(12)
    rospy.loginfo("当前时刻A%s",event.current_real)#
    rospy.loginfo("当前时刻B%s", now1.to_sec())
    rospy.loginfo("自定义时刻%s", now2.to_sec())
    
if __name__ == "__main__":
    rospy.init_node("time")
    # 获取当前时刻
    rospy.Timer(rospy.Duration(10),doMsg)#若有true的话，时间不会自动加1
    #把event = rospy.Duration(10),current_real为当前实时时间，当等待10秒后再继续循环
    #event.current_real和now.to_sec()的时间相同
    rospy.spin()


.总结
1.当前时间:now = rospy.Time.now(); now.to_sec()/to_nsec;
2.任意时间：
sometime = rospy.Time(123),sometime.to_sec();
sometime.Time.from_sec(23),sometime.to_sec();
3.持续时间：
du = rospy.Duration(2.3):持续时间
du.to_sec()：获取持续时间
rospy.sleep(du):持续休息时间
4.运行频率：rate = rospy.Rate(10)
5.event.current_real和now.to_sec()的时间相同,
把event = rospy.Duration(10),current_real为当前实时时间，当等待10秒后再继续执行循环

1-4.获取日志:
import rospy
if __name__ == "__main__":
    rospy.init_node("hello_log")
    rospy.loginfo("info消息")
    rospy.logdebug("bug消息")
    rospy.logwarn("warn消息")
    rospy.logerr("error消息")
    rospy.logfatal("fatal消息")

输出：
[INFO] [1648974832.834521]: info消息
[WARN] [1648974832.835280]: warn消息
[ERROR] [1648974832.835941]: error消息
[FATAL] [1648974832.836578]: fatal消息

1-5.python中的模块导入
/1.需求:首先新建一个Python文件A，再创建Python文件UseA，在UseA中导入A并调用A的实现。

/2.实现:
新建两个Python文件，使用 import 实现导入关系；
添加可执行权限、编辑配置文件并执行UseA。

1.新建两个Python文件并使用import导入

(1).文件A实现(包含一个变量):

#! /usr/bin/env python
def func(a):
    return a

(2).文件B核心实现:
#! /usr/bin/env python
import os 
import sys
import rospy
from pub_01 import *
path = os.path.abspath(".")
# 核心
sys.path.insert(0,path + "/src/model02/scripts")

if __name__ == "__main__":
    rospy.init_node("nodes")
    rospy.loginfo("num = %d",func(100))


"第4章ROS运行管理"

ROS是多进程(节点)的分布式框架，一个完整的ROS系统实现：
    可能包含多台主机；
    每台主机上又有多个工作空间(workspace)；
    每个的工作空间中又包含多个功能包(package)；
    每个功能包又包含多个节点(Node)，不同的节点都有自己的节点名称；
    每个节点可能还会设置一个或多个话题(topic)...
在多级层深的ROS系统中，其实现与维护可能会出现一些问题，比如，如何关联不同的功能包，
繁多的ROS节点应该如何启动？功能包、节点、话题、参数重名时应该如何处理？
不同主机上的节点如何通信？
本章主要内容介绍在ROS中上述问题的解决策略，预期达成学习目标也与上述问题对应：

    掌握元功能包使用语法；

    掌握launch文件的使用语法；

    理解什么是ROS工作空间覆盖，以及存在什么安全隐患；

    掌握节点名称重名时的处理方式；

    掌握话题名称重名时的处理方式；

    掌握参数名称重名时的处理方式；

    能够实现ROS分布式通信。

1.ROS元功能包
    场景:完成ROS中一个系统性的功能，可能涉及到多个功能包，比如实现了机器人导航模块，该模块下有地图、定位、路径规划...等不同的子级功能包。那么调用者安装该模块时，需要逐一的安装每一个功能包吗？
显而易见的，逐一安装功能包的效率低下，在ROS中，提供了一种方式可以将不同的功能包打包成一个功能包，当安装某个功能模块时，直接调用打包后的功能包即可，该包又称之为元功能包(metapackage)。
.概念
    MetaPackage是Linux的一个文件管理系统的概念。是ROS中的一个虚包，里面没有实质性的内容，但是它依赖了其他的软件包，通过这种方法可以把其他包组合起来，我们可以认为它是一本书的目录索引，告诉我们这个包集合中有哪些子包，并且该去哪里下载。
    例如：
        sudo apt install ros-noetic-desktop-full 命令安装ros时就使用了元功能包，该元功能包依赖于ROS中的其他一些功能包，安装该包时会一并安装依赖。
    还有一些常见的MetaPackage：navigation moveit! turtlebot3 ....
.作用
    方便用户的安装，我们只需要这一个包就可以把其他相关的软件包组织到一起安装了。
.实现
    首先:新建一个功能包
    然后:修改package.xml ,内容如下:
     <exec_depend>被集成的功能包</exec_depend>#表示当前的元功能包需要申明依赖哪些包？
     .....
     <export>
       <metapackage />
     </export>

    最后:修改 CMakeLists.txt,内容如下:

    cmake_minimum_required(VERSION 3.0.2)#保留前4行，删除其余部分，最后catkin_make
    project(demo)
    find_package(catkin REQUIRED)
    catkin_metapackage()

注意：在cmake中不能换行，不然配置可能会失败

2.launch文件

    2-1.launch标签：
    /1.属性:deprecated = "弃用声明"(通知用户当前launch文件已经弃用)
    /2.子级标签：所有其它标签都是launch的子级
    /3.启动界面：

    #launch文件中不要加逗号

    WARNING: [/home/kim/ROS_Space/demo02_ws/src/model01/launch/test.launch] DEPRECATED: 此文件已经过时，不建议使用

    2-2.launch文件标签之node
    <node>标签用于指定 ROS 节点，是最常见的标签，需要注意的是: 
    roslaunch 命令不能保证按照 node 的声明顺序来启动节点(节点的启动是多进程的)
    /1.属性

        pkg="包名":节点所属的包

        type="nodeType":节点类型(与之相同名称的可执行文件)

        name="nodeName":节点名称(在 ROS 网络拓扑中节点的名称)

        args="xxx xxx xxx" (可选):将参数传递给节点#利用args来传参数

        machine="机器名":在指定机器上启动节点#在不同的设备上启动节点

        respawn="true | false" (可选):如果节点退出，是否自动重启#自动启动

        respawn_delay=" N" (可选):如果 respawn 为 true, 那么延迟 N 秒后启动节点

        required="true | false" (可选):该节点是否必须，如果为 true,
        那么如果该节点退出，将杀死整个 roslaunch

        ns="xxx" (可选):在指定命名空间 xxx 中启动节点

        clear_params="true | false" (可选):在启动前，删除节点的私有空间的所有参数

        output="log | screen" (可选):日志发送目标，可以设置为 log 日志文件，或 screen 屏幕,默认是 log(要屏幕可见)
        
    /1-1.例子：
        <launch deprecated = "此文件已经过时，不建议使用">
        <!-- <node pkg = "turtlesim" type = "turtlesim_node" name = "my_turtle" output = "screen" respawn = "true" /> -->
        <!-- 节点退出后重新启动，respawn和required是对立的，不能同时写在同一个节点里面-->
        <!-- ns = "hello"为设置加节点的命名空间,在后期可以避免重名问题,此案例输出的rosnode的名称是：/hello/my_turtle--> 

            <node pkg = "turtlesim" type = "turtlesim_node" name = "my_turtle" output = "screen" required = "true" ns = "hello" />
        <!-- 节点退出后关闭整个系统 -->
            <node pkg = "turtlesim" type = "turtle_teleop_key" name = "my_key" output = "screen"/>
        <!--不要在里面加逗号-->

        </launch>

    /2.子级标签
        env 环境变量设置
        remap 重映射节点名称
        rosparam 参数设置
        param 参数设置

    2-3.launch文件标签之include

    include标签用于将另一个 xml 格式的 launch 文件导入到当前文件
    /1.属性
        file="$(find 包名)/xxx/xxx.launch"
        要包含的文件路径
        ns="xxx" (可选)
        在指定命名空间导入文件
        ------------------------------------------------------
        节点1：#导入节点2，然后直接执行此launch文件就可以启动新节点
            <launch>
            <include file = "$(find model01)/launch/test.launch" />
        节点2：
            <launch deprecated = "此文件已经过时，不建议使用">
                <!-- <node pkg = "turtlesim" type = "turtlesim_node" name = "my_turtle" output = "screen" respawn = "true" /> -->
            <!-- 节点退出后重新启动，respawn和required是对立的，不能同时写在同一个节点里面-->
            <!-- ns = "hello"为设置加节点的命名空间,在后期可以避免重名问题,此案例输出的rosnode的名称是：/hello/my_turtle--> 

                <node pkg = "turtlesim" type = "turtlesim_node" name = "my_turtle" output = "screen" required = "true" ns = "hello" />
            <!-- 节点退出后关闭整个系统 -->
                <node pkg = "turtlesim" type = "turtle_teleop_key" name = "my_key" output = "screen"/>
            <!--不要在里面加逗号-->
            </launch>


    /2.子级标签
        env 环境变量设置
        arg 将参数传递给被包含的文件

    2-4.launch文件标签之remap

    <launch deprecated = "此文件已经过时，不建议使用">#deprecate：强烈反对
    <node pkg = "turtlesim" type = "turtlesim_node" name = "my_turtle" output = "screen" respawn = "true" /> 
    # 节点退出后重新启动，respawn和required是对立的，不能同时写在同一个节点里面
    # ns = "hello"为设置加节点的命名空间,在后期可以避免重名问题,此案例输出的rosnode的名称是：/hello/my_turtle 

        <node pkg = "turtlesim" type = "turtlesim_node" name = "my_turtle" output = "screen">#此处格式要注意
            <remap from = "/turtle1/cmd_vel" to = "/cmd_vel" />
             # 将/turtle1/cmd_vel改成/cmd_vel，即从原话题到新话题的转化，从而实现从turtle_teleop_key到teleop_twist_keyboard teleop_twist_keyboard.py的通信
        </node>
        # 节点退出后关闭整个系统
        <node pkg = "turtlesim" type = "turtle_teleop_key" name = "my_key" output = "screen" />
        #不要在里面加逗号
    </launch>

    步骤：
        1.< node = turtlesim type = "turlesim_node" name = "my_node" output = "screen" respawn = "true" />
        2.< node = turtlesim type = "turtle_teleop_key" name = "my_key" output = "screen" respawn = "true" >
            < remap from = "/turtle/cmd_vel" to = "/cmd_vel" />
          </ node >
        3.启动roslaunch xxx xxx.launch ---------> rosrun turtle teleop_twist_keyboard teleop_twist_keyboard.py

    2-5.launch文件标签之param
    <param>标签主要用于在参数服务器上设置参数，参数源可以在标签中通过 value 指定，也可以通过外部文件加载，在<node>标签中时，相当于私有命名空间。

    /1.属性
        name="命名空间/参数名"
        参数名称，可以包含命名空间

        value="xxx" (可选)
        定义参数值，如果此处省略，必须指定外部文件作为参数源

        type="str | int | double | bool | yaml" (可选)
        指定参数类型，如果未指定，roslaunch 会尝试确定参数类型，规则如下:
            .如果包含 '.' 的数字解析未浮点型，否则为整型
            ."true" 和 "false" 是 bool 值(不区分大小写)
            .其他是字符串

    /2.子级标签
    /3.例子:
        <launch>
            <param name = "param_A" type = "int" value = "100" />
            <node pkg = "turtlesim" type = "turlesim_node" name = "myturtle" output = "screen">
                <remap from = "/turtle1/cmd_vel" to = "/cmd_vel"/>
                <!-- 格式2:在node下的node -->
                <param name = "param_B" type = "double" value = "100" />
            </node>
            <!-- 键盘控制节点 -->
            <node pkg = "turtlesim" type = "turtle_teleop_key" name = "my_key" output = "screen"/> 
            
        </launch>

    2-6.rosparam
    步骤:
    /1.launch文件
    <launch>
        <node pkg = "turtlesim" type = "turtle_teleop_key" name = "my_key" output = "screen"/>
        <node pkg = "turtlesim" type = "turtlesim_node" name = "my_node" output = "screen">
        # <!-- 当下面有子节点的时候就不要结尾不能有/,/要写在结尾node的句首,无子结点就要有/ -->
            <remap from = "/turtle1/cmd_vel" to = "cmd_vel"/>#remap节点替换要基于turtlesim_node
            <param name = "param_A" type = "int" value = "100"/>
            <param name = "param_B" type = "double" value = "100.1"/>
            <rosparam command = "load" file = "$(find model01)/launch/params.yaml"/>
            <rosparam command = "dump" file = "$(find model01)/launch/params_out.yaml"/>
        </node>
    </launch>

    /2.配置yaml文件   /3.roslaunch该文件,直接会导出节点
        bg_R: 100
        bg_G: 100
        bg_B: 100

    2-7.ros文件标签之group
    /1.属性
        ns="名称空间" (可选)
        clear_params="true | false" (可选)
        启动前，是否删除组名称空间的所有参数(慎用....此功能危险)
    /2.子级标签
    /3.例子:
    <launch>
        <group ns = "first">
            <node pkg = "turtlesim" type = "turtlesim_node" name = "my_turtle" output = "screen" />
            <node pkg = "turtlesim" type = "turtle_teleop_key" name = "my_key" output = "screen" />
        </group>
        <group ns = "second">
            <node pkg = "turtlesim" type = "turtlesim_node" name = "my_turtle" output = "screen" />
            <node pkg = "turtlesim" type = "turtle_teleop_key" name = "my_key" output = "screen" />
        </group>
    </launch>
    #将会产生2个乌龟GUI,且不会重名

    2-8.arg标签
    /1.属性
        name="参数名称"
        default="默认值" (可选)
        value="数值" (可选)
        不可以与 default 并存
        doc="描述"
    /2.子级标签
    /3.示例
    .例子：
    ..launch文件实现：
    <launch>
        <arg name = "car_length" default = "1034"/>
        <param name = "a" value = "$(arg car_length)" />
        <param name = "b" value = "$(arg car_length)" />
        <param name = "c" value = "$(arg car_length)" />
    </launch>

    ..命令行实现：roslaunch model01 arg.launch car_length:=100

    .launch文件传参语法实现,hello.launch
        <launch>
            <arg name="xxx" />
            <param name="param" value="$(arg xxx)" />
        </launch>
    .命令行调用launch传参

    roslaunch hello.launch xxx:=值
    #命名规则：按照大驼峰命名法，例如：Ros_Learning-------Pub_Sub_demo01.cpp


3.ROS工作空间覆盖
    3-1.问题：特定工作空间的功能包不能重名，但是自定义工作空间的功能包与内置的功能包与内置的功能包
    可以重名或者不同的自定义的工作空间中也可以出现重名的功能包，那么调用该名称的功能包时候，
    会调用哪一个功能包？比如说：自定义工作空间A内存在功能包turtlesim,自定义工作空间B内也存在功能包turtlesim，
    系统内置空间内也存在turtlesim ,那么调用turtlesim时，会调用哪一个工作空间中的呢？
    3-2.实现
    .工作空间A中创建turtlsim包，工作空间B中创建turtlsim包
    .添加source /home/kim/A/devel/setup.zsh
    source /home/kim/B/devel/setup.zsh在.zshrc文件中#因为已经添加了source在zshrc中，所以打开一次终端相当于source 了一次，故就不用source 
    #但是当修改zshrc文件后，必须要source才能继续下一次roscd
    #只当被添加到zshrc中的文件的工作空间才能roscd
    .roscd turtlesim:会直接进入到工作空间B中
        原因:ros会先解析.zshrc文件，并生成ROS_PACKAGE_PATH路径，该变量按照.bashrc中配置设置工作空间优先级，
        在设置时需要遵循一定的原则：ROS_PACKAGE_PATH中值，和.zshrc的配置顺序相反---->后配置的优先级更高
        所以roscd先去B文件而不去A文件
    3-3.存在安全隐患，比如当前工作空间B优先级更高，意味着当程序调用 turtlesim 时，
    不会调用工作空间A也不会调用系统内置的 turtlesim，如果工作空间A在实现时有其他功能包依赖于自身的 turtlesim，而按照ROS工作空间覆盖的涉及原则，
    那么实际执行时将会调用工作空间B的turtlesim，从而导致执行异常，出现安全隐患。
    3-4.BUG：在.zshrc中source了多个工作空间，可能出现的情况，在ROS_PACKAGE_PATH中只包括2个工作空间，可以删除自定义工作空间中的devep和build文件
    重新catkin_make,然后载入.zshrc文件，问题解决

4.ROS节点名称重名
    4-1.现象：rospy.init_node("yyy")来定义节点名称，在ROS中，是不允许出现重名节点的，如果出现会发生混淆，所以当启动的时候，重名节点会被直接关闭。
    命名空间就是为名称添加前缀，名称重映射是为名称起别名。这两种策略都可以解决节点重名问题，两种策略的实现途径有多种:
    4-2.解决方法：
    法1：命名空间：添加前缀 |法2：名称重映射:为名称起别名
    实现途径：rosrun 命令  launch 文件  编码实现

    4-3.设置命名空间与重映射：
        1.rosrun设置命名空间：
        rosrun 包名 节点名 __ns:=/xxx | rosrun turtlesim turtlesim_node __ns:=/xxx
        rosrun 包名 节点名 __ns:=/yyy | rosrun turtlesim turtlesim_node __ns:=/yyy
        .运行结果：rosnode list : /xxx/turtlesim; /yyy/turtlesim

        2.rosrun名称重映射：
        为节点起别名：rosrun 包名 节点名 __name:="新名称"
        rosrun turtlesim  turtlesim_node __name:=t1 
        rosrun turtlesim  turtlesim_node __name:=t2
        rosnode list : /t1 ; /t2

        3.rosrun命名空间同时名称重映射叠加：
        语法：rosrun 包名 节点名 __ns:=新名称 __name:=新名称
        例子：rosrun turtlesim turtlesim_node __ns:=/a  __name:=/b;
        结果：rosnode list:/a/b#__ns为包名，__name为子包名

    问题：[rosrun] Couldn't find executable named turtlesim_node below /home/kim/ROS_Space/test_ws/src/turtlesim
    这是因为在.zshrc中，已经添加了source A/devel/setup.zsh ，所以会默认进入到A的工作空间中，

        4.通过launch文件设置命名空间与重映射
        <launch>
            <node pkg = "turtlesim" type = "turtlesim_node" name = "t1" ns = "hello" />
        </launch>

        5.脚本的方式实现命名空间和重映射：rospy.init_node("lisi",anonymous=True)#这个代表可以启动多个同名节点

5.ROS话题名称重名
    两个节点之间使用了相同的
    5-1.