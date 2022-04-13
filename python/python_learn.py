'python基础'
1.zip()
zip() 函数用于将可迭代的对象作为参数，将对象中对应的元素打包成一个个元组，然后返回由这些元组组成的对象，这样做的好处是节约了不少的内存。

我们可以使用 list() 转换来输出列表。

如果各个迭代器的元素个数不一致，则返回列表长度与最短的对象相同，利用 * 号操作符，可以将元组解压为列表。

    zip 方法在 Python 2 和 Python 3 中的不同：在 Python 2.x zip() 返回的是一个列表。

    如果需要了解 Python2 的应用，可以参考 Python zip()。

语法

zip 语法：

zip([iterable, ...])

参数说明：

    iterabl -- 一个或多个迭代器;

返回值

返回一个对象。
实例

以下实例展示了 zip 的使用方法：
实例(Python 3.0+)
>>> a = [1,2,3]
>>> b = [4,5,6]
>>> c = [4,5,6,7,8]
>>> zipped = zip(a,b)     # 返回一个对象
>>> zipped
<zip object at 0x103abc288>
>>> list(zipped)  # list() 转换为列表
[(1, 4), (2, 5), (3, 6)]
>>> list(zip(a,c))              # 元素个数与最短的列表一致
[(1, 4), (2, 5), (3, 6)]

>>> a1, a2 = zip(*zip(a,b))          # 与 zip 相反，zip(*) 可理解为解压，返回二维矩阵式
>>> list(a1)
[1, 2, 3]
>>> list(a2)
[4, 5, 6]
>>>

2.enumerate
enumerate() 函数用于将一个可遍历的数据对象(如列表、元组或字符串)组合为一个索引序列，同时列出数据和数据下标，一般用在 for 循环当中,返回一个函数，
所以要用list才能结果列出
#enumerate()是枚举的意思

语法

以下是 enumerate() 方法的语法:

enumerate(sequence, [start=0])

参数

    sequence -- 一个序列、迭代器或其他支持迭代对象。
    start -- 下标起始位置的值。

实例

以下展示了使用 enumerate() 方法的实例：
>>> seasons = ['Spring', 'Summer', 'Fall', 'Winter']
>>> list(enumerate(seasons))
[(0, 'Spring'), (1, 'Summer'), (2, 'Fall'), (3, 'Winter')]
>>> list(enumerate(seasons, start=1))       # 下标从 1 开始
[(1, 'Spring'), (2, 'Summer'), (3, 'Fall'), (4, 'Winter')]
普通的 for 循环
>>> i = 0
>>> seq = ['one', 'two', 'three']
>>> for element in seq:
...     print i, seq[i]
...     i += 1
...
0 one
1 two
2 three
for 循环使用 enumerate
>>> seq = ['one', 'two', 'three']
>>> for i, element in enumerate(seq):
...     print i, element
...
0 one
1 two
2 three


3.Python 推导式

Python 推导式是一种独特的数据处理方式，可以从一个数据序列构建另一个新的数据序列的结构体。

Python 支持各种数据结构的推导式：

    列表(list)推导式
    字典(dict)推导式
    集合(set)推导式
    元组(tuple)推导式

列表推导式

列表推导式格式为：

[表达式 for 变量 in 列表] 
[out_exp_res for out_exp in input_list]

或者 

[表达式 for 变量 in 列表 if 条件]
[out_exp_res for out_exp in input_list if condition]

    out_exp_res：列表生成元素表达式，可以是有返回值的函数。
    for out_exp in input_list：迭代 input_list 将 out_exp 传入到 out_exp_res 表达式中。
    if condition：条件语句，可以过滤列表中不符合条件的值。

过滤掉长度小于或等于3的字符串列表，并将剩下的转换成大写字母：
实例
>>> names = ['Bob','Tom','alice','Jerry','Wendy','Smith']
>>> new_names = [name.upper()for name in names if len(name)>3]
>>> print(new_names)
['ALICE', 'JERRY', 'WENDY', 'SMITH']

计算 30 以内可以被 3 整除的整数：
实例
>>> multiples = [i for i in range(30) if i % 3 == 0]
>>> print(multiples)
[0, 3, 6, 9, 12, 15, 18, 21, 24, 27]
字典推导式

字典推导基本格式：

{ key_expr: value_expr for value in collection }

或

{ key_expr: value_expr for value in collection if condition }

使用字符串及其长度创建字典：
实例
listdemo = ['Google','Runoob', 'Taobao']
# 将列表中各字符串值为键，各字符串的长度为值，组成键值对
>>> newdict = {key:len(key) for key in listdemo}
>>> newdict
{'Google': 6, 'Runoob': 6, 'Taobao': 6}

提供三个数字，以三个数字为键，三个数字的平方为值来创建字典：
实例
>>> dic = {x: x**2 for x in (2, 4, 6)}
>>> dic
{2: 4, 4: 16, 6: 36}
>>> type(dic)
<class 'dict'>
集合推导式

集合推导式基本格式：

{ expression for item in Sequence }
或
{ expression for item in Sequence if conditional }

计算数字 1,2,3 的平方数：
实例
>>> setnew = {i**2 for i in (1,2,3)}
>>> setnew
{1, 4, 9}

判断不是 abc 的字母并输出：
实例
>>> a = {x for x in 'abracadabra' if x not in 'abc'}
>>> a
{'d', 'r'}
>>> type(a)
<class 'set'>
元组推导式

元组推导式可以利用 range 区间、元组、列表、字典和集合等数据类型，快速生成一个满足指定需求的元组。

元组推导式基本格式：

(expression for item in Sequence )
或
(expression for item in Sequence if conditional )

元组推导式和列表推导式的用法也完全相同，只是元组推导式是用 () 圆括号将各部分括起来，而列表推导式用的是中括号 []，另外元组推导式返回的结果是一个生成器对象。

例如，我们可以使用下面的代码生成一个包含数字 1~9 的元组：
实例
>>> a = (x for x in range(1,10))
>>> a
<generator object <genexpr> at 0x7faf6ee20a50>  # 返回的是生成器对象

>>> tuple(a)       # 使用 tuple() 函数，可以直接将生成器对象转换成元组
(1, 2, 3, 4, 5, 6, 7, 8, 9)



4.withopen

.withopen基础

    file = open("test.txt","r")#'r'指的是以只读的方式打开
    for line in file.readlines():
        print line
    file.close()

这样直接打开文件，如果出现异常，如读取过程中文件不存在或异常，则直接出现错误，close方法无法执行，文件无法关闭

    with open("test.txt","r") as file:
    for line in file.readlines():
        print line

用with语句的好处，就是到达语句末尾时，会自动关闭文件，即便出现异常。

with语句实际上是一个非常通用的结构，允许你使用所谓的上下文管理器。上下文管理器是支持两个方法的对象：__enter__和__exit__。

方法__enter__不接受任何参数，在进入with语句时被调用，其返回值被赋给关键字as后面的变量。

方法__exit__接受三个参数：异常类型、异常对象和异常跟踪。它在离开方法时被调用（通过前述参数将引发的异常提供给它）。如果__exit__返回False，将抑制所有的异常。

文件也可用作上下文管理器。它们的方法__enter__返回文件对象本身，而方法__exit__关闭文件

    file= open("test.txt","r")
    try:
        for line in file.readlines():
            print line
    except:
        print "error"
    finally:
        file.close()

with语句作用效果相当于上面的try-except-finally


.readlines基础

readlines() 方法用于读取所有行(直到结束符 EOF)并返回列表，该列表可以由 Python 的 for... in ... 结构进行处理。

如果碰到结束符 EOF 则返回空字符串。

语法

readlines() 方法语法如下：

fileObject.readlines( );

参数

    无。

返回值

返回列表，包含所有的行。
实例

以下实例演示了 readlines() 方法的使用：

文件 runoob.txt 的内容如下：

1:www.runoob.com
2:www.runoob.com
3:www.runoob.com
4:www.runoob.com
5:www.runoob.com

循环读取文件的内容：
实例
#!/usr/bin/python
# -*- coding: UTF-8 -*-
 
# 打开文件
fo = open("runoob.txt", "r")
print "文件名为: ", fo.name
 
for line in fo.readlines():                          #依次读取每行  
    line = line.strip()                             #去掉每行头尾空白  
    print "读取的数据为: %s" % (line)
 
# 关闭文件
fo.close()

以上实例输出结果为：

文件名为:  runoob.txt
读取的数据为: 1:www.runoob.com
读取的数据为: 2:www.runoob.com
读取的数据为: 3:www.runoob.com
读取的数据为: 4:www.runoob.com
读取的数据为: 5:www.runoob.com

.读取的路径方法:绝对路径/相对路径:  ./xxx.txt
----------------------------------------------------
2.jupyter快捷键

Jupyter Notebook 有两种键盘输入模式。编辑模式，允许你往单元中键入代码或文本；这时的单元框线是绿色的。命令模式，键盘输入运行程序命令；这时的单元框线是灰色。
命令模式 (按键 Esc 开启)

    Enter : 转入编辑模式
    Shift-Enter : 运行本单元，选中下个单元
    Ctrl-Enter : 运行本单元
    Alt-Enter : 运行本单元，在其下插入新单元
    Y : 单元转入代码状态
    M :单元转入markdown状态
    R : 单元转入raw状态
    1 : 设定 1 级标题
    2 : 设定 2 级标题
    3 : 设定 3 级标题
    4 : 设定 4 级标题
    5 : 设定 5 级标题
    6 : 设定 6 级标题
    Up : 选中上方单元
    K : 选中上方单元
    Down : 选中下方单元
    J : 选中下方单元
    Shift-K : 扩大选中上方单元
    Shift-J : 扩大选中下方单元
    A : 在上方插入新单元
    B : 在下方插入新单元
    X : 剪切选中的单元
    C : 复制选中的单元
    Shift-V : 粘贴到上方单元
    V : 粘贴到下方单元
    Z : 恢复删除的最后一个单元
    D,D : 删除选中的单元
    Shift-M : 合并选中的单元
    Ctrl-S : 文件存盘
    S : 文件存盘
    L : 转换行号
    O : 转换输出
    Shift-O : 转换输出滚动
    Esc : 关闭页面
    Q : 关闭页面
    H : 显示快捷键帮助
    I,I : 中断Notebook内核
    0,0 : 重启Notebook内核
    Shift : 忽略
    Shift-Space : 向上滚动
    Space : 向下滚动

编辑模式 ( Enter 键启动)

    Tab : 代码补全或缩进
    Shift-Tab : 提示
    Ctrl-] : 缩进
    Ctrl-[ : 解除缩进
    Ctrl-A : 全选
    Ctrl-Z : 复原
    Ctrl-Shift-Z : 再做
    Ctrl-Y : 再做
    Ctrl-Home : 跳到单元开头
    Ctrl-Up : 跳到单元开头
    Ctrl-End : 跳到单元末尾
    Ctrl-Down : 跳到单元末尾
    Ctrl-Left : 跳到左边一个字首
    Ctrl-Right : 跳到右边一个字首
    Ctrl-Backspace : 删除前面一个字
    Ctrl-Delete : 删除后面一个字
    Esc : 进入命令模式
    Ctrl-M : 进入命令模式
    Shift-Enter : 运行本单元，选中下一单元
    Ctrl-Enter : 运行本单元
    Alt-Enter : 运行本单元，在下面插入一单元
    Ctrl-Shift-- : 分割单元
    Ctrl-Shift-Subtract : 分割单元
    Ctrl-S : 文件存盘
    Shift : 忽略
    Up : 光标上移或转入上一单元
    Down :光标下移或转入下一单元

