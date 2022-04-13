1.标题使用
    # 一级标题
    ## 二级标题
    ### 三级标题
    #### 四级标题
    ##### 五级标题
    ###### 六级标题
2.段落：直接用enter键即可
3.字体：
*斜体文本*
_斜体文本_
**粗体文本**
__粗体文本__
***粗斜体文本***
***dfsdfsf***
___粗斜体文本___
4.分割线：
***

* * *

*****

- - -

----------

5.删除线
~~dfsfs~~

6.下划线：
<u>wengben<u>

7.角注：
[^A]

[^A]: 菜鸟教程 -- 学的不仅是技术，更是梦想！！！

8.列表：
8-1.无序列表(通过- 和 tab键来实现分级;shift+ tab退回上一级别)
* 第一项
* 第二项
* 第三项

+ 第一项
+ 第二项
+ 第三项



- 第一项
- 第二项
- 第三项
8-2.有序列表：
1. 第一项
2. 第二项

8-3.列表嵌套：
列表嵌套只需在子列表中的选项前面添加*/-/,然后再添加一个空格键就行：
1. 第一项：
    - 第一项嵌套的第一个元素
    - 第一项嵌套的第二个元素
2. 第二项：
    - 第二项嵌套的第一个元素
    - 第二项嵌套的第二个元素
    - fdsf
    - 斯蒂芬
- sdfsd
- 的风俗
- -dfs
- dfs
* dsfs 
* sdf 

8.区块：
8-1.每行开头接上一个>符号就行
8-2.嵌套
> 区块引用
> 菜鸟教程
> 学的不仅是技术更是梦想
> > 
8-3.实例：
* 区块中使用列表：
>区块中使用列表：
> 1. 第一项
> 2. 第二项
> + 第二项
> - 第三项
> * 第四项
* 列表中使用区块
* 第一项
* >菜鸟教程
* 第二项

9. 代码
* 格式：`sfsdf`
* 代码区块：
* * 方法一：TAB键插入代码区块
  int main(){
      if  (i > 0){
          cout << dfsfdsf << endl;
      }
- 注意事项：
  - 缩进式插入前方必须有空行；
  - 缩进 4 个空格或是 1 个制表符；
  - 一个代码区块会一直持续到没有缩进的那一行（或是文件结尾）。(但是此方法不能高亮语言)

    python
    
* * 方法二：用
```language
markdown
```
可以利用缩进来插入到子集中
* 
  ```python
  print("fdsf")I love markdown and I love c++ 
  ```

1.  链接
    1. 方法1：
        <链接名称>
    2. 方法2：
        [链接名称]<链接地址>
    3. 例子：
    * [菜鸟教程](https://www:runoob.com)
    * <https://www:runoob.com>
    1. 高级链接
    这个链接用 1 作为网址变量 [Google][1]
    这个链接用 runoob 作为网址变量 [Runoob][runoob]
    然后在文档的结尾为变量赋值（网址）

      [1]: http://www.google.com/
      [runoob]: http://www.runoob.com/
2.  图片
    1. 格式：![alt 属性文本](图片地址)
    * 格式2：![alt 文本](pictures/115226979_5_20171103055710761.jpg, "四元数字")
    1. 例子：
    * ![runboo 图标](pictures/7df1d8089fe8d556ec39389a48d66cbb.png,"图片")
    * 这个链接用 1 作为网址变量 [RUNOOB][1].
然后在文档的结尾为变量赋值（网址）
    * [1]: http://static.runoob.com/images/runoob-logo.png

12. 表格
    * 使用|来分隔不同的单元格，使用-来分隔表头和其他行

|  表头   | 表头  |
|  ----  | ----  |
| 单元格  | 单元格 |
| 单元格  | 单元格 |
* 对齐方式：
* -: 设置内容和标题栏居右对齐。
:- 设置内容和标题栏居左对齐。
:-: 设置内容和标题栏居中对齐。
*

13. 高级技巧
    * 支持HTML元素
      * 目前支持的 HTML 元素有：<kbd> <b> <i> <em> <sup> <sub> <br>等 
    - 转义
      - **文本加粗**
      - \*\* 正常显示星号\*\*
      - 
      \ 反斜线
      `   反引号
      *   星号
      _   下划线
      {}  花括号
      []  方括号
      ()  小括号
      #   井字号
      +   加号
      -   减号
      .   英文句点
      !   感叹号
    - 公式
      - 方法1：$...$**中间不要留空格**
      - 方法2：$$....$$**这个用来写数学表达式的块**
      - 例如：$f(x) = sin(x)$

13. markdown所支持的语言格式
    >actionscript3
    apache
      applescript
      asp
      brainfuck
      c
      cfm
      clojure
      cmake
      coffee-script, coffeescript, coffee
      cpp - C++
      cs
      csharp
      css
      csv
      bash
      diff
      elixir
      erb - HTML + Embedded Ruby
      go
      haml
      http
      java
      javascript
      json
      jsx
      less
      lolcode
      make - Makefile
      markdown
      matlab
      nginx
      objectivec
      pascal
      PHP
      Perl
      python
      profile - python profiler output
      rust
      salt, saltstate - Salt
      shell, sh, zsh, bash - Shell scripting
      sql
      scss
      sql
      svg
      swift
      rb, jruby, ruby - Ruby
      smalltalk
      vim, viml - Vim Script
      volt
      vhdl
      vue
      xml - XML and also used for HTML with inline CSS and Javascript
      yaml
    
14. 数学公式的输入：
    * 希腊字母
      * 显示	命令	显示	命令
      α	\alpha	β	\beta
      γ	\gamma	δ	\delta
      ε	\epsilon	ζ	\zeta
      η	\eta	θ	\theta
      ι	\iota	κ	\kappa
      λ	\lambda	μ	\mu
      ν	\nu	ξ	\xi
      π	\pi	ρ	\rho
      σ	\sigma	τ	\tau
      υ	\upsilon	φ	\phi
      χ	\chi	ψ	\psi
      ω	\omega	 	 
    * 位置描述
      * $\sum_{i=0}^N\int_{a}^{b}g(t,i)\text{d}t$
      * $$\sum_{i=0}N\int_{a}{b}g(t,i)\text{d}t$$
      * 上面$$...$$为单独显示的居中放大显示
      * **以下所有的公式和字母都要加入$...$
    * 字母修饰
      * 3-1. 上下标：
        * 上标：^
        * 下标：_
        * 例如：$C_n^2$
      * 3-2. 矢量：$\vec a$
      * 3-3. 字体：
        * $mathtt{A}$
        * $mathbb{A}$
      * 3-4. 分组
        * 使用{}将相同等级的内容扩入其中，成组处理
        * 举例：$10^{10}$,$10^10$
      * 3-5. 括号：
        * 小括号：$()$
        * 中括号：$[]$
        * 尖括号：$\langle,\rangle$ ** left angle**
        * $\left$和 $\right$使符大小与邻近的公式相适应
          * $(\frac{x}{y})$
          * $\left(\frac{x}{y}\right)$