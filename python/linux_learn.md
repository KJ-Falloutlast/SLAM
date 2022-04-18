常用命令：
!在退出终端的时候要用命令ctrl+c

一、系统信息

    显示机器的处理器架构

arch
# 或
uname -m
显示正在使用的内核版本
uname -r
显示硬件系统部件 – (SMBIOS / DMI)
dmidecode -q
罗列一个磁盘的架构特性
hdparm -i /dev/hda
在磁盘上执行测试性读取操作
hdparm -tT /dev/sda
显示CPU info的信息
cat /proc/cpuinfo
显示中断
cat /proc/interrupts
校验内存使用
cat /proc/meminfo
显示哪些swap被使用
cat /proc/swaps
显示内核的版本
cat /proc/version
显示网络适配器及统计
cat /proc/net/dev
显示已加载的文件系统
cat <file-system-dir>
罗列 PCI 设备
lspci -tv
显示 USB 设备
lsusb -tv
显示系统日期
date
显示2007年的日历表
cal 2007
设置日期和时间 – 月日时分年.秒
date 041217002007.00
将时间修改保存到 BIOS
clock -w

    几种查看CentOS系统版本和位数的方法

二、关机(系统的关机、重启以及登出)

    关闭系统

shutdown -h now
# 或
init 0
# 或
telinit 0
按预定时间关闭系统
shutdown -h <hours>:<minutes> &
取消按预定时间关闭系统
shutdown -c
重启
reboot
# 或
shutdown -r now
注销
logout

三、文件和目录

    进入 '/ home' 目录'

cd /home
返回上一级目录
cd ..
返回上两级目录
cd ../../
进入个人的主目录
cd
进入<username>的个人主目录
cd ~<username>
返回上次所在的目录
cd -
显示工作路径
pwd
查看目录中的文件
ls
查看目录中的文件
ls -f
显示文件和目录的详细资料
ls -l
显示隐藏文件
ls -a
显示文件和目录由根目录开始的树形结构(1)
tree
显示文件和目录由根目录开始的树形结构(2)
lstree
创建一个叫做 'dir1′ 的目录'
mkdir dir1
同时创建两个目录
mkdir dir1 dir2
创建一个目录树
mkdir -p <multilevel-directory>
删除一个叫做 '<file-name>′ 的文件'
rm -f <file-name>
删除一个叫做 'dir1′ 的目录'
rmdir dir1
删除一个叫做 'dir1′ 的目录并同时删除其内容
rm -rf dir1
同时删除两个目录及它们的内容
rm -rf dir1 dir2
重命名/移动 一个目录
mv dir1 new_dir
复制一个文件
cp <file-name> file2
复制一个目录下的所有文件到当前工作目录
cp dir/* .
复制一个目录到当前工作目录
cp -a /tmp/dir1 .
复制一个目录
cp -a dir1 dir2
创建一个指向文件或目录的软链接
ln -s <file-name> lnk1
创建一个指向文件或目录的物理链接
ln <file-name> lnk1
按照格式(YYMMDDhhmm)修改一个文件或目录的时间戳
touch -t 0712250000 <file-name>
输出指定文件的编码
file <file-name>
列出已知的编码
iconv -l
转换文件编码
iconv -f <from-encoding> -t <to-encoding> <input-file> > <output-file>
图片批量减小图片大小，将结果输入到另一个文件夹(依赖Imagemagick)
find ./ -maxdepth 1 -name -jpg -print -exec convert "{}” -resize 80×60 "thumbs/{}” ;

四、文件搜索

    从 '/' 开始进入根文件系统搜索文件和目录

find / -name <file-name> 
搜索属于用户 'user1′ 的文件和目录
find / -user user1
在目录 '/ home/user1′ 中搜索带有'.bin' 结尾的文件
find /home/user1 -name - bin
搜索在过去100天内未被使用过的执行文件
find /usr/bin -type f -atime +100 
搜索在10天内被创建或者修改过的文件
find /usr/bin -type f -mtime -10 
搜索以 ‘.rpm' 结尾的文件并定义其权限
find / -name - rpm -exec chmod 755 '{}'
搜索以 ‘.rpm' 结尾的文件，忽略光驱、捷盘等可移动设备
find / -xdev -name - rpm 
寻找以 ‘.ps' 结尾的文件 – 先运行 'updatedb' 命令
locate - ps 
显示一个二进制文件、源码或man的位置
whereis halt 
显示一个二进制文件或可执行文件的完整路径
which halt 

五、挂载一个文件系统

    挂载一个叫做hda2的盘 – 确定目录 '/ mnt/hda2′ 已经存在

mount /dev/hda2 /mnt/hda2
卸载一个叫做hda2的盘 – 先从挂载点 '/ mnt/hda2′ 退出
umount /dev/hda2 
当设备繁忙时强制卸载
fuser -km /mnt/hda2 
运行卸载操作而不写入 /etc/mtab 文件- 当文件为只读或当磁盘写满时非常有用
umount -n /mnt/hda2 
挂载一个软盘
mount /dev/fd0 /mnt/floppy 
挂载一个cdrom或dvdrom
mount /dev/cdrom /mnt/cdrom 
挂载一个cdrw或dvdrom
mount /dev/hdc /mnt/cdrecorder 
挂载一个cdrw或dvdrom
mount /dev/hdb /mnt/cdrecorder 
挂载一个文件或ISO镜像文件
mount -o loop file.iso /mnt/cdrom 
挂载一个Windows FAT32文件系统
mount -t vfat /dev/hda5 /mnt/hda5 
挂载一个usb 捷盘或闪存设备
mount /dev/sda1 /mnt/usbdisk 
挂载一个windows网络共享
mount -t smbfs -o username=user,password=pass //WinClient/share /mnt/share 

六、磁盘空间

    显示已经挂载的分区列表

df -h 
以尺寸大小排列文件和目录
ls -lSr |more 
估算目录 'dir1′ 已经使用的磁盘空间'
du -sh dir1
以容量大小为依据依次显示文件和目录的大小
du -sk * | sort -rn
以大小为依据依次显示已安装的rpm包所使用的空间 (fedora, redhat类系统)
rpm -q -a –qf '%10{SIZE}t%{NAME}n' | sort -k1,1n 
以大小为依据显示已安装的deb包所使用的空间 (ubuntu, debian类系统)
dpkg-query -W -f='${Installed-Size;10}t${Package}n' | sort -k1,1n

七、用户和群组

    创建一个新用户组

groupadd group_name
删除一个用户组
groupdel group_name
重命名一个用户组
groupmod -n new_group_name old_group_name
创建一个属于 "admin” 用户组的用户
useradd -c "Name Surname ” -g admin -d /home/user1 -s /bin/bash user1
创建一个新用户
useradd user1
删除一个用户 ( '-r' 排除主目录)
userdel -r user1
修改用户属性
usermod -c "User FTP” -g system -d /ftp/user1 -s /bin/nologin user1
修改口令
passwd
修改一个用户的口令 (只允许root执行)
passwd user1
设置用户口令的失效期限
chage -E 2005-12-31 user1
检查 '/etc/passwd' 的文件格式和语法修正以及存在的用户
pwck
检查 '/etc/passwd' 的文件格式和语法修正以及存在的群组
grpck
登陆进一个新的群组以改变新创建文件的预设群组
newgrp group_name

八、文件的权限

    显示权限

ls -lh
将终端划分成5栏显示
ls /tmp | pr -T5 -W$COLUMNS
设置目录的所有人(u)、群组(g)以及其他人(o)以读（r ）、写(w)和执行(x)的权限，使用 "+” 设置权限，使用 "-” 用于取消
chmod ugo+rwx <dir>
删除群组(g)与其他人(o)对目录的读写执行权限
chmod go-rwx <dir>
改变一个文件的所有人属性
chown <user-name> <file-name>
改变一个目录的所有人属性并同时改变改目录下所有文件的属性
chown -R <user-name> <dir>
改变文件的群组
chgrp <group-name> <file-name>
改变一个文件的owner和group
chown <user-name>:<group-name> <file-name>
罗列一个系统中所有使用了SUID控制的文件
find / -perm -u+s
设置一个二进制文件的 SUID 位 – 运行该文件的用户也被赋予和所有者同样的权限
chmod u+s /bin/<file-name>
禁用一个二进制文件的 SUID位
chmod u-s /bin/<file-name>
设置一个目录的SGID 位 – 类似SUID ，不过这是针对目录的
chmod g+s /home/public
禁用一个目录的 SGID 位
chmod g-s /home/public
设置一个文件的 STIKY 位 – 只允许合法所有人删除文件
chmod o+t /home/public
禁用一个目录的 STIKY 位
chmod o-t /home/public
只允许以追加方式读写文件
chattr +a <file-name>
允许这个文件能被内核自动压缩/解压
chattr +c <file-name>
在进行文件系统备份时，dump程序将忽略这个文件
chattr +d <file-name>
设置成不可变的文件，不能被删除、修改、重命名或者链接
chattr +i <file-name>
允许一个文件被安全地删除
chattr +s <file-name>
一旦应用程序对这个文件执行了写操作，使系统立刻把修改的结果写到磁盘
chattr +S <file-name>
若文件被删除，系统会允许你在以后恢复这个被删除的文件
chattr +u <file-name>
显示特殊的属性
lsattr

九、打包和压缩文件

    解压一个叫做 '<file-name>.bz2′的文件

bunzip2 <file-name>.bz2
压缩一个叫做 '<file-name>′ 的文件
bzip2 <file-name>
解压一个叫做 '<file-name>.gz'的文件
gunzip <file-name>.gz
压缩一个叫做 '<file-name>′的文件
gzip <file-name>
最大程度压缩
gzip -9 <file-name>
创建一个叫做 '<file-name>.rar' 的包
rar a <file-name>.rar test_file
同时压缩 '<file-name>′, 'file2′ 以及目录 'dir1′
rar a <file-name>.rar <file-name> file2 dir1
解压rar包
rar x <file-name>.rar
解压rar包
unrar x <file-name>.rar
创建一个非压缩的 tarball
tar -cvf archive.tar <file-name>
创建一个包含了 '<file-name>′, 'file2′ 以及 'dir1′的档案文件
tar -cvf archive.tar <file-name> file2 dir1
显示一个包中的内容
tar -tf archive.tar
释放一个包
tar -xvf archive.tar
将压缩包释放到 /tmp目录下
tar -xvf archive.tar -C /tmp
创建一个bzip2格式的压缩包
tar -cvfj archive.tar.bz2 dir1
解压一个bzip2格式的压缩包
tar -xvfj archive.tar.bz2
创建一个gzip格式的压缩包
tar -cvfz archive.tar.gz dir1
解压一个gzip格式的压缩包
tar -xvfz archive.tar.gz
创建一个zip格式的压缩包
zip <file-name>.zip <file-name>
将几个文件和目录同时压缩成一个zip格式的压缩包
zip -r <file-name>.zip <file-name> file2 dir1
解压一个zip格式压缩包
unzip <file-name>.zip

十、包管理器
RPM 包 – （Fedora, Redhat及类似系统）

    安装一个rpm包

rpm -ivh package.rpm
安装一个rpm包而忽略依赖关系警告
rpm -ivh –nodeeps package.rpm
更新一个rpm包但不改变其配置文件
rpm -U package.rpm
更新一个确定已经安装的rpm包
rpm -F package.rpm
删除一个rpm包
rpm -e package_name.rpm
显示系统中所有已经安装的rpm包
rpm -qa
显示所有名称中包含 "httpd” 字样的rpm包
rpm -qa | grep httpd
获取一个已安装包的特殊信息
rpm -qi package_name
显示一个组件的rpm包
rpm -qg "System Environment/Daemons"
显示一个已经安装的rpm包提供的文件列表
rpm -ql package_name
显示一个已经安装的rpm包提供的配置文件列表
rpm -qc package_name
显示与一个rpm包存在依赖关系的列表
rpm -q package_name –whatrequires
显示一个rpm包所占的体积
rpm -q package_name –whatprovides
显示在安装/删除期间所执行的脚本l
rpm -q package_name –scripts
显示一个rpm包的修改历史
rpm -q package_name –changelog
确认所给的文件由哪个rpm包所提供
rpm -qf /etc/httpd/conf/httpd.conf
显示由一个尚未安装的rpm包提供的文件列表
rpm -qp package.rpm -l
导入公钥数字证书
rpm –import /media/cdrom/RPM-GPG-KEY
确认一个rpm包的完整性
rpm –checksig package.rpm
确认已安装的所有rpm包的完整性
rpm -qa gpg-pubkey
检查文件尺寸、 许可、类型、所有者、群组、MD5检查以及最后修改时间
rpm -V package_name
检查系统中所有已安装的rpm包- 小心使用
rpm -Va
确认一个rpm包还未安装
rpm -Vp package.rpm
从一个rpm包运行可执行文件
rpm2cpio package.rpm | cpio –extract –make-directories bin
从一个rpm源码安装一个构建好的包
rpm -ivh /usr/src/redhat/RPMS/`arch`/package.rpm
从一个rpm源码构建一个 rpm 包
rpmbuild –rebuild package_name.src.rpm

YUM 软件包升级器 – （Fedora, RedHat及类似系统）

    下载并安装一个rpm包

yum install package_name
将安装一个rpm包，使用你自己的软件仓库为你解决所有依赖关系
yum localinstall package_name.rpm
更新当前系统中所有安装的rpm包
yum update package_name.rpm
更新一个rpm包
yum update package_name
删除一个rpm包
yum remove package_name
列出当前系统中安装的所有包
yum list
在rpm仓库中搜寻软件包
yum search package_name
清理rpm缓存删除下载的包
yum clean packages
删除所有头文件
yum clean headers
删除所有缓存的包和头文件
yum clean all

DEB 包 (Debian, Ubuntu 以及类似系统)

    安装/更新一个 deb 包

dpkg -i package.deb
从系统删除一个 deb 包
dpkg -r package_name
显示系统中所有已经安装的 deb 包
dpkg -l
显示所有名称中包含 "httpd” 字样的deb包
dpkg -l | grep httpd
获得已经安装在系统中一个特殊包的信息
dpkg -s package_name
显示系统中已经安装的一个deb包所提供的文件列表
dpkg -L package_name
显示尚未安装的一个包所提供的文件列表
dpkg –contents package.deb
确认所给的文件由哪个deb包提供
dpkg -S /bin/ping

APT 软件工具 (Debian, Ubuntu 以及类似系统)

    安装/更新一个 deb 包

apt-get install package_name
从光盘安装/更新一个 deb 包
apt-cdrom install package_name
升级列表中的软件包
apt-get update
升级所有已安装的软件
apt-get upgrade
从系统删除一个deb包
apt-get remove package_name
确认依赖的软件仓库正确
apt-get check
从下载的软件包中清理缓存
apt-get clean
返回包含所要搜索字符串的软件包名称
apt-cache search searched-package

十一、文本
查看文件内容

    从第一个字节开始正向查看文件的内容

cat <file-name>
从最后一行开始反向查看一个文件的内容
tac <file-name>
查看一个长文件的内容
more <file-name>

    下翻一页(空格)，上翻一页(b)，退出(q)

类似于 'more' 命令，但是它允许在文件中和正向操作一样的反向操作
less <file-name>

    下翻一页(空格)，上翻一页(b)，上翻一行(↑)，下翻一行(↓)，可以搜索关键字(/<keyword>)

查看一个文件的前两行
head -2 <file-name>
查看一个文件的最后两行
tail -2 <file-name>
实时查看被添加到一个文件中的内容
tail -f /var/log/messages

        -f跟踪文件的唯一inode号，就算文件改名后，还是跟踪原来这个inode表示的文件
        -F按照文件名来跟踪

文本处理

    合并一个文件的详细说明文本，并将简介写入一个新文件中

cat <file-name> | command( sed, grep, awk, etc…) > result.txt
合并一个文件的详细说明文本，并将简介写入一个已有的文件中
cat <file-name> | command( sed, grep, awk, etc…) >> result.txt
在文件'/var/log/messages'中查找关键词”Aug”
grep Aug /var/log/messages
在文件 '/var/log/messages'中查找以”Aug”开始的词汇
grep ^Aug /var/log/messages
选择 '/var/log/messages' 文件中所有包含数字的行
grep [0-9] /var/log/messages
在目录 '/var/log' 及随后的目录中搜索字符串”Aug”
grep Aug -R /var/log/*
将example.txt文件中的 "string1″ 替换成 "string2"
sed 's/stringa1/stringa2/g' example.txt
从example.txt文件中删除所有空白行
sed '/^$/d' example.txt
从example.txt文件中删除所有注释和空白行
sed '/ *#/d; /^$/d' example.txt
合并上下单元格内容
echo 'esempio' | tr '[:lower:]' '[:upper:]'
从文件example.txt 中排除第一行
sed -e '1d' result.txt
查看只包含词汇 "string1″的行
sed -n '/stringa1/p'
删除每一行最后的空白字符
sed -e 's/ *$//' example.txt
从文档中只删除词汇 "string1″ 并保留剩余全部
sed -e 's/stringa1//g' example.txt
查看从第一行到第5行内容
sed -n '1,5p;5q' example.txt
查看第5行
sed -n '5p;5q' example.txt
example.txt 用单个零替换多个零
sed -e 's/00*/0/g'
标示文件的行数
cat -n <file-name>
删除example.txt文件中的所有偶数行
cat example.txt | awk 'NR%2==1′
查看一行第一栏
echo a b c | awk '{print $1}'
查看一行的第一和第三栏
echo a b c | awk '{print $1,$3}'
合并两个文件或两栏的内容
paste <file-name> file2
合并两个文件或两栏的内容，中间用”+”区分
paste -d '+' <file-name> file2
排序两个文件的内容
sort <file-name> file2
取出两个文件的并集(重复的行只保留一份)
sort <file-name> file2 | uniq
删除交集，留下其他的行
sort <file-name> file2 | uniq -u
取出两个文件的交集(只留下同时存在于两个文件中的文件)
sort <file-name> file2 | uniq -d
比较两个文件的内容只删除 '<file-name>′ 所包含的内容
comm -1 <file-name> file2
比较两个文件的内容只删除 'file2′ 所包含的内容
comm -2 <file-name> file2
比较两个文件的内容只删除两个文件共有的部分
comm -3 <file-name> file2

字符设置和文件格式转换

    将一个文本文件的格式从MSDOS转换成UNIX

dos2unix filedos.txt fileunix.txt
将一个文本文件的格式从UNIX转换成MSDOS
unix2dos fileunix.txt filedos.txt
将一个文本文件转换成html
recode ..HTML < page.txt > page.html
显示所有允许的转换格式
recode -l | more

十二、文件系统分析

    检查磁盘hda1上的坏磁块

badblocks -v /dev/hda1
修复/检查hda1磁盘上linux文件系统的完整性
fsck /dev/hda1
修复/检查hda1磁盘上ext2文件系统的完整性
fsck.ext2 /dev/hda1
修复/检查hda1磁盘上ext2文件系统的完整性
e2fsck /dev/hda1
修复/检查hda1磁盘上ext3文件系统的完整性
e2fsck -j /dev/hda1
修复/检查hda1磁盘上ext3文件系统的完整性
fsck.ext3 /dev/hda1
修复/检查hda1磁盘上fat文件系统的完整性
fsck.vfat /dev/hda1
修复/检查hda1磁盘上dos文件系统的完整性
fsck.msdos /dev/hda1
修复/检查hda1磁盘上dos文件系统的完整性
dosfsck /dev/hda1

初始化一个文件系统

    在hda1分区创建一个文件系统

mkfs /dev/hda1
在hda1分区创建一个linux ext2的文件系统
mke2fs /dev/hda1
在hda1分区创建一个linux ext3(日志型)的文件系统
mke2fs -j /dev/hda1
创建一个 FAT32 文件系统
mkfs -t vfat 32 -F /dev/hda1
格式化一个软盘
fdformat -n /dev/fd0
创建一个swap文件系统
mkswap /dev/hda3

SWAP文件系统

    创建一个swap文件系统

mkswap /dev/hda3
启用一个新的swap文件系统
swapon /dev/hda3
启用两个swap分区
swapon /dev/hda2 /dev/hdb3

备份

    制作一个 '/home' 目录的完整备份

dump -0aj -f /tmp/home0.bak /home
制作一个 '/home' 目录的交互式备份
dump -1aj -f /tmp/home0.bak /home
还原一个交互式备份
restore -if /tmp/home0.bak
同步两边的目录
rsync -rogpav –delete /home /tmp
通过SSH通道rsync
rsync -rogpav -e ssh –delete /home ip_address:/tmp
通过ssh和压缩将一个远程目录同步到本地目录
rsync -az -e ssh –delete ip_addr:/home/public /home/local
通过ssh和压缩将本地目录同步到远程目录
rsync -az -e ssh –delete /home/local ip_addr:/home/public
通过ssh在远程主机上执行一次备份本地磁盘的操作
dd bs=1M if=/dev/hda | gzip | ssh user@ip_addr 'dd of=hda.gz'
备份磁盘内容到一个文件
dd if=/dev/sda of=/tmp/<file-name>
执行一次对 '/home/user' 目录的交互式备份操作
tar -Puf backup.tar /home/user
通过ssh在远程目录中复制一个目录内容
( cd /tmp/local/ && tar c . ) | ssh -C user@ip_addr 'cd /home/share/ && tar x -p'
通过ssh在远程目录中复制一个本地目录
( tar c /home ) | ssh -C user@ip_addr 'cd /home/backup-home && tar x -p'
本地将一个目录复制到另一个地方，保留原有权限及链接
tar cf – . | (cd /tmp/backup ; tar xf – )
从一个目录查找并复制所有以 '.txt' 结尾的文件到另一个目录
find /home/user1 -name '- txt' | xargs cp -av –target-directory=/home/backup/ –parents
查找所有以 '.log' 结尾的文件并做成一个bzip包
find /var/log -name '- log' | tar cv –files-from=- | bzip2 > log.tar.bz2
做一个将 MBR (Master Boot Record)内容复制到软盘的动作
dd if=/dev/hda of=/dev/fd0 bs=512 count=1
从已经保存到软盘的备份中恢复MBR内容
dd if=/dev/fd0 of=/dev/hda bs=512 count=1

光盘

    清空一个可复写的光盘内容

cdrecord -v gracetime=2 dev=/dev/cdrom -eject blank=fast -force
在磁盘上创建一个光盘的iso镜像文件
mkisofs /dev/cdrom > cd.iso
在磁盘上创建一个压缩了的光盘iso镜像文件
mkisofs /dev/cdrom | gzip > cd_iso.gz
创建一个目录的iso镜像文件
mkisofs -J -allow-leading-dots -R -V "Label CD” -iso-level 4 -o ./cd.iso data_cd
刻录一个ISO镜像文件
cdrecord -v dev=/dev/cdrom cd.iso
刻录一个压缩了的ISO镜像文件
gzip -dc cd_iso.gz | cdrecord dev=/dev/cdrom
挂载一个ISO镜像文件
mount -o loop cd.iso /mnt/iso
从一个CD光盘转录音轨到 wav 文件中
cd-paranoia -B
从一个CD光盘转录音轨到 wav 文件中（参数-3）
cd-paranoia "-3" 
扫描总线以识别scsi通道
cdrecord –scanbus
校验一个设备的md5sum编码
dd if=/dev/hdc | md5sum

十三、端口占用

    使用lsof

lsof -i:<port>

    需要安装yum -y install lsof

使用netstat
netstat -tunlp | grep <port>

        参数：
        -u：(udp)仅显示udp相关选项
        -n：拒绝显示别名，能显示数字的全部转化为数字
        -l：仅列出在Listen(监听)的服务状态
        -p：显示建立相关链接的程序名

十四、其他

    一块网卡添加多个IP

ip addr add <new-ip> dev <device-name>



开始学习：
'day01:'用户及文件权限管理
1.查看用户：

打开终端，输入命令：

who am i

# 或者

who mom likes

输出的第一列表示打开当前伪终端的用户的用户名（要查看当前登录用户的用户名，去掉空格直接使用 whoami 即可），第二列的 pts/0 中 pts 表示伪终端，所谓伪是相对于 /dev/tty 设备而言的，还记得上一节讲终端时的那七个使用 [Ctrl]+[Alt]+[F1]～[F7] 进行切换的 /dev/tty 设备么，这是“真终端”，伪终端就是当你在图形用户界面使用 /dev/tty7 时每打开一个终端就会产生一个伪终端，pts/0 后面那个数字就表示打开的伪终端序号，你可以尝试再打开一个终端，然后在里面输入 who am i，看第二列是不是就变成 pts/1 了，第三列则表示当前伪终端的启动时间。

还有一点需要注意的是，在某些环境中 who am i 和 who mom likes 命令不会输出任何内容，这是因为当前使用的 SHELL 不是登录时的 SHELL，没有用户与 who 的 stdin 相关联，因此不会输出任何内容。例如我在本地的 Ubuntu 系统上输入这个命令就不会有提示。

此时我们只需要打开一个登录 SHELL 的终端例如 Tmux，或者通过 ssh 登录到本机，再在新的终端里执行命令即可。

tmux

who 命令其它常用参数
参数  说明
-a  打印能打印的全部
-d  打印死掉的进程
-m  同am i，mom likes
-q  打印当前登录用户数及用户名
-u  打印当前登录用户登录信息
-r  打印运行等级

2.创建用户：
su，su- 与 sudo

需要注意 Linux 环境下输入密码是不会显示的。

su <user> 可以切换到用户 user，执行时需要输入目标用户的密码，sudo <cmd> 可以以特权级别运行 cmd 命令，需要当前用户属于 sudo 组，且需要输入当前用户的密码。su - <user> 命令也是切换用户，但是同时用户的环境变量和工作目录也会跟着改变成目标用户所对应的。

现在我们新建一个叫 lilei 的用户：

sudo adduser lilei

实验楼的环境目前设置为 shiyanlou 用户执行 sudo 不需要输入密码，通常此处需要按照提示输入 shiyanlou 密码（Linux 下密码输入是不显示任何内容的，shiyanlou 用户密码可以在右侧环境信息里查看，请勿自行设置密码）。然后是给 lilei 用户设置密码，后面的选项的一些内容你可以选择直接回车使用默认值。

这个命令不但可以添加用户到系统，同时也会默认为新用户在 /home 目录下创建一个工作目录：

ls /home

现在你已经创建好一个用户，并且你可以使用你创建的用户登录了，使用如下命令切换登录用户：

su -l lilei
输入刚刚设置的 lilei 的密码，然后输入如下命令并查看输出：

who am i
whoami
pwd


你发现了区别了吗？这就是上一小节我们讲到的 who am i 和 whoami 命令的区别。

退出当前用户跟退出终端一样，可以使用 exit 命令或者使用快捷键 Ctrl+D。

3.用户组：
在 Linux 里面每个用户都有一个归属（用户组），用户组简单地理解就是一组用户的集合，它们共享一些资源和权限，同时拥有私有资源，就跟家的形式差不多，你的兄弟姐妹（不同的用户）属于同一个家（用户组），你们可以共同拥有这个家（共享资源），爸妈对待你们都一样（共享权限），你偶尔写写日记，其他人未经允许不能查看（私有资源和权限）。当然一个用户是可以属于多个用户组的，正如你既属于家庭，又属于学校或公司。

在 Linux 里面如何知道自己属于哪些用户组呢？
方法一：使用 groups 命令

groups shiyanlou


其中冒号之前表示用户，后面表示该用户所属的用户组。这里可以看到 shiyanlou 用户属于 shiyanlou 用户组，每次新建用户如果不指定用户组的话，默认会自动创建一个与用户名相同的用户组（差不多就相当于家长的意思）。

默认情况下在 sudo 用户组里的可以使用 sudo 命令获得 root 权限。shiyanlou 用户也可以使用 sudo 命令，为什么这里没有显示在 sudo 用户组里呢？可以查看下 /etc/sudoers.d/shiyanlou 文件，我们在 /etc/sudoers.d 目录下创建了这个文件，从而给 shiyanlou 用户赋予了 sudo 权限：


方法二：查看 /etc/group 文件

cat /etc/group | sort

这里 cat 命令用于读取指定文件的内容并打印到终端输出，后面会详细讲它的使用。 | sort 表示将读取的文本进行一个字典排序再输出，然后你将看到如下一堆输出，你可以在最下面看到 shiyanlou 的用户组信息：



没找到？没关系，你可以使用 grep 命令过滤掉一些你不想看到的结果：

cat /etc/group | grep -E "shiyanlou"


/etc/group 文件格式说明

/etc/group 的内容包括用户组（Group）、用户组口令、GID（组 ID） 及该用户组所包含的用户（User），每个用户组一条记录。格式如下：

    group_name:password:GID:user_list

你看到上面的 password 字段为一个 x，并不是说密码就是它，只是表示密码不可见而已。

这里需要注意，如果用户的 GID 等于用户组的 GID，那么最后一个字段 user_list 就是空的，这里的 GID 是指用户默认所在组的 GID，可以使用 id 命令查看。比如 shiyanlou 用户，在 /etc/group 中的 shiyanlou 用户组后面是不会显示的。lilei 用户，在 /etc/group 中的 lilei 用户组后面是不会显示的。
将其它用户加入 sudo 用户组

默认情况下新创建的用户是不具有 root 权限的，也不在 sudo 用户组，可以让其加入 sudo 用户组从而获取 root 权限：

# 注意 Linux 上输入密码是不会显示的
su -l lilei
sudo ls


会提示 lilei 不在 sudoers 文件中，意思就是 lilei 不在 sudo 用户组中，至于 sudoers 文件（/etc/sudoers）你现在最好不要动它，操作不慎会导致比较麻烦的后果。

使用 usermod 命令可以为用户添加用户组，同样使用该命令你必需有 root 权限，你可以直接使用 root 用户为其它用户添加用户组，或者用其它已经在 sudo 用户组的用户使用 sudo 命令获取权限来执行该命令。

这里我用 shiyanlou 用户执行 sudo 命令将 lilei 添加到 sudo 用户组，让它也可以使用 sudo 命令获得 root 权限，首先我们切换回 shiyanlou 用户。

su - shiyanlou

此处需要输入 shiyanlou 用户密码，shiyanlou 的密码可以在右侧工具栏的环境信息里看到。


当然也可以通过 sudo passwd shiyanlou 进行设置，或者你直接关闭当前终端打开一个新的终端。

groups lilei
sudo usermod -G sudo lilei
groups lilei


然后你再切换回 lilei 用户，现在就可以使用 sudo 获取 root 权限了。

4.删除用户：sudo deluser lilei --remove-home

'day01:'
linux下的文件目录：
    /bin：
    bin 是 Binaries (二进制文件) 的缩写, 这个目录存放着最经常使用的命令。

    /boot：
    这里存放的是启动 Linux 时使用的一些核心文件，包括一些连接文件以及镜像文件。

    /dev ：
    dev 是 Device(设备) 的缩写, 该目录下存放的是 Linux 的外部设备，在 Linux 中访问设备的方式和访问文件的方式是相同的。

    /etc：
    etc 是 Etcetera(等等) 的缩写,这个目录用来存放所有的系统管理所需要的配置文件和子目录。

    /home：
    用户的主目录，在 Linux 中，每个用户都有一个自己的目录，一般该目录名是以用户的账号命名的，如上图中的 alice、bob 和 eve。

    /lib：
    lib 是 Library(库) 的缩写这个目录里存放着系统最基本的动态连接共享库，其作用类似于 Windows 里的 DLL 文件。几乎所有的应用程序都需要用到这些共享库。

    /lost+found：
    这个目录一般情况下是空的，当系统非法关机后，这里就存放了一些文件。

    /media：
    linux 系统会自动识别一些设备，例如U盘、光驱等等，当识别后，Linux 会把识别的设备挂载到这个目录下。

    /mnt：
    系统提供该目录是为了让用户临时挂载别的文件系统的，我们可以将光驱挂载在 /mnt/ 上，然后进入该目录就可以查看光驱里的内容了。

    /opt：
    opt 是 optional(可选) 的缩写，这是给主机额外安装软件所摆放的目录。比如你安装一个ORACLE数据库则就可以放到这个目录下。默认是空的。

    /proc：
    proc 是 Processes(进程) 的缩写，/proc 是一种伪文件系统（也即虚拟文件系统），存储的是当前内核运行状态的一系列特殊文件，这个目录是一个虚拟的目录，它是系统内存的映射，我们可以通过直接访问这个目录来获取系统信息。
    这个目录的内容不在硬盘上而是在内存里，我们也可以直接修改里面的某些文件，比如可以通过下面的命令来屏蔽主机的ping命令，使别人无法ping你的机器：

    echo 1 > /proc/sys/net/ipv4/icmp_echo_ignore_all

    /root：
    该目录为系统管理员，也称作超级权限者的用户主目录。

    /sbin：
    s 就是 Super User 的意思，是 Superuser Binaries (超级用户的二进制文件) 的缩写，这里存放的是系统管理员使用的系统管理程序。

    /selinux：
     这个目录是 Redhat/CentOS 所特有的目录，Selinux 是一个安全机制，类似于 windows 的防火墙，但是这套机制比较复杂，这个目录就是存放selinux相关的文件的。

    /srv：
     该目录存放一些服务启动之后需要提取的数据。

    /sys：

    这是 Linux2.6 内核的一个很大的变化。该目录下安装了 2.6 内核中新出现的一个文件系统 sysfs 。

    sysfs 文件系统集成了下面3种文件系统的信息：针对进程信息的 proc 文件系统、针对设备的 devfs 文件系统以及针对伪终端的 devpts 文件系统。

    该文件系统是内核设备树的一个直观反映。

    当一个内核对象被创建的时候，对应的文件和目录也在内核对象子系统中被创建。

    /tmp：
    tmp 是 temporary(临时) 的缩写这个目录是用来存放一些临时文件的。

    /usr：
     usr 是 unix shared resources(共享资源) 的缩写，这是一个非常重要的目录，用户的很多应用程序和文件都放在这个目录下，类似于 windows 下的 program files 目录。

    /usr/bin：
    系统用户使用的应用程序。

    /usr/sbin：
    超级用户使用的比较高级的管理程序和系统守护程序。

    /usr/src：
    内核源代码默认的放置目录。

    /var：
    var 是 variable(变量) 的缩写，这个目录中存放着在不断扩充着的东西，我们习惯将那些经常被修改的目录放在这个目录下。包括各种日志文件。

    /run：
    是一个临时文件系统，存储系统启动以来的信息。当系统重启时，这个目录下的文件应该被删掉或清除。如果你的系统上有 /var/run 目录，应该让它指向 run。

在 Linux 系统中，有几个目录是比较重要的，平时需要注意不要误删除或者随意更改内部文件。

/etc： 上边也提到了，这个是系统中的配置文件，如果你更改了该目录下的某个文件可能会导致系统不能启动。

/bin, /sbin, /usr/bin, /usr/sbin: 这是系统预设的执行文件的放置目录，比如 ls 就是在 /bin/ls 目录下的。

值得提出的是 /bin、/usr/bin 是给系统用户使用的指令（除 root 外的通用用户），而/sbin, /usr/sbin 则是给 root 使用的指令。

/var： 这是一个非常重要的目录，系统上跑了很多程序，那么每个程序都会有相应的日志产生，而这些日志就被记录到这个目录下，具体在 /var/log 目录下，另外 mail 的预设放置也是在这里。


'day02'linux文件的基本属性

1.Linux 文件基本属性

Linux 系统是一种典型的多用户系统，不同的用户处于不同的地位，拥有不同的权限。
为了保护系统的安全性，Linux 系统对不同的用户访问同一文件（包括目录文件）的权限做了不同的规定。
在 Linux 中我们通常使用以下两个命令来修改文件或目录的所属用户与权限：

    chown (change owner) ： 修改所属用户与组。
    chmod (change mode) ： 修改用户的权限。

在 Linux 中我们可以使用 ll 或者 ls –l 命令来显示一个文件的属性以及文件所属的用户和组，如：

[root@www /]# ls -l
total 64
dr-xr-xr-x   2 root root 4096 Dec 14  2012 bin
dr-xr-xr-x   4 root root 4096 Apr 19  2012 boot
……

|
|
V
0|123|456|789
文|属主|属组|其他用户
件|权限|权限|权限
类|   
型|
d|r-x|r-x|r-x   2 root root 4096 Dec 14  2012 bin

实例中，bin 文件的第一个属性用 d 表示。d 在 Linux 中代表该文件是一个目录文件。
在 Linux 中第一个字符代表这个文件是目录、文件或链接文件等等。

    当为 d 则是目录
    当为 - 则是文件；
    若是 l 则表示为链接文档(link file)；
    若是 b 则表示为装置文件里面的可供储存的接口设备(可随机存取装置)；
    若是 c 则表示为装置文件里面的串行端口设备，例如键盘、鼠标(一次性读取装置)。

接下来的字符中，以三个为一组，且均为 rwx 的三个参数的组合。其中， r 代表可读(read)、 w 代表可写(write)、 x 代表可执行(execute)。 
要注意的是，这三个权限的位置不会改变，如果没有权限，就会出现减号 - 而已。
从左至右用 0-9 这些数字来表示:

0|123|456|789   
文|属主|属组|其他用户
件|权限|权限|权限
类|   |    |          
型|   |    |   硬链
              接数 用户名 组名 size 最终修改时间   文件名
d|r-x|r-x|r-x  2 |root |root |4096| Dec 14  2012| bin

第 0 位确定文件类型，第 1-3 位确定属主（该文件的所有者）拥有该文件的权限。
第4-6位确定属组（所有者的同组用户）拥有该文件的权限，第7-9位确定其他用户拥有该文件的权限。
其中，第 1、4、7 位表示读权限，如果用 r 字符表示，则有读权限，如果用 - 字符表示，则没有读权限；
第 2、5、8 位表示写权限，如果用 w 字符表示，则有写权限，如果用 - 字符表示没有写权限；第 3、6、9 位表示可执行权限,
如果用 x 字符表示，则有执行权限，如果用 - 字符表示，则没有执行权限。 


2.Linux文件属主和属组

[root@www /]# ls -l
total 64
drwxr-xr-x 2 root  root  4096 Feb 15 14:46 cron
drwxr-xr-x 3 mysql mysql 4096 Apr 21  2014 mysql
……

对于文件来说，它都有一个特定的所有者，也就是对该文件具有所有权的用户。
同时，在Linux系统中，用户是按组分类的，一个用户属于一个或多个组。

文件所有者以外的用户又可以分为文件所属组的同组用户和其他用户。

因此，Linux系统按文件所有者、文件所有者同组用户和其他用户来规定了不同的文件访问权限。

在以上实例中，mysql 文件是一个目录文件，属主和属组都为 mysql，属主有可读、可写、可执行的权限；与属主同组的其他用户有可读和可执行的权限；其他用户也有可读和可执行的权限。

对于 root 用户来说，一般情况下，文件的权限对其不起作用。

3.更改文件属性

1、chgrp：更改文件属组

语法：

chgrp [-R] 属组名 文件名

参数选项

    -R：递归更改文件属组，就是在更改某个目录文件的属组时，如果加上-R的参数，那么该目录下的所有文件的属组都会更改。 

2、chown：更改文件属主，也可以同时更改文件属组

语法：

chown [–R] 属主名 文件名
chown [-R] 属主名：属组名 文件名

进入 /root 目录（~）将install.log的拥有者改为bin这个账号：

[root@www ~] cd ~
[root@www ~]# chown bin install.log
[root@www ~]# ls -l
-rw-r--r--  1 bin  users 68495 Jun 25 08:53 install.log

将install.log的拥有者与群组改回为root：

[root@www ~]# chown root:root install.log
[root@www ~]# ls -l
-rw-r--r--  1 root root 68495 Jun 25 08:53 install.log

3、chmod：更改文件9个属性

Linux文件属性有两种设置方法，一种是数字，一种是符号。

Linux 文件的基本权限就有九个，分别是 owner/group/others(拥有者/组/其他) 三种身份各有自己的 read/write/execute 权限。

先复习一下刚刚上面提到的数据：文件的权限字符为： -rwxrwxrwx ， 这九个权限是三个三个一组的！其中，我们可以使用数字来代表各个权限，各权限的分数对照表如下：

    r:4
    w:2
    x:1

每种身份(owner/group/others)各自的三个权限(r/w/x)分数是需要累加的，例如当权限为： -rwxrwx--- 分数则是：

    owner = rwx = 4+2+1 = 7
    group = rwx = 4+2+1 = 7
    others= --- = 0+0+0 = 0

所以等一下我们设定权限的变更时，该文件的权限数字就是 770。变更权限的指令 chmod 的语法是这样的：

 chmod [-R] xyz 文件或目录

选项与参数：

    xyz : 就是刚刚提到的数字类型的权限属性，为 rwx 属性数值的相加。
    -R : 进行递归(recursive)的持续变更，以及连同次目录下的所有文件都会变更

举例来说，如果要将 .bashrc 这个文件所有的权限都设定启用，那么命令如下：

[root@www ~]# ls -al .bashrc
-rw-r--r--  1 root root 395 Jul  4 11:45 .bashrc
[root@www ~]# chmod 777 .bashrc
[root@www ~]# ls -al .bashrc(a:所有文件，l:查看可执行权限)
-rwxrwxrwx  1 root root 395 Jul  4 11:45 .bashrc

那如果要将权限变成 -rwxr-xr-- 呢？那么权限的分数就成为 [4+2+1][4+0+1][4+0+0]=754。
符号类型改变文件权限

还有一个改变权限的方法，从之前的介绍中我们可以发现，基本上就九个权限分别是：

    user：用户
    group：组
    others：其他

那么我们就可以使用 u, g, o 来代表三种身份的权限。

此外， a 则代表 all，即全部的身份。读写的权限可以写成 r, w, x，也就是可以使用下表的方式来看：

chmod   u
g
o
a   +(加入)
-(除去)
=(设定)   r
w
x   文件或目录

如果我们需要将文件权限设置为 -rwxr-xr-- ，可以使用 chmod u=rwx,g=rx,o=r 文件名 来设定:

#  touch test1    // 创建 test1 文件
# ls -al test1    // 查看 test1 默认权限
-rw-r--r-- 1 root root 0 Nov 15 10:32 test1
# chmod u=rwx,g=rx,o=r  test1    // 修改 test1 权限
# ls -al test1
-rwxr-xr-- 1 root root 0 Nov 15 10:32 test1

而如果是要将权限去掉而不改变其他已存在的权限呢？例如要拿掉全部人的可执行权限，则：

#  chmod  a-x test1
# ls -al test1
-rw-r--r-- 1 root root 0 Nov 15 10:32 test1



'day03'Linux 文件与目录管理


我们知道Linux的目录结构为树状结构，最顶级的目录为根目录 /。

其他目录通过挂载可以将它们添加到树中，通过解除挂载可以移除它们。

在开始本教程前我们需要先知道什么是绝对路径与相对路径。

    绝对路径：
    路径的写法，由根目录 / 写起，例如： /usr/share/doc 这个目录。

    相对路径：
    路径的写法，不是由 / 写起，例如由 /usr/share/doc 要到 /usr/share/man 底下时，可以写成： cd ../man 这就是相对路径的写法。

1.处理目录的常用命令

接下来我们就来看几个常见的处理目录的命令吧：

    ls（英文全拼：list files）: 列出目录及文件名
    cd（英文全拼：change directory）：切换目录
    pwd（英文全拼：print work directory）：显示目前的目录
    mkdir（英文全拼：make directory）：创建一个新的目录
    rmdir（英文全拼：remove directory）：删除一个空的目录
    cp（英文全拼：copy file）: 复制文件或目录
    rm（英文全拼：remove）: 删除文件或目录
    mv（英文全拼：move file）: 移动文件与目录，或修改文件与目录的名称
    touch:创建文件
你可以使用 man [命令] 来查看各个命令的使用文档，如 ：man cp。



.touch(创建文件)
touch a.py aa.xml aaa.cpp


.ls (列出目录)

在Linux系统当中， ls 命令可能是最常被运行的。

语法：

[root@www ~]# ls [-aAdfFhilnrRSt] 目录名称
[root@www ~]# ls [--color={never,auto,always}] 目录名称
[root@www ~]# ls [--full-time] 目录名称

选项与参数：

    -a ：全部的文件，连同隐藏文件( 开头为 . 的文件) 一起列出来(常用)
    -d ：仅列出目录本身，而不是列出目录内的文件数据(常用)
    -l ：长数据串列出，包含文件的属性与权限等等数据；(常用)

将家目录下的所有文件列出来(含属性与隐藏档)

[root@www ~]# ls -al ~

.cd (切换目录)

cd是Change Directory的缩写，这是用来变换工作目录的命令。

语法：

 cd [相对路径或绝对路径]

#使用 mkdir 命令创建 runoob 目录
[root@www ~]# mkdir runoob

#使用绝对路径切换到 runoob 目录
[root@www ~]# cd /root/runoob/

#使用相对路径切换到 runoob 目录
[root@www ~]# cd ./runoob/

# 表示回到自己的家目录，亦即是 /root 这个目录
[root@www runoob]# cd ~

# 表示去到目前的上一级目录，亦即是 /root 的上一级目录的意思；
[root@www ~]# cd ..

接下来大家多操作几次应该就可以很好的理解 cd 命令的。

.pwd (显示目前所在的目录)

pwd 是 Print Working Directory 的缩写，也就是显示目前所在目录的命令。

[root@www ~]# pwd [-P]

选项与参数：

    -P ：显示出确实的路径，而非使用连结 (link) 路径。 

实例：单纯显示出目前的工作目录：

[root@www ~]# pwd
/root   <== 显示出目录啦～

实例显示出实际的工作目录，而非连结档本身的目录名而已。

[root@www ~]# cd /var/mail   <==注意，/var/mail是一个连结档
[root@www mail]# pwd
/var/mail         <==列出目前的工作目录
[root@www mail]# pwd -P
/var/spool/mail   <==怎么回事？有没有加 -P 差很多～
[root@www mail]# ls -ld /var/mail
lrwxrwxrwx 1 root root 10 Sep  4 17:54 /var/mail -> spool/mail
# 看到这里应该知道为啥了吧？因为 /var/mail 是连结档，连结到 /var/spool/mail 
# 所以，加上 pwd -P 的选项后，会不以连结档的数据显示，而是显示正确的完整路径啊！

.mkdir (创建新目录)

如果想要创建新的目录的话，那么就使用mkdir (make directory)吧。

语法：

mkdir [-mp] 目录名称

选项与参数：

    -m ：配置文件的权限喔！直接配置，不需要看默认权限 (umask) 的脸色～
    -p ：帮助你直接将所需要的目录(包含上一级目录)递归创建起来！

实例：请到/tmp底下尝试创建数个新目录看看：

[root@www ~]# cd /tmp
[root@www tmp]# mkdir test    <==创建一名为 test 的新目录
[root@www tmp]# mkdir test1/test2/test3/test4
mkdir: cannot create directory `test1/test2/test3/test4': 
No such file or directory       <== 没办法直接创建此目录啊！
[root@www tmp]# mkdir -p test1/test2/test3/test4

加了这个 -p 的选项，可以自行帮你创建多层目录！

实例：创建权限为 rwx--x--x 的目录。

[root@www tmp]# mkdir -m 711 test2
[root@www tmp]# ls -l
drwxr-xr-x  3 root  root 4096 Jul 18 12:50 test
drwxr-xr-x  3 root  root 4096 Jul 18 12:53 test1
drwx--x--x  2 root  root 4096 Jul 18 12:54 test2

上面的权限部分，如果没有加上 -m 来强制配置属性，系统会使用默认属性。

如果我们使用 -m ，如上例我们给予 -m 711 来给予新的目录 drwx--x--x 的权限。

.rmdir (删除空的目录)

语法：

 rmdir [-p] 目录名称

选项与参数：

    -p ：从该目录起，一次删除多级空目录 

删除 runoob 目录

[root@www tmp]# rmdir runoob/

将 mkdir 实例中创建的目录(/tmp 底下)删除掉！

[root@www tmp]# ls -l   <==看看有多少目录存在？
drwxr-xr-x  3 root  root 4096 Jul 18 12:50 test
drwxr-xr-x  3 root  root 4096 Jul 18 12:53 test1
drwx--x--x  2 root  root 4096 Jul 18 12:54 test2
[root@www tmp]# rmdir test   <==可直接删除掉，没问题
[root@www tmp]# rmdir test1  <==因为尚有内容，所以无法删除！
rmdir: `test1': Directory not empty
[root@www tmp]# rmdir -p test1/test2/test3/test4
[root@www tmp]# ls -l        <==您看看，底下的输出中test与test1不见了！
drwx--x--x  2 root  root 4096 Jul 18 12:54 test2

利用 -p 这个选项，立刻就可以将 test1/test2/test3/test4 一次删除。

不过要注意的是，这个 rmdir 仅能删除空的目录，你可以使用 rm 命令来删除非空目录。
rm -r a#可直接递归删除

.cp (复制文件或目录)

语法:

[root@www ~]# cp [-adfilprsu] 来源档(source) 目标档(destination)
[root@www ~]# cp [options] source1 source2 source3 .... directory

选项与参数：

    -a：相当於 -pdr 的意思，至於 pdr 请参考下列说明；(常用)

    -d：若来源档为连结档的属性(link file)，则复制连结档属性而非文件本身；

    -f：为强制(force)的意思，若目标文件已经存在且无法开启，则移除后再尝试一次；

    -i：若目标档(destination)已经存在时，在覆盖时会先询问动作的进行(常用)

    -l：进行硬式连结(hard link)的连结档创建，而非复制文件本身；

    -p：连同文件的属性一起复制过去，而非使用默认属性(备份常用)；

    -r：递归持续复制，用於目录的复制行为；(常用)

    -s：复制成为符号连结档 (symbolic link)，亦即『捷径』文件；

    -u：若 destination 比 source 旧才升级 destination ！

用 root 身份，将 root 目录下的 .bashrc 复制到 /tmp 下，并命名为 bashrc

[root@www ~]# cp ~/.bashrc /tmp/bashrc
[root@www ~]# cp -i ~/.bashrc /tmp/bashrc
cp: overwrite `/tmp/bashrc'? n  <==n不覆盖，y为覆盖

.rm (移除文件或目录)

语法：

 rm [-fir] 文件或目录

选项与参数：

    -f ：就是 force 的意思，忽略不存在的文件，不会出现警告信息；
    -i ：互动模式，在删除前会询问使用者是否动作
    -r ：递归删除啊！最常用在目录的删除了！这是非常危险的选项！！！

将刚刚在 cp 的实例中创建的 bashrc 删除掉！

[root@www tmp]# rm -i bashrc
rm: remove regular file `bashrc'? y

如果加上 -i 的选项就会主动询问喔，避免你删除到错误的档名！


.mv (移动文件与目录，或修改名称)

语法：

[root@www ~]# mv [-fiu] source destination
[root@www ~]# mv [options] source1 source2 source3 .... directory

选项与参数：

    -f ：force 强制的意思，如果目标文件已经存在，不会询问而直接覆盖；
    -i ：若目标文件 (destination) 已经存在时，就会询问是否覆盖！
    -u ：若目标文件已经存在，且 source 比较新，才会升级 (update)

复制一文件，创建一目录，将文件移动到目录中

[root@www ~]# cd /tmp
[root@www tmp]# cp ~/.bashrc bashrc
[root@www tmp]# mkdir mvtest
[root@www tmp]# mv bashrc mvtest

将某个文件移动到某个目录去，就是这样做！

将刚刚的目录名称更名为 mvtest2

[root@www tmp]# mv mvtest mvtest2(文件名的修改)


2.Linux 文件内容查看

Linux系统中使用以下命令来查看文件的内容：

    cat  由第一行开始显示文件内容
    tac  从最后一行开始显示，可以看出 tac 是 cat 的倒着写！
    nl   显示的时候，顺道输出行号！
    more 一页一页的显示文件内容
    less 与 more 类似，但是比 more 更好的是，他可以往前翻页！
    head 只看头几行
    tail 只看尾巴几行

你可以使用 man [命令]来查看各个命令的使用文档，如 ：man cp。

.cat

由第一行开始显示文件内容

语法：

cat [-AbEnTv]

选项与参数：

    -A ：相当於 -vET 的整合选项，可列出一些特殊字符而不是空白而已；
    -b ：列出行号，仅针对非空白行做行号显示，空白行不标行号！
    -E ：将结尾的断行字节 $ 显示出来；
    -n ：列印出行号，连同空白行也会有行号，与 -b 的选项不同；
    -T ：将 [tab] 按键以 ^I 显示出来；
    -v ：列出一些看不出来的特殊字符

检看 /etc/issue 这个文件的内容：

[root@www ~]# cat /etc/issue
CentOS release 6.4 (Final)
Kernel \r on an \m

.tac

tac与cat命令刚好相反，文件内容从最后一行开始显示，可以看出 tac 是 cat 的倒着写！如：


[root@www ~]# tac /etc/issue

Kernel \r on an \m
CentOS release 6.4 (Final)

.nl

显示行号

语法：

nl [-bnw] 文件

选项与参数：

    -b ：指定行号指定的方式，主要有两种：
    -b a ：表示不论是否为空行，也同样列出行号(类似 cat -n)；
    -b t ：如果有空行，空的那一行不要列出行号(默认值)；
    -n ：列出行号表示的方法，主要有三种：
    -n ln ：行号在荧幕的最左方显示；
    -n rn ：行号在自己栏位的最右方显示，且不加 0 ；
    -n rz ：行号在自己栏位的最右方显示，且加 0 ；
    -w ：行号栏位的占用的位数。

实例一：用 nl 列出 /etc/issue 的内容

[root@www ~]# nl /etc/issue
     1  CentOS release 6.4 (Final)
     2  Kernel \r on an \m

more

一页一页翻动

[root@www ~]# more /etc/man_db.config 
#
# Generated automatically from man.conf.in by the
# configure script.
#
# man.conf from man-1.6d
....(中间省略)....
--More--(28%)  <== 重点在这一行喔！你的光标也会在这里等待你的命令

在 more 这个程序的运行过程中，你有几个按键可以按的：

    空白键 (space)：代表向下翻一页；
    Enter         ：代表向下翻『一行』；
    /字串         ：代表在这个显示的内容当中，向下搜寻『字串』这个关键字；
    :f            ：立刻显示出档名以及目前显示的行数；
    q             ：代表立刻离开 more ，不再显示该文件内容。
    b 或 [ctrl]-b ：代表往回翻页，不过这动作只对文件有用，对管线无用。

less

一页一页翻动，以下实例输出/etc/man.config文件的内容：

[root@www ~]# less /etc/man.config
#
# Generated automatically from man.conf.in by the
# configure script.
#
# man.conf from man-1.6d
....(中间省略)....
:   <== 这里可以等待你输入命令！

less运行时可以输入的命令有：

    空白键    ：向下翻动一页；
    [pagedown]：向下翻动一页；
    [pageup]  ：向上翻动一页；
    /字串     ：向下搜寻『字串』的功能；
    ?字串     ：向上搜寻『字串』的功能；
    n         ：重复前一个搜寻 (与 / 或 ? 有关！)
    N         ：反向的重复前一个搜寻 (与 / 或 ? 有关！)
    q         ：离开 less 这个程序；

head

取出文件前面几行

语法：

head [-n number] 文件 

选项与参数：

    -n ：后面接数字，代表显示几行的意思 

[root@www ~]# head /etc/man.config

默认的情况中，显示前面 10 行！若要显示前 20 行，就得要这样：

[root@www ~]# head -n 20 /etc/man.config

tail

取出文件后面几行

语法：

tail [-n number] 文件 

选项与参数：

    -n ：后面接数字，代表显示几行的意思
    -f ：表示持续侦测后面所接的档名，要等到按下[ctrl]-c才会结束tail的侦测 

[root@www ~]# tail /etc/man.config
# 默认的情况中，显示最后的十行！若要显示最后的 20 行，就得要这样：
[root@www ~]# tail -n 20 /etc/man.config



'day04'Linux 磁盘管理

Linux 磁盘管理好坏直接关系到整个系统的性能问题。

Linux 磁盘管理常用三个命令为 df、du 和 fdisk。

    df（英文全称：disk full）：列出文件系统的整体磁盘使用量
    du（英文全称：disk used）：检查磁盘空间使用量
    fdisk：用于磁盘分区

1.df

df命令参数功能：检查文件系统的磁盘空间占用情况。可以利用该命令来获取硬盘被占用了多少空间，目前还剩下多少空间等信息。

语法：

df [-ahikHTm] [目录或文件名]

选项与参数：

    -a ：列出所有的文件系统，包括系统特有的 /proc 等文件系统；
    -k ：以 KBytes 的容量显示各文件系统；
    -m ：以 MBytes 的容量显示各文件系统；
    -h ：以人们较易阅读的 GBytes, MBytes, KBytes 等格式自行显示；
    -H ：以 M=1000K 取代 M=1024K 的进位方式；
    -T ：显示文件系统类型, 连同该 partition 的 filesystem 名称 (例如 ext3) 也列出；
    -i ：不用硬盘容量，而以 inode 的数量来显示

实例 1

将系统内所有的文件系统列出来！

[root@www ~]# df
Filesystem      1K-blocks      Used Available Use% Mounted on
/dev/hdc2         9920624   3823112   5585444  41% /
/dev/hdc3         4956316    141376   4559108   4% /home
/dev/hdc1          101086     11126     84741  12% /boot
tmpfs              371332         0    371332   0% /dev/shm

在 Linux 底下如果 df 没有加任何选项，那么默认会将系统内所有的 (不含特殊内存内的文件系统与 swap) 都以 1 Kbytes 的容量来列出来！
实例 2

将容量结果以易读的容量格式显示出来

[root@www ~]# df -h
Filesystem            Size  Used Avail Use% Mounted on
/dev/hdc2             9.5G  3.7G  5.4G  41% /
/dev/hdc3             4.8G  139M  4.4G   4% /home
/dev/hdc1              99M   11M   83M  12% /boot
tmpfs                 363M     0  363M   0% /dev/shm

实例 3

将系统内的所有特殊文件格式及名称都列出来

[root@www ~]# df -aT
Filesystem    Type 1K-blocks    Used Available Use% Mounted on
/dev/hdc2     ext3   9920624 3823112   5585444  41% /
proc          proc         0       0         0   -  /proc
sysfs        sysfs         0       0         0   -  /sys
devpts      devpts         0       0         0   -  /dev/pts
/dev/hdc3     ext3   4956316  141376   4559108   4% /home
/dev/hdc1     ext3    101086   11126     84741  12% /boot
tmpfs        tmpfs    371332       0    371332   0% /dev/shm
none   binfmt_misc         0       0         0   -  /proc/sys/fs/binfmt_misc
sunrpc  rpc_pipefs         0       0         0   -  /var/lib/nfs/rpc_pipefs

实例 4

将 /etc 底下的可用的磁盘容量以易读的容量格式显示

[root@www ~]# df -h /etc
Filesystem            Size  Used Avail Use% Mounted on
/dev/hdc2             9.5G  3.7G  5.4G  41% /

2.du

Linux du 命令也是查看使用空间的，但是与 df 命令不同的是 Linux du 命令是对文件和目录磁盘使用的空间的查看，还是和df命令有一些区别的，这里介绍 Linux du 命令。

语法：

du [-ahskm] 文件或目录名称

选项与参数：

    -a ：列出所有的文件与目录容量，因为默认仅统计目录底下的文件量而已。
    -h ：以人们较易读的容量格式 (G/M) 显示；
    -s ：列出总量而已，而不列出每个各别的目录占用容量；
    -S ：不包括子目录下的总计，与 -s 有点差别。
    -k ：以 KBytes 列出容量显示；
    -m ：以 MBytes 列出容量显示；

实例 1

只列出当前目录下的所有文件夹容量（包括隐藏文件夹）:

[root@www ~]# du
8       ./test4     <==每个目录都会列出来
8       ./test2
....中间省略....
12      ./.gconfd   <==包括隐藏文件的目录
220     .           <==这个目录(.)所占用的总量

直接输入 du 没有加任何选项时，则 du 会分析当前所在目录里的子目录所占用的硬盘空间。
实例 2

将文件的容量也列出来

[root@www ~]# du -a
12      ./install.log.syslog   <==有文件的列表了
8       ./.bash_logout
8       ./test4
8       ./test2
....中间省略....
12      ./.gconfd
220     .

实例 3

检查根目录底下每个目录所占用的容量

[root@www ~]# du -sm /*
7       /bin
6       /boot
.....中间省略....
0       /proc
.....中间省略....
1       /tmp
3859    /usr     <==系统初期最大就是他了啦！
77      /var

通配符 * 来代表每个目录。

与 df 不一样的是，du 这个命令其实会直接到文件系统内去搜寻所有的文件数据。
fdisk


'day05'环境变量与文件查找：

1.变量

要解释环境变量，得先明白变量是什么，准确的说应该是 Shell 变量，所谓变量就是计算机中用于记录一个值（不一定是数值，也可以是字符或字符串）的符号，而这些符号将用于不同的运算处理中。通常变量与值是一对一的关系，可以通过表达式读取它的值并赋值给其它变量，也可以直接指定数值赋值给任意变量。为了便于运算和处理，大部分的编程语言会区分变量的类型，用于分别记录数值、字符或者字符串等等数据类型。Shell 中的变量也基本如此，有不同类型（但不用专门指定类型名），可以参与运算，有作用域限定。

    变量的作用域即变量的有效范围（比如一个函数中、一个源文件中或者全局范围），在该范围内只能有一个同名变量。一旦离开则该变量无效，如同不存在这个变量一般。

在 Shell 中如何创建一个变量，如何给变量赋值和如何读取变量的值呢？这部分内容会在 高级 bash 脚本编程指南 这门课中详细介绍，这里我简单举例说明一下：

使用 declare 命令创建一个变量名为 tmp 的变量：

declare tmp

    其实也可以不用 declare 预声明一个变量，直接即用即创建，这里只是告诉你 declare 的作用，这在创建其它指定类型的变量（如数组）时会用到。

使用 = 号赋值运算符，将变量 tmp 赋值为 shiyanlou。注意，与其他语言不同的是， Shell 中的赋值操作，= 两边不可以输入空格，否则会报错。

# 正确的赋值
tmp=shiyanlou

# 错误的赋值
tmp = shiyanlou

读取变量的值，使用 echo 命令和 $ 符号（$ 符号用于表示引用一个变量的值，初学者经常忘记输入）：

echo $tmp



注意：并不是任何形式的变量名都是可用的，变量名只能是英文字母、数字或者下划线，且不能以数字作为开头。

2.环境变量

环境变量的作用域比自定义变量的要大，如 Shell 的环境变量作用于自身和它的子进程。
在所有的 UNIX 和类 UNIX 系统中，每个进程都有其各自的环境变量设置，且默认情况下，当一个进程被创建时，除了创建过程中明确指定的话，它将继承其父进程的绝大部分环境设置。
Shell 程序也作为一个进程运行在操作系统之上，而我们在 Shell 中运行的大部分命令都将以 Shell 的子进程的方式运行。

通常我们会涉及到的变量类型有三种：

    当前 Shell 进程私有用户自定义变量，如上面我们创建的 tmp 变量，只在当前 Shell 中有效。
    Shell 本身内建的变量。
    从自定义变量导出的环境变量。

也有三个与上述三种环境变量相关的命令：set，env，export。这三个命令很相似，都是用于打印环境变量信息，区别在于涉及的变量范围不同。详见下表：
命 令     说 明
set     显示当前 Shell 所有变量，包括其内建环境变量（与 Shell 外观等相关），用户自定义变量及导出的环境变量。
env     显示与当前用户相关的环境变量，还可以让命令在指定环境中运行。
export  显示从 Shell 中导出成环境变量的变量，也能通过它将自定义变量导出为环境变量。


你可以更直观的使用 vimdiff 工具比较一下它们之间的差别：

temp=shiyanlou
export temp_env=shiyanlou
env|sort>env.txt
export|sort>export.txt
set|sort>set.txt

上述操作将命令输出通过管道 | 使用 sort 命令排序，再重定向到对象文本文件中。管道的概念后面我们会学到，现在你知道这是什么意思就行了。

vimdiff env.txt export.txt set.txt

使用 vimdiff 工具比较导出的几个文件的内容，退出 vimdiff 需要按下 Esc 后输入 :q 即可退出。


关于哪些变量是环境变量，可以简单地理解成在当前进程的子进程有效则为环境变量，否则不是（有些人也将所有变量统称为环境变量，只是以全局环境变量和局部环境变量进行区分，我们只要理解它们的实质区别即可）。我们这里用 export 命令来体会一下，先在 Shell 中设置一个变量 temp=shiyanlou，然后再新创建一个子 Shell 查看 temp 变量的值：


注意：为了与普通变量区分，通常我们习惯将环境变量名设为大写。
永久生效

但是问题来了，当你关机后，或者关闭当前的 shell 之后，环境变量就没了啊。怎么才能让环境变量永久生效呢？

按变量的生存周期来划分，Linux 变量可分为两类：

    永久的：需要修改配置文件，变量永久生效；

    临时的：使用 export 命令行声明即可，变量在关闭 shell 时失效。

这里介绍两个重要文件 /etc/bashrc（有的 Linux 没有这个文件） 和 /etc/profile ，它们分别存放的是 shell 变量和环境变量。还有要注意区别的是每个用户目录下的一个隐藏文件：

# .profile 可以用 ls -a 查看
cd /home/shiyanlou
ls -a

这个 .profile 只对当前用户永久生效。因为它保存在当前用户的 Home 目录下，当切换用户时，工作目录可能一并被切换到对应的目录中，这个文件就无法生效。而写在 /etc/profile 里面的是对所有用户永久生效，
所以如果想要添加一个永久生效的环境变量，只需要打开 /etc/profile，在最后加上你想添加的环境变量就好啦。


3.命令的查找路径与顺序 


你可能很早之前就有疑问，我们在 Shell 中输入一个命令，Shell 是怎么知道去哪找到这个命令然后执行的呢？这是通过环境变量 PATH 来进行搜索的，熟悉 Windows 的用户可能知道 Windows 中的也是有这么一个 PATH 环境变量。这个 PATH 里面就保存了 Shell 中执行的命令的搜索路径。

查看 PATH 环境变量的内容：

echo $PATH

默认情况下你会看到如下输出：

/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games

如果你还记得 Linux 目录结构那一节的内容，你就应该知道上面这些目录下放的是哪一类文件了。通常这一类目录下放的都是可执行文件，当我们在 Shell 中执行一个命令时，系统就会按照 PATH 中设定的路径按照顺序依次到目录中去查找，如果存在同名的命令，则执行先找到的那个。

    下面我们将练习创建一个最简单的可执行 Shell 脚本和一个使用 C 语言创建的“ hello world ”程序，如果这两部分内容你之前没有学习过，那么你可以进行一个入门学习：

    C 语言入门教程
    高级 Bash 脚本编程指南
    Linux Shell Scripting Tutorial (LSST) v2.0

创建一个 Shell 脚本文件，你可以使用 gedit，vim，sublime 等工具编辑。如果你是直接复制的话，建议使用 gedit 或者 sublime，否则可能导致代码缩进混乱。

cd /home/shiyanlou
touch hello_shell.sh
gedit hello_shell.sh

在脚本中添加如下内容，保存并退出。

注意不要省掉第一行，这不是注释，有用户反映有语法错误，就是因为没有了第一行。

#!/bin/bash

for ((i=0; i<10; i++));do
    echo "hello shell"
done

exit 0

为文件添加可执行权限，否则执行会报错没有权限：

chmod 755 hello_shell.sh

执行脚本：

cd /home/shiyanlou
./hello_shell.sh

创建一个 C 语言 hello world 程序：

cd /home/shiyanlou
gedit hello_world.c

输入如下内容，同样不能省略第一行。

#include <stdio.h>

int main(void)
{
    printf("hello world!\n");
    return 0;
}

保存后使用 gcc 生成可执行文件：

gcc -o hello_world hello_world.c

gcc 生成二进制文件默认具有可执行权限，不需要修改。

在 /home/shiyanlou 家目录创建一个 mybin 目录，并将上述 hello_shell.sh 和 hello_world 文件移动到其中：

cd /home/shiyanlou
mkdir mybin
mv hello_shell.sh hello_world mybin/

现在你可以在 mybin 目录中分别运行你刚刚创建的两个程序：

cd mybin
./hello_shell.sh
./hello_world



回到上一级目录，也就是 shiyanlou 家目录，当再想运行那两个程序时，会发现提示命令找不到，除非加上命令的完整路径，但那样很不方便，如何做到像使用系统命令一样执行自己创建的脚本文件或者程序呢？
那就要将命令所在路径添加到 PATH 环境变量了。


在前面我们应该注意到 PATH 里面的路径是以 : 作为分割符的，所以我们可以这样添加自定义路径：

PATH=$PATH:/home/shiyanlou/mybin

注意这里一定要使用绝对路径。

现在你就可以在任意目录执行那两个命令了（注意需要去掉前面的 ./）。你可能会意识到这样还并没有很好的解决问题，因为我给 PATH 环境变量追加了一个路径，它也只是在当前 Shell 有效，我一旦退出终端，再打开就会发现又失效了。有没有方法让添加的环境变量全局有效？或者每次启动 Shell 时自动执行上面添加自定义路径到 PATH 的命令？下面我们就来说说后一种方式——让它自动执行。

在每个用户的 home 目录中有一个 Shell 每次启动时会默认执行一个配置脚本，以初始化环境，包括添加一些用户自定义环境变量等等。实验楼的环境使用的 Shell 是 zsh，它的配置文件是 .zshrc，相应的如果使用的 Shell 是 Bash，则配置文件为 .bashrc。它们在 etc 下还都有一个或多个全局的配置文件，不过我们一般只修改用户目录下的配置文件。Shell 的种类有很多，可以使用 cat /etc/shells 命令查看当前系统已安装的 Shell。


我们可以简单地使用下面命令直接添加内容到 .zshrc 中：

echo "PATH=$PATH:/home/shiyanlou/mybin" >> .zshrc

上述命令中 >> 表示将标准输出以追加的方式重定向到一个文件中，注意前面用到的 > 是以覆盖的方式重定向到一个文件中，使用的时候一定要注意分辨。在指定文件不存在的情况下都会创建新的文件。

4.修改和删除已有变量

.变量修改

变量的修改有以下几种方式：
变量设置方式  说明
${变量名#匹配字串}     从头向后开始匹配，删除符合匹配字串的最短数据
${变量名##匹配字串}    从头向后开始匹配，删除符合匹配字串的最长数据
${变量名%匹配字串}     从尾向前开始匹配，删除符合匹配字串的最短数据
${变量名%%匹配字串}    从尾向前开始匹配，删除符合匹配字串的最长数据
${变量名/旧的字串/新的字串}    将符合旧字串的第一个字串替换为新的字串
${变量名//旧的字串/新的字串}   将符合旧字串的全部字串替换为新的字串

比如我们可以修改前面添加到 PATH 的环境变量，将添加的 mybin 目录从环境变量里删除。为了避免操作失误导致命令找不到，我们先将 PATH 赋值给一个新的自定义变量 mypath：

mypath=$PATH
echo $mypath
mypath=${mypath%/home/shiyanlou/mybin}
# 或使用通配符 * 表示任意多个任意字符
mypath=${mypath%*/mybin}

可以看到路径已经不存在了。


.变量删除

可以使用 unset 命令删除一个环境变量：

unset mypath

 5. 如何让环境变量立即生效

前面我们在 Shell 中修改了一个配置脚本文件之后（比如 zsh 的配置文件 home 目录下的 .zshrc），每次都要退出终端重新打开甚至重启主机之后其才能生效，很是麻烦，我们可以使用 source 命令来让其立即生效，如：

cd /home/shiyanlou
source .zshrc

source 命令还有一个别名就是 .，上面的命令如果替换成 . 的方式就该是：

. ./.zshrc

图片描述

在使用 . 的时候，需要注意与表示当前路径的那个点区分开。

注意第一个点后面有一个空格，而且后面的文件必须指定完整的绝对或相对路径名，source 则不需要。


总结：
mkdir a---cd a---touch a.py---gedit a.py---PATH=$PATH:/home/kim/a(把PATH这个环境变量添加到PATH中---
echo 'PATH=$PATH:/home/kim/a' >> .bashrc---source .bashrc
---./a.py---unset PATH#删除path环境变量
(环境变量生效后就能在任意位置执行a.py)
#千万不要随便修改环境变量


6.常用的搜索命令：
与搜索相关的命令常用的有 whereis，which，find 和 locate。
whereis 简单快速
whereis who
whereis find



你会看到 whereis find 找到了三个路径，两个可执行文件路径和一个 man 在线帮助文件所在路径，这个搜索很快，因为它并没有从硬盘中依次查找，而是直接从数据库中查询。

whereis 只能搜索二进制文件（-b），man 帮助文件（-m）和源代码文件（-s）。如果想要获得更全面的搜索结果可以使用 locate 命令。

    locate 快而全

使用 locate 命令查找文件也不会遍历硬盘，它通过查询 /var/lib/mlocate/mlocate.db 数据库来检索信息。不过这个数据库也不是实时更新的，系统会使用定时任务每天自动执行 updatedb 命令来更新数据库。所以有时候你刚添加的文件，它可能会找不到，需要手动执行一次 updatedb 命令（在我们的环境中必须先执行一次该命令）。注意这个命令也不是内置的命令，在部分环境中需要手动安装，然后执行更新。

sudo apt-get update
sudo apt-get install locate
sudo updatedb

它可以用来查找指定目录下的不同文件类型，如查找 /etc 下所有以 sh 开头的文件：

locate /etc/sh


查找 /usr/share/ 下所有 jpg 文件：

locate /usr/share/*.jpg


'day06文件的打包和解压缩'

'1.用zip压缩解压'
在讲 Linux 上的压缩工具之前，有必要先了解一下常见常用的压缩包文件格式。在 Windows 上最常见的不外乎这两种 *.zip，*.7z 后缀的压缩文件。而在 Linux 上面常见的格式除了以上两种外，还有 .rar，*.gz，*.xz，*.bz2，*.tar，*.tar.gz，*.tar.xz，*.tar.bz2，简单介绍如下：
文件后缀名   说明
*.zip   zip 程序打包压缩的文件
*.rar   rar 程序压缩的文件
*.7z    7zip 程序压缩的文件
*.tar   tar 程序打包，未压缩的文件
*.gz    gzip 程序（GNU zip）压缩的文件
*.xz    xz 程序压缩的文件
*.bz2   bzip2 程序压缩的文件
*.tar.gz    tar 打包，gzip 程序压缩的文件
*.tar.xz    tar 打包，xz 程序压缩的文件
*tar.bz2    tar 打包，bzip2 程序压缩的文件
*.tar.7z    tar 打包，7z 程序压缩的文件

讲了这么多种压缩文件，这么多个命令，不过我们一般只需要掌握几个命令即可，包括 zip，tar。下面会依次介绍这几个命令及对应的解压命令。

1.zip压缩打包程序

    使用 zip 打包文件夹，注意输入完整的参数和路径：

cd /home/shiyanlou
zip -r -q -o shiyanlou.zip /home/shiyanlou/Desktop#一般用-r，第一个是压缩后的文件，第二个是将要被的压缩文件
du -h shiyanlou.zip
file shiyanlou.zip#将shiyanlou.zip解压

上面命令将目录 /home/shiyanlou/Desktop 打包成一个文件，并查看了打包后文件的大小和类型。
第一行命令中，-r 参数表示递归打包包含子目录的全部内容，
-q 参数表示为安静模式，即不向屏幕输出信息，-o，表示输出文件，需在其后紧跟打包输出文件名。
后面使用 du 命令查看打包后文件的大小（后面会具体说明该命令）。

    设置压缩级别为 9 和 1（9 最大，1 最小），重新打包：

zip -r -9 -q -o shiyanlou_9.zip /home/shiyanlou/Desktop -x ~/*.zip
zip -r -1 -q -o shiyanlou_1.zip /home/shiyanlou/Desktop -x ~/*.zip

这里添加了一个参数用于设置压缩级别 -[1-9]，1 表示最快压缩但体积大，9 表示体积最小但耗时最久。
最后那个 -x 是为了排除我们上一次创建的 zip 文件，否则又会被打包进这一次的压缩文件中，注意：这里只能使用绝对路径，否则不起作用。

我们再用 du 命令分别查看默认压缩级别、最低、最高压缩级别及未压缩的文件的大小：

du -h -d 0 *.zip ~ | sort

通过 man 手册可知：

    -h， --human-readable（顾名思义，你可以试试不加的情况）
    -d， --max-depth（所查看文件的深度）

图片描述

这样一目了然，理论上来说默认压缩级别应该是最高的，但是由于文件不大，这里的差异不明显（几乎看不出差别），不过你在环境中操作之后看到的压缩文件大小可能跟图上的有些不同，因为系统在使用过程中，会随时生成一些缓存文件在当前用户的家目录中，这对于我们学习命令使用来说，是无关紧要的，可以忽略这些不同。

    创建加密 zip 包

使用 -e 参数可以创建加密压缩包：

zip -r -e -o shiyanlou_encryption.zip /home/shiyanlou/Desktop

注意： 关于 zip 命令，因为 Windows 系统与 Linux/Unix 在文本文件格式上的一些兼容问题，比如换行符（为不可见字符），在 Windows 为 CR+LF（Carriage-Return+Line-Feed：回车加换行），而在 Linux/Unix 上为 LF（换行），所以如果在不加处理的情况下，在 Linux 上编辑的文本，在 Windows 系统上打开可能看起来是没有换行的。如果你想让你在 Linux 创建的 zip 压缩文件在 Windows 上解压后没有任何问题，那么你还需要对命令做一些修改：

zip -r -l -o shiyanlou.zip /home/shiyanlou/Desktop

需要加上 -l 参数将 LF 转换为 CR+LF 来达到以上目的。

2.unzip解压
将 shiyanlou.zip 解压到当前目录：

unzip shiyanlou.zip

使用安静模式，将文件解压到指定目录：

unzip -q shiyanlou.zip -d ziptest#-d代表解压地点destination

上述指定目录不存在，将会自动创建。如果你不想解压只想查看压缩包的内容你可以使用 -l 参数：

unzip -l shiyanlou.zip

注意： 使用 unzip 解压文件时我们同样应该注意兼容问题，不过这里我们关心的不再是上面的问题，而是中文编码的问题，通常 Windows 系统上面创建的压缩文件，如果有有包含中文的文档或以中文作为文件名的文件时默认会采用 GBK 或其它编码，而 Linux 上面默认使用的是 UTF-8 编码，
如果不加任何处理，直接解压的话可能会出现中文乱码的问题（有时候它会自动帮你处理），为了解决这个问题，我们可以在解压时指定编码类型。

使用 -O（英文字母，大写 o）参数指定编码类型：

unzip -O GBK 中文压缩文件.zip


'2.用tar压缩解压'


在 Linux 上面更常用的是 tar 工具，tar 原本只是一个打包工具，只是同时还是实现了对 7z、gzip、xz、bzip2 等工具的支持，这些压缩工具本身只能实现对文件或目录（单独压缩目录中的文件）的压缩，没有实现对文件的打包压缩，所以我们也无需再单独去学习其他几个工具，tar 的解压和压缩都是同一个命令，只需参数不同，使用比较方便。

下面先掌握 tar 命令一些基本的使用方式，即不进行压缩只是进行打包（创建归档文件）和解包的操作。

    创建一个 tar 包：

cd /home/shiyanlou
tar -P -cf shiyanlou.tar /home/shiyanlou/Desktop

上面命令中，-P 保留绝对路径符，-c 表示创建一个 tar 包文件'create'，-f 用于指定创建的文件名#file，
注意文件名必须紧跟在 -f 参数之后，比如不能写成 tar -fc shiyanlou.tar，可以写成 tar -f shiyanlou.tar -c ~。你还可以加上 -v 参数以可视的的方式输出打包的文件。

    解包一个文件（-x 参数）到指定路径的已存在目录（-C 参数）：

mkdir tardir
tar -xf shiyanlou.tar -C tardir

    只查看不解包文件 -t 参数：

tar -tf shiyanlou.tar

    保留文件属性和跟随链接（符号链接或软链接），有时候我们使用 tar 备份文件当你在其他主机还原时希望保留文件的属性（-p 参数）和备份链接指向的源文件而不是链接本身（-h 参数）：

tar -cphf etc.tar /etc

对于创建不同的压缩格式的文件，对于 tar 来说是相当简单的，需要的只是换一个参数，这里我们就以使用 gzip 工具创建 *.tar.gz 文件为例来说明。

    我们只需要在创建 tar 文件的基础上添加 -z 参数，使用 gzip 来压缩文件：

tar -czf shiyanlou.tar.gz /home/shiyanlou/Desktop

    解压 *.tar.gz 文件：

tar -xzf shiyanlou.tar.gz



现在我们要使用其它的压缩工具创建或解压相应文件只需要更改一个参数即可：
压缩文件格式  参数
*.tar.gz    -z
*.tar.xz    -J
*tar.bz2    -j

    tar 命令的参数很多，不过常用的就是上述这些，需要了解更多你可以查看 man 手册获取帮助。

注意：
zip：
打包 ：zip something.zip something （目录请加 -r 参数）
解包：unzip something.zip
指定路径：-d 参数
tar：
打包：tar -cf something.tar something
解包：tar -xf something.tar
指定路径：-C 参数
(任何时候都要加f,zip的路径-d,tar路径为-C)

'day07磁盘操作'


2.1 查看磁盘和目录的容量

    使用 df 命令查看磁盘的容量


物理主机上的 /dev/sda2 是对应着主机硬盘的分区，后面的数字表示分区号，数字前面的字母 a 表示第几块硬盘（也可能是可移动磁盘），你如果主机上有多块硬盘则可能还会出现 /dev/sdb，/dev/sdc 这些磁盘设备都会在 /dev 目录下以文件的存在形式。

接着你还会看到"1k-块"这个陌生的东西，它表示以磁盘块大小的方式显示容量，后面为相应的以块大小表示的已用和可用容量，在你了解 Linux 的文件系统之前这个就先不管吧，我们以一种你应该看得懂的方式展示：

df -h


现在你就可以使用命令查看你主机磁盘的使用情况了。至于挂载点如果你还记得前面第 4 节介绍 Linux 目录树结构的内容，那么你就应该能很好的理解挂载的概念，这里就不再赘述。

    使用 du 命令查看目录的容量

这个命令前面其实已经用了很多次了：

# 默认同样以块的大小展示
du
# 加上 `-h` 参数，以更易读的方式展示
du -h

-d 参数指定查看目录的深度

# 只查看 1 级目录的信息
du -h -d 0 ~
# 查看 2 级
du -h -d 1 ~

常用参数

du -h # 同 --human-readable 以 K，M，G 为单位，提高信息的可读性。
du -a # 同 --all 显示目录中所有文件的大小。
du -s # 同 --summarize 仅显示总计，只列出最后加总的值。

注意：
du（estimate file space usage）命令与 df（report file system disk space usage）命令只有一字之差，希望大家注意不要弄混淆了，你可以像我这样从 man 手册中获取命令的完整描述，记全称就不会搞混了。
du是记录文件空间使用的，df是记录磁盘空间使用的


'day08Linux 下的帮助命令 '


    内建命令实际上是 shell 程序的一部分，其中包含的是一些比较简单的 Linux 系统命令，这些命令是写在 bash 源码的 builtins 里面的，由 shell 程序识别并在 shell 程序内部完成运行，通常在 Linux 系统加载运行时 shell 就被加载并驻留在系统内存中。而且解析内部命令 shell 不需要创建子进程，因此其执行速度比外部命令快。比如：history、cd、exit 等等。

    外部命令是 Linux 系统中的实用程序部分，因为实用程序的功能通常都比较强大，所以其包含的程序量也会很大，在系统加载时并不随系统一起被加载到内存中，而是在需要时才将其调入内存。虽然其不包含在 shell 中，但是其命令执行过程是由 shell 程序控制的。外部命令是在 Bash 之外额外安装的，通常放在/bin，/usr/bin，/sbin，/usr/sbin 等等。比如：ls、vi 等。

简单来说就是：一个是天生自带的天赋技能，一个是后天得来的附加技能。我们可以使用 type 命令来区分命令是内建的还是外部的。例如这两个得出的结果是不同的

type exit

type vim

得到的是两种结果，若是对 ls 你还能得到第三种结果



# 得到这样的结果说明是内建命令，正如上文所说内建命令都是在 bash 源码中的 builtins 的.def中
xxx is a shell builtin
# 得到这样的结果说明是外部命令，正如上文所说，外部命令在/usr/bin or /usr/sbin等等中
xxx is /usr/bin/xxx
# 若是得到alias的结果，说明该指令为命令别名所设定的名称；
xxx is an alias for xx --xxx

'1.help'

本实验环境是 zsh，而 zsh 中内置并没有 help 命令，我们可以进入 bash 中，在 bash 中内置有该命令

bash


做好了以上的准备，我们就可以愉快的使用 help 命令了，我们可以尝试下这个命令:

help ls#help ls表示显示内建的信息

得到的结果如图所示，为什么是这样的结果？


因为 help 命令是用于显示 shell 内建命令的简要帮助信息。帮助信息中显示有该命令的简要说明以及一些参数的使用以及说明，一定记住 help 命令只能用于显示内建命令的帮助信息，不然就会得到你刚刚得到的结果。

那如果是外部命令怎么办，不能就这么抛弃它呀。其实外部命令基本上都有一个参数 --help，这样就可以得到相应的帮助，看到你想要的东西了。试试下面这个命令是不是能看到你想要的东西了。

ls --help#ls --help表示显示外部的信息

'2.man'

得到的内容比用 help 更多更详细，而且 man 没有内建与外部命令的区分，因为 man 工具是显示系统手册页中的内容，也就是一本电子版的字典，这些内容大多数都是对命令的解释信息，还有一些相关的描述。
通过查看系统文档中的 man 也可以得到程序的更多相关信息和 Linux 的更多特性。

是不是好用许多，当然也不代表 help 就没有存在的必要，当你非常紧急只是忘记该用哪个参数的时候，help 这种显示简单扼要的信息就特别实用，若是不太紧急的时候就可以用 man 这种详细描述的查询方式

在尝试上面这个命令时我们会发现最左上角显示“ LS （1）”，在这里，“ LS ”表示手册名称，而“（1）”表示该手册位于第一章节。这个章节又是什么？在 man 手册中一共有这么几个章节



'3. Linux 任务计划 crontab '
1.简介:
我们时常会有一些定期定时的任务，如周期性的清理一下 /tmp，周期性的去备份一次数据库，周期性的分析日志等等。
而且有时候因为某些因素的限制，执行该任务的时间会很尴尬。本课程将带你很好的利用 Linux 系统的计划工具。

crontab 命令从输入设备读取指令，并将其存放于 crontab 文件中，以供之后读取和执行。通常，crontab 储存的指令被守护进程激活，crond 为其守护进程，crond 常常在后台运行，每一分钟会检查一次是否有预定的作业需要执行。

通过 crontab 命令，我们可以在固定的间隔时间执行指定的系统指令或 shell 脚本。时间间隔的单位可以是分钟、小时、日、月、周的任意组合。

这里我们看一看 crontab 的格式：
# Example of job definition:
# .---------------- minute (0 - 59)
# |  .------------- hour (0 - 23)
# |  |  .---------- day of month (1 - 31)
# |  |  |  .------- month (1 - 12) OR jan,feb,mar,apr ...
# |  |  |  |  .---- day of week (0 - 6) (Sunday=0 or 7) OR sun,mon,tue,wed,thu,fri,sat
# |  |  |  |  |
# *  *  *  *  * user-name command to be executed

2.准备：
crontab 在本实验环境中需要做一些特殊的准备，首先我们会启动 rsyslog，以便我们可以通过日志中的信息来了解我们的任务是否真正的被执行了（在本实验环境中需要手动启动，而在自己本地中 Ubuntu 会默认自行启动不需要手动启动）。

sudo apt-get install -y rsyslog
sudo service rsyslog start



'day09.命令执行顺序控制与管道' 
顺序执行、选择执行、管道、cut 命令、grep 命令、wc 命令、sort 命令等，高效率使用 Linux 的技巧。

1.选择性执行
 2.1 顺序执行多条命令

当我们需要使用 apt-get 安装一个软件，然后安装完成后立即运行安装的软件或命令工具，又恰巧你的主机才更换的软件源还没有更新软件列表（比如之前我们的环境中，每次重新开始实验就得 sudo apt-get update，否则可能会报错提示 404），那么你可能会有如下一系列操作：

sudo apt-get update
# 等待执行完毕，然后输入下面的命令
sudo apt-get install some-tool # 这里 some-tool 需要替换成具体的软件包
# 等待安装完毕，然后输入软件包名称执行
some-tool

这时你可能就会想：要是我可以一次性输入完，让它自己去依次执行各命令就好了，这就是我们这一小节要解决的问题。

简单的顺序执行你可以使用 ; 来完成，比如上述操作你可以：

sudo apt-get update;sudo apt-get install some-tool;some-tool # 让它自己运行


 2.2 有选择的执行命令

关于上面的操作，不知你有没有思考过一个问题，如果我们在让它自动顺序执行命令时，前面的命令执行不成功，而后面的命令又依赖于上一条命令的结果，那么就会造成花了时间，最终却得到一个错误的结果，而且有时候直观的看你还无法判断结果是否正确。
那么我们需要能够有选择性的来执行命令，比如上一条命令执行成功才继续下一条，或者不成功又该做出其它什么处理，比如我们使用 which 来查找是否安装某个命令，如果找到就执行该命令，否则什么也不做，虽然这个操作没有什么实际意义，但可帮你更好的理解一些概念：

which cowsay>/dev/null && cowsay -f head-in ohch~

你如果没有安装 cowsay，你可以先执行一次上述命令，你会发现什么也没发生，你再安装好之后你再执行一次上述命令，你也会发现一些惊喜。

上面的 && 就是用来实现选择性执行的，它表示如果前面的命令执行结果（不是表示终端输出的内容，而是表示命令执行状态的结果）返回 0 则执行后面的，否则不执行，你可以从 $? 环境变量获取上一次命令的返回结果：


2.管道：


管道是一种通信机制，通常用于进程间的通信（也可通过 socket 进行网络通信），它表现出来的形式就是将前面每一个进程的输出（stdout）直接作为下一个进程的输入（stdin）。

管道又分为匿名管道和具名管道（这里将不会讨论在源程序中使用系统调用创建并使用管道的情况，它与命令行的管道在内核中实际都是采用相同的机制）。我们在使用一些过滤程序时经常会用到的就是匿名管道，在命令行中由 | 分隔符表示，| 在前面的内容中我们已经多次使用到了。具名管道简单的说就是有名字的管道，通常只会在源程序中用到具名管道。下面我们就将通过一些常用的可以使用管道的过滤程序来帮助你熟练管道的使用。

先试用一下管道，比如查看 /etc 目录下有哪些文件和目录，使用 ls 命令来查看：

ls -al /etc

有太多内容，屏幕不能完全显示，这时候可以使用滚动条或快捷键滚动窗口来查看。不过这时候可以使用管道：

ls -al /etc | less

通过管道将前一个命令(ls)的输出作为下一个命令(less)的输入，然后就可以一行一行地看。


3.cut 命令，打印每一行的某一字段

打印 /etc/passwd 文件中以 : 为分隔符的第 1 个字段和第 6 个字段分别表示用户名和其家目录：

cut /etc/passwd -d ':' -f 1,6


打印 /etc/passwd 文件中每一行的前 N 个字符：

# 前五个（包含第五个）
cut /etc/passwd -c -5
# 前五个之后的（包含第五个）
cut /etc/passwd -c 5-
# 第五个
cut /etc/passwd -c 5
# 2 到 5 之间的（包含第五个）
cut /etc/passwd -c 2-5


4.rep 命令，在文本中或 stdin 中查找匹配字符串

grep 命令是很强大的，也是相当常用的一个命令，它结合正则表达式可以实现很复杂却很高效的匹配和查找，不过在学习正则表达式之前，这里介绍它简单的使用，而关于正则表达式后面将会有单独一小节介绍到时会再继续学习 grep 命令和其他一些命令。

grep 命令的一般形式为：

grep [命令选项]... 用于匹配的表达式 [文件]...


还是先体验一下，我们搜索/home/shiyanlou目录下所有包含"shiyanlou"的文本文件，并显示出现在文本中的行号：

grep -rnI "shiyanlou" ~



-r 参数表示递归搜索子目录中的文件，-n 表示打印匹配项行号，-I 表示忽略二进制文件。这个操作实际没有多大意义，但可以感受到 grep 命令的强大与实用。

当然也可以在匹配字段中使用正则表达式，下面简单的演示：

# 查看环境变量中以 "yanlou" 结尾的字符串
export | grep ".*yanlou$"


其中$就表示一行的末尾。

！export的用法
Linux export 命令用于设置或显示环境变量。

在 shell 中执行程序时，shell 会提供一组环境变量。export 可新增，修改或删除环境变量，供后续执行的程序使用。export 的效力仅限于该次登陆操作。
语法

export [-fnp][变量名称]=[变量设置值]

参数说明：

    -f 　代表[变量名称]中为函数名称。
    -n 　删除指定的变量。变量实际上并未删除，只是不会输出到后续指令的执行环境中。
    -p 　列出所有的shell赋予程序的环境变量。


4.wc 命令，简单小巧的计数工具

wc 命令用于统计并输出一个文件中行、单词和字节的数目，比如输出 /etc/passwd 文件的统计信息：

wc /etc/passwd

分别只输出行数、单词数、字节数、字符数和输入文本中最长一行的字节数：

# 行数
wc -l /etc/passwd
# 单词数
wc -w /etc/passwd
# 字节数
wc -c /etc/passwd
# 字符数
wc -m /etc/passwd
# 最长行字节数
wc -L /etc/passwd


注意：对于西文字符来说，一个字符就是一个字节，但对于中文字符一个汉字是大于 2 个字节的，具体数目是由字符编码决定的。



再来结合管道来操作一下，下面统计 /etc 下面所有目录数：

ls -dl /etc/*/ | wc -l

5.sort 排序命令

这个命令前面我们也是用过多次，功能很简单就是将输入按照一定方式排序，
然后再输出，它支持的排序有按字典排序，数字排序，按月份排序，随机排序，反转排序，指定特定字段进行排序等等。

默认为字典排序：

cat /etc/passwd | sort#按照首字母行排序

反转排序：

cat /etc/passwd | sort -r


按特定字段排序：

cat /etc/passwd | sort -t':' -k 3


上面的-t参数用于指定字段的分隔符，这里是以":"作为分隔符；-k 字段号用于指定对哪一个字段进行排序。这里/etc/passwd文件的第三个字段为数字，默认情况下是以字典序排序的，如果要按照数字排序就要加上-n参数：

6.uniq 去重命令

uniq 命令可以用于过滤或者输出重复行。

    过滤重复行

我们可以使用 history 命令查看最近执行过的命令（实际为读取 ${SHELL}_history 文件，如我们环境中的 .zsh_history 文件），不过你可能只想查看使用了哪个命令而不需要知道具体干了什么，那么你可能就会要想去掉命令后面的参数然后去掉重复的命令：

history | cut -c 8- | cut -d ' ' -f 1 | uniq

然后经过层层过滤，你会发现确是只输出了执行的命令那一列，不过去重效果好像不明显，仔细看你会发现它确实去重了，只是不那么明显，之所以不明显是因为 uniq 命令只能去连续重复的行，不是全文去重，所以要达到预期效果，我们先排序：

history | cut -c 8- | cut -d ' ' -f 1 | sort | uniq
# 或者
history | cut -c 8- | cut -d ' ' -f 1 | sort -u

这就是 Linux/UNIX 哲学吸引人的地方，大繁至简，一个命令只干一件事却能干到最好。

    输出重复行

# 输出重复过的行（重复的只输出一个）及重复次数
history | cut -c 8- | cut -d ' ' -f 1 | sort | uniq -dc
# 输出所有重复的行
history | cut -c 8- | cut -d ' ' -f 1 | sort | uniq -D

文本处理命令还有很多，下一节将继续介绍一些常用的文本处理的命令。
轻松一下

使用以前介绍过的方法，安装aview和imagemagick，然后用asciiview命令显示图片，使用方法可以用 man 命令查看。


'day10简单的文本处理'

.tr

tr 命令可以用来删除一段文本信息中的某些文字。或者将其进行转换。
使用方式

linux tr 命令用于转换或删除文件中的字符。

tr 指令从标准输入设备读取数据，经过字符串转译后，将结果输出到标准输出设备。
语法

tr [-cdst][--help][--version][第一字符集][第二字符集]  
tr [OPTION]…SET1[SET2] #!/usr/bin/env python
常用的选项有
选项  说明
-d  删除和 set1 匹配的字符，注意不是全词匹配也不是按字符顺序匹配
-s  去除 set1 指定的在输入文本中连续并重复的字符
操作举例

# 删除 "hello shiyanlou" 中所有的'o'，'l'，'h'
$ echo 'hello shiyanlou' | tr -d 'olh'
# 将"hello" 中的ll，去重为一个l
$ echo 'hello' | tr -s 'l'
# 将输入文本，全部转换为大写或小写输出
$ echo 'input some text here' | tr '[:lower:]' '[:upper:]'
# 上面的'[:lower:]' '[:upper:]'你也可以简单的写作'[a-z]' '[A-Z]'，当然反过来将大写变小写也是可以的


将文件testfile中的小写字母全部转换成大写字母，此时，可使用如下命令：

cat testfile |tr a-z A-Z #转换

cat testfile | tr -d asd #删除调testfile中的asd

更多 tr 的使用，你可以使用--help或者man tr获得。

.col

col 命令可以将Tab换成对等数量的空格键，或反转这个操作。
使用方式

col [option]

常用的选项有
选项  说明
-x  将Tab转换为空格
-h  将空格转换为Tab（默认选项）
操作举例

# 查看 /etc/protocols 中的不可见字符，可以看到很多 ^I ，这其实就是 Tab 转义成可见字符的符号
cat -A /etc/protocols
# 使用 col -x 将 /etc/protocols 中的 Tab 转换为空格，然后再使用 cat 查看，你发现 ^I 不见了
cat /etc/protocols | col -x | cat -A


.join

学过数据库的用户对这个应该不会陌生，这个命令就是用于将两个文件中包含相同内容的那一行合并在一起。
使用方式

join [option]... file1 file2

常用的选项有
选项  说明
-t  指定分隔符，默认为空格
-i  忽略大小写的差异
-1  指明第一个文件要用哪个字段来对比，默认对比第一个字段
-2  指明第二个文件要用哪个字段来对比，默认对比第一个字段
操作举例

cd /home/shiyanlou
# 创建两个文件
echo '1 hello' > file1#将'1 hello'追加在file1中，若无file1则自动创建
echo '1 shiyanlou' > file2
join file1 file2
# 将 /etc/passwd 与 /etc/shadow 两个文件合并，指定以':'作为分隔符
sudo join -t':' /etc/passwd /etc/shadow
# 将 /etc/passwd 与 /etc/group 两个文件合并，指定以':'作为分隔符，分别比对第4和第3个字段
sudo join -t':' -1 4 /etc/passwd -2 3 /etc/group


.paste

paste这个命令与join 命令类似，它是在不对比数据的情况下，简单地将多个文件合并一起，以Tab隔开。
使用方式

paste [option] file...

常用的选项有
选项  说明
-d  指定合并的分隔符，默认为 Tab
-s  不合并到一行，每个文件为一行
操作举例

echo hello > file1
echo shiyanlou > file2
echo www.shiyanlou.com > file3
paste -d ':' file1 file2 file3
paste -s file1 file2 file3


'day11数据流重定向'

下面我们简单的回顾一下我们前面经常用到的两个重定向操作：

echo 'hello shiyanlou' > redirect
echo 'www.shiyanlou.com' >> redirect
cat redirect

    当然前面没有用到的 < 和 << 操作也是没有问题的，如你理解的一样，它们的区别在于重定向的方向不一致而已，
    > 表示是从左到右，< 右到左。

1.简单重定向


在更多了解 Linux 的重定向之前，我们需要先知道一些基本的东西，前面我们已经提到过 Linux 默认提供了三个特殊设备，用于终端的显示和输出，分别为 stdin（标准输入，对应于你在终端的输入），stdout（标准输出，对应于终端的输出），stderr（标准错误输出，对应于终端的输出）。
文件描述符   设备文件    说明
0   /dev/stdin  标准输入
1   /dev/stdout     标准输出
2   /dev/stderr     标准错误

    文件描述符：文件描述符在形式上是一个非负整数。实际上，它是一个索引值，指向内核为每一个进程所维护的该进程打开文件的记录表。当程序打开一个现有文件或者创建一个新文件时，内核向进程返回一个文件描述符。在程序设计中，一些涉及底层的程序编写往往会围绕着文件描述符展开。但是文件描述符这一概念往往只适用于 UNIX、Linux 这样的操作系统。

我们可以这样使用这些文件描述符。例如默认使用终端的标准输入作为命令的输入和标准输出作为命令的输出：

cat # 按 Ctrl+C 退出

将 cat 的连续输出（heredoc 方式）重定向到一个文件：

mkdir Documents
cat > Documents/test.c <<EOF
#include <stdio.h>

int main()
{
    printf("hello world\n");
    return 0;
}

EOF

将一个文件作为命令的输入，标准输出作为命令的输出：

cat Documents/test.c

将 echo 命令通过管道传过来的数据作为 cat 命令的输入，将标准输出作为命令的输出：

echo 'hi' | cat

将 echo 命令的输出从默认的标准输出重定向到一个普通文件：

echo 'hello shiyanlou' > redirect
cat redirect


初学者这里要注意不要将管道和重定向混淆，管道默认是连接前一个命令的输出到下一个命令的输入，
而重定向通常是需要一个文件来建立两个命令的连接，你可以仔细体会一下上述第三个操作和最后两个操作的异同点。

2.标准错误重定向

重定向标准输出到文件，这是一个很实用的操作，另一个很实用的操作是将标准错误重定向，标准输出和标准错误都被指向伪终端的屏幕显示，
所以我们经常看到的一个命令的输出通常是同时包含了标准输出和标准错误的结果的。比如下面的操作：

# 使用cat 命令同时读取两个文件，其中一个存在，另一个不存在
cat Documents/test.c hello.c
# 你可以看到除了正确输出了前一个文件的内容，还在末尾出现了一条错误信息
# 下面我们将输出重定向到一个文件
cat Documents/test.c hello.c > somefile



遗憾的是，这里依然出现了那条错误信息，这正是因为如我上面说的那样，标准输出和标准错误虽然都指向终端屏幕，实际它们并不一样。
那有的时候我们就是要隐藏某些错误或者警告，那又该怎么做呢。这就需要用到我们前面讲的文件描述符了：

# 将标准错误重定向到标准输出，再将标准输出重定向到文件，注意要将重定向到文件写到前面
cat Documents/test.c hello.c >somefile  2>&1
# 或者只用bash提供的特殊的重定向符号"&"将标准错误和标准输出同时重定向到文件
cat Documents/test.c hello.c &>somefile#直接将cat显示出来的值重定向到somefile,若是没有hello.c文件，则将错误信息追加到somefile

注意你应该在输出重定向文件描述符前加上&，否则 shell 会当做重定向到一个文件名为 1 的文件中

!!!echo 和 cat 重定向的区别
echo 'adfsd' > a.py#将'adfsd'重定向到a.py
cat a.py b.py > c.py#将a.py ，b.py直接追加到c.py内，但若是无a.py或者b.py会出错

cat a.py b.py &> c.py#若无b.py,则将错误信息追加到c.py

3.永久重定向

你应该可以看出我们前面的重定向操作都只是临时性的，即只对当前命令有效，那如何做到永久有效呢，比如在一个脚本中，你需要某一部分的命令的输出全部进行重定向，难道要让你在每个命令上面加上临时重定向的操作嘛？

当然不需要，我们可以使用 exec 命令实现永久重定向。exec 命令的作用是使用指定的命令替换当前的 Shell，即使用一个进程替换当前进程，或者指定新的重定向：

# 先开启一个子 Shell
zsh
# 使用exec替换当前进程的重定向，将标准输出重定向到一个文件
exec 1>somefile
# 后面你执行的命令的输出都将被重定向到文件中，直到你退出当前子shell，或取消exec的重定向（后面将告诉你怎么做）
ls
exit
cat somefile


'day12正则表达式'

一个正则表达式通常被称为一个模式（pattern），为用来描述或者匹配一系列符合某个句法规则的字符串。
选择

| 竖直分隔符表示选择，例如 boy|girl 可以匹配 boy 或者 girl。
数量限定

数量限定除了我们举例用的 * 还有 + 加号 ? 问号，如果在一个模式中不加数量限定符则表示出现一次且仅出现一次：

    + 表示前面的字符必须出现至少一次(1 次或多次)，例如 goo+gle 可以匹配 gooogle，goooogle 等；
    ? 表示前面的字符最多出现一次（0 次或 1 次），例如，colou?r，可以匹配 color 或者 colour;
    * 星号代表前面的字符可以不出现，也可以出现一次或者多次（0 次、或 1 次、或多次），例如，0*42 可以匹配 42、042、0042、00042 等。

范围和优先级

() 圆括号可以用来定义模式字符串的范围和优先级，这可以简单的理解为是否将括号内的模式串作为一个整体。例如，gr(a|e)y 等价于 gray|grey，（这里体现了优先级，竖直分隔符用于选择 a 或者 e 而不是 gra 和 ey），(grand)?father 匹配 father 和 grandfather（这里体现了范围，? 将圆括号内容作为一个整体匹配）。
语法（部分）

正则表达式有多种不同的风格，下面列举一些常用的作为 PCRE 子集的适用于 perl 和 python 编程语言及 grep 或 egrep 的正则表达式匹配规则：

    PCRE（Perl Compatible Regular Expressions 中文含义：perl 语言兼容正则表达式）是一个用 C 语言编写的正则表达式函数库，由菲利普.海泽(Philip Hazel)编写。PCRE 是一个轻量级的函数库，比 Boost 之类的正则表达式库小得多。PCRE 十分易用，同时功能也很强大，性能超过了 POSIX 正则表达式库和一些经典的正则表达式库。

(由于 markdown 表格解析的问题，下面的竖直分隔符 | 用全角字符代替，实际使用时请换回半角字符。
字符  描述
\   将下一个字符标记为一个特殊字符、或一个原义字符。 例如 n 匹配字符 n。\n 匹配一个换行符。序列 \\ 匹配 \ 而 \( 则匹配 (。
^   匹配输入字符串的开始位置。
$   匹配输入字符串的结束位置。
{n}     n 是一个非负整数。匹配确定的 n 次。例如 o{2} 不能匹配 Bob 中的 o，但是能匹配 food 中的两个 o。
{n,}    n 是一个非负整数。至少匹配 n 次。例如 o{2,} 不能匹配 Bob 中的 o，但能匹配 foooood 中的所有 o。o{1,} 等价于 o+。o{0,} 则等价于 o*。
{n,m}   m 和 n 均为非负整数，其中 n<=m。最少匹配 n 次且最多匹配 m 次。例如，o{1,3} 将匹配 fooooood 中的前三个 o。o{0,1} 等价于 o?。请注意在逗号和两个数之间不能有空格。
*   匹配前面的子表达式零次或多次。例如，zo* 能匹配 z、zo 以及 zoo。* 等价于 {0,}。
+   匹配前面的子表达式一次或多次。例如，zo+ 能匹配 zo 以及 zoo，但不能匹配 z。+ 等价于 {1,}。
?   匹配前面的子表达式零次或一次。例如，do(es)? 可以匹配 do 或 does 中的 do。? 等价于 {0,1}。
?   当该字符紧跟在任何一个其他限制符（*，+，?，{n}，{n,}，{n,m}）后面时，匹配模式是非贪婪的。非贪婪模式尽可能少的匹配所搜索的字符串，而默认的贪婪模式则尽可能多的匹配所搜索的字符串。例如，对于字符串 oooo，o+? 将匹配单个 o，而 o+ 将匹配所有 o。
.   匹配除 \n 之外的任何单个字符。要匹配包括 \n 在内的任何字符，请使用类似 (.｜\n) 的模式。
(pattern)   匹配 pattern 并获取这一匹配的子字符串。该子字符串用于向后引用。要匹配圆括号字符，请使用 \( 和 \)。
x ｜ y   匹配 x 或 y。例如，“z ｜ food”能匹配 z 或 food。“(z ｜ f)ood”则匹配 zood 或 food。
[xyz]   字符集合（character class）。匹配所包含的任意一个字符。例如，[abc] 可以匹配 plain 中的 a。其中特殊字符仅有反斜线 \ 保持特殊含义，用于转义字符。其它特殊字符如星号、加号、各种括号等均作为普通字符。脱字符^如果出现在首位则表示负值字符集合；如果出现在字符串中间就仅作为普通字符。连字符 - 如果出现在字符串中间表示字符范围描述；如果出现在首位则仅作为普通字符。
[^xyz]  排除型（negate）字符集合。匹配未列出的任意字符。例如，[^abc] 可以匹配 plain 中的 plin。
[a-z]   字符范围。匹配指定范围内的任意字符。例如，[a-z] 可以匹配 a 到 z 范围内的任意小写字母字符。
[^a-z]  排除型的字符范围。匹配任何不在指定范围内的任意字符。例如，[^a-z] 可以匹配任何不在 a 到 z 范围内的任意字符。
优先级

优先级为从上到下从左到右，依次降低：
运算符     说明
\   转义符
()，(?:)，(?=)，[]     括号和中括号
*，+，?，{n}，{n,}，{n,m}    限定符
^，$，\ 任何元字符     定位点和序列
｜   选择

1.基本操作：

grep 命令用于打印输出文本中匹配的模式串，它使用正则表达式作为模式匹配的条件。grep 支持三种正则表达式引擎，分别用三个参数指定：
参数  说明
-E  POSIX 扩展正则表达式，ERE
-G  POSIX 基本正则表达式，BRE
-P  Perl 正则表达式，PCRE

不过在你没学过 perl 语言的大多数情况下你将只会使用到 ERE 和 BRE，
所以我们接下来的内容都不会讨论到 PCRE 中特有的一些正则表达式语法（它们之间大部分内容是存在交集的，所以你不用担心会遗漏多少重要内容）。

在通过grep命令使用正则表达式之前，先介绍一下它的常用参数：
参数  说明
-b  将二进制文件作为文本来进行匹配
-c  统计以模式匹配的数目
-i  忽略大小写
-n  显示匹配文本所在行的行号
-v  反选，输出不匹配行的内容
-r  递归匹配查找
-A n    n 为正整数，表示 after 的意思，除了列出匹配行之外，还列出后面的 n 行
-B n    n 为正整数，表示 before 的意思，除了列出匹配行之外，还列出前面的 n 行
--color=auto    将输出中的匹配项设置为自动颜色显示

    注：在大多数发行版中是默认设置了 grep 的颜色的，你可以通过参数指定或修改GREP_COLOR环境变量。


2 使用正则表达式
使用基本正则表达式，BRE

    位置

查找 /etc/group 文件中以 shiyanlou 为开头的行

grep 'shiyanlou' /etc/group
grep '^shiyanlou' /etc/group



    数量

# 将匹配以'z'开头以'o'结尾的所有字符串
echo 'zero\nzo\nzoo' | grep 'z.*o'
# 将匹配以'z'开头以'o'结尾，中间包含一个任意字符的字符串
echo 'zero\nzo\nzoo' | grep 'z.o'
# 将匹配以'z'开头，以任意多个'o'结尾的字符串
echo 'zero\nzo\nzoo' | grep 'zo*'

注意：其中 \n 为换行符



    选择

# grep默认是区分大小写的，这里将匹配所有的小写字母
echo '1234\nabcd' | grep '[a-z]'
# 将匹配所有的数字
echo '1234\nabcd' | grep '[0-9]'
# 将匹配所有的数字
echo '1234\nabcd' | grep '[[:digit:]]'
# 将匹配所有的小写字母
echo '1234\nabcd' | grep '[[:lower:]]'
# 将匹配所有的大写字母
echo '1234\nabcd' | grep '[[:upper:]]'
# 将匹配所有的字母和数字，包括0-9，a-z，A-Z
echo '1234\nabcd' | grep '[[:alnum:]]'
# 将匹配所有的字母
echo '1234\nabcd' | grep '[[:alpha:]]'



下面包含完整的特殊符号及说明：
特殊符号    说明
[:alnum:]   代表英文大小写字母及数字，亦即 0-9，A-Z，a-z
[:alpha:]   代表任何英文大小写字母，亦即 A-Z，a-z
[:blank:]   代表空白键与 [Tab] 按键两者
[:cntrl:]   代表键盘上面的控制按键，亦即包括 CR，LF，Tab，Del...
[:digit:]   代表数字而已，亦即 0-9
[:graph:]   除了空白字节（空白键与 [Tab] 按键）外的其他所有按键
[:lower:]   代表小写字母，亦即 a-z
[:print:]   代表任何可以被列印出来的字符
[:punct:]   代表标点符号（punctuation symbol），即："，'，?，!，;，:，#，$...
[:upper:]   代表大写字母，亦即 A-Z
[:space:]   任何会产生空白的字符，包括空格键，[Tab]，CR 等等
[:xdigit:]  代表 16 进位的数字类型，因此包括： 0-9，A-F，a-f 的数字与字节

    注意：之所以要使用特殊符号，是因为上面的 [a-z] 不是在所有情况下都管用，这还与主机当前的语系有关，即设置在 LANG 环境变量的值，zh_CN.UTF-8 的话 [a-z]，即为所有小写字母，其它语系可能是大小写交替的如，"a A b B...z Z"，[a-z] 中就可能包含大写字母。所以在使用 [a-z] 时请确保当前语系的影响，使用 [:lower:] 则不会有这个问题。

# 排除字符
echo 'geek\ngood' | grep '[^o]'

    当 ^ 放到中括号内为排除字符，否则表示行首。

使用扩展正则表达式，ERE

要通过 grep 使用扩展正则表达式需要加上 -E 参数，或使用 egrep。

    数量

# 只匹配"zo"
echo 'zero\nzo\nzoo' | grep -E 'zo{1}'
# 匹配以"zo"开头的所有单词
echo 'zero\nzo\nzoo' | grep -E 'zo{1,}'

    推荐掌握 {n,m} 即可 +，?，* 这几个不太直观，且容易弄混淆。

    选择

# 匹配"www.shiyanlou.com"和"www.google.com"
echo 'www.shiyanlou.com\nwww.baidu.com\nwww.google.com' | grep -E 'www\.(shiyanlou|google)\.com'
# 或者匹配不包含"baidu"的内容
echo 'www.shiyanlou.com\nwww.baidu.com\nwww.google.com' | grep -Ev 'www\.baidu\.com'

    因为 . 号有特殊含义，所以需要转义。

2.sed编辑器

sed 工具在 man 手册里面的全名为"sed - stream editor for filtering and transforming text "，意即，用于过滤和转换文本的流编辑器。

在 Linux/UNIX 的世界里敢称为编辑器的工具，大都非等闲之辈，比如前面的 vi/vim（编辑器之神），emacs（神的编辑器），gedit 这些编辑器。sed 与上述的最大不同之处在于它是一个非交互式的编辑器，下面我们就开始介绍 sed 这个编辑器。

sed 命令基本格式：

sed [参数]... [执行命令] [输入文件]...
# 形如：
$ sed -i 's/sad/happy/' test # 表示将test文件中的"sad"替换为"happy"

参数  说明
-n  安静模式，只打印受影响的行，默认打印输入数据的全部内容
-e  用于在脚本中添加多个执行命令一次执行，在命令行中执行多个命令通常不需要加该参数
-f filename     指定执行 filename 文件中的命令
-r  使用扩展正则表达式，默认为标准正则表达式
-i  将直接修改输入文件内容，而不是打印到标准输出设备


.sed 执行命令格式：

[n1][,n2]command
[n1][~step]command

其中一些命令可以在后面加上作用范围，形如：

sed -i 's/sad/happy/g' test # g 表示全局范围
sed -i 's/sad/happy/4' test # 4 表示指定行中的第四个匹配字符串

其中 n1,n2 表示输入内容的行号，它们之间为 , 逗号则表示从 n1 到 n2 行，如果为 ~ 波浪号则表示从 n1 开始以 step 为步进的所有行；command 为执行动作，下面为一些常用动作指令：
命令  说明
s   行内替换
c   整行替换
a   插入到指定行的后面
i   插入到指定行的前面
p   打印指定行，通常与 -n 参数配合使用
d   删除指定行

# day13软件学习
1.apt-get

.软件安装：
apt-get 是用于处理 apt包的公用程序集，我们可以用它来在线安装、卸载和升级软件包等，下面列出一些 apt-get 包含的常用的一些工具：
工具  说明
install     其后加上软件包名，用于安装一个软件包
update  从软件源镜像服务器上下载/更新用于更新本地软件源的软件包列表
upgrade     升级本地可更新的全部软件包，但存在依赖问题时将不会升级，通常会在更新之前执行一次 update
dist-upgrade    解决依赖关系并升级（存在一定危险性）
remove  移除已安装的软件包，包括与被移除软件包有依赖关系的软件包，但不包含软件包的配置文件
autoremove  移除之前被其他软件包依赖，但现在不再被使用的软件包
purge   与 remove 相同，但会完全移除软件包，包含其配置文件
clean   移除下载到本地的已经安装的软件包，默认保存在 /var/cache/apt/archives/
autoclean   移除已安装的软件的旧版本软件包

下面是一些apt-get常用的参数：
参数  说明
-y  自动回应是否安装软件包的选项，在一些自动化安装脚本中使用这个参数将十分有用
-s  模拟安装
-q  静默安装方式，指定多个 q 或者 -q=#，# 表示数字，用于设定静默级别，这在你不想要在安装软件包时屏幕输出过多时很有用
-f  修复损坏的依赖关系#这一步很重要，否则无法安装成功
-d  只下载不安装
--reinstall     重新安装已经安装但可能存在问题的软件包
--install-suggests  同时安装 APT 给出的建议安装的软件包

#重新安装
sudo apt-get --reinstall install <packagename>
# 更新软件源
sudo apt-get update

# 升级没有依赖问题的软件包
sudo apt-get upgrade

# 升级并解决依赖关系
sudo apt-get dist-upgrade


.软件卸载


sudo apt-get remove w3m
或者，你可以执行

# 不保留配置文件的移除
sudo apt-get purge w3m
# 或者
sudo apt-get --purge remove w3m
# 移除不再需要的被依赖的软件包
sudo apt-get autoremove

!!新版中-get都可以删除

.软件搜索

当自己刚知道了一个软件，想下载使用，需要确认软件仓库里面有没有，就需要用到搜索功能了，命令如下：

sudo apt-cache search softname1 softname2 softname3……
==sudo apt search softname1，softname2
apt-cache 命令则是针对本地数据进行相关操作的工具，search 顾名思义在本地的数据库中寻找有关 softname1，softname2 相关软件的信息。现在我们试试搜索一下之前我们安装的软件 w3m，如图：


结果显示了 4 个 w3m 相关的软件，并且有相关软件的简介。

关于在线安装的内容我们就介绍这么多，想了解更多关于 APT 的内容，你可以参考：


本节讲解如何使用 dpkg 从本地磁盘安装 deb 软件包。

2.dpkg 介绍(debian package)

    dpkg 是 Debian 软件包管理器的基础，它被伊恩·默多克创建于 1993 年。dpkg 与 RPM 十分相似，同样被用于安装、卸载和供给和 .deb 软件包相关的信息。

    dpkg 本身是一个底层的工具。上层的工具，像是 APT，被用于从远程获取软件包以及处理复杂的软件包关系。"dpkg"是"Debian Package"的简写。

我们经常可以在网络上见到以deb形式打包的软件包，就需要使用dpkg命令来安装。

dpkg常用参数介绍：
参数  说明
-i  安装指定 deb 包
-R  后面加上目录名，用于安装该目录下的所有 deb 安装包
-r  remove，移除某个已安装的软件包
-I  显示 deb 包文件的信息
-s  显示已安装软件的信息
-S  搜索已安装的软件包
-L  显示已安装软件包的目录信息

我们先使用apt-get加上-d参数只下载不安装，下载 emacs 编辑器的 deb 包：

sudo apt-get update
sudo apt-get -d install -y emacs

下载完成后，我们可以查看/var/cache/apt/archives/目录下的内容，如下图：



然后我们将第一个deb拷贝到 /home/shiyanlou 目录下，并使用dpkg安装

cp /var/cache/apt/archives/emacs24_24.5+1-6ubuntu1.1_amd64.deb ~
# 安装之前参看deb包的信息
sudo dpkg -I emacs24_24.5+1-6ubuntu1.1_amd64.deb

如你所见，这个包还额外依赖了一些软件包，这意味着，如果主机目前没有这些被依赖的软件包，直接使用 dpkg 安装可能会存在一些问题，因为dpkg并不能为你解决依赖关系。

# 使用dpkg安装
sudo dpkg -i emacs24_24.5+1-6ubuntu1.1_amd64.deb

跟前面预料的一样，这里你可能出现了一些错误：



我们将如何解决这个错误呢？这就要用到apt-get了，使用它的-f参数了，修复依赖关系的安装

sudo apt-get update
sudo apt-get -f install -y

没有任何错误，这样我们就安装成功了，然后你可以运行 emacs 程序

3.查看已安装软件包的安装目录

如果你依然在纠结到底 linux 将软件安装到了什么地方，那么很幸运你将可以通过dpkg找到答案

使用dpkg -L查看deb包目录信息

sudo dpkg -L emacs24


4.从二进制包安装

二进制包的安装比较简单，我们需要做的只是将从网络上下载的二进制包解压后放到合适的目录，然后将包含可执行的主程序文件的目录添加进PATH环境变量即可，如果你不知道该放到什么位置，请重新复习第四节关于 Linux 目录结构的内容。

5.垃圾清理
    1.sudo apt-get clean

    　　在网络连接正常的情况下，我们执行软件安装命令，软件安装结束后，以 .deb 为后缀的软件包就不再需要了。
    这种情况和 Windows 平台、手机的安卓平台上的情况是类似的。我们可以定期对这些不再需要的软件安装包进行清理。 

    　　Ctrl + Alt + t 组合键调出终端，键入以下命令并执行：
    　　如图所示，它实际上删除了 /var/cache/apt/archives 目录下所有以 .deb 结尾的文件。
    利用命令清理Linux系统垃圾文件优化技巧
    2.autoclean 命令删除不再可用的软件安装包。
    　该命令与 clean 类似，只不过它有选择地删除软件包：
    那些不再可用的安装包(比如，你再也不能够从软件仓库中下载到该软件包的当前版本、或更新版本)。
    　　在终端内执行：
    　　sudo apt-get autoclean
    　　即可删除不再可用的软件安装包。
    3.remove 命令删除特定软件。
    类似于 Windows 控制面板中的“程序卸载命令”，
    remove 命令可以删除软件。sudo apt-get remove 软件名

    4.用purge 命令删除软件“残余”。
    purge 命令是 remove 命令的另一个版本，它可以在删除软件本身的同时，删除软件包的残余设置。类似于 Windows 环境下删除软件后的“软件残余”清理。
    sudo apt-get purge 软件名
    将删除相关软件，同时删除该软件的配置文件。
    5.autoremove 命令删除不再需要的依赖软件包。
    比如，我们安装软件 A，但是 A 依赖软件包 B，当 A 被安装的过程中，B 也必须被安装。
    有一天，我们不再需要软件 A 并删除了它，我们就可以用 autoremove 命令，删除当初为了满足 A 的依赖关系而安装的软件 B。
    sudo apt-get autoremove
6.查找软件名
    1.rpm包安装的，可以用rpm -qa看到，如果要查找某软件包是否安装，用 rpm -qa | grep “软件或者包的名字”。
    [root@hexuweb102 ~] rpm -qa | grep ruby

    2、以deb包安装的，可以用dpkg -l能看到。如果是查找指定软件包，用dpkg -l | grep “软件或者包的名字”；
    [root@hexuweb102~]dpkg-l|grep ruby

    3、yum方法安装的，可以用yum list installed查找，如果是查找指定包，命令后加 | grep “软件名或者包名”；
    [root@hexuweb102 ~] yum list installed | grep ruby


'day14进程'

1.进程的分类

首先程序与进程是什么？程序与进程又有什么区别？

    程序（procedure）：不太精确地说，程序就是执行一系列有逻辑、有顺序结构的指令，帮我们达成某个结果。就如我们去餐馆，给服务员说我要牛肉盖浇饭，她执行了做牛肉盖浇饭这么一个程序，最后我们得到了这么一盘牛肉盖浇饭。它需要去执行，不然它就像一本武功秘籍，放在那里等人翻看。

    进程（process）：进程是程序在一个数据集合上的一次执行过程，在早期的 UNIX、Linux 2.4 及更早的版本中，它是系统进行资源分配和调度的独立基本单位。同上一个例子，就如我们去了餐馆，给服务员说我要牛肉盖浇饭，她执行了做牛肉盖浇饭这么一个程序，而里面做饭的是一个进程，做牛肉汤汁的是一个进程，把牛肉汤汁与饭混合在一起的是一个进程，把饭端上桌的是一个进程。它就像是我们在看武功秘籍这么一个过程，然后一个篇章一个篇章地去练。

#程序是一系列有逻辑的指令，进程是程序中的一次执行过程
简单来说，程序是为了完成某种任务而设计的软件，比如 vim 是程序。什么是进程呢？进程就是运行中的程序。

程序只是一些列指令的集合，是一个静止的实体，而进程不同，进程有以下的特性：

    动态性：进程的实质是一次程序执行的过程，有创建、撤销等状态的变化。而程序是一个静态的实体。
    并发性：进程可以做到在一个时间段内，有多个程序在运行中。程序只是静态的实体，所以不存在并发性。
    独立性：进程可以独立分配资源，独立接受调度，独立地运行。
    异步性：进程以不可预知的速度向前推进。
    结构性：进程拥有代码段、数据段、PCB（进程控制块，进程存在的唯一标志）。也正是因为有结构性，进程才可以做到独立地运行。

    并发：在一个时间段内，宏观来看有多个程序都在活动，有条不紊的执行（每一瞬间只有一个在执行，只是在一段时间有多个程序都执行过）

    并行：在每一个瞬间，都有多个程序都在同时执行，这个必须有多个 CPU 才行

引入进程是因为传统意义上的程序已经不足以描述 OS 中各种活动之间的动态性、并发性、独立性还有相互制约性。程序就像一个公司，只是一些证书，文件的堆积（静态实体）。而当公司运作起来就有各个部门的区分，财务部，技术部，销售部等等，就像各个进程，各个部门之间可以独立运作，也可以有交互（独立性、并发性）。

而随着程序的发展越做越大，又会继续细分，从而引入了线程的概念，当代多数操作系统、Linux 2.6 及更新的版本中，进程本身不是基本运行单位，而是线程的容器。就像上述所说的，每个部门又会细分为各个工作小组（线程），而工作小组需要的资源需要向上级（进程）申请。

    线程（thread）是操作系统能够进行运算调度的最小单位。它被包含在进程之中，是进程中的实际运作单位。一条线程指的是进程中一个单一顺序的控制流，一个进程中可以并发多个线程，每条线程并行执行不同的任务。因为线程中几乎不包含系统资源，所以执行更快、更有效率。

简而言之，一个程序至少有一个进程，一个进程至少有一个线程。线程的划分尺度小于进程，使得多线程程序的并发性高。另外，进程在执行过程中拥有独立的内存单元，而多个线程共享内存，从而极大地提高了程序的运行效率。就如下图所示：

---------------------------------------------------------------------------
大概明白进程是个什么样的存在后，我们需要进一步了解的就是进程分类。可以从两个角度来分：

    以进程的功能与服务的对象来分；
    以应用程序的服务类型来分；

第一个角度来看，我们可以分为用户进程与系统进程：

    用户进程：通过执行用户程序、应用程序或称之为内核之外的系统程序而产生的进程，此类进程可以在用户的控制下运行或关闭。
    系统进程：通过执行系统内核程序而产生的进程，比如可以执行内存资源分配和进程切换等相对底层的工作；而且该进程的运行不受用户的干预，即使是 root 用户也不能干预系统进程的运行。

第二角度来看，我们可以将进程分为交互进程、批处理进程、守护进程：

    交互进程：由一个 shell 终端启动的进程，在执行过程中，需要与用户进行交互操作，可以运行于前台，也可以运行在后台。
    批处理进程：该进程是一个进程集合，负责按顺序启动其他的进程。
    守护进程：守护进程是一直运行的一种进程，在 Linux 系统启动时启动，在系统关闭时终止。它们独立于控制终端并且周期性的执行某种任务或等待处理某些发生的事件。例如 httpd 进程，一直处于运行状态，等待用户的访问。还有经常用的 cron（在 centOS 系列为 crond）进程，这个进程为 crontab 的守护进程，可以周期性的执行用户设定的某些任务。

2.进程的衍生

进程有这么多的种类，那么进程之间定是有相关性的，而这些有关联性的进程又是如何产生的，如何衍生的？

就比如我们启动了终端，就是启动了一个 bash 进程，我们可以在 bash 中再输入 bash 则会再启动一个 bash 的进程，此时第二个 bash 进程就是由第一个 bash 进程创建出来的，他们之间又是个什么关系？

我们一般称呼第一个 bash 进程是第二 bash 进程的父进程，第二 bash 进程是第一个 bash 进程的子进程，这层关系是如何得来的呢？

关于父进程与子进程便会提及这两个系统调用 fork() 与 exec()

    fork-exec是由 Dennis M. Ritchie 创造的

    fork() 是一个系统调用（system call），它的主要作用就是为当前的进程创建一个新的进程，这个新的进程就是它的子进程，这个子进程除了父进程的返回值和 PID 以外其他的都一模一样，如进程的执行代码段，内存信息，文件描述，寄存器状态等等

    exec() 也是系统调用，作用是切换子进程中的执行程序也就是替换其从父进程复制过来的代码段与数据段

子进程就是父进程通过系统调用 fork() 而产生的复制品，fork() 就是把父进程的 PCB 等进程的数据结构信息直接复制过来，只是修改了 PID，所以一模一样，只有在执行 exec() 之后才会不同，而早先的 fork() 比较消耗资源后来进化成 vfork()，效率高了不少，感兴趣的同学可以查查为什么。

这就是子进程产生的由来。简单的实现逻辑就如下方所示：

pid_t p;

p = fork();
if (p == (pid_t) -1)
        /* ERROR */
else if (p == 0)
        /* CHILD */
else
        /* PARENT */

既然子进程是通过父进程而衍生出来的，那么子进程的退出与资源的回收定然与父进程有很大的相关性。当一个子进程要正常的终止运行时，或者该进程结束时它的主函数 main() 会执行 exit(n); 或者 return n，这里的返回值 n 是一个信号，系统会把这个 SIGCHLD 信号传给其父进程，当然若是异常终止也往往是因为这个信号。

在将要结束时的子进程代码执行部分已经结束执行了，系统的资源也基本归还给系统了，但若是其进程的进程控制块（PCB）仍驻留在内存中，而它的 PCB 还在，代表这个进程还存在（因为 PCB 就是进程存在的唯一标志，里面有 PID 等消息），并没有消亡，这样的进程称之为僵尸进程（Zombie）。

如图中第四列标题是 S，S 表示的是进程的状态，而在下属的第三行的 Z 表示的是 Zombie 的意思。（ ps 命令将在后续详解）


正常情况下，父进程会收到两个返回值：exit code（SIGCHLD 信号）与 reason for termination 。之后，父进程会使用 wait(&status) 系统调用以获取子进程的退出状态，然后内核就可以从内存中释放已结束的子进程的 PCB；而如若父进程没有这么做的话，子进程的 PCB 就会一直驻留在内存中，一直留在系统中成为僵尸进程（Zombie）。

虽然僵尸进程是已经放弃了几乎所有内存空间，没有任何可执行代码，也不能被调度，在进程列表中保留一个位置，记载该进程的退出状态等信息供其父进程收集，从而释放它。但是 Linux 系统中能使用的 PID 是有限的，如果系统中存在有大量的僵尸进程，系统将会因为没有可用的 PID 从而导致不能产生新的进程。

另外如果父进程结束（非正常的结束），未能及时收回子进程，子进程仍在运行，这样的子进程称之为孤儿进程。在 Linux 系统中，孤儿进程一般会被 init 进程所“收养”，成为 init 的子进程。由 init 来做善后处理，所以它并不至于像僵尸进程那样无人问津，不管不顾，大量存在会有危害。

进程 0 是系统引导时创建的一个特殊进程，也称之为内核初始化，其最后一个动作就是调用 fork() 创建出一个子进程运行 /sbin/init 可执行文件，而该进程就是 PID=1 的进程 1，而进程 0 就转为交换进程（也被称为空闲进程），进程 1 （init 进程）是第一个用户态的进程，再由它不断调用 fork() 来创建系统里其他的进程，所以它是所有进程的父进程或者祖先进程。同时它是一个守护程序，直到计算机关机才会停止。

通过以下的命令我们可以很明显的看到这样的结构

pstree


或者从此图我们可以更加形象的看清子父进程的关系


通过以上的显示结果我们可以看的很清楚，init 为所有进程的父进程或者说是祖先进程

我们还可以使用这样一个命令来看，其中 pid 就是该进程的一个唯一编号，ppid 就是该进程的父进程的 pid，command 表示的是该进程通过执行什么样的命令或者脚本而产生的

ps －fxo user,ppid,pid,pgid,command


可以在图中看见我们执行的 ps 就是由 zsh 通过 fork-exec 创建的子进程而执行的

使用这样的一个命令我们也能清楚的看见 init 如上文所说是由进程 0 这个初始化进程来创建出来的子进程，而其他的进程基本是由 init 创建的子进程，或者是由它的子进程创建出来的子进程。所以 init 是用户进程的第一个进程也是所有用户进程的父进程或者祖先进程。（ps 命令将在后续课程详解）

就像一个树状图，而 init 进程就是这棵树的根，其他进程由根不断的发散，开枝散叶


3.进程组和session

每一个进程都会是一个进程组的成员，而且这个进程组是唯一存在的，他们是依靠 PGID（process group ID）来区别的，而每当一个进程被创建的时候，它便会成为其父进程所在组中的一员。

一般情况，进程组的 PGID 等同于进程组的第一个成员的 PID，并且这样的进程称为该进程组的领导者，也就是领导进程，进程一般通过使用 getpgrp() 系统调用来寻找其所在组的 PGID，领导进程可以先终结，此时进程组依然存在，并持有相同的 PGID，直到进程组中最后一个进程终结。

与进程组类似，每当一个进程被创建的时候，它便会成为其父进程所在 Session 中的一员，每一个进程组都会在一个 Session 中，并且这个 Session 是唯一存在的，

Session 主要是针对一个 tty 建立，Session 中的每个进程都称为一个工作(job)。每个会话可以连接一个终端(control terminal)。当控制终端有输入输出时，都传递给该会话的前台进程组。Session 意义在于将多个 jobs 囊括在一个终端，并取其中的一个 job 作为前台，来直接接收该终端的输入输出以及终端信号。 其他 jobs 在后台运行。

    前台（foreground）就是在终端中运行，能与你有交互的

    后台（background）就是在终端中运行，但是你并不能与其任何的交互，也不会显示其执行的过程

-----------
4.工作管理：
bash(Bourne-Again shell)支持工作控制（job control），而 sh（Bourne shell）并不支持。

并且每个终端或者说 bash 只能管理当前终端中的 job，不能管理其他终端中的 job。比如我当前存在两个 bash 分别为 bash1、bash2，bash1 只能管理其自己里面的 job 并不能管理 bash2 里面的 job

我们都知道当一个进程在前台运作时我们可以用 ctrl + c 来终止它，但是若是在后台的话就不行了。

我们可以通过 & 这个符号，让我们的命令在后台中运行：

ls &我们可以通过

用jobs来查看后台的命令


# 'day15'


wine ——简介

能够在多种 POSIX-compliant 操作系统（诸如 Linux，Mac OSX 及 BSD 等）上运行 Windows 应用的兼容层

 
wine——安装

方式一：在Ubuntu中安装wine，只需要一个指令就可完成安装：

sudo apt-get install wine 

请注意：由这种方法安装的Wine通常不是最新版本。要获取最新版，请使用由官方网站上下载安装包、添加ppa源（针对Ubuntu用户）等方法或直接编译安装
 
wine——命令

1、wine安装软件的三种方式：

    wine  xxx.exe
    ./ xxx.exe
    直接双击软件包

2、wine常用命令：

    winecfg               （wine的设置~）
    wine  taskmgr     （任务管理器）
    wine  uninstaller （卸载软件）
    wine  regedit      （注册表）
    wine  notepad    （记事本）
    wineboot            （ 重启wine）
##wine安装的文件夹在home/kim的隐藏文件中
 
微信安装

1、在已经安装好wine的前提下；点击链接（https://weixin.qq.com/）下载微信windows安装包；点开之后如下图所示

 

2、在安装包WeChatSetup.exe被下载存放的目录中打开终端，输入下面的指令就可以开始安装微信；

wine WeChatSetup.exe

3、接下来按照提示步骤操作即可成功安装微信；

 
QQ安装

1、在已经安装好wine的前提下；点击链接（https://im.qq.com/pcqq/）下载QQ的windows版本安装包；点开之后如下图所示

2、在安装包PCQQ2021.exe被下载存放的目录中打开终端，输入下面的指令就可以开始安装QQ；

wine PCQQ2021.exe

3、接下来按照提示步骤操作即可成功安装QQ；

# 其余问题
1. 关于内存的使用情况和电脑的CPU的查看
   * df -h:查看磁盘使用状况
   * top:看cpu使用情况
   * free -g:看内存使用情况 
   * 