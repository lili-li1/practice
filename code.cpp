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

//李
void start()
{
	memset(world, 0, 102 * 202 * sizeof(bool));   //初始化world数组
	setbkcolor(WHITE);// 设置背景色为白色
	cleardevice();// 用背景色清空屏幕
	setfillcolor(BLACK);   //设置填充颜色为黑色
	kongjian(0, 0, " ");
	setcolor(BROWN);    // 设置字体颜色为棕色
	outtextxy(900, 5, s1); //打印速度值
	setcolor(BLACK);    // 设置字体颜色为黑色
	outtextxy(400, 5, "Q/清空  W/保存  E/加载  S/随机"); //打印文字
}
void jianpanjiankong()   //键盘监控
{
	if (_kbhit())   
	{
		char c = _getch();    //读取键盘    //Speed等于450时，此处暂停

		if (c >='0' && c <= '9')
		{
			sprintf(s2, "%d", c - '0');      //将速度值写入字符数组s2中
			strcpy(s1, "速度：");     //初始化s1
			strcat(s1, s2);          //将s2连接到s1后
			setcolor(BROWN);    // 设置字体颜色为棕色
			outtextxy(900, 5, s1); //打印速度值
			if (c == '0')
				Speed = 900;
			else
				Speed = ('9' - c) * 25;  //根据输入数字调整速度
		}
		switch (c)
		{
		case 'q':
			start();  //世界初始化
			break;
		case 'w':
			shuchu();     //输出操作
			break;
		case 'e':
			shuru();     //输入操作
			break;

		case 's':
			RandWorld();   // 创建一个细胞随机分布的世界
			dy_world();			// 绘制世界
			break;

		case ' ':
			c = '/';
			setcolor(LIGHTRED);    // 设置字体颜色为亮红色
			outtextxy(1400, 5, "暂停"); //打印文字
			while (c != ' ')
			{
				shubiao();  //鼠标监控与操作
				Sleep(500);
				if (_kbhit())
				{
					c = _getch();
					dy_world();			// 绘制世界	
					shengsi();			// 生死判断	
				}
			}
			setfillcolor(WHITE);        //设置当前填充颜色为白色
			solidrectangle(1400, 5, 1450, 20);    //打印白色方格,覆盖“暂停”文字
			setfillcolor(BLACK);        //设置当前填充颜色为黑色
			break;
		}
	}
}