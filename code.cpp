//��һ����д�������ͷ�ļ�
#include<graphics.h>//��װ��EASY X���ܴ����ͷ�ļ���
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include <conio.h>
#include <time.h>
__int8 world[102][202] = {0};
IMAGE imgLive, imgEmpty;		// �����ϸ������ϸ�������ͼ��  //��������ͼ�����

MOUSEMSG m;              //���������Ϣ�ṹ��ı�����������ָ������ָ��
MOUSEMSG *_m = &m;

char s1[20] = "�ٶȣ�1", s2[20] = " ";    //�ٶ�ֵ�ַ���s1,s2
int Speed = 125;			// ��Ϸ�ٶȣ����룩

//��һ������Ҫ�õ������ɸ��������Լ� main �����ı�д
void start();   //�����ʼ��
void kongjian(int x1, int x2, char *s);   //�ؼ�����
void zuotu(MOUSEMSG *_m);   //��ͼ
void shengsi();  //�����ж�
void shuru();   //���뺯��
void shuchu();    //�������
void dy_world();   //��ӡ����
void shubiao();   //����������
void RandWorld();  //�����������
void huitushebei();    //������ͼ�豸
void jianpanjiankong();   //���̼��

int main()
{
	

	initgraph(1800, 900);  //����һ���ߴ�Ϊ 1800x900 �Ļ�ͼ������ԭ�����꣨0��0����λ�����Ͻ�
	start();   //�����ʼ��
	huitushebei();     //������ͼ�豸
	while (true)
	{
		jianpanjiankong();  //���̼��
		shubiao();		//����������
		dy_world();			// ��������
		shengsi();			// �����ж�
		Sleep(Speed);
	}
	return 0;
}

//���������� start() �� jianpanjiankong()�����ı�д
void start()
{
	memset(world, 0, 102 * 202 * sizeof(bool));   //��ʼ��world����
	setbkcolor(WHITE);// ���ñ���ɫΪ��ɫ
	cleardevice();// �ñ���ɫ�����Ļ
	setfillcolor(BLACK);   //���������ɫΪ��ɫ
	kongjian(0, 0, " ");
	setcolor(BROWN);    // ����������ɫΪ��ɫ
	outtextxy(900, 5, s1); //��ӡ�ٶ�ֵ
	setcolor(BLACK);    // ����������ɫΪ��ɫ
	outtextxy(400, 5, "Q/���  W/����  E/����  S/���"); //��ӡ����
}
void jianpanjiankong()   //���̼��
{
	if (_kbhit())   
	{
		char c = _getch();    //��ȡ����    //Speed����450ʱ���˴���ͣ

		if (c >='0' && c <= '9')
		{
			sprintf(s2, "%d", c - '0');      //���ٶ�ֵд���ַ�����s2��
			strcpy(s1, "�ٶȣ�");     //��ʼ��s1
			strcat(s1, s2);          //��s2���ӵ�s1��
			setcolor(BROWN);    // ����������ɫΪ��ɫ
			outtextxy(900, 5, s1); //��ӡ�ٶ�ֵ
			if (c == '0')
				Speed = 900;
			else
				Speed = ('9' - c) * 25;  //�����������ֵ����ٶ�
		}
		switch (c)
		{
		case 'q':
			start();  //�����ʼ��
			break;
		case 'w':
			shuchu();     //�������
			break;
		case 'e':
			shuru();     //�������
			break;

		case 's':
			RandWorld();   // ����һ��ϸ������ֲ�������
			dy_world();			// ��������
			break;

		case ' ':
			c = '/';
			setcolor(LIGHTRED);    // ����������ɫΪ����ɫ
			outtextxy(1400, 5, "��ͣ"); //��ӡ����
			while (c != ' ')
			{
				shubiao();  //����������
				Sleep(500);
				if (_kbhit())
				{
					c = _getch();
					dy_world();			// ��������	
					shengsi();			// �����ж�	
				}
			}
			setfillcolor(WHITE);        //���õ�ǰ�����ɫΪ��ɫ
			solidrectangle(1400, 5, 1450, 20);    //��ӡ��ɫ����,���ǡ���ͣ������
			setfillcolor(BLACK);        //���õ�ǰ�����ɫΪ��ɫ
			break;
		}
	}
}
//����������� huitushebei() ��shubiao()��zuotu(MOUSEMSG *_m)�����ı�д
void huitushebei()     //������ͼ�豸
{
	// ��������ͼ���Ĵ�С
	Resize(&imgLive, 9, 9);    //
	Resize(&imgEmpty, 9, 9);   //���ڵ���ָ����ͼ�豸�ĳߴ硣

	// ���������������ͼ��
	SetWorkingImage(&imgLive);   //�����趨��ǰ�Ļ�ͼ�豸��
	setfillcolor(BLACK);        //���õ�ǰ�����ɫΪ��ɫ
	setcolor(LIGHTGRAY);        //���ñ߿���ɫΪ��ɫ
	fillrectangle(0, 0, 8, 8);    //��ӡ��ɫ�����б߿�

	// ���������������ͼ��
	SetWorkingImage(&imgEmpty);
	setfillcolor(WHITE);        //���õ�ǰ�����ɫΪ��ɫ
	solidrectangle(0, 0, 8, 8);    //��ӡ��ɫ����

	// �ָ���Ĭ�ϴ��ڵĻ�ͼ
	SetWorkingImage(NULL);
}
void shubiao()    //����������
{
	

	int x1 = 0, x2 = 0;      //x1,x2�洢�����ؼ������ұߵ�X����λ��
	while (MouseHit())   //����Ƿ��������Ϣ
	{
		m = GetMouseMsg();       //��ȡ�����Ϣ
		if (m.mkLButton || m.mkRButton)   //������Ҽ��Ƿ��а���
		{

			if (m.y > 26)      //m.y>26˵�����λ����ͼ��������λ�ڿؼ���
			{
				do
				{
					if (m.y > 26)
						zuotu(_m);  //�������Ϣ���ݸ���ͼ����
					m = GetMouseMsg();       //��ȡ�����Ϣ
				} while (m.mkLButton || m.mkRButton);   //ֱ���ɿ������Ž�����ͼ
			}
			else      //�ж����λ���ĸ��ؼ�
			{
				if (2 < m.x&&m.x < 63)
				{
					x1 = 2; x2 = 63;      //��һ���ؼ���λ��
					char s[] = "���";
					kongjian(x1, x2, s);  //ʵ�ֿؼ�����
					x1 = 0; x2 = 0;

					start();

				}
				if (72 < m.x&&m.x < 133)
				{
					x1 = 72; x2 = 133;     //�ڶ����ؼ���λ��
					char s[] = "����";
					kongjian(x1, x2, s);  //ʵ�ֿؼ�����
					x1 = 0;  x2 = 0;

					shuchu();     //�������

				}
				if (142 < m.x&&m.x < 203)
				{
					x1 = 142; x2 = 203;     //�������ؼ���λ��
					char s[] = "����";
					kongjian(x1, x2, s);  //ʵ�ֿؼ�����
					x1 = 0;  x2 = 0;

					shuru();     //�������
				}
				if (212 < m.x&&m.x < 273)
				{
					x1 = 212; x2 = 273;     //�������ؼ���λ��
					char s[] = "���";
					kongjian(x1, x2, s);  //ʵ�ֿؼ�����
					x1 = 0;  x2 = 0;

					RandWorld();   // ����һ��ϸ������ֲ�������
					dy_world();			// ��������

				}
				if (282 < m.x&&m.x < 343)
				{
					x1 = 142; x2 = 203;     //�������ؼ���λ��
					char s[] = "����";
					kongjian(x1, x2, s);  //ʵ�ֿؼ�����
					x1 = 0;  x2 = 0;

					exit(0);     //��������
				}

			};
		}
	}
	FlushMouseMsgBuffer();   //��������Ϣ������
}
void zuotu(MOUSEMSG *_m)   //��ͼ
{
	int x, y, xb, yb;

	xb = _m->x / 9+1;
	yb = (_m->y - 26) / 9+1;
	x = (xb - 1) * 9;
	y = (yb - 1) * 9 + 26;
	if (_m->mkLButton)
	{
		putimage(x, y, &imgLive);   //�����ʱ����ӡ�����б߿�
		world[yb][xb] = 1;
	}
	if (_m->mkRButton)
	{
		putimage(x, y, &imgEmpty);	//���Ҽ�ʱ��ɾ������
		world[yb][xb] = 0;
	}

}
//���� ���kongjian(int x1, int x2, char *s)��shengsi()�����ı�д
void kongjian(int x1, int x2, char *s)     //�ؼ�����
{
	if (x1 == 0 && x2 == 0)  //��x1,x2==0,���ʼ���ؼ�
	{
		setcolor(BLACK);// ����������ɫΪ��ɫ
		setfillcolor(WHITE);   //���������ɫΪ��ɫ

		fillrectangle(2, 2, 63, 23);  //����ɫ������
		outtextxy(15, 5, "���"); //��ӡ����

		fillrectangle(72, 2, 133, 23);  //����ɫ������
		outtextxy(85, 5, "����"); //��ӡ����

		fillrectangle(142, 2, 203, 23);  //����ɫ������
		outtextxy(155, 5, "����"); //��ӡ����

		fillrectangle(212, 2, 273, 23);  //����ɫ������
		outtextxy(225, 5, "���"); //��ӡ����

		fillrectangle(282, 2, 343, 23);  //����ɫ������
		outtextxy(295, 5, "����"); //��ӡ����

		setfillcolor(BLACK);   //���������ɫΪ��ɫ
	}
	if (x1 != 0 && x2 != 0)    //�ؼ�����Ч��
	{
		MOUSEMSG m;    //���������Ϣ�ṹ��ı���

		setcolor(BLACK);// ����������ɫΪ��ɫ

		setfillcolor(LIGHTGRAY);   //���������ɫΪǳ��ɫ
		fillrectangle(x1, 2, x2, 23);  //��ǳ��ɫ������

		setbkcolor(LIGHTGRAY);// ���ñ���ɫΪǳ��ɫ
		outtextxy(x1 + 15, 5, s); //��ӡ���֣����ʼ����������ƶ�2���أ�ʵ�ֶ���Ч��
		setbkcolor(WHITE);// ���ñ���ɫΪ��ɫ

		do  { m = GetMouseMsg(); } while (m.mkLButton || m.mkRButton);

		setfillcolor(WHITE);   //���������ɫΪ��ɫ
		fillrectangle(x1, 2, x2, 23);  //����ɫ������
		outtextxy(x1 + 15 - 2, 5, s); //��ӡ���֣����س�ʼ��λ��

		setfillcolor(BLACK);   //���������ɫΪ��ɫ
	}
}
void shengsi()  //�����ж�
{
	__int8 tmp[102][202] = { 0 };		// ��ʱ����
	int i, j;
	int sum=0;
	for (i = 1; i < 101;i++)
	for (j = 1; j < 201; j++)
	{
		// ������Χ���ŵ���������
		sum = world[i + 1][j] + world[i + 1][j - 1] + world[i][j - 1] + world[i- 1][j - 1]
			+ world[i - 1][j] + world[i - 1][j + 1] + world[i][j + 1] + world[i + 1][j + 1];

		// ���㵱ǰλ�õ�����״̬
		switch (sum)
		{
		case 3:		tmp[i][j] = 1;				break;
		case 2:		tmp[i][j] = world[i][j];	break;
		default:	tmp[i][j] = 0;				break;
		}
	}
	memcpy(world, tmp, 102 * 202 * sizeof(bool));  //��tmp�и���102 * 102 * sizeof(__int8)���ȵ����ݸ�world

	
}
//��������� ��ӡ�����룬�������
void dy_world()   //��ӡ����
{
	int x, y;
	int i, j;
	for (i = 1; i <101; i++)
	{
		for (j = 1; j <201; j++)     //����ѭ�����ݷ���״̬�洢��������
		{
			x = (j - 1) * 9;
			y = (i - 1) * 9+26;
			putimage(x, y, world[i][j] ? &imgLive : &imgEmpty);   //������ָ��λ�ã���ǰ�豸�ϻ���ָ��ͼ��
		}
	}
}

void RandWorld()   // ����һ��ϸ������ֲ�������
{
	
	srand((unsigned)time(NULL));  // �����������

	for (int i = 1; i < 101; i++)
	for (int j = 1; j <= 201; j++)
		world[i][j] = rand() % 2;
}
void shuru()   //���뺯��
{
	FILE *fp;
	if ((fp = fopen("data", "r")) == NULL)        //���ļ�
	{
		setcolor(LIGHTRED);    // ����������ɫΪ����ɫ
		outtextxy(1600, 5, "����"); //��ӡ����
		exit(0);
	}

	int i, j;
	char ch;
	for (i = 1; i <101; i++)   //����ѭ����ֵ��tu[][]
	{
		for (j =1; j<201; j++)
		{
			ch=fgetc(fp);
			switch (ch)
			{
			case 48: world[i][j]=0; break;       //���÷���״̬
			case 49: world[i][j] = 1; break;    //���÷���״̬
			}

		}
	}
	dy_world();  //��������
	setcolor(LIGHTRED);    // ����������ɫΪ����ɫ
	outtextxy(1600, 5, "���سɹ���"); //��ӡ����


}
void shuchu()    //�������
{
	FILE *fp;   //�����ļ�ָ��
	if ((fp = fopen("data", "w")) == NULL)       //���ļ���ʹfpָ���ļ�
	{
		setcolor(LIGHTRED);    // ����������ɫΪ����ɫ
		outtextxy(1600, 5, "����"); //��ӡ����
		exit(0);
	}

	char ch;
	int i, j;
	for (i = 1; i<101; i++)          //������ѭ�����ļ�����������
	{
		for (j = 1; j <201; j++)
		{
			switch (world[i][j])
			{
			case 0: ch = '0'; break;
			case 1: ch = '1'; break;
			}
			fputc(ch, fp);
		}
	}
	fclose(fp);      //�ر�

	setcolor(LIGHTRED);    // ����������ɫΪ����ɫ
	outtextxy(1600, 5, "����ɹ���"); //��ӡ����
}