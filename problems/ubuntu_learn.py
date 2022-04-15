1.clash安装：
(1)网址：https://www.jianshu.com/p/02e3e8ccfe80；最后执行./cfw;
若是连接clash后仍然无法上网的解决方法：选项 高级 网络 然后在里面设置一下代理服务器为无/自动
(2)直接使用终端，按ctrl+h找到相应的.config文件下的clash的.yaml文件,直接导入配置文件即可
sudo systemctl enable clash.service  #设置开机自启动
sudo systemctl start clash.service  #手动启动





2.vim命令行：https://blog.csdn.net/xiaolong2w/article/details/8224839?spm=1001.2101.3001.6650.3&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-3.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-3.pc_relevant_default&utm_relevant_index=6



3.utuntu命令：https://www.jianshu.com/p/38594c59c585
sudo dpkg -i package.deb
sudo apt install package

4.ros安装的坑：
补坑的方法https://blog.csdn.net/yeluoyeqiushui/article/details/108310121
查询地址网站：https://ipaddress.com/website/raw.githubusercontent.com
将梯子改成rule

5.kitti问题：
安装data raw
复制链接：wget -b https://s3.eu-central-1.amazonaws.com/avg-kitti/data_object_velodyne.zip
查看下载进度：tail -f wget-log

6.安装和卸载软件：
卸载软件：https://blog.csdn.net/luckydog612/article/details/80877179(dpkg 是Debian package的简写)
	dpkg --list  在终端中找到你需要卸载的软件的名称，列表是按照首字母排序的  在终端上输入命令
	sudo apt-get --purge remove 包名（--purge是可选项，写上这个属性是将软件及其配置文件一并删除，如不需要删除配置文件，可执行sudo apt-get remove 包名） ，此处我要删除的是polipo ，那么在终端输入sudo apt-get --purge remove polipo，按下回车，输入密码，再次回车。 (包名是第二列)
安装软件：https://blog.csdn.net/weixin_45309916/article/details/107778655
	1.appstore
	2.sudo apt xxx install
	3.sudo dpkg  -i  xxx.deb

7.ctrl+H显示默认文件夹

8.catkin_make的编译错误：每次使用catin_ws前都要编译



