
1.太阳系的项目
认识 OpenGL 和 GLUT

OpenGL 包含了很多渲染函数，但是他们的设计目的是独立于任何窗口系统或操作系统的。因此，它自身并没有包含创建打开窗口或者从键盘或鼠标读取时间的函数，甚至连最基本的显示窗口的功能都没有，所以单纯只使用 OpenGL 是完全不可能创建一个完整的图形程序的。并且绝大多数程序都需要与用户进行交互（响应键盘鼠标等操作）。GLUT 则提供了这一便利。

GLUT 其实是 OpenGL Utility Toolkit 的缩写，它是一个处理 OpenGL 程序的工具库，主要负责处理与底层操作系统的调用及 I/O 操作。使用 GLUT 可以屏蔽掉底层操作系统 GUI 实现上的一些细节，仅使用 GLUT 的 API 即可跨平台的创建应用程序窗口、处理鼠标键盘事件等等。

我们先在实验楼环境中安装 GLUT：

sudo apt-get update && sudo apt-get install freeglut3 freeglut3-dev
[copy]

一个标准的 GLUT 程序结构如下代码所示：


// 使用 GLUT 的基本头文件
#include <GL/glut.h>

// 创建图形窗口的基本宏
#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 700
#define HEIGHT 700

// 用于注册 GLUT 的回调
void onDisplay(void);
void onUpdate(void);
void onKeyboard(unsigned char key, int x, int y);

int main(int argc, char*  argv[]) {

    // 对 GLUT 进行初始化，并处理所有的命令行参数
    glutInit(&argc, argv);
    // 这个函数指定了使用 RGBA 模式还是颜色索引模式。另外还可以
    // 指定是使用单缓冲还是双缓冲窗口。这里我们使用 RGBA 和 双缓冲窗口
    glutInitDisplayMode(GLUT_RGBA |  GLUT_DOUBLE);
    // 设置窗口被创建时左上角位于屏幕上的位置
    glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);
    // 设置窗口被创建时的宽高, 为了简便起见
    glutInitWindowSize(WIDTH, HEIGHT);
    // 创建一个窗口，输入的字符串为窗口的标题
    glutCreateWindow("SolarSystem at Shiyanlou");

    // glutDisplayFunc 的函数原型为 glutDisplayFunc(void (*func)(void))
    // 这是一个回调函数，每当 GLUT 确定一个窗口的内容需要更新显示的时候,
    // glutDisplayFunc 注册的回调函数就会被执行.
    //
    // glutIdleFunc(void (*func)(void)) 将指定一个函数，用于处理当事件循环
    // 处于空闲的时候，就执行这个函数。这个回调函数接受一个函数指针作为它的唯一参数
    //
    // glutKeyboardFunc(void (*func)(unsigned char key, int x, int y))
    // 会将键盘上的键与一个函数关联，当这个键被按下或者释放时，函数就会调用
    //
    // 因此下面的三行实际上是在向 GLUT 注册关键的三个回调函数
    glutDisplayFunc(onDisplay);
    glutIdleFunc(onUpdate);
    glutKeyboardFunc(onKeyboard);

    glutMainLoop();
    return 0;

}

在 /home/shiyanlou/ 目录下新建 main.cpp 文件，并向其中写入如下代码：

//
//  main.cpp
//  solarsystem
//
#include <GL/glut.h>
#include "solarsystem.hpp"

#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 700
#define HEIGHT 700

SolarSystem solarsystem;

void onDisplay(void) {
    solarsystem.onDisplay();
}
void onUpdate(void) {
    solarsystem.onUpdate();
}
void onKeyboard(unsigned char key, int x, int y) {
    solarsystem.onKeyboard(key, x, y);
}

int main(int argc, char*  argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA |  GLUT_DOUBLE);
    glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);
    glutCreateWindow("SolarSystem at Shiyanlou");
    glutDisplayFunc(onDisplay);
    glutIdleFunc(onUpdate);
    glutKeyboardFunc(onKeyboard);
    glutMainLoop();
    return 0;
}

提示

    单缓冲，是将所有的绘图指令在窗口上执行，就是直接在窗口上绘图，这样的绘图效率是比较慢的，如果使用单缓冲，而电脑处理性能不够，屏幕会出现闪烁状。
    双缓冲，会将绘图指令是在一个缓冲区完成，这里的绘图非常的快，在绘图指令完成之后，再通过交换指令把完成的图形立即显示在屏幕上，进而避免出现绘图的不完整，效率很高。

双缓冲则主要分为前台缓冲和后台缓冲，前台缓冲即我们说看到的屏幕，后台缓冲则维护内存中，对用户不可见。使用双缓冲时所有绘图操作都会在后台进行，当完成绘制后，才会将结果复制到屏幕上。这么做的好处是，如果我们让绘制操作实时与显卡进行操作，当绘制任务复杂时，IO 操作同样会变得复杂，造成性能较低；而双缓冲只会在交换缓冲区时将绘制完成后的结果直接发送给显卡进行渲染，IO 显著降低。

