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

//王
void start();   //世界初始化
void kongjian(int x1, int x2, char *s);   //控件函数
void zuotu(MOUSEMSG *_m);   //作图
void shengsi();  //生死判断
void shuru();   //输入函数
void shuchu();    //输出函数
void dy_world();   //打印世界
void shubiao();   //鼠标监控与操作
void RandWorld();  //随机设置世界
void huitushebei();    //建立绘图设备
void jianpanjiankong();   //键盘监控

int main()
{
	

	initgraph(1800, 900);  //创建一个尺寸为 1800x900 的绘图环境，原点坐标（0，0），位于左上角
	start();   //世界初始化
	huitushebei();     //建立绘图设备
	while (true)
	{
		jianpanjiankong();  //键盘监控
		shubiao();		//鼠标监控与操作
		dy_world();			// 绘制世界
		shengsi();			// 生死判断
		Sleep(Speed);
	}
	return 0;
}