# 1.latex基础框架
```tex
%导言区
\documentclass{report}%book, report, letter
\title{My First Document}
\author{Nan Geng}
\date{\today}
%导言区主要是一些全局的设置，正文区只能有一个


%正文区(文稿区),正文区有且仅能有1个letex环境
\begin{document}
  \maketitle  %表示能够有题目，作者等标题信息
  Hello world!  
  %空行表示换行
  Let $f(x)$ be defined by the formula 
  $$f(x) = 3x^2 + x - 1$$ which is a polynomial of degree 2.
  
\end{document}
```