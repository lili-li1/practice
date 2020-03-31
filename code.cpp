//李
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include <conio.h>
#include <time.h>
__int8 world[102][202] = {0};
IMAGE imgLive, imgEmpty;		// 定义活细胞和无细胞区域的图案  //创建两个图像对象。

MOUSEMSG m;              //定义鼠标消息结构体的变量，并定义指向它的指针
MOUSEMSG *_m = &m;

char s1[20] = "速度：1", s2[20] = " ";    //速度值字符串s1,s2
int Speed = 125;			// 游戏速度（毫秒）