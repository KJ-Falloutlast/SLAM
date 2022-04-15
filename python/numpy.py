'1.numpy来读取数据'

     NumPy提供了多种存取数组内容的文件操作函数。保存数组数据的文件可以是二进制格式或者文本格式。二进制格式的文件又分为NumPy专用的格式化二进制类型和无格式类型。
 

numpy格式的文件可以保存为后缀为（.npy/.npz）格式的文件

1. tofile()和fromfile()

    tofile()将数组中的数据以二进制格式写进文件
    tofile()输出的数据不保存数组形状和元素类型等信息
    fromfile()函数读回数据时需要用户指定元素类型，并对数组的形状进行适当的修改

    import numpy as np
     
    # 随机生成12个数字并将其有一维转换成3*4的矩阵形式
    a = np.arange(12)
    print("一维数组:",a)
    a.shape = 3,4
    print("3*4的矩阵:",a)
     
    # 将数组中的数据以二进制格式写入到文件
    a.tofile('a.bin')
    # fromfile在读取numpy文件时需要自己指定数据格式,并且原格式并为保存
    b1 = np.fromfile('a.bin', dtype=np.float) # 按照float读取数据
    b2 = np.fromfile('a.bin', dtype=np.int) # 按照int读取数据
    b3 = np.fromfile('a.bin', dtype=np.int32) # 按照int32读取数据
    print('float格式b1:{},\nint格式b2:{},\nint32格式b3:{}'.format(b1,b2,b3))
     
    b3.shape = 3,4
    print('b3:',b3)

!!!reshape(-1,x)/reshape(x,-1)的含义

大意是说，数组新的shape属性应该要与原来的配套，如果等于-1的话，那么Numpy会根据剩下的维度计算出数组的另外一个shape属性值。
 举几个例子或许就清楚了，有一个数组z，它的shape属性是(4, 4)z = np.array([[1, 2, 3, 4],
          [5, 6, 7, 8],
          [9, 10, 11, 12],
          [13, 14, 15, 16]])
z.shape(4, 4)，z.reshape(-1)，z.reshape(-1)
array([ 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16])z.reshape(-1, 1)也就是说，先前我们不知道z的shape属性是多少，但是想让z变成只有一列，行数不知道多少，通过`z.reshape(-1,1)`，Numpy自动计算出有12行，新的数组shape属性为(16, 1)，与原来的(4, 4)配套。z.reshape(-1,1)
 array([[ 1],
        [ 2],
        [ 3],
        [ 4],
        [ 5],
        [ 6],
        [ 7],
        [ 8],
        [ 9],
        [10],
        [11],
        [12],
        [13],
        [14],
        [15],
        [16]])
 z.reshape(-1, 2)newshape等于-1，列数
 

2. save() 和 load(),savez()

    NumPy专用的二进制格式保存数据，它们会自动处理元素类型和形状等信息
    如果想将多个数组保存到一个文件中，可以使用savez()
    savez()的第一个参数是文件名，其后的参数都是需要保存的数组，也可以使用关键字参数为数组起名
    非关键字参数传递的数组会自动起名为arr_0、arr_1、...。
    savez()输出的是一个扩展名为npz的压缩文件，其中每个文件都是一个save()保存的npy文件，文件名和数组名相同
    load()自动识别npz文件，并且返回一个类似于字典的对象，可以通过数组名作为键获取数组的内容

    import numpy as np
     
    a = np.arange(12)
    a.shape = 3,4
    # 将数据存储为npy/npz
    np.save('a.npy', a)
    np.save('a.npz', a)
    c = np.load('a.npy')
    print('save-load：',c)
     
    # 存储多个数组
    b1 = np.array([[6, 66, 666],[888, 88,8]])
    b2 = np.arange(0, 1.0, 0.1)
    c2 = np.sin(b2)
    np.savez('result.npz', b1,b2,sin_arry = c)
    c3 = np.load('result.npz') # npz文件时一个压缩文件
    print(c3)
    print("数组b1:{}\n数组b2：{}\n数组sin_arry:{}".format(c3['arr_0'],c3['arr_1'],c3['sin_arry']))

 

 

3. savetxt() 和 loadtxt()

    读写1维和2维数组的文本文件
    可以用它们读写CSV格式的文本文件

2.转置

1.transpose：转置

Numpy 文档 numpy.transpose 中做了些解释，transpose 作用是改变序列，下面是一些文档Examples：

代码1：

x = np.arange(4).reshape((2,2))

#x 为：
array([[0, 1],
       [2, 3]])


代码2：

import numpy as np
x.transpose()


输出2：

array([[0, 2],
       [1, 3]])



对于二维 ndarray，transpose在不指定参数是默认是矩阵转置。如果指定参数，有如下相应结果：
代码3：

x.transpose((0,1))



输出3：

# x 没有变化
array([[0, 1],
       [2, 3]])


代码4：

x.transpose((1,0))



输出4：

# x 转置了
array([[0, 2],
       [1, 3]])


这个很好理解：
对于x，因为：

代码5：

x[0][0] == 0
x[0][1] == 1
x[1][0] == 2
x[1][1] == 3



我们不妨设第一个方括号“[]”为 0轴 ，第二个方括号为 1轴 ，则x可在 0-1坐标系 下表示如下：
这里写图片描述

代码6：

因为 x.transpose((0,1)) 表示按照原坐标轴改变序列，也就是保持不变
而 x.transpose((1,0)) 表示交换 ‘0轴’ 和 ‘1轴’，所以就得到如下图所示结果：



注意，任何时候你都要保持清醒，告诉自己第一个方括号“[]”为 0轴 ，第二个方括号为 1轴
此时，transpose转换关系就清晰了。

我们来看一个三维的：
代码7：

import numpy as np

# A是array([ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15])
A = np.arange(16)

# 将A变换为三维矩阵
A = A.reshape(2,2,4)
print(A)




输出7：

A = array([[[ 0,  1,  2,  3],
            [ 4,  5,  6,  7]],
            
           [[ 8,  9, 10, 11],
            [12, 13, 14, 15]]])



我们对上述的A表示成如下三维坐标的形式：



所以对于如下的变换都很好理解啦：
代码8：

A.transpose((0,1,2))  #保持A不变
A.transpose((1,0,2))  #将 0轴 和 1轴 交换


将 0轴 和 1轴 交换：


此时，输出

代码9：

A.transpose((1,0,2)) [0][1][2]  
