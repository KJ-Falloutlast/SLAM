# 1.vim的模式
基本上 vi/vim 共分为三种模式，分别是命令模式（Command mode），输入模式（Insert mode）和底线命令模式（Last line mode）。 这三种模式的作用分别是：

## 1.命令模式：
用户刚刚启动 vi/vim，便进入了命令模式。

此状态下敲击键盘动作会被Vim识别为命令，而非输入字符。比如我们此时按下i，并不会输入一个字符，i被当作了一个命令。

以下是常用的几个命令：

i 切换到输入模式，以输入字符。
x 删除当前光标所在处的字符。
: 切换到底线命令模式，以在最底一行输入命令。
若想要编辑文本：启动Vim，进入了命令模式，按下i，切换到输入模式。

命令模式只有一些最基本的命令，因此仍要依靠底线命令模式输入更多命令。

## 2.输入模式
在命令模式下按下i就进入了输入模式。

在输入模式中，可以使用以下按键：

字符按键以及Shift组合，输入字符
ENTER，回车键，换行
BACK SPACE，退格键，删除光标前一个字符
DEL，删除键，删除光标后一个字符
方向键，在文本中移动光标
HOME/END，移动光标到行首/行尾
Page Up/Page Down，上/下翻页
Insert，切换光标为输入/替换模式，光标将变成竖线/下划线
ESC，退出输入模式，切换到命令模式

## 3.底线命令模式
在命令模式下按下:（英文冒号）就进入了底线命令模式。

底线命令模式可以输入单个或多个字符的命令，可用的命令非常多。

在底线命令模式中，基本的命令有（已经省略了冒号）：

q 退出程序
w 保存文件
按ESC键可随时退出底线命令模式。




宏命令(Macros)

高级一些的编辑器，都会包含宏功能，vim当然不能缺少了，在vim中使用宏是非常方便的：

 

:qx 

开始记录宏，并将结果存入寄存器x 

q 

退出记录模式 

@x 

播放记录在x寄存器中的宏命令 

稍微解释一下，当在normal模式下输入:qx后，你对文本的所有编辑动作将会被记录下来，再次输入q即退出了记录模式，然后输入@x对刚才记录下来的命令进行重复，此命令后可跟数字，表示要重复多少次，比如@x20，可以重复20次。这个在文本的批处理中是非常有用的。

同时编辑多个文件

在vim众多的插件中，有一个叫minibuffer的插件，就是下面所说的标签页功能了，可以支持同时编辑多个文件。

标签命令

 

:tabe fn 

在一个新的标签页中编辑文件fn 

gt 

切换到下一个标签页 

gT 

切换到上一个标签页 

:tabr 

切换到第一个标签页 

:tabl 

切换到最后一个标签页 

:tabm [N] 

把当前tab移动到第N个tab之后 

对，正如你所想象的那样，跟eclipse, ue等的标签页是一个意思！

窗口命令

 

ctrl+w s 

水平分割窗口 

ctrl+w w 

切换窗口 

ctrl+w q 

退出当前窗口(由于同时有多个文件，此命令不会影响其他窗口) 

ctrl+w v 

垂直分割窗口 

其他

vim在保存之前不会对文件做实际的修改，只是加载到缓冲区中，对文件的编辑其实是对缓冲区的编辑，直到:w时才会存入物理文件。

 

:e file 

把file加载到新的缓冲区中 

:bn 

跳转到下一个缓冲区 

:bd 

删除缓冲区(关闭文件) 

:sp fn 

分割窗口，并将fn加载到新的窗口中 

退出编辑器

 

:w 

将缓冲区写入文件，即保存修改 

:wq 

保存修改并退出 

:x 

保存修改并退出 

:q 

退出，如果对缓冲区进行过修改，则会提示 

:q! 

强制退出，放弃修改 

查找替换

 

/pattern 

向后搜索字符串pattern 

?pattern 

向前搜索字符串pattern 

n 

下一个匹配(如果是/搜索，则是向下的下一个，?搜索则是向上的下一个) 

N 

上一个匹配(同上) 

:%s/old/new/g 

搜索整个文件，将所有的old替换为new 

:%s/old/new/gc 

搜索整个文件，将所有的old替换为new，每次都要你确认是否替换 

复制粘贴

dd 

删除光标所在行 

dw 

删除一个字(word) 

x 

删除当前字符 

X 

删除前一个字符 

D 

删除到行末 

yy 

复制一行，此命令前可跟数字，标识复制多行，如6yy，表示从当前行开始复制6行 

yw 

复制一个字 

y$ 

复制到行末 

p 

粘贴粘贴板的内容到当前行的下面 

P 

粘贴粘贴板的内容到当前行的上面 

]p 

有缩进的粘贴，vim会自动调节代码的缩进 

"a 

将内容放入/存入a寄存器，可以支持多粘贴板 

附：比如常用的一个寄存器就是系统寄存器，名称为+，所以从系统粘贴板粘贴到vim中的命令为"+p,注意此处的+不表示操作符，二十一个寄存器。

移动光标

在vim中移动光标跟其他的编辑器中有很大的区别，不过一旦学会了，就会飞速 的在文本中移动了。

 

h,j,k,l 

上，下，左，右 

ctrl-f 

上翻一页 

ctrl-b 

下翻一页 

% 

跳到与当前括号匹配的括号处，如当前在{，则跳转到与之匹配的}处 

w 

跳到下一个字首，按标点或单词分割 

W 

跳到下一个字首，长跳，如end-of-line被认为是一个字 

e 

跳到下一个字尾 

E 

跳到下一个字尾，长跳 

b 

跳到上一个字 

B 

跳到上一个字，长跳 

0 

跳至行首，不管有无缩进，就是跳到第0个字符 

^ 

跳至行首的第一个字符 

$ 

跳至行尾 

gg 

跳至文件的第一行 

gd 

跳至当前光标所在的变量的声明处 

[N]G 

跳到第N行，如0G，就等价于gg，100G就是第100行 

fx 

在当前行中找x字符，找到了就跳转至 

; 

重复上一个f命令，而不用重复的输入fx 

tx 

与fx类似，但是只是跳转到x的前一个字符处 

Fx 

跟fx的方向相反 

),( 

跳转到上/下一个语句 

* 

查找光标所在处的单词，向下查找 

# 

查找光标所在处的单词，向上查找 

`. 

跳转至上次编辑位置 

在屏幕上移动

 

H 

移动光标到当前屏幕上最上边的一行 

M 

移动光标到当前屏幕上中间的一行 

L 

移动光标到当前屏幕上最下边的一行 

书签

 

ma 

把当前位置存成标签a 

`a 

跳转到标签a处 

 编辑

 

r 

替换一个字符 

J 

将下一行和当前行连接为一行 

cc 

删除当前行并进入编辑模式 

cw 

删除当前字，并进入编辑模式 

c$ 

擦除从当前位置至行末的内容，并进入编辑模式 

s 

删除当前字符并进入编辑模式 

S 

删除光标所在行并进入编辑模式 

xp 

交换当前字符和下一个字符 

u 

撤销 

ctrl+r 

重做 

. 

重复上一个编辑命令 

~ 

切换大小写，当前字符 

g~iw 

切换当前字的大小写 

gUiw 

将当前字变成大写 

guiw 

将当前字变成小写 

>> 

将当前行右移一个单位 

<< 

将当前行左移一个单位(一个tab符) 

== 

自动缩进当前行 

 

插入模式

 

i 

从当前光标处进入插入模式 

I 

进入插入模式，并置光标于行首 

a 

追加模式，置光标于当前光标之后 

A 

追加模式，置光标于行末 

o 

在当前行之下新加一行，并进入插入模式 

O 

在当前行之上新加一行，并进入插入模式 

Esc 

退出插入模式 

可视模式

标记文本

v 

进入可视模式，单字符模式 

V 

进入可视模式，行模式 

ctrl+v 

进入可视模式，列模式 ，类似于UE的列模式 

o 

跳转光标到选中块的另一个端点 

U 

将选中块中的内容转成大写 

O 

跳转光标到块的另一个端点 

aw 

选中一个字 

ab 

选中括号中的所有内容，包括括号本身 

aB 

选中{}括号中的所有内容 

ib 

选中括号中的内容，不含括号 

iB 

选中{}中的内容，不含{} 

对标记进行动作

 

> 

块右移 

< 

块左移 

y 

复制块 

d 

删除块 

~ 

切换块中内容的大小写 

 

好了，这张简表就说到这里，当然它涵盖的范围有限，但是正如片头说的那样，vim的强大之处在于这些命令可以组合起来使用，那样才能体现出其强大的编辑功能。我在网上找到的这个文档也顺便贴出来，大家可以同时参考。如果有机会，我尽量找些例子来说明这些命令在实际中的用法，那样才可以更好的使用它，提高我们的工作效率。

VIM中常用的替换模式总结。


1，简单替换表达式

替换命令可以在全文中用一个单词替换另一个单词：

:%s/four/4/g


“%” 范围前缀表示在所有行中执行替换。最后的 “g” 标记表示替换行中的所有匹配点。如果仅仅对当前行进行操作，那么只要去掉%即可

如果你有一个象 “thirtyfour” 这样的单词，上面的命令会出错。这种情况下，这个单词会被替换成”thirty4″。要解决这个问题，用 “\<” 来指定匹配单词开头：

:%s/\<four/4/g

显然，这样在处理 “fourty” 的时候还是会出错。用 “\>” 来解决这个问题：

:%s/\<four\>/4/g

如果你在编码，你可能只想替换注释中的 “four”，而保留代码中的。由于这很难指定，可以在替换命令中加一个 “c” 标记，这样，Vim 会在每次替换前提示你：

:%s/\<four\>/4/gc

2，删除多余的空格

要删除这些每行后面多余的空格，可以执行如下命令：

:%s/\s\+$//

命令前面指明范围是 “%”，所以这会作用于整个文件。”substitute” 命令的匹配模式是

“\s\+$”。这表示行末（$）前的一个或者多个（\+）空格（\s）。替换命令的 “to” 部分是空的：”//”。这样就会删除那些匹配的空白字符。

3，匹配重复性模式

星号项 “*” 规定在它前面的项可以重复任意次。因此:

/a*

匹配 “a”，”aa”，”aaa”，等等。但也匹配 “” (空字串)，因为零次也包含在内。星号 “*” 仅仅应用于那个紧邻在它前面的项。因此 “ab*” 匹配 “a”，”ab”，”abb”,”abbb”，等等。如要多次重复整个字符串，那么该字符串必须被组成一个项。组成一项的方法就是在它前面加 “\(”，后面加 “\)”。因此这个命令:

/*

匹配: “ab”，”abab”，”ababab”，等等。而且也匹配 “”。

要避免匹配空字串，使用 “\+”。这表示前面一项可以被匹配一次或多次。

/ab\+

匹配 “ab”，”abb”，”abbb”，等等。它不匹配 后面没有跟随 “b” 的 “a”。

要匹配一个可选项，用 “\=”。 例如:

/folders\=

匹配 “folder” 和 “folders”。

4，指定重复次数

要匹配某一项的特定次数重复，使用 “\{n,m}” 这样的形式。其中 “n” 和 “m” 都是数字。在它前面的那个项将被重复 “n” 到 “m” 次 (|inclusive| 包含 “n” 和 “m”)。例如:

/ab\{3,5}

匹配 “abbb”，”abbbb” 以及 “abbbbb”。

当 “n” 省略时，被默认为零。当 “m” 省略时，被默认为无限大。当 “,m” 省略时，就表示重复正好 “n” 次。例如:

模式 匹配次数 

\{,4} 0，1，2，3 或 4

\{3,} 3，4，5，等等

\{0,1} 0 或 1，同 \=

\{0,} 0 或 更多，同 *

\{1,} 1 或 更多，同 \+

\{3} 3

5，多选一匹配

在一个查找模式中，”或” 运算符是 “\|”。例如:

/foo\|bar

这个命令匹配了 “foo” 或 “bar”。更多的抉择可以连在后面:

/one\|two\|three

匹配 “one”，”two” 或 “three”。

如要匹配其多次重复，那么整个抉择结构须置于 “\(” 和 “\)” 之间:

/\+

这个命令匹配 “foo”，”foobar”，”foofoo”，”barfoobar”，等等。

再举个例子:

/end

这个命令匹配 “endif”，”endwhile” 和 “endfor”。

------------------------------------------------


在vim下可以使用常用的箭头键
但是 还有其它键可以让你更快的达到目标

hjkl 这是代替箭头键功能的
H M L 跳到屏幕的顶上 中间 下方

w 跳到下一个单词的开始
e 跳到单词的结束
b 向后跳

gg 跳到文件的开始
G 跳到文件的结束
10gg 或10G 跳到第10行


ta 跳到下一个a 前面
fa 跳到下一个a
大写的意思相反

 

另外还有%(跳到文件的%多少) 和|(跳到第几列) 不过我很少用


上面的都可以加上数字前缀 表示第几个匹配


另外看文件时 除了pageup pagedown外还有其它的快速键
如CTRL-F 向前一页 CTRL-B 向后一页

上面不是重要的
CTRL-D 向下半页 CTRL-U 向上半页我觉得更实用 这样看文章时就不会跳转出错
另外还有
CTRL-E 向下一行
CTRL-Y 向上一行


^ 行首
$行尾
0 第一个字符


另外上面也作为vim其它命令的定位符 如删除d

dt)
一直删除到这行的)

另外 懂了跳转键后 那删除或是复制时就不再是以行为单位了 可以指定到某个条件
我觉得这是新手成长的必要方法


另外还有ctrl-t ctrl-i ctrl-]

如果已经使用了ctags 或是cscope创建索引文件的话 那看代码时很是方便

本文来自CSDN博客，转载请标明出处：http://blog.csdn.net/unbutun/archive/2009/10/06/4635944.aspx

 

跳转到函数、变量定义处：
[+ctrl+i 跳转到函数、变量和#define
[+ctrl+d 跳转到#define处
ctrl+i 向前跳到前几次光标位置
ctrl+o 向后跳到后几次光标位置

函数体跳转：
[[
]]
[]
][
{}

2009-07-07 17:31 补充

如何选中括号中的内容 进行：
将光标移至括号内，按shift+v进入行选模式，然后

i｛ － 选小括号中内容，不包括小括号
a｛ － 选小括号中内容，包括小括号
ib － 选中括号中内容，不包括括号
ab － 选中括号中内容，包括括号
i｛ － 选大括号中内容，不包括大括号
a｛ － 选大括号中内容，包括大括号

:h text-objects

下面还有些相关的tips，未全部验证：
vi{ 选中{}中间的内容,不包括{}
va{ 选中{}中间内容，包括{}
vi( 选中()中间内容
vi< 选中<>中间内容
vi[ 选中[]中间内容
vit 选中中间的内容
vi” 选中”"中间内容
vi’ 选中”中间的内容
vis 选中一个句子
vib 选中一个block
viw选中一个单词
vip 选中一个段落