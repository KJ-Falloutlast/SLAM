# 1.ros学习问题：

!!注意:要保证caktin_make 和rosrun 在终端中跑，不要在vscode的终端中跑

## 1. 编译过程要注意：catkin_make -DPYTHON_EXECUTABLE=/usr/bin/python3
## 2. cd和roscd的区别：
   1. cd命令和roscd命令都是切换到指定目录的命令。不同的是，cd是Linux系统的命令，在使用时必须指定目标目录的完整路径；而roscd是ros系统中的命令，它可以直接切换到指定目录（ros系统中的软件包），而不需要输入冗长的完整路径。
   2. 例如，要切换到roscpp这个软件包，两个命令的格式分别为：
      1. cd /opt/ros/kinetic/share/roscpp
      2. roscd roscpp
显然，在ros系统之中，使用roscd比cd更加的方便的。
但在使用的过程中，我们有时候会发现，roscd命令不能正常使用，系统会提示找不到软件包，这是因为roscd只能切换到那些路径已经包含在ROS_PACKAGE_PATH环境变量中的软件包，这时候我们需要切换到ros系统的工作空间（catkin_ws）下，通过source命令将软件包添加到环境变量中，即：
    cd ~/catkin_ws
    source ./devel/setup.bash
添加环境变量之后，roscd即可正常使用。
注意，如果新打开了一个终端，在使用某一工作空间之前，都需要执行上述命令切换到该工作空间的目录下将工作空间的路径添加到环境变量中。

## 3. rosrun kitti.py

## 4. py脚本要加可执行权限
chmod +x test.py
如何寻找文件：whereis xxx

## 5. rosrun的python接口
pip install rospkg，pip install catkin-tools

## 6. 关于Usage
rosrun [--prefix cmd] [--debug] PACKAGE EXECUTABLE [ARGS]
  rosrun will locate PACKAGE and try to find
  an executable named EXECUTABLE in the PACKAGE tree.
  If it finds it, it will run it with ARGS.
解决办法：
   1. 确认Python的可执行权限，选中右击属性，找到权限那一栏，确保文件为允许作为程序执行文件。
   2. rosrun命令需要后边加功能包的名字，然后再跟Python程序文件名字。
以运行在功能包my_ros_helloworld功能包下的talker.py程序为例。
rosrun my_ros_helloworld talker.py

## 7. 关于anoncoda和ros兼容的问题：conda create -n ROS python=3.8


## 8. ROS依赖包安装问题
   1. 问题描述
在ROS编译过程中经常会遇到找不到ROS包的情况，如下所示
>
   CMake Error at /opt/ros/kinetic/share/catkin/cmake/catkinConfig.cmake:83 (find_package):
     Could not find a package configuration file provided by
     "gazebo_ros_control" with any of the following names:

       gazebo_ros_controlConfig.cmake
       gazebo_ros_control-config.cmake

     Add the installation prefix of "gazebo_ros_control" to CMAKE_PREFIX_PATH or
     set "gazebo_ros_control_DIR" to a directory containing one of the above
     files.  If "gazebo_ros_control" provides a separate development package or
     SDK, be sure it has been installed.

   2. 解决方案

在ROS wiki上有这么一段话，可能很多人都将他忽略了
单个软件包安装: 你也可以安装某个指定的ROS软件包（使用软件包名称替换掉下面的PACKAGE）：

sudo apt-get install ros-kinetic-PACKAGE

例如：

sudo apt-get install ros-kinetic-slam-gmapping


这段话的意思就是：
  当你需要安装ROS的依赖包时，可以使用sudo apt-get install ros-kinetic-PACKAGE命令，其中
  sudo是root用户的意思，
  apt-get install是代表要安装软件
  ros-kinetic-PACKAGE是依赖包的名字（其中ros-kinetic-代表是ROS的依赖包，kinetic是你所使用ROS版本名字，PACKAGE是需要替换的地方，指的是依赖包的名字）
  例如，针对问题中的依赖包，使用如下命令
  sudo apt-get install ros-kinetic-gazebo-ros-control

## 9. 关于python执行路径和环境的问题：

    运行环境位于运行页面左下角，点击一下就可以改变运行环境了。按照网上大部分教程，安装tensorflow时一般都会新建一个环境，而vscode默认很有可能是在根环境下运行的，所以这里要改一下运行环境到安装tensorflow的环境下。
    第二步 检查运行环境下是否安装tensorflow

    在anaconda安装tensorflow的环境下，点击open with python，在指令行中一步步输入以下命令。

    import tensorflow as tf
    tf.__version__
    tf.__path__

    就可以得到下图的结果，输入tf.__version__得到的是安装tensorflow的版本，输入tf.__path__得到的是tensorflow的安装路径，这个后面会用到。
    如果有这些说明安装成功了，那么可以继续看第三步。如果提示没有安装成功那么可能需要去安装一下tensorflow了。
    'D:\\Anaconda3\\envs\\tensorflow\\lib\\site-packages\\tensorflow'

    话不多说，直接上代码。在需要导入tensorflow库的文件内加入以下代码。其中路径是第二步得
   1.
```cpp
import sys cpp
 sys.path.append(r'/home/kim/catkin_ws/src/demo_01/scripts')
```

   2. 如果切换路径仍然无法解决问题,切换python的运行环境

    source /home/kim/anaconda3/bin/activate
    conda activate base
    在此环境下运行


   3. 总结：使用import xx 可以修改模块对象的属性（无论属性是不是可变类型）

    　　    使用from xx import x 只能修改模块对象的属性是可变类型的（不可变类型不能修改）

    这也是为甚麽，尽量不要使用 from XX import * 的原因，会发生属性错误，

    这也是为什么，导入模块需要写在程序开头的位置，并且先导入内置模块，再导入库模块，再导入自定义模块
   
   4. 导包方法：
    若是主程序与被导入的文件在同一个路径，则可以直接from import *
    若是主程序与被导入的文件不在同一个路径，则直接sys.path.apppend('abspath')到的tensorflow安装路径的上一级。

   5. 环境问题:一个环境对应一个工程,要确保你运行的包在你用的这个环境中,否则运行会出错

## 10. 命名规则：

问题：**WARNING: Package name "Sever" does not follow the naming conventions. 
It should start with a lower case letter and only**
解决方案：在rospackage 中不能有大写，所以必须只能用小写

## 12. cmake问题：
    1. 问题
CMake Error at /opt/ros/noetic/share/catkin/cmake/catkin_install_python.cmake:86 (message):
  catkin_install_python() called with non-existing file
  '/home/kim/ROS_Space/demo02_ws/src/model03_service/scripts/pub_twist.py'.
Call Stack (most recent call first):
  model03_service/CMakeLists.txt:161 (catkin_install_python)
  
    2. 原因：cmake中添加了文件，但是文件并不在scripts目录下

    3. 解决方案：删除cmake_install中的这个文件

    4. 当新创建了一个功能包的时候，如果不能自动补全，那么就自己输入包的名称
    5. 当改变包的名字后，可以改变cmake和xml文件名：
```cpp
xml:<name>model02</name>  
cmakelists:project(model02)
```

## 13. launch文件的使用
    1. launch文件不能加","；子标签以/结尾；尾标签以/开头；
    2. 每次启动launch文件都不需要catkin_make，直接source后运行就行

## 14. catkin_make问题
1. CMake Error: The source directory "/home/kim/ROS_Space/catkin_ws_cpp/src" does not exist.
   1. 解决方案：删除build和devep后重新catkin_make
2. fatal error: pub_sub/Person.h: 没有那个文件或目录
   1. 解决方案：重新catkin_make
3. 问题3
   1. 描述
```cpp
/usr/bin/ld: turtle_control.cpp:(.text+0x21b): undefined reference to `tf2_ros::TransformListener::TransformListener(tf2::BufferCore&, bool, ros::TransportHints)'
```
   2. 解决方案：重新创建功能包
## 15. 自动补全的问题
**直接使用这个配置就可以自动补全**
```json
{
  "configurations": [
      {
          "name": "Linux",
          "includePath": [
              "/opt/ros/noetic/include",
              "/usr/include",
              "${workspaceFolder}/**",
              "${workspaceFolder}/devel/include",
              "/usr/include/pcl-1.8",
              "/usr/include/eigen3",
              "/usr/include/x86_64-linux-gnu/qt5/QtWidgets",
              "/usr/include/x86_64-linux-gnu/qt5",
              "/usr/include/x86_64-linux-gnu/qt5/QtCore"
          ],
          "defines": [],
          "compilerPath": "/usr/bin/gcc",
          "cStandard": "c11",
          "cppStandard": "c++17",
          "intelliSenseMode": "clang-x64"
      }
  ],
  "version": 4
}
```

# 2.linux学习问题



## 1. sublime的python编译环境：
   1. 快捷键：在Perferences -> Key Binding，打开配置文件，添加如下几行：
```cpp
{ "keys": ["ctrl+l"], "command": "move", "args": {"by": "characters", "forward": true} },
{ "keys": ["ctrl+j"], "command": "move", "args": {"by": "characters", "forward": false} },
{ "keys": ["ctrl+k"], "command": "move", "args": {"by": "lines", "forward": true} },
{ "keys": ["ctrl+i"], "command": "move", "args": {"by": "lines", "forward": false}},
```
   2. 编译环境：https://blog.csdn.net/mx472756841/article/details/50535517?spm=1001.2101.3001.6650.17&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7EHighlightScore-17.queryctrv2&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7EHighlightScore-17.queryctrv2&utm_relevant_index=22
   3. 步骤：ctrl+shift+p-->install package-->xxxxx



## 2. 利用clash代理问题：
https://www.jianshu.com/p/260fbac1d4a2
启动：clash;proxy_on,proxy_off分别代表开关代理


## 3. 进程问题：

   1. 常规篇：
　首先，用ps查看进程，方法如下：
$ ps -ef
此时如果我想杀了火狐的进程就在终端输入：
$ kill -s 9 1827
其中-s 9 制定了传递给进程的信号是９，即强制、尽快终止进程。各个终止信号及其作用见附录。
1827则是上面ps查到的火狐的PID。

简单吧，但有个问题，进程少了则无所谓，进程多了，就会觉得痛苦了，无论是ps -ef 还是ps -aux，每次都要在一大串进程信息里面查找到要杀的进程，看的眼都花了。

2. 进阶篇：

改进１：

把ps的查询结果通过管道给grep查找包含特定字符串的进程。管道符“|”用来隔开两个命令，管道符左边命令的输出会作为管道符右边命令的输入。

$ ps -ef | grep firefox

smx 1827 1 4 11:38 ? 00:27:33 /usr/lib/firefox-3.6.18/firefox-bin
smx 12029 1824 0 21:54 pts/0 00:00:00 grep --color=auto firefox

这次就清爽了。然后就是

$kill -s 9 1827

 

改进２——使用pgrep：

一看到pgrep首先会想到什么？没错，grep！pgrep的p表明了这个命令是专门用于进程查询的grep。

$ pgrep firefox
1827

看到了什么？没错火狐的PID，接下来又要打字了：

$kill -s 9 1827
3. 无法获得锁
   1. 问题描述：正在等待缓存锁：无法获得锁 /var/lib/dpkg/lock-frontend。锁正由进程322
   2. 解决方案：
      1. sudo rm /var/cahe/apt/archives/lock
      2. sudo rm /var/lib/dpkg/lock
## 3. 将anoconda设为默认python解释器的方法
  
  在终端输入$sudo gedit /etc/profile，打开profile文件。
  在文件末尾添加一行：export PATH=/home/kim/anaconda3/bin:$PATH，其中，将“/home/grant/anaconda2/bin”替换为你实际的安装路径。保存。

## 4.改变默认终端的问题：
   1. 安装terminator:sudo apt install terminator2
   2. 安装oh-my-zsh

oh-my-zsh中整理了常用的zsh扩展和主题,所以先安装oh-my-zsh

    使用curl安装 :

sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"

    使用wget安装 :

sh -c "$(wget https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh -O -)"

注意: 这两个地址都已经变更，个人文章不再跟进，具体的以OhMyZsh官网的地址为准


   3. 安装主题

这儿列出了zsh的主题列表,选一个自己喜欢的吧

    个人比较喜欢agnoster这个主题

      1. 安装:

        在安装之前先保证自己电脑上有powerline font,因为该主题会使用到这些特殊的字符,使用下面语句检测是否存在该主题需要的特殊字符
        $ echo "\ue0b0 \u00b1 \ue0a0 \u27a6 \u2718 \u26a1 \u2699"
        正确的输出应该是这样:

        如果没有,就安装该字体库:
        $ sudo apt-get install fonts-powerline

        主题在安装oh-my-zsh时已经下载,直接在oh-my-zsh的配置文件中配置使用的主题即可

        配置文件是~/.zshrc,打开编辑

        将这一行后面改成自己想要的主题名,保存退出即可

        打开zsh看看效果:

      2. 将zsh设置为系统默认终端

        执行这条语句:
        chsh -s which zsh
        然后重新登录系统即可
        切换回去的话：
        chsh -s /bin/bash


   4. 卸载zsh:
cd .oh-my-zsh/tools
chmod +x uninstall.sh
./uninstall.sh
rm -rif .zshrc



   5. 安装zsh以后的修改

linux中的执行文件.bashrc 变更为 .zshrc

目录为/home下的用户文件夹中

正确的做法：

    将所需配置修改写入~/.zshrc
    执行 source ~/.zshrc
    将所有的操作转成zshrc

## 5. 使用typora

官网下载链接：Typora-linux-x64.tar.gz
进入下载文件夹，解压Typora-linux-x64.tar.gz
tar -zxvf Typora-linux-x64.tar.gz
解压得到bin文件夹
cd bin
进入后可以看到Typora-linux-x64文件夹
将Typora-linux-x64文件夹复制到默认用来存放软件的/opt目录
sudo cp -ar Typora-linux-x64 /opt

vim typora.desktop

复制如下配置信息

  [Desktop Entry]
  Name=Typora
  Exec=/opt/Typora-linux-x64/Typora
  Type=Application
  Icon=/opt/Typora-linux-x64/resources/asserts/icon/icon_512x512.png

  保存（ESC -> shift+: -> wq）
  wq
将快捷方式复制到/usr/share/applications
sudo cp typora.desktop /usr/share/applications/#此文件夹是专门放快捷方式的

至此就可以搜索到Typora并将其添加进收藏夹啦

## 6. jupyter notebook的相关问题
```py
Opencv无法显示图像，报错QObject::moveToThread: Current thread is not the object's thread . Cannot move to target thread

解决方案：conda install pyqt，pip install opencv-python==4.1.2.30

PS：因为这个报错信息比较模糊不够具体，所以无法定位问题的根源在哪。在网上寻找了各种解决方法，基本上都是如下的方法，但是我是在实验室的服务器上，没有sudo权限，没法apt-get，因此下面这种方案并没有亲自尝试，这里贴出来作为参考吧。
```
## 7. 软件源的问题
1. 方法一：!!!一定不能随便修改软件源，否则程序安装会出错
如果不慎修改了source.list内容，导致一系列错误，建议恢复默认源文件。

sudo gedit /etc/apt/sources.list

然后把下面默认源内容复制进去

ubuntu20.LTS系统默认源sources.list文件内容

```sh
#deb cdrom:[Ubuntu 20.04 LTS _Focal Fossa_ - Release amd64 (20200423)]/ focal main restricted
 
# See http://help.ubuntu.com/community/UpgradeNotes for how to upgrade to
# newer versions of the distribution.
deb http://cn.archive.ubuntu.com/ubuntu/ focal main restricted
# deb-src http://cn.archive.ubuntu.com/ubuntu/ focal main restricted
 
## Major bug fix updates produced after the final release of the
## distribution.
deb http://cn.archive.ubuntu.com/ubuntu/ focal-updates main restricted
# deb-src http://cn.archive.ubuntu.com/ubuntu/ focal-updates main restricted
 
## N.B. software from this repository is ENTIRELY UNSUPPORTED by the Ubuntu
## team. Also, please note that software in universe WILL NOT receive any
## review or updates from the Ubuntu security team.
deb http://cn.archive.ubuntu.com/ubuntu/ focal universe
# deb-src http://cn.archive.ubuntu.com/ubuntu/ focal universe
deb http://cn.archive.ubuntu.com/ubuntu/ focal-updates universe
# deb-src http://cn.archive.ubuntu.com/ubuntu/ focal-updates universe
 
## N.B. software from this repository is ENTIRELY UNSUPPORTED by the Ubuntu 
## team, and may not be under a free licence. Please satisfy yourself as to 
## your rights to use the software. Also, please note that software in 
## multiverse WILL NOT receive any review or updates from the Ubuntu
## security team.
deb http://cn.archive.ubuntu.com/ubuntu/ focal multiverse
# deb-src http://cn.archive.ubuntu.com/ubuntu/ focal multiverse
deb http://cn.archive.ubuntu.com/ubuntu/ focal-updates multiverse
# deb-src http://cn.archive.ubuntu.com/ubuntu/ focal-updates multiverse
 
## N.B. software from this repository may not have been tested as
## extensively as that contained in the main release, although it includes
## newer versions of some applications which may provide useful features.
## Also, please note that software in backports WILL NOT receive any review
## or updates from the Ubuntu security team.
deb http://cn.archive.ubuntu.com/ubuntu/ focal-backports main restricted universe multiverse
# deb-src http://cn.archive.ubuntu.com/ubuntu/ focal-backports main restricted universe multiverse
 
## Uncomment the following two lines to add software from Canonical's
## 'partner' repository.
## This software is not part of Ubuntu, but is offered by Canonical and the
## respective vendors as a service to Ubuntu users.
# deb http://archive.canonical.com/ubuntu focal partner
# deb-src http://archive.canonical.com/ubuntu focal partner
 
deb http://security.ubuntu.com/ubuntu focal-security main restricted
# deb-src http://security.ubuntu.com/ubuntu focal-security main restricted
deb http://security.ubuntu.com/ubuntu focal-security universe
# deb-src http://security.ubuntu.com/ubuntu focal-security universe
deb http://security.ubuntu.com/ubuntu focal-security multiverse
# deb-src http://security.ubuntu.com/ubuntu focal-security multiverse
 
# This system was installed using small removable media
# (e.g. netinst, live or single CD). The matching "deb cdrom"
# entries were disabled at the end of the installation process.
# For information about how to configure apt package sources,
# see the sources.list(5) manual.
```

sudo apt update

   2. 方法2
W: 目标 DEP-11-icons-hidpi (multiverse/dep11/icons-64x64@2.tar) 在 
/etc/apt/sources.list:21 和 /etc/apt/sources.list:85 中被配置了多次
注释掉重复的软件源

2. 采用update-alternatives 切换版本

    update-alternatives是Debian提供的一个工具，通过链接的方式，但是其切换的过程非常方便。
    首先看一下update-alternatives的帮助信息：

    $ update-alternatives --help
3. 目标 * 在 /etc/apt/sources.list:41 和 /etc/apt/sources.list.d/xenial-partner.list:4 中被配置了多次
   1. 解决办法：*sudo vim /etc/apt/sources.list*,然后直接直接将重复的那几行注释掉就行


## 8. 用法：update-alternatives [<选项> ...] <命令>
```cpp
    命令：
      --install <链接> <名称> <路径> <优先级>
        [--slave <链接> <名称> <路径>] ...
                               在系统中加入一组候选项。
      --remove <名称> <路径>   从 <名称> 替换组中去除 <路径> 项。
      --remove-all <名称>      从替换系统中删除 <名称> 替换组。
      --auto <名称>            将 <名称> 的主链接切换到自动模式。
      --display <名称>         显示关于 <名称> 替换组的信息。
      --query <名称>           机器可读版的 --display <名称>.
      --list <名称>            列出 <名称> 替换组中所有的可用候选项。
      --get-selections         列出主要候选项名称以及它们的状态。
      --set-selections         从标准输入中读入候选项的状态。
      --config <名称>          列出 <名称> 替换组中的可选项，并就使用其中
                               哪一个，征询用户的意见。
      --set <名称> <路径>      将 <路径> 设置为 <名称> 的候选项。
      --all                    对所有可选项一一调用 --config 命令。
     
    <链接> 是指向 /etc/alternatives/<名称> 的符号链接。
        (如 /usr/bin/pager)
    <名称> 是该链接替换组的主控名。
        (如 pager)
    <路径> 是候选项目标文件的位置。
        (如 /usr/bin/less)
    <优先级> 是一个整数，在自动模式下，这个数字越高的选项，其优先级也就越高。
     
    选项：
      --altdir <目录>          改变候选项目录。
      --admindir <目录>        设置 statoverride 文件的目录。
      --log <文件>             改变日志文件。
      --force                  就算没有通过自检，也强制执行操作。
      --skip-auto              在自动模式中跳过设置正确候选项的提示
                               (只与 --config 有关)
      --verbose                启用详细输出。
      --quiet                  安静模式，输出尽可能少的信息。不显示输出信息。
      --help                   显示本帮助信息。
      --version                显示版本信息。

    首先我们先看一下有没有关于Python的可选项：

$ update-alternatives --display python

    update-alternatives: 错误: 无 python 的候选项
    那首先先建立python的组,并添加Python2和Python3的可选项

    $ sudo update-alternatives --install /usr/bin/python python /usr/bin/python2.7 2 # 添加Python2可选项，优先级为2
    $ sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.4 1 #添加Python3可选项，优先级为1

    注意，这里的/usr/bin/python链接文件，两个可选项必须是一样的，这样这个链接文件才可以选择两个不同的可选项去进行链接工作。
    这时如果我们查看/usr/bin/python这个文件时，会发现它已经链接到了/etc/alternatives/python。
    查看当前版本

    $ python --version
    Python 2.7.6

使用命令查看python的可以切换的版本，命令如下

$ sudo update-alternatives --config python

      选择       路径              优先级  状态
    ------------------------------------------------------------
    * 0            /usr/bin/python2.7   2         自动模式
      1            /usr/bin/python2.7   2         手动模式
      2            /usr/bin/python3.4   1         手动模式

    要维持当前值[*]请按回车键，或者键入选择的编号：
    原来是因为默认选中了自动模式，而Python2的优先级高于Python3，这时候只要键入2，就可以使用Python3了。
```
## 9. 修改为只读状态：
sudo chmod 444 /etc/environment

## 10. tar and rar
sudo apt-get install rar
sudo apt-get install unrar 
执行unrar xxxxx.rar可以解压文件

## 11. 简体和繁体转换：ctrl+shift+f

## 12. 错误：
ERROR: Could not open requirements file: [Errno 2] 没有那个文件或目录: 'requrements.txt'
解决方案：
    sudo pip freeze > requirements.txt
    sudo pip install -r requirements.txt


## 13.利用管道筛选
ls -l | grep python

## 14. 查看电脑配置
  * free -g 
  cat /etc/issue
  lscpu
  ifconfig
## 15. 内存条问题：
  *  sudo dmidecode -t memory**查看内存条和内存槽**
  * sudo dmidecode -t memory | grep Size**查看每个内存多大**
  * sudo dmidecode | grep "System Information" -A9 | egrep "Manufacturer|Product|Serial"

## 16.卸载问题
1. 任何时候都不要用sudo apt autoremove xxx
2. 卸载时候用:sudo apt remove xxx | sudo apt purge xxx
## 17.vscode的配置问题
1. 打开c_cpp_properties的方法：

   Ctrl+Shift+P
   Edit configuration
   c_cpp_properties.json
```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "/opt/ros/noetic/include",
                "/usr/include",
                "${workspaceFolder}/**",
                "${workspaceFolder}/devel/include",
                "/usr/include/pcl-1.8",
                "/usr/include/eigen3",
                "/usr/include/x86_64-linux-gnu/qt5/QtWidgets",
                "/usr/include/x86_64-linux-gnu/qt5",
                "/usr/include/x86_64-linux-gnu/qt5/QtCore"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "clang-x64"
        }
    ],
    "version": 4
  }
```
## 18.软件问题
1. amd64 = x64

## 19.输入法问题：
1. 问题：若是无法输入中文了，直接删掉.config下的fctix文件和/home目录下的配置文件，然后按照linux搜狗输入法重装

## 20.安装opencv的问题
1. 安装方法
[当source /etc/bash.bashrc失败怎么做？](https://blog.csdn.net/PecoHe/article/details/97476135)
[步骤](https://blog.csdn.net/public669/article/details/99044895?spm=1001.2101.3001.6650.5&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Edefault-5-99044895-blog-120614133.pc_relevant_aa&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Edefault-5-99044895-blog-120614133.pc_relevant_aa&utm_relevant_index=10)
[opencv耦合vscode](https://blog.csdn.net/qq_42950957/article/details/123899581)
2. 问题
   1. 安装路径查看:sudo find / -iname "*opencv*"
   2. 最终配置文件
```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "/opt/ros/noetic/include",
                "/usr/include",
                "${workspaceFolder}/**",
                "/usr/local/share/**",
                "${workspaceFolder}/devel/include",
                "/usr/local/include/opencv4/**",
                "/usr/local/lib/**",
                "/usr/include/pcl-1.8",
                "/usr/include/eigen3",
                "/usr/include/x86_64-linux-gnu/qt5/QtWidgets",
                "/usr/include/x86_64-linux-gnu/qt5",
                "/usr/include/x86_64-linux-gnu/qt5/QtCore"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "clang-x64"
        }
    ],
    "version": 4
  }
```
# 3.c++学习问题

1. endl的问题:
加<<endl后会有一个换行,下次再用cout输出字符时就会在下一行开始输出，
如果不加，就会跟在当前行的最后输出。
2. 什么时候加;的问题:
    1.定义变量:int a;using namespace std;调用函数:printcolor();cout;cin;return 0;表达式后要加
    2.头文件不要加;语句后不要加,if(){},switch(){};等等
    除了头文件,各种流程结构不要加外,其余都要加:1.变量定义;2.namespace;3.cout,cin,return,break都要加
    
3. 变量定义的:1.可以不先赋值:int a;2.可以一次定义多个变量:int a, b, c(此时也可多变量赋值);int a=1 ,b=2;
4. 多行注释：/* int a;int b;  */
5. 是否加花括号问题：
有括号的话，if语句控制{}里面的所有语句，没括号的话，if语句只控制最近的一行，每句代码以分号 ; 分隔开来。
例子:
demo2（if语句后跟分隔语句）：
if(1<2) var a = 10;var b=20;var c=30;//都执行
console.log(a,b,c)

if(1>2) var a = 10;var b=20;var c=30;//不执行a
console.log(a,b,c)
/注意事项：所有的选择语句和循环语句都可以不加花括号，但是这仅限于循环体或者选择体中只有一个语句，且执行一句
如果不用大括号括起来,那么只循环它下面的那一句

6. 命名问题：函数采用小驼峰命名法，类和结构体采用大驼峰命名法
7. 双引号的问题：类，结构体定义后面要接分号，定义函数和语句最后面不要接分号
8. 程序分段错误”（Segmentationfault）的信息
9. argc合argv的关系
```cpp
#include <iostream>
using namespace std;
int main(int argc, char *argv[]){
    for (int i = 0; i < argc; i++){
        cout << argv[i] << endl;
    }
    return 0;
}
```

# 4.其余学习问题
## 1. 进制输入 
    a，默认为10进制 ，10 ，20。
    b，以0开头为8进制，045，021。
    c，以0b开头为2进制，0b11101101。
    d，以0x开头为16进制，0x21458adf。   

## 2. 欧拉角度
## 3. 终端的控制命令
ctrl+shift+o/p：水平/垂直分割
tab:自动补全
win+方向箭头:移动终端的位置
alt+方向键：移动到某个终端
ctrl+shift+w:关闭终端
ctrl+alt+t:重新打开某个终端

## 4. 代理的使用

   1. clash for windows
```cpp
步骤：
1. cd download
解压包并放入opt文件夹

sudo tar -zxf Clash.for.Windows-0.17.1-x64-linux.tar.gz -C /opt
打开 opt文件夹
cd /opt

重命名文件夹
sudo mv 'Clash for Windows-0.17.1-x64-linux' clash

打开程序文件夹
cd clash 

运行clash
./cfw 

2. 配置clash
将首页设置为以下样式：allow lan打开
将订阅链接导入,点击 Download

3. 修改配置文件
将文件改为可读可写状态
sudo chmod 666 /etc/environment

4. 编辑文件
vi /etc/environment
填入以下内容且保存
http_proxy=http://127.0.0.1:7890/
https_proxy=http://127.0.0.1:7890/
ftp_proxy=http://127.0.0.1:7890/
HTTP_PROXY=http://127.0.0.1:7890/
HTTPS_PROXY=http://127.0.0.1:7890/
FTP_PROXY=http://127.0.0.1:7890/
改为原来的只读状态
sudo chmod 444 /etc/environment
最后重启即可
```
   2. clash-linux-amd64-v1.9.0.gz
      1. 下载

下载对应的Linux-amd64版本，也可以直接在线下载
wget https://github.com/Dreamacro/clash/releases/download/v1.8.0/clash-linux-amd64-v1.8.0.gz
      2. 安装

进入安装包存放目录，解压安装
gunzip clash-linux-amd64-v1.9.0.gz
sudo mv clash-linux-amd64-v1.9.0 /usr/local/bin/clash
sudo chmod +x /usr/local/bin/clash
cd /usr/local/bin/
./clash

clash启动后会在~/.config/clash 目录生成配置文件


将你从机场导出的配置文件(路径根据你实际修改，我的放在tools目录下)，替换默认的配置
sudo cat tools/FY-21329.yaml > ~/.config/clash/config.yaml

然后重新执行/usr/local/bin/clash
配置开机启动

在配置开机启动之前，将配置文件移动到 /etc 目录：
sudo mv ~/.config/clash /etc
**此处要注意：1.在重新移动的过程中，要将原来的在/etc的clash文件删除然后才能执行此步骤,或者直接替换调/etc下的clash.ymal文件 2.在没有在配置开机启动前，linux会执行在.config下的yaml文件，所以配置好开机启动后，就要直接修改在/etc下的yaml文件 3.cfw 和 clash不要同时启动 4.每次配置完后都要开机启动才能使节点生效**
以后修改配置都记住修改 /etc/clash 目录下的这个配置文件。
然后使用 vim 增加 systemd 配置 ,：
sudo vim /etc/systemd/system/clash.service
放入如下内容:
[Unit]
Description=Clash Daemon

[Service]
ExecStart=/usr/local/bin/clash -d /etc/clash/
Restart=on-failure

[Install]
WantedBy=multi-user.target

启用 clash service:
sudo systemctl enable clash.service  #设置开机自启动
sudo systemctl start clash.service  #手动启动
配置启用/关闭代理函数
sudo vim .bashrc
增加以下内容


```sh
# proxy on
# proxy off
function proxy_off() {
        unset http_proxy
            unset https_proxy
                unset no_proxy
                    echo -e "Proxy Off"
                }

function proxy_on(){
      export http_proxy="http://127.0.0.1:7890"
        export https_proxy=$http_proxy
          export no_proxy="localhost,127.0.0.1,localaddress,.localdomain.com"
            echo -e "Proxy On"
    }
```

`$source .bashrc  #使配置生效`

接下里就可以通过命令开关代理了
proxy_on
proxy_off

   3. 注意：当网络不能用的时候，要用cd /opt/clash---->./cfw---->profile节点------>导出yaml文件---->用yaml替换/etc/clash/.cofig.yml文件
   4. 当重新迁移系统之后，如何恢复和以前一样的配置
      1. 将原来在**usr/local/bin/clash + .config/clash + etc/clash**这三个文件全部删除(sudo rm -r /etc/clash)
      2. 将原来在/usr/local/bin/clash 复制到新的系统的/usr/local/bin这个路经
      3. 将原来在.config/clash 复制新的系统的.config/clash文件  (sudo cp -r olddir newdir)
      4. 将原来在/etc/clash 复制新的系统的/etc/clash文件   
   5. *补充*：在ubuntu系统中也要设置为手动代理：
      1. 127.0.0.1 7890*http*
      2. 127.0.0.1 7890*https*
      3. 127.0.0.1 7891*socks*
      4. 127.0.0.1 *忽略主机*
   6. 常用节点
https://suo.yt/151bpdM(失效了)
https://suo.yt/1LxmMPA(gg)
https://raw.githubusercontent.com/ssrsub/ssr/master/V2Ray
https://suo.yt/ZKjZa7R
https://suo.yt/uXoibyeJ
https://suo.yt/dsXxAuV(**稳定**)
## 5. wine的相关问题：
1. 未安装windows应用
 $ sudo apt-get update
 $ sudo apt-get install wine
 $ sudo apt-get install winetricks ##直接运行winetricks来运行程序

2. wine新版 wine-5.12 微信、QQ 等软件输入框无法输入的问题解决办法
 winetricks riched20
 .文件删除：直接启动winetricks---->默认容器---->卸载程序
 .文件安装：方法1：在当前目录下执行：wine XXX.exe;方法2：直接运行winetricks---->安装windows应用
 .qq和微信文件的安装路径：/home/kim/.wine/drive_c/Program Files (x86)/Tencent

3. 问题:
 . 描述：You are using a 64-bit WINEPREFIX. Note that many verbs only install 32-bit versions of packages. 
 If you encounter problems, please retest in a clean 32-bit WINEPREFIX
  before reporting a bug.
 . 解决方案：winetricks riched20
4. winetricks配置方案
   1. sudo apt install winetricks
   2. winetricks **colorprofile corefonts d3dx9 fontfix fontsmooth-gray fontsmooth-rgb fontsmooth-bgr *gdiplus mfc40 mfc42 msxml3 msxml4 msxml6* riched20 riched30 tahoma urlmon vb6run vcrun6 vcrun2003 vcrun2005 vcrun2008 ie6 allfonts**(*直接安装相关依赖就行*)
```sh
winetricks colorprofile corefonts d3dx9 fontfix fontsmooth-gray fontsmooth-rgb fontsmooth-bgr gdiplus mfc40 mfc42 msxml3 msxml4 msxml6 riched20 riched30 tahoma urlmon vb6run vcrun6 vcrun2003 vcrun2005 vcrun2008 ie6 allfonts
```
  
## 6. 删除在linux的垃圾图标
看/usr/share/applications下是否有xxx.desktop，若有就直接删除
可以到～/.local/share/applications下看是否有xxx.desktop,若有就直接

## 7. github的问题：
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

## 8. 关于网络重启问题
   1. 关闭：systemctl stop systemd-resolved---重启：sudo systemctl enable systemd-resolved.service(**这样开机就可以自动重启**)
   2. 切记千万不能乱操作这些在根目录下的配置文件;

## 9. 关于linux源的问题
1. 问题：不要随意修改源，要将原来的源及时备份，以防丢失
2. 问题：**ubuntu安装nodejs，执行sudo apt-get update报错的解决办法。错误信息: 仓库 “http://ppa.launchpad.net/chris-lea/node.js/ubuntu focal Release” 没有 Release 文件**
   1. step1:sudo add-apt-repository --remove ppa:/chris-lea/node.js(按照出错的文件名来写)
   2. step2:sudo apt update
3. 若迁移系统后，源发生问题，则直接复制原来/etc/apt文件到新的系统中，sudo apt update若有错误，则按照2的方法改进


## 10. 关于网站和学习细节的问题
1. 将书签分类整理
2. 在上网时将网站分类打开，不要弄得毫无逻辑